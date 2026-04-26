// Ariane Oliveira Neves
// Ysis Barduco Straub de Lima
/** 
Trabalho I - Matrizes Esparsas
	Oberva��es:
	- O usu�rio deve informar a dimens�o das matrizes.
	- Considerar as regras de opera��es com matrizes para implementar a soma, subtra��o, multiplica��o, transposta e diagonal principal de matrizes.
	- As listas encadeadas devem ser passadas como par�metros das fun��es.
	- O usu�rio poder� fazer quantas opera��es desejar com as matrizes
**/

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	float dado;
	int lin, col;
	struct nodo *prox;
}Matriz_Esparsa;

//Prot�tipos
Matriz_Esparsa aloca_nodo();
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

//Implementa��o

Matriz_Esparsa aloca_nodo(){
	Matriz_Esparsa *p; //Cria Nodo
	p = (Matriz_Esparsa *) malloc(sizeof (Matriz_Esparsa)); //Aloca mem�ria
	if(!p){
		printf("Problema de alocacao!");
		exit(0);
	}
	return *p;
}

void insere_lista(Matriz_Esparsa **m, float dado, int linha, int coluna){
	Matriz_Esparsa *novo, *aux; // variaveis temporarias
	*novo = aloca_nodo(); // chama fun��o para criar o nodo
	novo->dado = dado;
	novo->lin = linha;
	novo->col = coluna;
	novo->prox = NULL;
	
	//Insere ordenado por linha e coluna
	if((*m)->lin >= linha || (*m)->col >= coluna || *m == NULL){
		novo->prox = *m; // insere antes do primeiro valor salvo
		*m = novo;
		return;
	}
	
	aux = *m;
	while(aux->prox != NULL && aux->lin < linha && aux->col < coluna){
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
	
	printf("\nDigite os dados diferentes de 0 e suas posi��es.\n Para finalizar a leitura, digite 0.");
   do{ // solicita a entreda do us�rio ao menos uma vez
        printf("\nDado: ");
        scanf("%f", &dado);
         
        if(dado == 0){
             printf("\nLeitura finalizada!\n");
             return; // garante que o dado 0 n�o seja salvo na lista
        }
         
        printf("\nLinha: ");
        scanf("%d", &linha);
         
        printf("\nColuna: ");
        scanf("%d", &coluna);
         
        insere_lista(m, dado, linha, coluna); // chama a fun��o para inserir o novo dado na lista
         
        printf("\n***\n");

    }while(dado != 0); // encerra a execu��o quando o dado for 0
   
	
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
	
	if(m == NULL){
      printf("\nMatriz vazia!\n");
      return;
      }
	
	for(i = 0; i < tot_lin; i++){ // para cada linha
     for(j = 0; j < tot_col; j++){ // para cada coluna
        if(m->col == j && m->lin == i){ // imprime os dados da lista em suas posi��es na matriz
            printf("%d ", m->dado);
        }
        else{ // imprime os 0
            	printf("0 ");
        }
     m = m->prox;
   }
    printf("\n"); // Mudan�a de linha
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
