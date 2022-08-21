/* The reason I'm creating this data abstraction is because GRelation (glib
 * API was deprecated and limited to only two attributes).
 * This got me thinking and decided to apply a dataset (glib API) instead. The
 * problem? You can't add indexing to it and you couldn't sort the elements by
 * column. And we needed it for a school assignment. So I came up with the
 * boring job to create a copy of the famous SQL Table and add the ability to
 * perform indexing to make it somewhat more efficient.
 */
#include "../includes/table.h"

#include <glib-2.0/glib.h>
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */
#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc */
#include <string.h>

/* Private declarations */
#include "../includes/generic.h"
#include "../includes/memory.h"


/**
 * @title: Table
 * @short_description: data structure for data storing and querying.
 * 	otimizations are also implemented
 *
 * This tables are supposed to emulate the typical database tables. You can
 * choose to index some collumns to make it more eficient for queries using that
 * atribute.
 *
 * You can create indexing but don't overuse it :) The more indexing the more
 * over-head for management. And thus efficiency is lost...
 *
 * To create a new table with a printf like arguments, use table_new().
 * If you want a more generic aproach tou can use table_new_generic(). This last
 * version is good if you want to automate.
 *
 * To append content use table_append(). For a more generic aproach use
 * table_new_generic(). (If you want to automate things :) ).
 *
 * To explain how it works, if you create a new table then you have to specify
 * an atribute as an index. The table created will only be optimized to the index
 * column. This way the average case for searching the index column will be
 * O(log n). For searchs using other non-indexed columns will be O(n).
 *
 * Don't forget to destroy the table after using it. Otherwise you'll
 * have a lot of information not freed.
 */

/**
 * table_new_generic:
 * @fields: number of fields of the desired table
 * @index: number of the collumn to be the primary index (-1 if there isn't)
 * @types: Array of types
 * @headers: Array of strings for the headers name
 *
 * Creates a new TABLE and prepares all the resources needed for its management
 *
 * Returns: A pointer to the table
 */
TABLE *table_new_generic(int fields, int index, int *types, char **headers) {
	//allocs a table with a number of fields + a default field for row number
	TABLE *t = alloc_table(fields + 1);

	if (t == NULL) {
		perror("Table allocation failed.");
		return NULL;
	}
	//user fields + row field
	t->fields = fields + 1;

	//if index is out of bounds the default index will be the row_no collumn
	if (index <= 0 || index > fields)
		index = 0;

	t->index = index;

	//insert the row_no collumn
	header_generic_insert(&(t->header[0]), TYPE_INT, "row_no",0);

	//insert user defined collumns
	for(int i = 1; i <= fields; i++)
		header_generic_insert(&(t->header[i]), types[i - 1], headers[i - 1], i);

	//creates the primary tree for the table
	t->gtree[0] = g_tree_new_full(key_generic_cmp, NULL, NULL, NULL);

	if (index > 0) {
		//creates an indexed tree for collumn "index"
		t->gtree[index] = g_tree_new_full(key_generic_cmp, NULL, NULL, NULL);
	}
	return t;
}


/**
 * table_new:
 * @fields: number of fields of the desired table
 * @index: number of the collumn to be the primary index (-1 if there isn't)
 * @fmt: the desired format of the various collumns
 *     Example: the format "s ld lf f" would mean that the 1st collumn is a string,
 *     2nd collumn is a long integer, 3rd collumn is a double and the 4th collumn
 *     is a float.
 * @...: the name of the collumns
 *
 * Creates a new TABLE and prepares all the resources needed for its management.
 * This is done by parsing the arguments and calling table_new_generic
 *
 * Returns: A pointer to the table
*/
TABLE *table_new(int fields, int index, const char *fmt, ...) {
	TABLE *t;
	va_list ap;
	va_start(ap, fmt);
	int i;
	int types[fields];
	char *headers[fields];

	for (i = 0; i < fields; i++) {
		headers[i] = va_arg(ap, char *);
		fmt_generic_type(fields, types, fmt);
	}
	va_end(ap);
	t = table_new_generic(fields, index, types, headers);

	return t;
}


/**
 * table_destroy:
 * @table: table to be destroyed
 *
 * Deallocs every alloced memory in the table and destroys every data structure used
 *
 */
void table_destroy(TABLE *table) {
	//deallocs all cells

	for (int i = 0; i < table->fields; i++) {
		if (table->gtree[i])
			g_tree_destroy(table->gtree[i]);
	}
	//frees table
	free_table(table);
}
