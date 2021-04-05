#include "table.h"
#include "table_p.h"
#include <stdlib.h>
#include <stdio.h>

int alloc_cell_cont(CELL *c, size_t size) {
	c->cont = malloc(size);
	if (c == NULL) {
		perror("Could not allocate cell.");
		return -1;
	}
	return 0;
}

void free_cell(CELL *c) {
	// Need to check this on valgrind
	// Possible memory leaks in here
	free(c);
}

ROW alloc_row(int fields) {
	ROW r = malloc(sizeof(struct cell) * fields);
	if (r == NULL) perror("Could not allocate row.");
	return r;
}

void free_row(ROW row, int fields) {
	for (int i = 0; i < fields; i++) {
		free_cell(&row[i]);
	}
}

INFO *alloc_header(int fields) {
	INFO *r = malloc(sizeof(struct info) * fields);
	if (r == NULL) perror("Could not allocate header");
	return r;
}

void free_header(HEADER h) { free(h); }

TABLE *alloc_table(int fields) {
	TABLE *t = malloc(sizeof(struct table));
	if (t == NULL) {
		perror("Table allocation failed.");
		return NULL;
	}
	t->header = alloc_header(fields);
	return t;
}

// Only to be used after destroying the hash implementation
void free_table(TABLE *t) {
	free_header(t->header);
	free(t);
}
