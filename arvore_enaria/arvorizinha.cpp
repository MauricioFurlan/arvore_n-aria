#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct No {
	char* palavra;
	int index;
	No* next_brother;
	No* next_child;
}No;

No* NewNo(char* palavra, int index) {

	int size = strlen(palavra);
	No* New = (No*)malloc(sizeof(No));
	New->next_brother = NULL;
	New->next_child = NULL;
	New->palavra = (char*)malloc((size + 1) * sizeof(char));
	strcpy(New->palavra, palavra);
	New->index = index;
	return New;
}


No* initialize(char* palavra, int index) {
	return NewNo(palavra, index);
}

No* BuscaItem(int chavePai, No* root) {
	if (root == NULL) return (NULL);
	if (root->index == chavePai) return root;
	No* p = root->next_child;
	while (p) {
		No* resp = BuscaItem(chavePai, p);
		if (resp) return resp;
		p = p->next_brother;

	}
	return (NULL);
}

bool AddItemTree(char* palavra, int index, int chavePai, No* root) {
	No* pai = BuscaItem(chavePai, root);
	if (!pai) return false;
	No* filho = NewNo(palavra, index);

	No* p = pai->next_child;
	if (!p) pai->next_child = filho;
	else {
		while (p->next_brother) {
			p = p->next_brother;
		}
		p->next_brother = filho;
	}
	return true;
}

//void AddItemTreiner(char* palavra, int index, int chavePai, No* root){
//	if (root == NULL) {
//		return;
//	}
//	if (root->next_child == NULL){
//		No* 
//	}
//
//
//}

void imprimir(No* root) {
	if (root == NULL) return;
	printf("%d(", root->index);
	printf("%s", root->palavra);

	No* tmp = root->next_child;
	while (tmp) {
		imprimir(tmp);
		tmp = tmp->next_brother;
	}
	printf(")");
}

//No* Delete(int num, No* root) {
//	if (root == NULL) return (NULL);
//	if (root->palavra == num) return root;
//	No* p = root->next_child;
//	while (p) {
//		No* resp = BuscaItem(num, p);
//		if (resp) return resp;
//		p = p->next_brother;
//	}
//	return (NULL);
//}

int menu() {
	int op;
	printf("Pokemon\n");
	printf("[1] - Add Treinador: \n");
	printf("[2] - Add Elemento: \n");
	printf("Escolha: ");
	scanf_s("%d", &op);
	return op;
}

int main() {




	char inicio[] = "Inicio";
	int x = 10;
	No* lista = initialize(inicio, 0);
	do {
		int x = menu();


		switch (x) {

		case 1:
			int index;
			int count;
			printf("Quantos treinadores?");
			scanf_s("%d", &count);
			for (int i = 0; i < count; i++) {
				char nome[50];
				printf("Digite o Index do treinador\n");
				printf("Index: ");
				scanf_s("%d", &index);
				printf("Digite o Nome do treinador\n");
				printf("Nome: ");
				scanf("%s", nome);
				AddItemTree(nome, index, 0, lista);
			}


		case 2:
			system("CLS");
			imprimir(lista);
			printf("\nDigite o Index do treinador\n");
			printf("Index: ");
			scanf_s("%d", &index);
		}

		imprimir(lista);
		//printf("%s", arvore->palavra);
		//No* id = BuscaItem(40, arvore);
		//imprimir(arvore);
	} while (x != 0);


	return 0;
}