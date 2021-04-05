#include <stdlib.h>

#include "table.h"
#include "table_p.h"

INFO header_helper_type(HEADER h, int fields, char *col_name) {
	INFO r = {0, 0, 0};

	int i;
	for (i = 0; i < fields && strcmp(h->field_name, col_name); i++)
		;
	if (i == fields)
		perror(
		    "Could not find the specified header. Expect"
		    "undefined behaviour.");
	else
		r = h[i];

	return r;
}
