#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
	char* palavra;
	int index;
	int nivel;
	No* next_brother;
	No* next_child;

}No;

No* NewNo(char* palavra, int index, int nivel) {

	int size = strlen(palavra);
	No* New = (No*)malloc(sizeof(No));
	New->next_brother = NULL;
	New->next_child = NULL;
	New->palavra = (char*)malloc((size + 1) * sizeof(char));
	strcpy(New->palavra, palavra);
	New->index = index;
	New->nivel = nivel;
	return New;
}


No* initialize(char* palavra, int index, int nivel) {
	return NewNo(palavra, index, nivel);
}

No* BuscaItem(int chavePai, No* root, int nivel) {
	if (root == NULL) return (NULL);
	if (root->index == chavePai && root->nivel == nivel) return root;
	No* p = root->next_child;
	while (p) {
		No* resp = BuscaItem(chavePai, p, nivel);
		if (resp) return resp;
		p = p->next_brother;

	}
	return (NULL);
}
No* BuscaItemEx(int chavePai, No* anterior, No* root, int nivel) {
	if (root == NULL) return (NULL);
	if (root->next_child->index == chavePai && root->nivel == nivel) return root;
	
	No* p = root->next_child;

	while (p) {
		
		No* resp = BuscaItemEx(chavePai, root, p, nivel);
		if (resp) return resp;
		p = p->next_brother;

	}
	return (NULL);
}

bool AddItemTree(char* palavra, int index, int chavePai, No* root, int nivel) {
	No* pai = BuscaItem(chavePai, root, nivel);
	if (!pai) return false;
	No* filho = NewNo(palavra, index, nivel);
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



void AddItemElement(char* palavra, int index, int chavePai, No* root, int nivel){
	if (root == NULL) {
		return;
	}
	No* element = NewNo(palavra, index, nivel);
	No* pai = BuscaItem(chavePai, root, nivel-1);
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


void imprimir(No* root) {
	if (root == NULL) return;
	printf("%d(_ ", root->index);
	printf("%s :", root->palavra);
	
	No* tmp = root->next_child;
	while (tmp) {
		imprimir(tmp);
		tmp = tmp->next_brother;
	}
	printf(")");
}

No* Editar(No* root, int chavePai,  char *nova_palavra, int nivel ) {
	int size = strlen(nova_palavra);
	char* s = (char*)malloc((size+1)* sizeof(char));
	No* p;
	p = BuscaItem(chavePai, root, nivel);
	free(p->palavra);
	p->palavra = s;
	strcpy(s,nova_palavra);
	return root;
}


bool Delete(No* anterior, No* root, int chavePai, int nivel, bool e_filho) {
	if (!root) return false;
	if (root->index == chavePai && root->nivel == nivel) {

		anterior->next_child = root->next_brother;
		free(root);
		return true;
	}
	else {
		if (root->next_child) {
			if (Delete(root, root->next_child, chavePai, nivel, true)) {
				return true;
			}
		}
		if (Delete(root, root->next_brother, chavePai, nivel, false)) {
			return true;
		}
	}
	return false;
}

//No* Delete(No* anterior, No* root, int chavePai, int nivel) {
//	No* p = root;
//	No* p1;
//	No* p2;
//	p = BuscaItem(chavePai, root, nivel);
//	p1 = BuscaItem(chavePai, root, nivel-1);
//
//	if (p->next_child == NULL && p->next_brother == NULL) {
//		p1->next_child = NULL;
//		p1->next_brother = NULL;
//		free(p->palavra);
//		free(p);
//	}
//	if (p->next_brother != NULL) {
//		p1->next_child = p->next_brother;
//		while (p->next_child != NULL) {
//			p = p->next_child;
//			while (p->next_brother != NULL) {
//				p = p->next_brother;
//			}
//		}
//		
//		free(p->palavra);
//		free(p);
//	}
//	else{
//		while (p->next_child != NULL) {
//			p = p->next_child;
//			while (p->next_brother != NULL) {
//				p = p->next_brother;
//			}
//		}
//		p1->next_child = NULL;
//		p1->next_brother = NULL;
//		free(p->palavra);
//		free(p);
//	} 
//	return root;
//}

int menu() {


	int op = 1;
	printf("Pokemon\n");
	printf("[1] - Add Personagens: \n");
	printf("[2] - Editar: \n");
	printf("[3] - Excluir: \n");
	printf("[4] - listar: \n");
	printf("Escolha: ");
	scanf_s("%d", &op);
	return op;
}


int main() {

	char inicio[] = "Inicio";
	int x = 10;
	No* lista = initialize(inicio, 0, 0);
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
				AddItemTree(nome, index, 0, lista, 0);
				imprimir(lista);
				printf("\nQual treinador deseja add o elemento? [index treinador]:");
				scanf("%d", &index_element);
				printf("Elemento:");
				scanf("%s", element);
				AddItemElement(element, index, index_element, lista, 1);
				imprimir(lista);
				printf("\nQual elemento voce deseja adicionar o pokemon? [index element]:");
				scanf("%d", &indexpoke);
				printf("Pokemon: ");
				scanf("%s", pokemon);
				AddItemElement(pokemon, index, indexpoke, lista, 2);
				++index;
			}
			break;
		case 2:
			char nome1[50];
			int index1;
			system("CLS");
			imprimir(lista);
			int op1;
			printf("Pokemon\n");
			printf("[0] - Editar Treinador \n");
			printf("[1] - Editar Elemento: \n");
			printf("[2] - Editar Pokemon: \n");
			printf("Escolha: ");
			scanf_s("%d", &op1);
			printf("\nDigite o Index:");
			scanf("%d", &index1);
			printf("Digite o novo nome:");
			scanf("%s", nome1);
			lista = Editar(lista, index1, nome1, op1);
			break;

		case 3:
			system("CLS");
			imprimir(lista);
			int op2, index2;
			printf("Pokemon\n");
			printf("[0] - Excluir Treinador \n");
			printf("[1] - Excluir Elemento: \n");
			printf("[2] - Excluir Pokemon: \n");
			printf("Escolha: ");
			scanf_s("%d", &op2);
			printf("\nDigite o Index:");
			scanf("%d", &index2);
		
			Delete(lista, lista, index2 ,op2);
			break;

		case 4:
			system("CLS");
			imprimir(lista);
			break;
		}


	} while (x != 0);
	printf("Fim");

	return 0;
}