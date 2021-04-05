#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "table.h"

ROW table_search_row_id(TABLE *t, void *key);
TABLE *table_search_row(TABLE *t, char *header, void *cont);

#endif //_SEARCH_H_
