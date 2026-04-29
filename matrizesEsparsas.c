// Ariane Oliveira Neves
// Ysis Barduco Straub de Lima
/** 
Trabalho I - Matrizes Esparsas
	Obervações:
	- O usuário deve informar a dimens�o das matrizes.
	- Considerar as regras de opera��es com matrizes para implementar a soma, subtração, multiplicação, transposta e diagonal principal de matrizes.
	- As listas encadeadas devem ser passadas como parametros das funções.
	- O usuário poderia fazer quantas operações desejar com as matrizes
**/

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	float dado;
	int lin, col;
	struct nodo *prox;
}Matriz_Esparsa;

//Protótipos
Matriz_Esparsa *aloca_nodo();
void insere_lista(Matriz_Esparsa **m, float dado, int linha, int coluna);
void busca_dados(Matriz_Esparsa *m);
void libera_memoria(Matriz_Esparsa **m);
void le_matriz(Matriz_Esparsa **m, int *tot_lin, int *tot_col);
void soma_matriz(Matriz_Esparsa **m1, Matriz_Esparsa **m2);
void subtrai_matriz(Matriz_Esparsa **m1, Matriz_Esparsa **m2);
void mutiplica_matriz(Matriz_Esparsa **m1, Matriz_Esparsa **m2);
void gera_transposta(Matriz_Esparsa **m);
void imprime_matriz(Matriz_Esparsa *m, int tot_lin, int tot_col);
void imprime_diagonal(Matriz_Esparsa *m);

//Implementação

Matriz_Esparsa *aloca_nodo(){
	Matriz_Esparsa *p; //Cria Nodo
	p = (Matriz_Esparsa *) malloc(sizeof (Matriz_Esparsa)); //Aloca mem�ria
	if(!p){
		printf("Problema de alocacao!");
		exit(0);
	}
	return p;
}

void insere_lista(Matriz_Esparsa **m, float dado, int linha, int coluna){
	Matriz_Esparsa *novo, *aux; // variaveis temporarias
	novo = aloca_nodo(); // chama função para criar o nodo
	novo->dado = dado;
	novo->lin = linha;
	novo->col = coluna;
	novo->prox = NULL;
	
	//Insere ordenado por linha e coluna
	if(*m == NULL || (*m)->lin > linha && (*m)->col > coluna){
		novo->prox = *m; // insere antes do primeiro valor salvo
		*m = novo;
		return;
	}
	
	aux = *m;
	while(aux->prox != NULL && (aux->lin < linha || (aux->lin == linha && aux->col < coluna))){
		aux = aux->prox; // procura a maior posição salva
	}
	novo->prox = aux->prox; // insere antes da posição maior
	aux->prox = novo;
	
}

void busca_dados(Matriz_Esparsa *m){
	
}

void libera_memoria(Matriz_Esparsa **m){
	
}

void le_matriz(Matriz_Esparsa **m, int *tot_lin, int *tot_col){
   float dado = 0.00;
   int linha = 0, coluna = 0;
     
	printf("Total de linhas: ");
	scanf("%d", tot_lin);
	
	printf("Total de colunas: ");
	scanf("%d", tot_col);
	
	printf("\nDigite os dados diferentes de 0 e suas posições.\n Para finalizar a leitura, digite 0.");
   do{ // solicita a entrada do usuário ao menos uma vez
        printf("\nDado: ");
        scanf("%f", &dado);
         
        if(dado == 0){
             printf("\nLeitura finalizada!\n");
             return; // garante que o dado 0 não seja salvo na lista
        }
         
        printf("\nLinha: ");
        scanf("%d", &linha);
         
        printf("\nColuna: ");
        scanf("%d", &coluna);
         
        insere_lista(m, dado, linha, coluna); // chama a função para inserir o novo dado na lista
         
        printf("\n***\n");

    }while(dado != 0); // encerra a execução quando o dado for 0
   
	
}

void soma_matriz(Matriz_Esparsa **m1, Matriz_Esparsa **m2){
	
}

void subtrai_matriz(Matriz_Esparsa **m1, Matriz_Esparsa **m2){
	
}

void mutiplica_matriz(Matriz_Esparsa **m1, Matriz_Esparsa **m2){
	
}

void gera_transposta(Matriz_Esparsa **m){
	
}

void imprime_matriz(Matriz_Esparsa *m, int tot_lin, int tot_col){
	int i, j;
	Matriz_Esparsa *aux;
	
	if(m == NULL){
      printf("\nMatriz vazia!\n");
      return;
      }
	
	aux = m;

	for(i = 0; i < tot_lin; i++){ // para cada linha
		for(j = 0; j < tot_col; j++){ // para cada coluna
			if(aux != NULL && aux->lin == j && aux->col == i){ // imprime os dados da lista em suas posições na matriz
				printf("%.2f ", aux->dado);
			}
			else{ // imprime os 0
				printf("0.0 ");
			}
			m = m->prox;
		}
		printf("\n"); // Mudança de linha
	}
	
}

void imprime_diagonal(Matriz_Esparsa *m){
	
}

int main(){
	// (!!!) Criar um array de matrizes para salvar mais de uma matriz

	Matriz_Esparsa *mat1;
	int tlinhas, tcolunas;
	
	le_matriz(&mat1, &tlinhas, &tcolunas);
	imprime_matriz(mat1, tlinhas, tcolunas);
	
	return 0;
}