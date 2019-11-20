#include <stdio.h>

typedef struct no {
	char* dado;
	no *proximo;
}no;


int main() {
	no mau;
	mau.dado['a'];

	printf(mau.dado);

	return 0;
}