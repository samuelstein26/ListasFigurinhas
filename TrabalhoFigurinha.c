#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma pack(push, 1)
typedef struct lista {
	short codigo;
	short repetidas;
	struct lista *prox;
} LISTA;

typedef struct jogador {
	short codigo;
	char nome[50];
	char telefone[15];
	struct lista *inicioLista;
	struct jogador *prox;
} JOGADOR;

//struct para a funcao troca()

typedef struct nodo_carta {
	short numero;
	struct nodo_carta *prox;
} NODO_CARTA;

typedef struct nodo_jogador {
	short codigo;
	struct nodo_carta *repetidas;
	struct nodo_carta faltantes;
	struct nodo_jogador *prox;
} NODO_JOGADOR;

#pragma pack(pop)

struct jogador *listaJogador;

int menuPrincipal() {
	short op, op2 = 0;
	printf("\nMENU");
	printf("\n1 - Insercao:");
	printf("\n2 - Consulta:");
	printf("\n3 - Trocas:");
	printf("\n4 - Sair");
	do {
		printf("\nOpcao: ");
		scanf("%hd", &op);
		fflush(stdin);
	} while (op < 1 || op > 4);
	switch (op) {
	case 1: {
		printf("\n1 - Novo Integrante");
		printf("\n2 - Figurinhas de um Integrante");
		printf("\n3 - Pacote de figurinhas(5) para um Integrante");
		printf("\n4 - Importacao de documento");
		do {
			printf("\nOpcao: ");
			scanf("%hd", &op2);
			fflush(stdin);
		} while (op2 < 1 || op2 > 4);
	}
		break;
	case 2: {
		printf("\n1 - Informacoes de um Integrante");
		printf("\n2 - Informacoes de todos os Integrantes");
		printf("\n3 - Exportar documento");
		do {
			printf("\nOpcao: ");
			scanf("%hd", &op2);
			fflush(stdin);
		} while (op2 < 1 || op2 > 3);
	}
		break;
	case 3: {
		printf("\n1 - Troca entre dois integrantes");
		printf("\n2 - Troca entre todos os Integrates");
		printf("\n3 - Dar figurinha para outro Integrante");
		do {
			printf("\nOpcao: ");
			scanf("%hd", &op2);
			fflush(stdin);
		} while (op2 < 1 || op2 > 3);
	}
		break;
	default:
		op = 0;
	}
	return op * 10 + op2;
}

void novoIntegrante() {
	struct jogador *pnovo = (struct jogador*) malloc(sizeof(JOGADOR));
	struct jogador *aux = listaJogador;
	printf("Nome: ");
	gets(pnovo->nome);
	printf("Telefone: ");
	gets(pnovo->telefone);
	pnovo->inicioLista = NULL;
	pnovo->prox = NULL;
	if (listaJogador == NULL) {
		pnovo->codigo = 01;
		listaJogador = pnovo;
	} else {
		while (aux->prox != NULL) {
			aux = aux->prox;
		}
		pnovo->codigo = (aux->codigo) + 1;
		aux->prox = pnovo;
	}
}

int insereFigurinha(short figurinha, short j) {
	short player, achou = 0;
	struct jogador *pnovo;

	if (figurinha == 0) {
		printf("Digite o codigo do Integrante: ");
		scanf("%hd", &player);
		fflush(stdin);
	} else {
		player = j;
	}

	if (listaJogador == 0) {
		return 0;
	} else {
		pnovo = listaJogador;
		while (pnovo != NULL && achou == 0) {
			if (player == pnovo->codigo) {
				achou = 1;
			} else
				pnovo = pnovo->prox;
		}
	}
	if (achou == 0) {
		return 0;
	} else {
		struct lista *card = (struct lista*) malloc(sizeof(LISTA));
		struct lista *auxCard;
		if (figurinha == 0) {
			do {
				printf("Digite o numero da figurinha: ");
				scanf("%hd", &card->codigo);
				fflush(stdin);
				if (card->codigo < 1 || card->codigo > 100) {
					printf("\nFigurinha nao existe.\n");
				}
			} while (card->codigo < 1 || card->codigo > 100);
		} else {
			card->codigo = figurinha;
		}
		//pnovo = listaJogador;
		if (pnovo->inicioLista == NULL) { //primeira figurinha
			card->prox = NULL;
			card->repetidas = 0;
			pnovo->inicioLista = card;
		} else {
			auxCard = pnovo->inicioLista;
			while (auxCard != NULL) {
				if (auxCard->codigo == card->codigo) { //se é igual
					auxCard->repetidas++;
					break;
				}
				if (card->codigo < (pnovo->inicioLista)->codigo) { //no inicio
					card->repetidas = 0;
					card->prox = auxCard;
					pnovo->inicioLista = card;
					break;
				}

				if (auxCard->prox == NULL) { //no fim
					card->repetidas = 0;
					card->prox = NULL;
					auxCard->prox = card;
					break;
				}

				if (card->codigo <= (auxCard->prox)->codigo) { //no meio
					card->repetidas = 0;
					card->prox = auxCard->prox;
					auxCard->prox = card;
					break;
				}
				auxCard = auxCard->prox;
			}
		}
	}
	return 1;
}

short removeFigurinha(short j, short card) {
	struct jogador *pnovo = listaJogador;
	while (pnovo->codigo != j && pnovo != NULL) {
		pnovo = pnovo->prox;
	}

	struct lista *aux_Card = pnovo->inicioLista;
	struct lista *prev_Aux_Card = NULL;

	if (aux_Card != NULL) {
		while (aux_Card != NULL) {
			if (aux_Card->codigo == card)
				break;
			else {
				prev_Aux_Card = aux_Card;
				aux_Card = aux_Card->prox;
			}
		}
	} else
		return 0;

	//figurinha não existe
	if (aux_Card == NULL)
		return 0;

	//Remocao - primeiro da lista
	if (prev_Aux_Card == NULL && aux_Card->codigo == card) {
		//printf("Aqui 1\n");
		if (aux_Card->prox != NULL) {
			pnovo->inicioLista = aux_Card->prox;
			free(aux_Card);
		} else {
			free(aux_Card);
			pnovo->inicioLista = NULL;
		}
		return 1;
	}

	//Remocao - ultimo da lista
	if (aux_Card->prox == NULL) {
		//printf("aqui 2\n");
		prev_Aux_Card->prox = NULL;
		free(aux_Card);
		return 1;
	}

	//Remocao - meio da lista
	//printf("aqui 3\n");
	prev_Aux_Card->prox = aux_Card->prox;
	free(aux_Card);
	return 1;
}

void mostraIntegrante(short func) {
	struct jogador *pnovo = listaJogador;
	short player, controle = 0;
	if (func == 1) {
		printf("Digite o codigo do Integrante: ");
		scanf("%hd", &player);
		fflush(stdin);
	}
	while (pnovo != NULL) {
		if (pnovo->codigo == player && func == 1) {
			printf("\n_0%hd", pnovo->codigo);
			printf("\n%s\n%s\nFigurinhas", pnovo->nome, pnovo->telefone);
			if (pnovo->inicioLista == NULL) {
				printf("\n0\n");
			} else {
				struct lista *aux = pnovo->inicioLista;
				while (aux != NULL) {
					int i = 0;
					while (i <= (aux->repetidas)) {
						printf("\n%hd", aux->codigo);
						++i;
					}
					aux = aux->prox;
				}
			}
			controle = 1;
			printf("\n");
			break;
		} else {
			if (func == 0) {
				printf((pnovo->codigo <= 9 ? "\n_0%hd" : "\n_%hd"),
						pnovo->codigo);
				printf("\n%s\n%s\nFigurinhas", pnovo->nome, pnovo->telefone);
				if (pnovo->inicioLista == NULL) {
					printf("\n0");
				} else {
					struct lista *aux = pnovo->inicioLista;
					while (aux != NULL) {
						short i;
						for (i = 0; i <= aux->repetidas; i++) {
							printf("\n%hd", aux->codigo);
						}
						aux = aux->prox;
					}
				}
				controle = 1;
				printf("\n");
			}
		}
		pnovo = pnovo->prox;
	}
	if (controle == 0)
		printf("Nao ha registros com esse codigo ou nao tem registros\n");
}

void inserePacoteFigurinha(short pacote) {
	short r, i, j, soma = 0;
	srand((unsigned) time(NULL));
	printf("Digite o codigo do Integrante: ");
	scanf("%hd", &j);
	fflush(stdin);
	for (i = 0; i < pacote; i++) {
		r = rand() % 101 + 1; //rand de 1 a 100
		soma += insereFigurinha(r, j);
	}
	if (soma == 5) {
		printf("\nPacote inserido.\n");
	} else {
		printf("\nPacote nao inserido.\n");
	}
}

void exportar() {
	struct jogador *pnovo = listaJogador;
	if (pnovo != NULL) {
		FILE *arq = fopen("exportacaFigurinha.txt", "w+");
		while (pnovo != NULL) {
			fprintf(arq, (pnovo->codigo <= 9 ? "_0%hd" : "\n_%hd"),
					pnovo->codigo);
			fprintf(arq, "\n%s\n%s\nFigurinhas", pnovo->nome, pnovo->telefone);
			if (pnovo->inicioLista == NULL) {
				fprintf(arq, "\n%s", "0");
			} else {
				struct lista *aux = pnovo->inicioLista;
				while (aux != NULL) {
					short i;
					for (i = 0; i <= aux->repetidas; i++) {
						fprintf(arq, "\n%hd", aux->codigo);
					}
					aux = aux->prox;
				}
			}
			fprintf(arq, "%s", "\n");
			pnovo = pnovo->prox;
		}
		fclose(arq);
		printf("exportacaFigurinha.txt teve exito.\n");
	} else
		printf("\nNao foi possivel exportar pois nao tem integrantes.\n");
}

//void importar(){
//	char local[200], linha[200];
//	printf("Digite o local do arquivo a ser importado: ");
//	gets(local);
//
//	FILE *arq = fopen(local, "r+");
//	if (arq == NULL){
//		printf("\nErro ao importar.\n");
//	}else{
//		short sequencia=0;
//		while(!feof(arq)){
//			fgets(linha, 100, arq);
//			printf("%c", linha[3]);
//			if (linha[0] == '_'){
//				struct jogador *pnovo = (struct jogador*) malloc(sizeof(JOGADOR));
//				short n=0;
//				while (linha[sequencia] != '\n'){
//					n+= atoi(linha[n]) * 10;
//					sequencia++;
//				}
//				pnovo->codigo = n;
//				printf("Codigo: %d", n);
//			}
//		}
//	}
//	fclose(arq);
//}

int verificaJogadorExiste(short j) {
	struct jogador *pnovo = listaJogador;
	while (pnovo != NULL) {
		if (pnovo->codigo == j)
			return 1;
		else
			pnovo = pnovo->prox;
	}
	return 0;
}

void darFigurinha() {
	short playerOrigem, playerDestino, card, resCard;

	//lendo o integrante
	printf("Digite o codigo do Integrante de Origem: ");
	scanf("%hd", &playerOrigem);
	fflush(stdin);
	//lendo a figurinha
	if (verificaJogadorExiste(playerOrigem) == 1) {
		printf("Digite a figurinha: ");
		scanf("%hd", &card);
		fflush(stdin);

		resCard = removeFigurinha(playerOrigem, card);

		switch (resCard) {
		case 0:
			printf("Figurinha não existe.\n");
			break;
		default: {
			printf("Digite o codigo do Integrante de Destino: ");
			scanf("%hd", &playerDestino);
			fflush(stdin);

			if (verificaJogadorExiste(playerDestino) == 1) {
				//printf("\nPlayer: %hd ResCard: %hd", player, resCard);
				if (insereFigurinha(card, playerDestino) == 1) {
					printf("Dada figurinha com sucesso.\n");
				} else {
					printf("Troca não realizada.\n");
				}
			} else {
				printf("Jogador de destino nao existe.\n");
				insereFigurinha(card, playerOrigem);
			}
		}
		}
	} else {
		printf("Jogador de origem nao existe.\n");
	}
}

void trocadois() {
	short playerOrigem, playerDestino, cardOrigem, cardDest, resCard;

	//lendo o integrante Origem
	printf("Digite o codigo do Integrante 1: ");
	scanf("%hd", &playerOrigem);
	fflush(stdin);

	if (verificaJogadorExiste(playerOrigem) == 1) {
		printf("Digite a figurinha: ");
		scanf("%hd", &cardOrigem);
		fflush(stdin);

		resCard = removeFigurinha(playerOrigem, cardOrigem);

		switch (resCard) {
		case 0:
			printf("Figurinha não existe.\n");
			break;
		default: {
			printf("Digite o codigo do Integrante 2: ");
			scanf("%hd", &playerDestino);
			fflush(stdin);

			if (verificaJogadorExiste(playerDestino) == 1) {
				printf("Digite a figurinha: ");
				scanf("%hd", &cardDest);
				fflush(stdin);

				resCard = removeFigurinha(playerDestino, cardDest);

				switch (resCard) {
				case 0:
					printf("Figurinha não existe.\n");
					insereFigurinha(cardDest, playerDestino);
					break;
				default: {
					insereFigurinha(cardDest, playerOrigem);
					insereFigurinha(cardOrigem, playerDestino);
					printf("Troca realizada.\n");
				}
				}
			} else {
				insereFigurinha(cardOrigem, playerOrigem);
			}
		}
		}
	} else {
		printf("Jogador de origem nao existe.\n");
	}
}

void troca() {
	struct jogador *pnovo = listaJogador;
	if (pnovo == NULL)
		printf("Nao ha jogadores.\n");
	else {
		short i;
		while (pnovo != NULL) {
			struct nodo_jogador *nj = (struct nodo_jogador*) malloc(sizeof(NODO_JOGADOR));
			short controlePrimeiroJogar = 0;
			struct lista *card = listaJogador->inicioLista;
			nj->codigo = pnovo->codigo;
			short controlePrimeiraRepetida = 0, controlePrimeiraFaltante = 0;
			for (i = 1; i <= 100; i++) {
				if (card->codigo == i) {
					if (card->repetidas > 0) {
						while (card->repetidas > 0) {
							struct nodo_carta *nc = (struct nodo_carta*) malloc(sizeof(NODO_CARTA));
							nc->numero = i;
							if (controlePrimeiraRepetida == 0) {
								nc->prox = NULL;
							} else {
								nc->prox = nj->repetidas;
							}
							nj->repetidas = nc;
							card->repetidas--;
						}
					}
				} else {
					struct nodo_carta *nc = (struct nodo_carta*) malloc(sizeof(NODO_CARTA));
					nc->numero = i;
					if (controlePrimeiraFaltante == 0) {
						nc->prox = NULL;
					} else {
						nc->prox = nj->repetidas;
					}
					nj->repetidas = nc;
				}
			}
			if (controlePrimeiroJogar == 0){
				nj->prox = NULL;
			}else{
				//falta fazer
			}
			pnovo = pnovo->prox;
		}
	}
}

int main(void) {
	setbuf(stdout, NULL);
	int opcao;
	while (1) {
		opcao = menuPrincipal();
		if (opcao == 0)
			exit(0);
		switch (opcao) {
		case 11:
			novoIntegrante();
			break;
		case 12: {
			if (insereFigurinha(0, 0) == 1) {
				printf("\nFigurinha inserida.\n");
			} else {
				printf("\nFigurinha nao inserida\n");
			}
		}
			break;
		case 13: {
			inserePacoteFigurinha(5);
		}
			break;
		case 14:
			//importar();
			break;
		case 21:
			mostraIntegrante(1);
			break;
		case 22:
			mostraIntegrante(0);
			break;
		case 23:
			exportar();
			break;
		case 31:
			trocadois();
			break;
		case 32:
			troca();
			break;
		case 33:
			darFigurinha();
		}
	}
	return EXIT_SUCCESS;
}
