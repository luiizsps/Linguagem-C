#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

// Struct que armazena os cadastros
typedef struct candidatos { 
	char nome[40];
	int idade;
	int area;
	int pontos;
	int CPF;
	struct candidatos *next; 
}dados;

// struct que armazena o endereço do primeiro elemento da lista e número de inscrições
typedef struct lista {
	dados *start;
	int total;
}List;

void inscricao(List *list);
void ranking(List *list);
void buscar_remover(List *list);

void main() {
	setlocale(LC_ALL, "Portuguese");
	List list;
	int i=0;
	char curso[5];
	
	list.start = NULL;
	list.total = 0;
	do {
		inscricao(&list);
		list.total++;

		printf("Realizar mais uma inscrição? ");
		fgets(curso, 5, stdin);
		fflush(stdin);
	}while(curso[0] != 'N' && curso[0] != 'n');

	buscar_remover(&list);
	ranking(&list);

}

// Fun��o que aplica o question�rio, contabiliza as pontua��es e armazena em listas encadeadas
void inscricao(List *list) {
	int pont;
	char duracao[10], curso[5];

	dados *aux = (dados*) malloc(sizeof(dados));

	printf("Nome: ");
	fgets(aux->nome, 40, stdin);
	fflush(stdin);

	printf("CPF (somente n�meros): ");
	scanf("%d", &aux->CPF);
	getchar();
	
	printf("Idade: ");
	scanf("%d", &aux->idade);
	getchar();
		
	printf("�rea pretendida:\n[1] Engenharia de Software\n[2] Banco de Dados\n[3] An�lise e Projeto de Algoritmos\n");
	scanf("%d", &aux->area);
	getchar();

	printf("J� realizou algum curso na �rea? ");
	fgets(curso, 5, stdin);
	fflush(stdin);

	aux->pontos = 0;
		
	while (curso[0] == 's'|| curso[0] == 'S') {
		printf("De curta dura��o (at� 10 horas), m�dia dura��o (de 11 � 40 horas) ou longa dura��o (mais de 40 horas)? ");
		fgets(duracao, 10, stdin);
		fflush(stdin);
			
		if (duracao[0] == 'c' || duracao[0] == 'C') {
			printf("Quantos? ");
			scanf("%d", &aux->pontos);
			getchar();
		}
		else if (duracao[0] == 'm' || duracao[0] == 'M') {
			printf("Quantos? ");
			scanf("%d", &pont);
			getchar();
				
			aux->pontos += pont*2;
		}
		else if (duracao[0] == 'l' || duracao[0] == 'L') {
			printf("Quantos? ");
			scanf("%d", &pont);
			getchar();
				
			aux->pontos += pont*3;
		}
		printf("Possui mais algum curso na �rea? ");
		fgets(curso, 5, stdin);
		fflush(stdin);	
	}
		
	printf("Possui algum curso afim? ");
	fgets(curso, 5, stdin);
	fflush(stdin);
		
	if (curso[0] == 's' || curso[0] == 'S') {
		printf("Quantos? ");
		scanf("%d", &pont);
		getchar();
			
		aux->pontos += pont*2;
	}
		
	printf("Possui algum curso de l�ngua estrangeira? ");
	fgets(curso, 5, stdin);
	fflush(stdin);
		
	if (curso[0] == 's' || curso[0] == 'S') {
		printf("Quantos? ");
		scanf("%d", &pont);
		getchar();

		aux->pontos += pont*2;
	} 
	printf("Pesquisa ou trabalha na �rea pretendida a mais de 3 anos? ");
	fgets(curso, 5, stdin);
	fflush(stdin);
		
	if (curso[0]=='s' || curso[0]=='S') {
		aux->pontos +=1;
	}
		
	printf("Possui certifica��es nacionais ou internacionais? ");
	fgets(curso, 5, stdin);
	fflush(stdin);
		
	if (curso[0]=='s' || curso[0]=='S') {
		aux->pontos +=1;
	}
		
	printf("J� participou de alguma equipe de desenvolvimento de software para o governo? ");
	fgets(curso, 5, stdin);
	fflush(stdin);
		
	if (curso[0]=='s' || curso[0]=='S') {
		aux->pontos +=1;
	}

	aux->next = list->start;
	list->start = aux;
}

// Fun��o que gera e imprime o raking, al�m de imprimir o total e incri��es e o total de incri��es em cada �rea
void ranking(List *list) {
	
	int i=0;
	char nomes_an[2][100], nomes_eng[2][100],nomes_bc[2][100];
	int posicoes[6], maior_an[2], maior_eng[2], maior_bc[2];
	int tam_an = 0, tam_eng = 0, tam_bc=0;
	dados  *aux;
	
	aux = list->start;
	
	for (i=0;i<2;i++){
		maior_an[i]=0;
		maior_eng[i]=0;
		maior_bc[i]=0;
	}
	i=0;
	
	if (aux == NULL) {
		printf("Lista vazia.\n");
	}
	else {
		//La�o que encontra as maiores pontua��es por �rea
		while(aux != NULL) {
			if(aux->area == 3){			
				if(aux->pontos > maior_an[0]){
					posicoes[0] = i;
					maior_an[0] = aux->pontos;
					strcpy(nomes_an[0], aux->nome);
				}
				tam_an +=1;
			}
			if(aux->area == 1){			
				if(aux->pontos > maior_eng[0]){
					posicoes[2] = i;
					maior_eng[0] = aux->pontos;
					strcpy(nomes_eng[0], aux->nome);
				}
				tam_eng +=1;
			}
			if(aux->area == 2){			
				if(aux->pontos > maior_bc[0]){
					posicoes[4] = i;
					maior_bc[0] = aux->pontos;
					strcpy(nomes_bc[0], aux->nome);
				}
				tam_bc +=1;
			}
			
			i+=1;
			aux = aux->next;
		}
		
		aux = list->start;
		
		if(i>1){
			i=0;
			//La�o que encontra as segundas maiores pontua��es por �rea
			while(aux != NULL){
				
				if(aux->area == 3) {	
					if(tam_an>1) {
						
						if(aux->pontos > maior_an[1] && posicoes[0]!=i){
							posicoes[1] = i;
							maior_an[1] = aux->pontos;
							strcpy(nomes_an[1], aux->nome);
						}
					}
				}
				if(aux->area == 1){	
					if(tam_eng>1) {
					
						if(aux->pontos > maior_eng[1] && posicoes[2]!=i) {
							posicoes[3] = i;
							maior_eng[1] = aux->pontos;
							strcpy(nomes_eng[1], aux->nome);
						}
					}
				}
				if(aux->area == 2){	
					if(tam_bc>1){
					
						if(aux->pontos > maior_bc[1] && posicoes[4]!=i){
							posicoes[5] = i;
							maior_bc[1] = aux->pontos;
							strcpy(nomes_bc[1], aux->nome);
								}
					}
				}
				i+=1;
				aux = aux->next;
			}
		}
		aux = list->start;
		if(aux!=NULL) {
			printf("Total de candidatos inseridos: %d\n", i);
			printf("Total de candidatos de An�lise e Projeto de Algoritmos: %d\n", tam_an);
			printf("Total de candidatos de Engenharia de Software: %d\n", tam_eng);
			printf("Total de candidatos de Banco de Dados: %d\n", tam_bc);

			printf("\nRanking: \n");
			if(tam_an>0) {
				printf("An�lise e Projeto de Algoritmos: \n");
				printf("1 - %s: %d pontos\n", nomes_an[0], maior_an[0]);
				if (tam_an>1) {
					printf("2 - %s: %d pontos\n", nomes_an[1], maior_an[1]);
				}
			}
			if(tam_eng>0) {
				printf("Engenharia de Software: \n");
				printf("1 - %s: %d pontos\n", nomes_eng[0], maior_eng[0]);
				if(tam_eng>1) {
					printf("2 - %s: %d pontos\n", nomes_eng[1], maior_eng[1]);
				}
			}
			if(tam_bc>0) {
				printf("Banco de Dados: \n");
				printf("1 - %s: %d pontos\n", nomes_bc[0], maior_bc[0]);
				if(tam_bc>1) {
					printf("2 - %s: %d pontos\n", nomes_bc[1], maior_bc[1]);
				}
			}
		}
	}	
}

// Fun��o que realiza a busca e remo��o de uma incri��o atrav�s do CPF
void buscar_remover(List *list) {
	
	int x, del, remove;
	dados *aux2, *aux, *aux3;
	
	aux = list->start;
	
	printf("Digite quem deseja encontrar: ");
	scanf("%d", &x);
	
	if (aux == NULL) {
		printf("Lista vazia.\n");
	}
	else {
		while(aux != NULL && aux->CPF != x) {
			aux2 = aux;
			aux = aux->next;
		}

		if (aux != NULL) {
			printf("Candidato encontrado\n");

			printf("Deseja remover a incri��o?\n[0] N�o\n[1] Sim\n");
			scanf("%d", &remove); 
			getchar();

			if(remove == 1) {
				aux3 = list->start;

				if(aux3 == aux) {
					list->start = list->start->next;
					free(aux);
				}
				else {
					aux2->next = aux->next;
					free(aux);
				}

				aux = list->start;
				// Procura pela inscri��o removida, verificando se a remo��o foi efetiva
				while(aux != NULL && aux->CPF != x) {
					aux = aux->next;
				}
				if(aux != NULL) {
					printf("Candidato n�o removido.\n");
				}
				else {
					printf("Candidato removido.\n");
				}
			}
		}
		else {
			printf("Candidato n�o encontrado.\n");
		}
	}
}
