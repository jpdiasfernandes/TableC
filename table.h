#ifndef _TABLE_
#define _TABLE_
#include <stdio.h>

#define COL_TYPE_INT     0 
#define COL_TYPE_DOUBLE  1 
#define COL_TYPE_FLOAT   2
#define COL_TYPE_STRING  3
#define COL_TYPE_CHAR    4
#define COL_TYPE_DEFAULT 5

typedef struct info INFO;
typedef struct cell CELL;
typedef CELL *ROW;
typedef INFO *HEADER;
typedef struct table TABLE;

TABLE *table_new(int fields, int index, const char *fmt, ...);
int table_append(TABLE *t, ...);
char *table_to_file(FILE *fp, TABLE *t);
TABLE *table_search_row(TABLE *t, char *header, void *cont);

#endif //_TABLE_
