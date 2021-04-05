#ifndef __TABLE_P_H_
#define __TABLE_P_H_
#include "table.h"
#include <glib-2.0/glib.h>

/**
 * INFO:
 * @type: type of the content
 * @size: size of the content
 * @header_no: number of the collumn
 * @field_name: name of the collumn
 */
struct info {
	int type;
	int size;
	int header_no;
	const char *field_name;
};
/**
 * CELL:
 * @cont: pointer to the alloc'ed content
 * @row_ptr: pointer to the row of the cell
 */
struct cell {
	void *cont;
	ROW row_ptr;
};

/**
 * TABLE:
 * @fields: Number of columns
 * @header: Information of each collumn
 * @gtree: Balanced binary tree to store the content
 */
struct table {
	int fields;
	int index;
	HEADER header;
	GTree *gtree;
};

CELL cell_copy(CELL c);
ROW row_copy(int fields, ROW row, HEADER header);
INFO header_helper_type(HEADER h, int fields, char *col_name);
GTree *header_helper_indexed(TABLE *t, char *header);
int fmt_generic_type(int count, int *fields, const char *fmt);
int header_generic_insert(HEADER h, int type, char *header, int col);
void * void_ptr_generic_insert(void *cont, int type, void *arg);
int cell_generic_insert(CELL *c, int type, void *arg);
static gint row_cmp(gconstpointer row1, gconstpointer row2);
TABLE *table_new_generic(int fields, int index, int *types, char **headers);
int table_append_generic(TABLE *t, void **args);
int table_append_row(TABLE *t, ROW row);
ROW table_search_row_id(TABLE *t, void *key);
TABLE *table_search_row(TABLE *t, char *header, void *cont);
int table_insert_internal(TABLE *t, gpointer key, gpointer value);
TABLE *table_new_header(int fields, int index, HEADER header);
int table_insert_internal(TABLE *t, gpointer key, gpointer value);
int table_append_row(TABLE *t, ROW row);
#endif //__TABLE_P_H_
