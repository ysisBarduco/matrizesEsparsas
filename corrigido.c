/* TRABALHO I - Matrizes Esparsas
    Ariane Oliveira Neves
    Ysis Barduco Straub de Lima
*/

#include <stdio.h>
#include <stdlib.h>

// Dados Abstratos
typedef struct nodo{
	float dado;
	int lin, col;
	struct nodo *prox;
}Matriz_Esparsa;

typedef struct navegacao{
    int id;
    Matriz_Esparsa *matriz;
    int tot_lin, tot_col;
    struct navegacao *prox;
}Lista_Matrizes;

// Variveis globais
int count_matrizes = 1;

// Protótipos
void menu();
// Operações na matriz
Matriz_Esparsa *aloca_nodo();
void insere_matriz(Matriz_Esparsa **m, float dado, int lin, int col);
void busca_dado(Matriz_Esparsa *m);
void libera_matriz(Matriz_Esparsa **m);
void le_dados(Matriz_Esparsa **m, int id);
int posicao_ocupada(Matriz_Esparsa *m, int lin, int col);
void soma_matriz(Lista_Matrizes *l);
void subtrai_matriz(Lista_Matrizes *l);
void multiplica_matriz(Lista_Matrizes *l);
void gera_transposta(Lista_Matrizes *l);
void imprime_matriz(Matriz_Esparsa *m,int id, int tot_lin, int tot_col);
void imprime_diagonal(Matriz_Esparsa *m,int id, int tot_lin, int tot_col);
// Operações na lista de matrizes
Lista_Matrizes *aloca_navegacao();
void insere_lista(Lista_Matrizes **l, int id, int tot_lin, int tot_col);
void le_matriz(Lista_Matrizes **l);
Lista_Matrizes *busca_matriz(Lista_Matrizes *l);
void libera_lista(Lista_Matrizes **l);

// Implementação
void menu(){
	printf("\n--- OPERACOES COM MATRIZES ---\n");
	printf("1.  Criar nova matriz\n");
	printf("2.  Imprimir matriz\n");
	printf("3.  Buscar dado\n");
	printf("4.  Imprimir diagonal principal\n");
	printf("5.  Somar matrizes\n");
	printf("6.  Subtrair matrizes\n");
	printf("7.  Multiplicar matrizes\n");
	printf("8.  Gerar matriz transposta\n");
	printf("9.  Liberar matriz\n");
	printf("0.  Sair\n");
	printf("Digite uma opcao: ");

}

Matriz_Esparsa *aloca_nodo(){
    Matriz_Esparsa *p;
    p = (Matriz_Esparsa*) malloc(sizeof(Matriz_Esparsa));
    
    if(!p){
        printf("Problema de alocacao do nodo!");
        exit(0);
    }
    
    return p;

}

Lista_Matrizes *aloca_navegacao(){
	Lista_Matrizes *q;
	q = (Lista_Matrizes *) malloc(sizeof(Lista_Matrizes));

	if(!q){
		printf("Problema de alocacao da Navegacao!");
		exit(0);
	}

	return q;
}

void le_matriz(Lista_Matrizes **l){
    int id = 0, tot_lin = 0, tot_col = 0;
    Lista_Matrizes *aux;
	
    id = count_matrizes;

	printf("Total de linhas: ");
	scanf("%d", &tot_lin);

	printf("Total de colunas: ");
	scanf("%d", &tot_col);

    insere_lista(l, id, tot_lin, tot_col);

}

void insere_lista(Lista_Matrizes **l, int id, int tot_lin, int tot_col){
    Lista_Matrizes *nova;

    nova = aloca_navegacao();
    nova->id = id;
    nova->tot_lin = tot_lin;
    nova->tot_col = tot_col;
    nova->matriz = NULL; // Inicializa matriz
    le_dados(&nova->matriz, nova->id);
    nova->prox = *l; // Insere novas matrizes no inicio
    *l = nova;
    
    count_matrizes++;
}

void le_dados(Matriz_Esparsa **m, int id){
    float dado;
    int lin, col, ocupado = 0;
    Matriz_Esparsa *aux;

    printf("\n---Leitura da matriz [%d]---\n", id);
	printf("Digite os dados diferentes de 0 e suas posiÃ§Ãµes.\nPara finalizar digite 0.");

	do{ 
		printf("\nDado: ");
		scanf("%f", &dado);

		if(dado == 0){
			printf("Leitura finalizada!\n");
			return;
		}

        aux = *m;
        do{

            printf("Linha: ");
            scanf("%d", &lin);
            
            printf("Coluna: ");
            scanf("%d", &col);
 
            ocupado = (posicao_ocupada(*m, lin, col));

            if(ocupado){
                printf("posicao [%d,%d] ja foi preencida!\n", lin, col);
                printf("Digite novamente!\n");
            }

        }while(ocupado); // Verifica se a posiÃ§Ã£o digitada nÃ£o foi preenchida antes de inserir

		insere_matriz(m, dado, lin, col);
	}while(dado != 0);
}

int posicao_ocupada(Matriz_Esparsa *m, int lin, int col){
    Matriz_Esparsa *aux;

    if(m == NULL){
        return 0;
    }

    aux = m;
    while(aux != NULL){
        if(aux->lin == lin && aux->col == col){
            return 1;
        }
    else{
        aux = aux->prox;
        }
    }

    return 0;
}

void insere_matriz(Matriz_Esparsa **m, float dado, int lin, int col){
    Matriz_Esparsa *novo, *aux;
	
    novo = aloca_nodo();
    novo->dado = dado;
    novo->lin = lin;
    novo->col = col;
    novo->prox = NULL;

    if(*m == NULL || //Se a matriz estiver vazia
        ((*m)->lin > lin || // ou a linha atual Ã© menor
        ((*m)->lin == lin && (*m)->col > col))){//ou na mesma linha, mas coluna maior

        // Insere no comeÃ§o
        novo->prox = *m;
        *m = novo;
        return;
    }

    aux = *m;
    while(aux->prox != NULL &&
	     (aux->prox->lin < lin ||
	     (aux->prox->lin == lin && aux->prox->col < col))){
                aux =aux->prox; // Percorre a lista
            }
    // Insere ordenado
    novo->prox = aux->prox;
    aux->prox = novo;
}

void imprime_matriz(Matriz_Esparsa *m, int id, int tot_lin, int tot_col){
    int i, j;
    Matriz_Esparsa *aux;

	printf("\n--- MATRIZ %d ---\n", id);

	if(m == NULL){
		printf("\nMatriz vazia!\n");
		return;
	}

    aux = m;
    for(i=1; i <= tot_lin; i++){ // Para cada linha
        for(j=1; j <= tot_col; j++){ // Para cada coluna
            if(aux != NULL && aux->lin == i && aux->col == j ){
                printf("%.1f ", aux->dado);
                aux = aux->prox; // AvanÃ§a quando o nodo for utilizado
            }
            else{
                printf("0.0 ");
            }
        }
        printf("\n");
    }

}

Lista_Matrizes *busca_matriz(Lista_Matrizes *l){
    int id;
    Lista_Matrizes *aux;

	printf("ID da matriz: ");
	scanf("%d", &id);

    aux = l;
    while(aux != NULL){
        if(aux->id == id){
            return aux;
        }
        else{
            aux = aux->prox;
        }
    }

    printf("\nMatriz nao encontrada!");
    return NULL;
}

void busca_dado(Matriz_Esparsa *m){
    Matriz_Esparsa *aux;
    float dado = 0.0;
    int achou = 0;

    printf("Dado: ");
    scanf("%f", &dado);
    
    aux = m;
    while(aux != NULL){
        if(aux->dado == dado){
            printf("Dado %.1f encontrado na posicao [%d,%d]\n", dado, aux->lin, aux->col);
            achou = 1;
        }
        
        aux = aux->prox;
    }

    if(!achou){
        printf("Dado não encontrado!");
    }
}

//---------------------- Execução ---------------------
int main(){
    Lista_Matrizes *matrizes, *matriz_atual;
    int opcao = 0;

    do{
        menu();
        scanf("%d", &opcao);

        switch(opcao){
            case 0:
                printf("Encerrando...");
                break;

            case 1:
                le_matriz(&matrizes);
                imprime_matriz(matrizes->matriz, matrizes->id, matrizes->tot_lin, matrizes->tot_col);
                break;

            case 2:
                matriz_atual = busca_matriz(matrizes);
                if(matriz_atual != NULL){
                    imprime_matriz(matriz_atual->matriz, matriz_atual->id, matriz_atual->tot_lin, matriz_atual->tot_col);
                }
                break;

            case 3:
                matriz_atual = busca_matriz(matrizes);
                if(matriz_atual != NULL){
                    busca_dado(matriz_atual->matriz);
                }
                break;

            case 4:
                
                break;

            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            default:
                printf("Opcao invalida!\n\n");

        }
    }while(opcao != 0);

    return 0;
}
