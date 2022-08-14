#include "../includes/table.h"
#include "../includes/table_p.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * alloc_header:
 * @fields: number of fields the table has
 *
 * Allocates the header
 *
 * Returns: the header data structure
*/
INFO *alloc_header(int fields) {
	INFO *r = malloc(sizeof(struct info) * fields);
	if (r == NULL) perror("Could not allocate header");
	return r;
}

/**
 * free_header:
 * @header: the header to be freed
 *
 * Frees the header (for organization purposes since this is not as efficient as calling free directly)
 *
 */
void free_header(INFO *header) {
	free(header);
}

/**
 * alloc_table:
 * @fields: number of fields the table has
 *
 * Allocates the space for all the structures that are
 * needed to host the table data structure.
 *
 * Returns: the table data structure
*/
TABLE *alloc_table(int fields) {
	TABLE *t = malloc(sizeof(struct table));
	if (t == NULL) {
		perror("Table allocation failed.");
		return NULL;
	}
	t->gtree = calloc(fields, sizeof(GTree *));
	if (t->gtree == NULL) {
		perror("Tree array allocation failed.");
		return NULL;
	}
	t->header = alloc_header(fields);
	return t;
}

/**
 * free_table:
 * @table: the  table to be freed
 *
 * Frees the table (for organization purposes since this not as efficient as calling free directly)
 *
 * It is supposed to be called only after deallocing every content of every tree.
 *
 */
void free_table(TABLE *table) {
	//frees gtrees array
	free(table->gtree);
	//frees header
	free_header(table->header);
	//frees the table
	free(table);
}
