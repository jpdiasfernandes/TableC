#ifndef _TABLE_
#define _TABLE_
#include <stdio.h>
#include <glib-2.0/glib.h>

#define TYPE_INT     0
#define TYPE_DOUBLE  1
#define TYPE_FLOAT   2
#define TYPE_STRING  3
#define TYPE_CHAR    4
#define TYPE_DEFAULT 5
#define TYPE_LONG    6

typedef struct info INFO;
typedef struct cell CELL;
typedef CELL *ROW;
typedef INFO *HEADER;
typedef struct table TABLE;


TABLE *table_new_generic(int fields, int index, int *types, char **headers);
void table_destroy(TABLE *table);

#endif //_TABLE_
