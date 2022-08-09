#ifndef _GENERIC_H_
#define _GENERIC_H_

#include "table.h"

int header_generic_insert(HEADER h, int type, char *header, int col);
gint key_generic_cmp(gconstpointer key1, gconstpointer key2, gpointer data);

#endif //_GENERIC_H_
