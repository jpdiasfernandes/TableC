#include "table_p.h"
#include "table.h"

ROW table_search_row_id(TABLE *t, void *key) {
	return g_tree_lookup(t->gtree, key);
}

TABLE *table_search_row(TABLE *t, char *header, void *cont) {
	INFO info = header_helper_type(t->header, t->fields, header);

	TABLE *r = table_new_header(t->fields, t->index, t->header);

	ROW row;
	// GTree *g = header_helper_indexed(t, header);
	if (t->index == info.header_no) row = table_search_row_id(t, cont);

	table_append_row(r, row);

	return r;
}
