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
 * @type: cell type (ie. float, int, string...)
 * @size: size of cell
 * @cont: pointer to the alloc'ed content
 * @row_ptr: pointer to the row of the cell
 */
struct cell {
	int type;
	int size;
	void *cont;
	ROW row_ptr;
};

/**
 * TABLE:
 * @fields: number of columns
 * @index: the column number of the index column
 * @header: information of each collumn
 * @gtree: balanced binary trees to store the content
 */
struct table {
	int fields;
	int index;
	HEADER header;
	GTree **gtree;
};

#endif //__TABLE_P_H_
