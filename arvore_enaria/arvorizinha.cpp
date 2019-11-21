#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <corecrt_malloc.h>
#define true 1
#define false 0


typedef char DATA_NEW[20];

typedef struct no {
  DATA_NEW data;
  struct no* next_child;
  struct no* next_brother;
} no;


no* NewNo(DATA_NEW data) {
  no* new_no = (no*)malloc(sizeof(no));
  new_no->next_child = NULL;
  new_no->next_brother = NULL;
  new_no->data = data;
  return (new_no);
}

no* Initialize(DATA_NEW data) {
  return (NewNo(data));
}

no* AddItemTree(no* lista, char data) {
	no* tmp = (no*)malloc(sizeof(no));
	tmp = lista;
	no* child = NewNo(data);
	return tmp;
}

int main() {
  no* lista = Initialize('oi');

  printf("%s", lista->data);

	

  return 0;
}