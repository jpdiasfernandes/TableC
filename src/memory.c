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
	t->header = alloc_header(fields);
	return t;
}

