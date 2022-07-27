// código fonte do problema 2 proposto em pd2 prática, onde realiza-se a inscrição de usuarios em um processo seletivo

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

typedef struct candidatos {
	char nome[40];
	int idade;
	int area;
	int pontos;
	int CPF;
	struct candidatos *next; 
}dados;

typedef struct lista {
	dados *start;
	int total;
}List;

void inscricao(List *list);
//void ranking(*p);
void ranking(List *list);
void print(List *list);
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
	//print(&list);
}

void inscricao(List *list) {
	int pont;
	char duracao[10], curso[5];

	dados *aux = (dados*) malloc(sizeof(dados));

	printf("Nome: ");
	fgets(aux->nome, 40, stdin);
	fflush(stdin);

	printf("CPF(somente numeros): ");
	scanf("%d", &aux->CPF);
	getchar();
	
	printf("Idade: ");
	scanf("%d", &aux->idade);
	getchar();
		
	printf("Área pretendida:\n[1] Engenharia de Software\n[2] Banco de Dados\n[3] Análise e Projeto de Algoritmos\n");
	scanf("%d", &aux->area);
	getchar();

	printf("Jï¿½ realizou algum curso na ï¿½rea? ");
	fgets(curso, 5, stdin);
	fflush(stdin);

	aux->pontos = 0;
		
	while (curso[0] == 's'|| curso[0] == 'S') {
		printf("De curta duraï¿½ï¿½o(atï¿½ 10 horas), mï¿½dia duraï¿½ï¿½o(de 11 ï¿½ 40 horas) ou longa duraï¿½ï¿½o (mais de 40 horas)? ");
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
		printf("Possui mais algum curso na ï¿½rea?");
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
		
	printf("Possui algum curso de lï¿½ngua estrangeira? ");
	fgets(curso, 5, stdin);
	fflush(stdin);
		
	if (curso[0] == 's' || curso[0] == 'S') {
		printf("Quantos? ");
		scanf("%d", &pont);
		getchar();

		aux->pontos += pont*2;
	} 
	printf("Pesquisa ou trabalha na ï¿½rea pretendida a mais de 3 anos? ");
	fgets(curso, 5, stdin);
	fflush(stdin);
		
	if (curso[0]=='s' || curso[0]=='S') {
		aux->pontos +=1;
	}
		
	printf("Possui certificaï¿½ï¿½es nacionais ou internacionais? ");
	fgets(curso, 5, stdin);
	fflush(stdin);
		
	if (curso[0]=='s' || curso[0]=='S') {
		aux->pontos +=1;
	}
		
	printf("Jï¿½ participou de alguma equipe de desenvolvimento de software para o governo? ");
	fgets(curso, 5, stdin);
	fflush(stdin);
		
	if (curso[0]=='s' || curso[0]=='S') {
		aux->pontos +=1;
	}

	aux->next = list->start;
	list->start = aux;
}

//void ranking(*p) {
void ranking(List *list) {
	
	int i=0;
	char nomes_an[2][100], nomes_eng[2][100],nomes_bc[2][100];
	int posicoes[6], maior_an=0, maior_eng=0, maior_bc=0;
	int tam_an = 0, tam_eng = 0, tam_bc=0;
	dados  *aux;
	
	aux = list->start;
	
	if (aux == NULL) {
		printf("erro de memoria.");
	}
	else {
		while(aux != NULL) {
			if(aux->area == 3){			
				if(aux->pontos > maior_an){
					posicoes[0] = i;
					maior_an = aux->pontos;
					strcpy(nomes_an[0], aux->nome);
				//	nomes_an[0]= aux[posicoes[0]].nome;
				}
				tam_an +=1;
			}
			if(aux->area == 1){			
				if(aux->pontos > maior_eng){
					posicoes[2] = i;
					maior_eng = aux->pontos;
					strcpy(nomes_eng[0], aux->nome);
				//	nomes_eng[0]= aux[posicao[2]].nome;
				}
				tam_eng +=1;
			}
			if(aux->area == 2){			
				if(aux->pontos > maior_bc){
					posicoes[4] = i;
					maior_bc = aux->pontos;
					strcpy(nomes_bc[0], aux->nome);
				//	nomes_bc[0]= aux[posicao[4]].nome;
				}
				tam_bc +=1;
			}
			
			i+=1;
			aux = aux->next;
		}
		
		aux = list->start;
		
		if(i>1){
			i=0;
			maior_an=0;
			while(aux != NULL){
				
				if(aux->area == 3) {	
					if(tam_an>1) {
						
						if(aux->pontos > maior_an && posicoes[0]!=i){
							posicoes[1] = i;
							maior_an = aux->pontos;
							strcpy(nomes_an[1], aux->nome);
						//	nomes_an[1]= aux[posicao[1]].nome;
						}
					}
				}
				if(aux->area == 1){	
					if(tam_eng>1)	{
					
						if(aux->pontos > maior_an && posicoes[2]!=i){
							posicoes[3] = i;
							maior_an = aux->pontos;
							strcpy(nomes_eng[1], aux->nome);
		
					//		nomes_eng[1]= aux[posicao[3]].nome;
						}
					}
				}
				if(aux->area == 2){	
					if(tam_bc>1){
					
						if(aux->pontos > maior_an && posicoes[4]!=i){
							posicoes[5] = i;
							maior_an = aux->pontos;
							strcpy(nomes_bc[1], aux->nome);
		
						//	nomes_bc[1]= aux[posicao[5]].nome;
						}
					}
				}
				i+=1;
				aux = aux->next;
			}
		}
		aux = list->start;
		if(aux!=NULL) {
			printf("\nRanking: \n");
			if(tam_an>0) {
				printf("Análise e Projeto de Algoritmos: \n");
				printf("1 - %s", nomes_an[0]);
				if (tam_an>1) {
					printf("2 - %s", nomes_an[1]);
				}
			}
			if(tam_eng>0) {
				printf("Engenharia de Software: \n");
				printf("1 - %s", nomes_eng[0]);
				if(tam_eng>1) {
					printf("2 - %s", nomes_eng[1]);
				}
			}
			if(tam_bc>0) {
				printf("Banco de Dados: \n");
				printf("1 - %s", nomes_bc[0]);
				if(tam_bc>1) {
					printf("2 - %s", nomes_bc[1]);
				}
			}
		}
	}	
}
//}
void print(List *list) {
	dados *aux = list->start;

	while (aux != NULL) {
		printf("Nome: %s\n",aux->nome);
		printf("Protocolo: %d\n",aux->CPF);
		aux = aux->next;
	}
}

void buscar_remover(List *list) {
	
	int x, del, remove;
	dados *aux2, *aux, *aux3;
	
	aux = list->start;
	
	printf("Digite quem deseja encontrar: ");
	scanf("%d", &x);
	
	if (aux == NULL) {
		printf("erro de memoria.");
	}
	else {
		while(aux != NULL && aux->CPF != x) {
			aux2 = aux;
			aux = aux->next;
		}

		if (aux != NULL) {
			printf("Elemento encontrado 1\n");

			printf("Deseja remover a incriï¿½ï¿½o? ");
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

				while(aux != NULL && aux->CPF != x) {
					aux = aux->next;
				}
				if(aux != NULL) {
					printf("elemento não removido.");
				}
				else {
					printf("elemento removido");
				}
			}

		}
		else {
			printf("Elemento não encontrado 1");
		}
	}
}
