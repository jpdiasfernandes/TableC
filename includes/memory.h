#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "table.h"
#include "table_p.h"

/* Func prototypes */
INFO *alloc_header(int fields);
void free_header(INFO *header);
TABLE *alloc_table(int fields);
void free_table(TABLE *table);

#endif 	//_MEMORY_H_
