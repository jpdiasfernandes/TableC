#ifndef _GENERIC_H_
#define _GENERIC_H_

#include "table.h"

int fmt_generic_type(int count, int *fields, const char *fmt);
int header_generic_insert(HEADER h, int type, char *header, int col);
void *void_ptr_generic_insert(void *cont, int type, void *arg);
int cell_generic_insert(CELL *c, int type, void *arg);

#endif //_GENERIC_H_
