#include "../includes/table.h"
#include "../includes/table_p.h"
#include <stdlib.h>
#include <string.h>

/**
 * header_generic_insert:
 * @h: the info reference to be manipulated
 * @type: the type of data to be stored in the collumn
 * @header: the name of the collumn
 * @col: the number of the collumn
 *
 * Inserts the information needed in the header for the correct
 * info reference
 *
 * Returns: 0 if success -1 if not */
int header_generic_insert(INFO *h, int type, char *header, int col) {
	switch (type) {
		case TYPE_STRING:
			h->size = sizeof(char *);
			h->type = TYPE_STRING;
			break;
		case TYPE_INT:
			h->size = sizeof(int);
			h->type = TYPE_INT;
			break;
		case TYPE_CHAR:
			h->size = sizeof(char);
			h->type = TYPE_CHAR;
			break;
		case TYPE_FLOAT:
			h->size = sizeof(float);
			h->type = TYPE_FLOAT;
			break;
		case TYPE_DOUBLE:
			h->size = sizeof(double);
			h->type = TYPE_DOUBLE;
			break;
		case TYPE_LONG:
			h->size = sizeof(long int);
			h->type = TYPE_LONG;
			break;
		default:
			return -1;
	}
	h->field_name = strdup(header);
	h->header_no = col;
	return 0;
}

/**
 * key_generic_cmp:
 * @key1: key number 1 to be compared
 * @key2: key number 2 to be compared
 * @data: additinal data to use in the function (Not needed in our case)
 *
 * Used in glib tree function to return the result of comparing two keys of a balanced tree
 *
 * Returns: The difference between the keys
*/
gint key_generic_cmp(gconstpointer key1, gconstpointer key2, gpointer data) {
	CELL *cell1 = (CELL *)key1;
	CELL *cell2 = (CELL *)key2;
	int type1 = cell1->type;
	int type2 = cell2->type;

	int r = 0;


	if (type1 != type2) return r;

	void *cont1 = cell1->cont;
	void *cont2 = cell2->cont;

	switch(type1) {
		case TYPE_STRING:
			r = strcmp((char *)cont1,(char *)cont2);
			break;
		case TYPE_INT:
			r = *(int *)cont1 - *(int *)cont2;
			break;
		case TYPE_CHAR:
			r = *(char *)cont1 - *(char *)cont2;
			break;
		case TYPE_FLOAT:
			r = *(float *)cont1 - *(float *)cont2;
			break;
		case TYPE_DOUBLE:
			r = *(double *)cont1 - *(double *)cont2;
			break;
		case TYPE_LONG:
			r = *(long int*)cont1 - *(long int*)cont2;
		default:
			break;
	}
	return (gint)r;
}

/**
 * @fmt_generic_type:
 * @count: amount of types to read
 * @fields: pointer to save the resulting fields
 * @fmt: the string containing the foormat keywords to be parsed
 *
 * Parses the fmt string and stores the result of the type parsing in fields
 * pointer
 *
 * Returns: amount of types parsed
*/
int fmt_generic_type(int count, int *fields, const char *fmt) {
	//argument preparation for strtok_r
	char *str = strdup(fmt);
	char *init_ptr = str;
	char **saveptr = &str;
	char *token;

	//counter variable
	int i = 0;

	while ((token = strtok_r(str, " ", saveptr)) && i < count) {
		int type;

		if (strncmp(token, "s", 1) == 0)
			type = TYPE_STRING;
		else if (strncmp(token, "d", 1) == 0)
			type = TYPE_INT;
		else if (strncmp(token, "c", 1) == 0)
			type = TYPE_CHAR;
		else if (strncmp(token, "f", 1) == 0)
			type = TYPE_FLOAT;
		else if (strncmp(token, "lf", 1) == 0)
			type = TYPE_DOUBLE;
		else if (strncmp(token, "ld", 1) == 0)
			type = TYPE_LONG;
		else type = TYPE_DEFAULT;

		fields[i++] = type;
	}

	free(init_ptr);
	return i;
}
