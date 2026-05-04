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

// Prototipos
void menu();
// Operacoes na matriz
Matriz_Esparsa *aloca_nodo();
void insere_matriz(Matriz_Esparsa **m, float dado, int lin, int col);
void busca_dado(Matriz_Esparsa *m);
void apaga_dados(Matriz_Esparsa **m);
void le_dados(Matriz_Esparsa **m, int id);
int posicao_ocupada(Matriz_Esparsa *m, int lin, int col);
void soma_matriz(Lista_Matrizes **l);
void subtrai_matriz(Lista_Matrizes **l);
void mult_matriz(Lista_Matrizes **l);
void matriz_transposta(Lista_Matrizes **l);
void imprime_matriz(Matriz_Esparsa *m,int id, int tot_lin, int tot_col);
void imprime_diagonal(Matriz_Esparsa *m,int id, int tot_lin, int tot_col);
// Operacoes na lista de matrizes
Lista_Matrizes *aloca_navegacao();
void insere_lista(Lista_Matrizes **l, int id, int tot_lin, int tot_col);
void le_matriz(Lista_Matrizes **l);
Lista_Matrizes *busca_matriz(Lista_Matrizes *l);
void adicionar_matriz(Lista_Matrizes **l, Matriz_Esparsa *resultado, int tot_lin, int tot_col, int *id);
void libera_matriz(Lista_Matrizes **l);
void libera_lista(Lista_Matrizes **l);

// Implementacao
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

    printf("\n---Leitura da matriz [%d]---\n", id);
	printf("Digite os dados diferentes de 0 e suas posicoes.\nPara finalizar digite 0.");

	do{ 
		printf("\nDado: ");
		scanf("%f", &dado);

		if(dado == 0){
			printf("Leitura finalizada!\n");
			return;
		}

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

        }while(ocupado); // Verifica se a posicao digitada nao foi preenchida antes de inserir

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
        ((*m)->lin > lin || // ou a linha atual for menor
        ((*m)->lin == lin && (*m)->col > col))){// ou na mesma linha, mas coluna maior

        // Insere no comeÃƒÂ§o
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
                aux = aux->prox; // Avanca quando o nodo for utilizado
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
        printf("Dado nao encontrado!\n");
    }
}

void imprime_diagonal(Matriz_Esparsa *m,int id, int tot_lin, int tot_col){
    int i, j;
    Matriz_Esparsa *aux;

    if(m == NULL){
		printf("\nMatriz vazia!\n");
		return;
	}
	
	if(tot_lin == tot_col){
	
	    aux = m;
	    printf("\n---Diagonal principal da matriz [%d]---\n", id);
	    for(i = 1; i <= tot_lin; i++){ // i representa posição de linha e coluna
            for(j = 1; j <= tot_col; j++){ // Para formatação da saida
                if(i == j){
                    while(aux != NULL && (aux->lin < i || (aux->lin == i && aux->col < i))){
                        aux = aux->prox; // Avança até encontrar um nodo na posição (i,i)
                    }

                    if(aux != NULL && aux->lin == i && aux->col == i){
                        printf("%.1f ", aux->dado);
                        aux = aux->prox;
                    }

                    else{
                        printf("0.0 ");
                    }
                    
                }
                else{
                    printf(" ");
                }
            }
            
            printf("\n");
	    }
	}
	else{
		printf("Matriz invalida!\n");
		return;
	}
}

void adicionar_matriz(Lista_Matrizes **l, Matriz_Esparsa *resultado, int tot_lin, int tot_col, int *id){
    Lista_Matrizes *nova;

    *id = count_matrizes; // Passa o novo id por referencia

    if(resultado == NULL){
        printf("\nResultado vazio!");
        return;
    }

    nova = aloca_navegacao();
    nova->id = *id;
    nova->tot_lin = tot_lin;
    nova->tot_col = tot_col;
    nova->matriz = resultado;
    nova->prox = *l; // Insere novas matrizes no inicio
    *l = nova;
    
    count_matrizes++;

}

void soma_matriz(Lista_Matrizes **l){
    int novo_id;
    Lista_Matrizes *m1, *m2;
    Matriz_Esparsa *h1, *h2, *resultado = NULL;

    printf("Informe a primeira matriz:");
    m1 = busca_matriz(*l);

    printf("Informe a segunda matriz:");
    m2 = busca_matriz(*l);

    if(m1 == NULL || m2 == NULL){
        printf("Matriz vazia\n!");
        return;
    }

    if(m1->tot_lin != m2->tot_lin || m1->tot_col != m2->tot_col){
        printf("Tamanhos diferentes!\n");
        return;
    }

    h1 = m1->matriz;
    h2 = m2->matriz;

    while(h1 != NULL || h2 != NULL){
        if(h1 != NULL && h2 != NULL 
          && h1->lin == h2->lin 
          && h1->col == h2->col){

            insere_matriz(&resultado, (h1->dado + h2->dado), h1->lin, h2->col);
            h1 = h1->prox;
            h2 = h2->prox;
        }
        else if(h1 != NULL){

            insere_matriz(&resultado, h1->dado, h1->lin, h1->col);
            h1 = h1->prox;
        }
        else{

            insere_matriz(&resultado, h2->dado, h2->lin, h2->col);
            h2 = h2->prox;
        }
    }

    adicionar_matriz(l, resultado, m1->tot_lin, m2->tot_col, &novo_id);

    printf("Resultado:\n");
    imprime_matriz(resultado, novo_id, m2->tot_lin, m2->tot_col);

}

void subtrai_matriz(Lista_Matrizes **l){
    int novo_id;
    float diferenca = 0;
    Lista_Matrizes *m1, *m2;
    Matriz_Esparsa *h1, *h2, *resultado = NULL;

    printf("Informe a primeira matriz:");
    m1 = busca_matriz(*l);

    printf("Informe a segunda matriz:");
    m2 = busca_matriz(*l);

    if(m1 == NULL || m2 == NULL){
        printf("Matriz vazia\n!");
        return;
    }

    if(m1->tot_lin != m2->tot_lin || m1->tot_col != m2->tot_col){
        printf("Tamanhos diferentes!\n");
        return;
    }

    h1 = m1->matriz;
    h2 = m2->matriz;

    while(h1 != NULL && h2 != NULL){
        if(h1->lin == h2->lin && h1->col == h2->col){

            diferenca = h1->dado - h2->dado;

            if(diferenca != 0.0){
                insere_matriz(&resultado, diferenca, h1->lin, h2->col);
            }
            h1 = h1->prox;
            h2 = h2->prox;
        }
        else if(h1->lin < h2->lin ||
           (h1->lin == h2->lin && h1->col < h2->col)){
	        insere_matriz(&resultado, h1->dado, h1->lin, h1->col);
	        h1 = h1->prox;
	    }
	
	    else{
	        insere_matriz(&resultado, -h2->dado, h2->lin, h2->col);
	        h2 = h2->prox;
	    }
    }

    adicionar_matriz(l, resultado, m1->tot_lin, m2->tot_col, &novo_id);

    printf("Resultado:\n");
    imprime_matriz(resultado, novo_id, m2->tot_lin, m2->tot_col);
}

void mult_matriz(Lista_Matrizes **l){
    int novo_id;
    int a, b, k;
    float r;
    Lista_Matrizes *m1, *m2;
    Matriz_Esparsa *h1, *h2, *resultado = NULL;

    printf("Informe a primeira matriz:");
    m1 = busca_matriz(*l);

    printf("Informe a segunda matriz:");
    m2 = busca_matriz(*l);

    if(m1 == NULL || m2 == NULL){
        printf("Matriz vazia\n!");
        return;
    }

    if(m1->tot_col != m2->tot_lin){
        printf("\nNao e possivel multiplicaca-las!");
        return;
    }

    for(a = 1; a <= m1->tot_lin; a++){ // Para cada linha de m1
        for(b = 1; b <= m2->tot_col; b++){ // Para cada coluna de m2
            r = 0; // Soma das multiplicacoes inicializada
            for(k = 1; k <= m1->tot_col; k++){ // Para cada coluna de m1
                h1 = m1->matriz; // Aponta para o inicio de m1
                h2 = m2->matriz; // Aponta para o inicio de m2

                while(h1 != NULL){ // Percorre m1
                    if(h1->lin == a && h1->col == k){
                        while(h2 != NULL){ // Percorre m2
                            if(h2->lin == k && h2->col == b){
                                r += h1->dado * h2->dado; // Multiplica linha de m1 pela coluna de m2 e soma com as demais
                            }
                            h2 = h2->prox;
                        }
                        break;
                    }
                    h1 = h1->prox;
                }
        
            }

            printf("Posicao [%d][%d] = %.1f\n", a, b, r); // Teste
            if(r != 0){
                insere_matriz(&resultado, r, a, b);
            }
        }
    }

    adicionar_matriz(l, resultado, m1->tot_lin, m2->tot_col, &novo_id);

    printf("Resultado:\n");
    imprime_matriz(resultado, novo_id, m2->tot_lin, m2->tot_col);
}


void matriz_transposta(Lista_Matrizes **l){
    int novo_id;
    Lista_Matrizes *m;
    Matriz_Esparsa *h, *resultado = NULL;

	printf("Digite a matriz: ");
	m = busca_matriz(*l);
	
	if(m == NULL){
    printf("Matriz nao encontrada!\n");
    return;
	}

    h = m->matriz;
    while(h != NULL){
        insere_matriz(&resultado, h->dado, h->col, h->lin);
        h = h->prox;
    }

    adicionar_matriz(l, resultado, m->tot_col, m->tot_lin, &novo_id);

    printf("Resultado:\n");
    imprime_matriz(resultado, novo_id, m->tot_col, m->tot_lin);
}


void libera_matriz(Lista_Matrizes **l){
    int id = 0;
    Lista_Matrizes *aux, *anterior = NULL;

    printf("Digite a matriz: ");
    printf("ID: ");
    scanf("%d", &id);

    aux = *l;
    if(aux == NULL){
        printf("\nMatriz vazia!");
        return;
    }

    while(aux != NULL && aux->id != id){
        anterior = aux;
        aux = aux->prox;
    }

    if(aux != NULL && aux->id == id){
        apaga_dados(&aux->matriz);

		if(anterior == NULL){
			*l = aux->prox;
		}
		else{
			anterior->prox = aux->prox;
		}
		
        free(aux);
        printf("\nMatriz [%d] liberada!", id);
        return;
    }

    printf("\n\nMatriz nao encontrada!");
}

void apaga_dados(Matriz_Esparsa **m){
    Matriz_Esparsa *aux, *proximo;

    aux = *m;
    while(aux != NULL){
        proximo = aux->prox;
        free(aux);
        aux = proximo;
    }

    *m = NULL;
}

void libera_lista(Lista_Matrizes **l){
    Lista_Matrizes *aux, *proximo;

    aux = *l;
    while(aux != NULL){
        proximo = aux->prox;
        apaga_dados(&aux->matriz);
        free(aux);
        aux = proximo;
    }

    *l = NULL;
    count_matrizes = 1;
}

//---------------------- Execucao ---------------------
int main(){
    Lista_Matrizes *matrizes = NULL, *matriz_atual = NULL;
    int opcao = 0;

    do{
        menu();
        scanf("%d", &opcao);

        switch(opcao){
            case 0:
                printf("Encerrando...");
                libera_lista(&matrizes);
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
                matriz_atual = busca_matriz(matrizes);
                if(matriz_atual != NULL){
                    imprime_diagonal(matriz_atual->matriz, matriz_atual->id, matriz_atual->tot_lin, matriz_atual->tot_col);
                }
                break;

            case 5:
                soma_matriz(&matrizes);
                break;

            case 6:
                subtrai_matriz(&matrizes);
                break;

            case 7:
                mult_matriz(&matrizes);
                break;

            case 8:
                matriz_transposta(&matrizes);
                break;

            case 9:
                libera_matriz(&matrizes);
                break;

            default:
                printf("Opcao invalida!\n\n");
        }
    }while(opcao != 0);

    return 0;
}