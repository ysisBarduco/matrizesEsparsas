#include <stdio.h>
#include <stdlib.h>

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
}lista_matrizes;

//Protótipos
void menu();
// Operações da matriz
Matriz_Esparsa *aloca_nodo();
void insere_matriz(Matriz_Esparsa **m, float dado, int linha, int coluna);
void le_dados(Matriz_Esparsa **m, int id);
void imprime_matriz(Matriz_Esparsa *m, int tot_lin, int tot_col, int id);
void imprime_diagonal();
void buscar_dado(lista_matrizes *l);
void remove_dados_matriz(Matriz_Esparsa *m);
void adicionar_matriz(lista_matrizes **l, Matriz_Esparsa *resultado, int lin, int col,int id);
void soma_matriz(lista_matrizes **j, int count_m);
void subtrai_matriz(lista_matrizes **j, int count_m);
void mult_matriz(lista_matrizes **j, int count_m);
void div_matriz(lista_matrizes **j, int count_m);
void matriz_transposta(lista_matrizes **j);
// Operação da lista
lista_matrizes *aloca_navegacao();
void inicializa_lista(lista_matrizes **l);
void insere_lista(lista_matrizes **l, int id, int tot_lin, int tot_col);
void le_matriz(lista_matrizes **l);
lista_matrizes *buscar_matriz(lista_matrizes *l);
void apaga_matriz(lista_matrizes *l);

//Implementação
Matriz_Esparsa *aloca_nodo(){
	Matriz_Esparsa *p;
	p = (Matriz_Esparsa *) malloc(sizeof(Matriz_Esparsa));

	if(!p){ 
		printf("Problema de alocacao do Nodo!");
		exit(0);
	}
	return p;
}

lista_matrizes *aloca_navegacao(){
	lista_matrizes *q;
	q = (lista_matrizes *) malloc(sizeof(lista_matrizes));

	if(!q){
		printf("Problema de alocacao da Navegacao!");
		exit(0);
	}

	return q;
}

void inicializa_lista(lista_matrizes **l){
	*l = NULL; // lista inicializa vazia;
}

void insere_lista(lista_matrizes **l, int id, int tot_lin, int tot_col){
	lista_matrizes *novo;

	novo = aloca_navegacao();
	novo->id = id;
	novo->tot_lin = tot_lin;
	novo->tot_col = tot_col;
	novo->matriz = NULL; // inicializa matriz
	le_dados(&novo->matriz, novo->id);

	// insere novas matrizes no inicio
	novo->prox = *l;
	*l = novo;
	

}

void insere_matriz(Matriz_Esparsa **m, float dado, int linha, int coluna){

	Matriz_Esparsa *novo, *aux;

	novo = aloca_nodo();
	novo->dado = dado;
	novo->lin = linha;
	novo->col = coluna;
	novo->prox = NULL;

	// Inserção ordenada por linha e coluna
	if(*m == NULL || // verifica se está vazio
	   (*m)->lin > linha || //linha menor
	   ((*m)->lin == linha && (*m)->col > coluna)){ // mesma linha coluna menor

		//inseri no começo
		novo->prox = *m;
		*m = novo;
		return;
	}

	aux = *m;

	while(aux->prox != NULL &&
	     (aux->prox->lin < linha ||
	     (aux->prox->lin == linha && aux->prox->col < coluna))){

		aux = aux->prox; // para o próximo ponteiro da lista
	}

	novo->prox = aux->prox;
	aux->prox = novo;
}

void le_matriz(lista_matrizes **l){
	int id, tot_lin, tot_col;

	printf("Identificador numerico: ");
	scanf("%d", &id);

	printf("Total de linhas: ");
	scanf("%d", &tot_lin);

	printf("Total de colunas: ");
	scanf("%d", &tot_col);

	insere_lista(l, id, tot_lin, tot_col);
}

void le_dados(Matriz_Esparsa **m, int id){
	float dado;
	int linha, coluna;

	printf("\n---Leitura da matriz [%d]---\n", id);
	printf("Digite os dados diferentes de 0 e suas posições.\nPara finalizar digite 0.\n");

	do{
		printf("\nDado: ");
		scanf("%f", &dado);

		if(dado == 0){
			printf("\nLeitura finalizada!\n");
			return;
		}

		printf("Linha: ");
		scanf("%d", &linha);

		printf("Coluna: ");
		scanf("%d", &coluna);

		insere_matriz(m, dado, linha, coluna);

	}while(dado != 0);
}


void imprime_matriz(Matriz_Esparsa *m, int tot_lin, int tot_col, int id){
	int i, j;
	Matriz_Esparsa *aux;

	printf("\n--- MATRIZ %d ---\n", id);

	if(m == NULL){
		printf("\nMatriz vazia!\n");
		return;
	}

	aux = m;

	for(i = 1; i <= tot_lin; i++){
		for(j = 1; j <= tot_col; j++){

			// verifica se existe elemento nessa posição
			if(aux != NULL && aux->lin == i && aux->col == j){
				printf("%.1f ", aux->dado);
				aux = aux->prox; // avança somente quando usa o nodo
			}
			else{
				printf("0.0 ");
			}
		}
		printf("\n");
	}
}

void imprime_diagonal(lista_matrizes *l){
	int i, j;
	lista_matrizes *matriz_atual;
	Matriz_Esparsa *aux;

	matriz_atual = buscar_matriz(l); // salva a posição da matriz
	aux = matriz_atual->matriz; // salva a posição do primeiro nodo

	printf("\n---Diagonal principal da matriz %d---\n", matriz_atual->id);

	for(i = 1; i <= matriz_atual->tot_lin; i++){
		for(j = 1; j <= matriz_atual->tot_col; j++){
			if(i == j){
				if(aux->lin == i && aux->col == j){
					printf("%.1f ", aux->dado);
					aux = aux->prox; // avança somente quando usa o nodo
				}
				else{
					printf("0.0 ");
				}
			}
			else{
				printf("  ");
			}
		}
		printf("\n");
	}

}

lista_matrizes *buscar_matriz(lista_matrizes *l){
	int id;
	lista_matrizes *aux;

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

void buscar_dado(lista_matrizes *l){
	float dado;
	lista_matrizes *matriz_atual;
	Matriz_Esparsa *aux;

	matriz_atual = buscar_matriz(l);
	aux = matriz_atual->matriz;

	if(matriz_atual != NULL){
		printf("\nBuscar dado: ");
		scanf("%f", &dado);

		while(aux != NULL){
			if(aux->dado == dado){
				printf("%.1f encontrado na linha %d e coluna %d.", dado, aux->lin, aux->col);
				return;
			}
			else{
				aux = aux->prox;
			}
		}
		printf("\nDado nao encontrado!");
	}
}

void adicionar_matriz(lista_matrizes **l, Matriz_Esparsa *resultado, int lin, int col,int id){
	
	if(resultado == NULL){
        printf("Resultado vazio! \n");
        return;
    }
	
    lista_matrizes *novo;

    novo = aloca_navegacao();
    novo->id = id;
    novo->tot_lin = lin;
    novo->tot_col = col;
    novo->matriz = resultado;

	// insere novas matrizes no inicio
    novo->prox = *l;
	*l = novo;
}

void soma_matriz(lista_matrizes **j, int count_m){
	int novo_id;
    lista_matrizes *m2, *m3, *nova;
    Matriz_Esparsa *h1, *h2, *resultado = NULL;

    if(count_m < 2){
        printf("Matrizes Invalidas!");
        return;
    }

    printf("Informe a 1 matriz: ");
    m2 = buscar_matriz(*j);

    printf("Informe a 2 matriz: ");
    m3 = buscar_matriz(*j);

	if(m2 == NULL || m3 == NULL){
    	printf("Matriz inválida");
    	return;
	}
	
    if(m2->tot_lin != m3->tot_lin ||  m2->tot_col != m3->tot_col){
		printf("Tamanhos diferentes!\n");
        return;
    }

    h1 = m2->matriz;
    h2 = m3->matriz;

    while(h1 != NULL || h2 != NULL){

        if(h1 != NULL && h2 != NULL && h1->lin == h2->lin && h1->col == h2->col){

            insere_matriz(&resultado, h1->dado + h2->dado, h1->lin, h1->col);

            h1 = h1->prox;
            h2 = h2->prox;
        }
        else if(h1 != NULL){
            insere_matriz(&resultado, h1->dado, h1->lin, h1->col);

            h1 = h1->prox;
        }
        else{
            insere_matriz(&resultado, h2->dado,h2->lin,h2->col);

            h2 = h2->prox;
        }
    }
	
	printf("ID da nova matriz: ");
    scanf("%d", &novo_id);
    
    adicionar_matriz(j, resultado, m2->tot_lin, m2->tot_col, novo_id);
    
    printf("Resultado:\n");
    imprime_matriz(resultado, m2->tot_lin, m2->tot_col, novo_id);
    
}


void subtrai_matriz(lista_matrizes **j, int count_m){
	int novo_id;
    lista_matrizes *m2, *m3, *nova;
    Matriz_Esparsa *h1, *h2, *resultado = NULL;

    if(count_m < 2){
        printf("Matrizes Invalidas!");
        return;
    }

    printf("Informe a 1 matriz: ");
    m2 = buscar_matriz(*j);

    printf("Informe a 2 matriz: ");
    m3 = buscar_matriz(*j);


    if(m2->tot_lin != m3->tot_lin ||  m2->tot_col != m3->tot_col){
		printf("Tamanhos diferentes!\n");
        return;
    }

    h1 = m2->matriz;
    h2 = m3->matriz;

    while(h1 != NULL || h2 != NULL){

        if(h1 != NULL && h2 != NULL &&  h1->lin == h2->lin && h1->col == h2->col){

            insere_matriz(&resultado, h1->dado - h2->dado, h1->lin, h1->col);

            h1 = h1->prox;
            h2 = h2->prox;
        }
        else if(h1 != NULL){
            insere_matriz(&resultado, h1->dado, h1->lin, h1->col);

            h1 = h1->prox;
        }
        else{
            insere_matriz(&resultado, h2->dado,h2->lin,h2->col);

            h2 = h2->prox;
        }
    }
	
	printf("ID da nova matriz: ");
    scanf("%d", &novo_id);
    
    adicionar_matriz(j, resultado, m2->tot_lin, m2->tot_col, novo_id);
    
    printf("Resultado:\n");
    imprime_matriz((*j)->matriz, (*j)->tot_lin, (*j)->tot_col, (*j)->id);
}

void mult_matriz(lista_matrizes **j, int count_m){
    int novo_id, a, b, k;
    lista_matrizes *m2, *m3;
    Matriz_Esparsa *hA, *hB, *resultado = NULL ;
    float r;

    if(count_m < 2){
        printf("Matrizes Invalidas!");
        return;
    }

    printf("Informe a 1 matriz: ");
    m2 = buscar_matriz(*j);

    printf("Informe a 2 matriz: ");
    m3 = buscar_matriz(*j);

    if(m2->tot_col != m3->tot_lin){
        printf("Nao foi possivel multiplicar!\n");
        return;
    }

    for(a = 1; a <= m2->tot_lin; a++){
        for(b = 1; b <= m3->tot_col; b++){
            r = 0;
            for(k = 1; k <= m2->tot_col; k++){
                hA = m2->matriz;
                hB = m3->matriz;
                while(hA != NULL){
                    if(hA->lin == a && hA->col == k){
                        while(hB != NULL){
                            if(hB->lin == k && hB->col == b){
                                r += hA->dado * hB->dado;
                            }
                            hB = hB->prox;
                        }
                        break;
                    }
                    hA = hA->prox;
                }
            }
            printf("Posicao [%d][%d] = %d\n", a, b, r);
            if(r != 0){
                insere_matriz(&resultado, r, a, b);
            }
        }
    }

	printf("ID da nova matriz: ");
    scanf("%d", &novo_id);
    
    adicionar_matriz(j, resultado, m2->tot_lin, m2->tot_col, novo_id);
    
    printf("Resultado:\n");
    imprime_matriz((*j)->matriz, (*j)->tot_lin, (*j)->tot_col, (*j)->id);
}

void div_matriz(lista_matrizes **j, int count_m){
	int novo_id, encontrou;
    lista_matrizes *m2, *m3, *nova;
    Matriz_Esparsa *h1, *h2, *resultado = NULL;
	float r;
	
    if(count_m < 2){
        printf("Matrizes Invalidas!");
        return;
    }

    printf("Informe a 1 matriz: ");
    m2 = buscar_matriz(*j);

    printf("Informe a 2 matriz: ");
    m3 = buscar_matriz(*j);


    if(m2->tot_lin != m3->tot_lin ||  m2->tot_col != m3->tot_col){
		printf("Tamanhos diferentes!\n");
        return;
    }

	h1 = m2->matriz;

    while(h1 != NULL){

        h2 = m3->matriz;
        encontrou = 0;
        r = 0;

        while(h2 != NULL){

            if(h1->lin == h2->lin && h1->col == h2->col){
                encontrou = 1;

                if(h2->dado != 0){
                    r = h1->dado / h2->dado;
                    printf("[%d][%d] = %.1f\n", h1->lin, h1->col, r);
                }
                break;
            }
            h2 = h2->prox;
        }

        if(encontrou && r != 0){
            insere_matriz(&resultado, r, h1->lin, h1->col);
        }
        h1 = h1->prox;
    }
   
	
	printf("ID da nova matriz: ");
    scanf("%d", &novo_id);
    
    adicionar_matriz(j, resultado, m2->tot_lin, m2->tot_col, novo_id);
    
    printf("Resultado:\n");
    imprime_matriz((*j)->matriz, (*j)->tot_lin, (*j)->tot_col, (*j)->id);
}

void matriz_transposta(lista_matrizes **j){
	lista_matrizes *m;
	Matriz_Esparsa *h, *resultado = NULL;
	int novo_id;
	
	printf("Digite a matriz: ");
	m = buscar_matriz(*j);
	
	h = m->matriz;
	
	while(h != NULL){
		insere_matriz(&resultado, h->dado, h->col, h->lin);
		h = h->prox;
	}
	
	printf("ID da nova matriz: ");
    scanf("%d", &novo_id);
    
    adicionar_matriz(j, resultado, m->tot_lin, m->tot_col, novo_id);
    
    printf("Resultado:\n");
    imprime_matriz((*j)->matriz, (*j)->tot_lin, (*j)->tot_col, (*j)->id);
}

void apaga_matriz(lista_matrizes *l){
	int id;
	lista_matrizes *aux, *anterior;

	printf("ID da matriz: ");
	scanf("%d", &id);

	aux = l;
	while(aux != NULL){
		anterior = aux;
		aux = aux->prox;

		if(aux != NULL && aux->id == id){
			remove_dados_matriz(aux->matriz);
			anterior->prox = aux->prox; // Pula o nodo
			free(aux);
			return;
		}
	}
	printf("\nMatriz nao encontrada!");

}

void remove_dados_matriz(Matriz_Esparsa *m){
	Matriz_Esparsa *aux, *proximo;

	aux = m;
	while(aux->prox != NULL){
		proximo = aux->prox;
		free(aux);
		aux = proximo;
	}
	m = NULL;
}

void menu(){
	printf("\n--- OPERACOES COM MATRIZES ---\n");
	printf("1.  Criar nova Matriz\n");
	printf("2.  Imprimir uma Matriz\n");
	printf("3.  Buscar a posicao de um dado\n");
	printf("4.  Imprime a diagona principal\n");
	printf("5.  Somar matrizes\n");
	printf("6.  Subtrair matrizes\n");
	printf("7.  Multiplicar matrizes\n");
	printf("8.  Dividir matrizes\n");
	printf("9.  Matriz transposta\n");
	printf("10. Remover dados da matriz\n");
	printf("11. Apagar lista\n");
	printf("0.  Sair\n");
	printf("Digite uma opcao: ");
	
}


// ================= MAIN =================

int main(){
	lista_matrizes *matrizes;
	lista_matrizes *matriz_atual;
	int *tlinhas = NULL, *tcolunas = NULL;
	int count_m = 0, opcao = 0;
	int m = 0;

	inicializa_lista(&matrizes);

	do{
		menu();
		scanf("%d", &opcao);

		switch(opcao){
			case 0: 
				printf("Saindo...\n");
				break;

			case 1:
				le_matriz(&matrizes);
				count_m++;
				imprime_matriz(matrizes->matriz, matrizes->tot_lin, matrizes->tot_col, matrizes->id);
				break;

			case 2:
				matriz_atual = buscar_matriz(matrizes);

				if(matriz_atual != NULL){
					imprime_matriz(matriz_atual->matriz, matriz_atual->tot_lin, matriz_atual->tot_col, matriz_atual->id);
				}

				break;

			case 3:
				buscar_dado(matrizes);
				break;

			case 4:
				imprime_diagonal(matrizes);
				break;
			
      		case 5:
			    soma_matriz( &matrizes, count_m);
			    break;
			
			case 6:
			    subtrai_matriz(&matrizes, count_m);
			    break;
			
			case 7:
			    mult_matriz(&matrizes, count_m);
			    break;
			
			case 8:
			    div_matriz(&matrizes, count_m);
			    break;
			
			case 9:
			    matriz_transposta(&matrizes);
			    break;
			    
			case 10:
				matriz_atual = buscar_matriz(matrizes);

			    if(matriz_atual != NULL){
			        remove_dados_matriz(matriz_atual->matriz);
			        count_m--;
			    }
				break;
			
			case 11:
				apaga_matriz(matrizes);
				break;
				
			default: 
				printf("Opcao invalida!\n");
				break;
		}
	}while(opcao != 0);

	return 0;
}
