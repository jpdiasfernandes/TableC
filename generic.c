#include "table.h"
#include "table_p.h"
#include <stdlib.h>

int fmt_generic_type(int count, int *fields, const char *fmt) {
	int i = 0;
	while (i < count) {
		switch (*fmt++) {
			case 's':
				fields[i++] = COL_TYPE_STRING;
				break;
			case 'd':
				fields[i++] = COL_TYPE_INT;
				break;
			case 'c':
				fields[i++] = COL_TYPE_CHAR;
				break;
			case 'f':
				fields[i++] = COL_TYPE_FLOAT;
				break;
			case 'b':
				fields[i++] = COL_TYPE_DOUBLE;
				break;
		}
	}
	return i;
}
int header_generic_insert(HEADER h, int type, char *header, int col) {
	switch (type) {
		case COL_TYPE_STRING:
			h->size = sizeof(char *);
			h->type = COL_TYPE_STRING;
			break;
		case COL_TYPE_INT:
			h->size = sizeof(int);
			h->type = COL_TYPE_INT;
			break;
		case COL_TYPE_CHAR:
			h->size = sizeof(char);
			h->type = COL_TYPE_CHAR;
			break;
		case COL_TYPE_FLOAT:
			h->size = sizeof(float);
			h->type = COL_TYPE_FLOAT;
			break;
		case COL_TYPE_DOUBLE:
			h->size = sizeof(double);
			h->type = COL_TYPE_DOUBLE;
			break;
		default:
			break;
	}
	h->field_name = strdup(header);
	h->header_no = col;
	return 0;
}

/**
 * void_ptr_generic_insert:
 * @cont: Pointer to the alloc'ed pointer where the content will be inserted
 * @type: Data type of the content to be inserted
 * @arg: Pointer to the content to be inserted
 *
 * Inserts arg pointer content in cont pointer content
 *
 * Returns: the new pointer of the content.
 */
void *void_ptr_generic_insert(void *cont, int type, void *arg) {
	char *tmp;
	switch (type) {
		case COL_TYPE_STRING:
			tmp = (char *)strdup((char *)arg);
			*(char **)cont = (char *)tmp;
			break;
		case COL_TYPE_INT:
			*(int *)cont = *(int *)arg;
			break;
		case COL_TYPE_CHAR:
			*(char *)cont = *(char *)arg;
			break;
		case COL_TYPE_FLOAT:
			*(float *)cont = *(float *)arg;
			break;
		case COL_TYPE_DOUBLE:
			*(double *)cont = *(double *)arg;
			break;
		default:
			break;
	}
	return cont;
}
int cell_generic_insert(CELL *c, int type, void *arg) {
	void_ptr_generic_insert(c->cont, type, arg);
	return 0;
}
