#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "table.h"
#include "table_p.h"

/* Func prototypes */
INFO *alloc_header(int fields);
TABLE *alloc_table(int fields);

#endif 	//_MEMORY_H_
