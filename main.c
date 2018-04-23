/*
 ============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct lista{
	short codigo;
	short repetidas;
	struct lista *prox;
}LISTA;

typedef struct jogador{
	short numero;
	char nome[50];
	char telefone[15];
	struct lista *inicioLista;
	struct jogador *prox;
}JOGADOR;
#pragma pack(pop)

int menu(){
		short op=0;
		printf("MENU");
		printf("1 - Insercao Novo Componente");


		do{
			printf("Opcao: ");
		}while (op < 1 || op > 1);
	return 1;
}

int main(void) {
	menu;


	return EXIT_SUCCESS;
}
