#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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



void AddItemElement(char* palavra, int index, int chavePai, No* root){
	if (root == NULL) {
		return;
	}
	No* pai = BuscaItem(chavePai, root);
	No* element = NewNo(palavra, index);
	No* p = pai;
	if (p->next_child != NULL) {
			p = p->next_child;
			while (p->next_brother != NULL) {
				p = p->next_brother;
			}
			p->next_brother = element;
	}else{
	pai->next_child = element;
	}
}
void AddItemPokemon(char* palavra, int index, int chavePai, No* root) {
	if (root == NULL) {
		return;
	}
	No* pai = BuscaItem(chavePai, root);
	No* pokemon = NewNo(palavra, index);
	No* p = pai;
	if (p->next_child != NULL) {
	
		while (p->next_brother != NULL) {
			p = p->next_brother;
		}
		p->next_brother = pokemon;
	}
	else {
		pai->next_child = pokemon;
	}
}

void imprimir(No* root) {
	if (root == NULL) return;
	printf("%d( ", root->index);
	printf("%s ", root->palavra);

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
	printf("[2] - Add Buscar: \n");
	printf("Escolha: ");
	scanf_s("%d", &op);
	return op;
}

int main() {

	char inicio[] = "Inicio";
	int x = 10;
	No* lista = initialize(inicio, 0);
	int index = 1;
	do {
		int x = menu();


		switch (x) {

		case 1:
			
			int count;
			int index_element;
			int indexpoke;
			printf("Quantos treinadores?");
			scanf_s("%d", &count);
			for (int i = 0; i < count; i++) {
				char nome[50];
				char element[30];
				char pokemon[10];
				printf("Digite o nome do treinador:\n");
				printf("Nome: ");
				scanf("%s", nome);
				AddItemTree(nome, index, 0, lista);
				imprimir(lista);
				printf("\nQual treinador deseja add o elemento? [index treinador]:");
				scanf("%d", &index_element);
				printf("Elemento:");
				scanf("%s", element);
				AddItemElement(element, index, index_element, lista);
				printf("Qual elemento voce deseja adicionar o pokemon? [index element]:");
				scanf("%d", &indexpoke);
				printf("Pokemon: ");
				scanf("%s", pokemon);
				AddItemPokemon(pokemon, index, 1, lista);
				++index;
			}

		case 2:
			system("CLS");
			imprimir(lista);
	
		}

	} while (x != 0);
	printf("Fim");

	return 0;
}