#include "table.h"
#include <glib-2.0/glib.h>
#include <glib-2.0/gmodule.h>
#include <glib-2.0/glib/ghash.h>
#include <stdio.h>
#include "table.h"

int main() {
	int a = 2;
	int b = 999;
	int c = 101;
	TABLE *t1 = table_new(3,0, "sss", "Users_id", "Pais", "Nome");
	table_append(t1, "x3kjdfjfe", "Brasil", "Henriquinho");
	table_append(t1, "x3kjdfjfe", "Portugal", "Henriquinho");
	table_append(t1, "dkfjkfjkfd", "Portugal", "Marco");
	table_append(t1, "ex3kjdfjfe", "Brasil", "Henriquinho");
	table_append(t1, "edkfjkfjkfd", "Portugal", "Marco");
	table_append(t1, "dfx3kjdfjfe", "Brasil", "Henriquinho");
	table_append(t1, "dfdkfjkfjkfd", "Portugal", "Marco");
	table_append(t1, "dfx3kjdfjfe", "Brasil", "Henriquinho");
	table_append(t1, "dfdkfjkfjkfd", "Portugal", "Marco");
	table_append(t1, "dfex3kjdfjfe", "Brasil", "Henriquinho");
	table_append(t1, "dfedkfjkfjkfd", "Portugal", "Marco");
	table_append(t1, "dfx3kjdfjfe", "Brasil", "Henriquinho");
	table_append(t1, "dfdkfjkfjkfd", "Portugal", "Marco");
	table_append(t1, "dfedkfjkfjkfd", "Portugal", "Marco");   	
	table_append(t1, "edkfjkfjkfd", "Portugal", "Marco");   	
	table_to_file(stdout, t1);
	table_search_row(t1, "Users_id", "x3kjdfjfe");
	
	return 0;
}


