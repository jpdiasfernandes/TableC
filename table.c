/* The reason I'm creating this data abstraction is because GRelation (glib
 * API was deprecated and limited to only two atributes).
 * This got me thinking and decided to apply a dataset (glib API) instead. The
 * problem? You can't add indexing to it and you couldn't sort the elements by
 * collumn. And we needed it for a school assignment. So I came up with the
 * boring job to create a copy of the famous SQL Table and add the ability to
 * perform indexing to make it somewhat more efficient.
 */
#include "table.h"

#include <glib-2.0/glib.h>
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */
#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc */
#include <string.h>

#include "table_p.h" /* private declarations */

/**
 * @title: Table
 * @short_description: data strucure for data storing and querying.
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
 *
 * Still to add: destroy function
 */

/* Copy */
ROW row_copy(int fields, ROW row, HEADER header) {
	int i;
	ROW r = alloc_row(fields);
	for (i = 0; i < fields; i++)
		cell_generic_insert(&r[i], header[i].type, row[i].cont);
	return r;
}
/* End of copy */

/**
 * row_cmp:
 * @row1: Row to be compared
 * @row2: Row to be compared
 *
 * Compares to rows
 *
 * Returns: Result of the comparison
 */
static gint row_cmp(gconstpointer row1, gconstpointer row2) {
	return strcmp((char *)row1, (char *)row2);
}

/**
 * table_new_generic:
 * @fields: number of fields of the desired table
 * @types: Array of types
 * @headers: Array of strings for the headers name
 *
 * Creates a new TABLE and prepares all the resources needed for it management
 *
 * Returns: A pointer to the table
 */
TABLE *table_new_generic(int fields, int index, int *types, char **headers) {
	TABLE *t = alloc_table(fields);
	t->fields = fields;
	t->index = index;
	t->gtree = g_tree_new(row_cmp);
	if (t->gtree) {
		int i = 0;
		while (i < fields) {
			header_generic_insert(&t->header[i], types[i],
					      headers[i], i);
			i++;
		}
	}
	return t;
}
/**
 * table_new:
 * @fields: number of fields to be inserted
 * @fmt: The desired format of the column
 * 	Example: The format "s s" would mean the first and second column are of
 * 	type string.
 * @...: The name of the headers.
 *
 * Parses the arguments and calls table_new_generic
 *
 * Returns: The pointer to the new table
 */
TABLE *table_new(int fields, int index, const char *fmt, ...) {
	TABLE *t;
	va_list ap;
	va_start(ap, fmt);
	int i = 0;
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
 * table_append_generic:
 * @t: Pointer to the table
 * @args: Array of pointers to content
 *
 * Allocs the arguments received to the cell and assigns the cells to a row.
 * 	Inserts the row to the binary tree.
 *
 * Returns: The exit status
 */
int table_append_generic(TABLE *t, void **args) {
	if (t == NULL) {
		perror("TABLE was not correctly initiated");
		return -1;
	}
	int i;
	ROW r = alloc_row(t->fields);

	for (i = 0; i < t->fields; i++) {
		// Can't forget to free in delete function
		alloc_cell_cont(&r[i], t->header[i].size);
		cell_generic_insert(&r[i], t->header->type, args[i]);
		r[i].row_ptr = r;
	}

	return table_insert_internal(t, *(char **)r[t->index].cont, r);
}
/**
 * table_append:
 * @t: Pointer to the table
 *
 * Parses the arguments and calls table_append_generic().
 *
 * Returns: The exit status
 */
int table_append(TABLE *t, ...) {
	if (t == NULL) {
		perror("TABLE was not correctly initiated");
		return -1;
	}
	// Creates an instance of type va_list object type
	va_list ap;
	va_start(ap, t);
	void *args[t->fields];

	for (int i = 0; i < t->fields; i++) {
		int type = t->header->type;
		switch (t->header->type) {
			case COL_TYPE_STRING:
				args[i] = (void *)va_arg(ap, char *);
				break;
			case COL_TYPE_INT:
				args[i] = (void *)va_arg(ap, int *);
				break;
			case COL_TYPE_CHAR:
				args[i] = (void *)va_arg(ap, char *);
				break;
			case COL_TYPE_FLOAT:
				args[i] = (void *)va_arg(ap, float *);
				break;
			case COL_TYPE_DOUBLE:
				args[i] = (void *)va_arg(ap, double *);
				break;
			default:
				break;
		}
	}

	va_end(ap);
	table_append_generic(t, args);

	// TODO: create error defines
	return 0;
}
TABLE *table_new_header(int fields, int index, HEADER header) {
	int types[fields];
	char *headers[fields];
	int i;

	for (i = 0; i < fields; i++) {
		types[i] = header[i].type;
		headers[i] = strdup(header->field_name);
	}

	TABLE *r = table_new_generic(fields, index, types, headers);

	for (i = 0; i < fields; i++) free(headers[i]);

	return r;
}
int table_insert_internal(TABLE *t, gpointer key, gpointer value) {
	g_tree_replace(t->gtree, key, value);
	return 0;
}
int table_append_row(TABLE *t, ROW row) {
	ROW r = row_copy(t->fields, row, t->header);
	table_insert_internal(t, *(char **)r[t->index].cont, r);
	return 0;
}

/* String and File functions */
/* Needs cleaning and critical thinking */
GString *string_line(GString *g, int width) {
	int i;
	g_string_append_c(g, '+');
	for (i = 0; i < width; i++) g_string_append_c(g, '-');
	g_string_append(g, "+\n");
	return g;
}
int header_to_string(TABLE *t, GString *g) {
	int i;
	int width = 0;
	for (i = 0; i < t->fields; i++)
		width += strlen(t->header[i].field_name);
	// Padding
	width += (t->fields) * 2;
	string_line(g, width);
	for (i = 0; i < t->fields; i++)
		g_string_append_printf(g, "|%s |", t->header[i].field_name);
	g_string_append_c(g, '\n');
	string_line(g, width);
	return width;
}
GString *row_to_string(TABLE *t, ROW r, GString *g, int width) {
	int col_len = (width / t->fields) - 4;
	string_line(g, width);
	for (int i = 0; i < t->fields; i++) {
		g_string_append_printf(g, "| %.*s |", col_len,
				       (char *)r[i].cont);
	}
	g_string_append_c(g, '\n');
	string_line(g, width);
	return g;
}

static gint print_row(gpointer key, gpointer value, gpointer data) {
	int *args = (int *)data;
	ROW row = (ROW)value;
	int col_len = (args[0] / args[1]) - 2;
	printf("| %s |", *(char **)row[0].cont);
	printf("| %s |", *(char **)row[1].cont);
	printf("| %s |", *(char **)row[2].cont);
	putchar('\n');
	return FALSE;
}
char *table_to_file(FILE *fp, TABLE *t) {
	char buf[4096];
	int i;
	gpointer key, value;
	GString *g = g_string_new("");
	int width = header_to_string(t, g);
	int args[2] = {width, t->fields};
	printf("%s", g->str);
	g_tree_foreach(t->gtree, print_row, &args);
	return NULL;
}
