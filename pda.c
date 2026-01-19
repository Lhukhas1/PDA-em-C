#include "pda.h"

Transicao** cria_listaAdj(int numEstados){// Aloca memoria para uma lista de adj 
    Transicao **grafo = (Transicao**)malloc(sizeof(Transicao*) * numEstados);

    for(int i = 0; i < numEstados; i++) 
        grafo[i] = NULL;
    
    return grafo;
}

Transicao* criaTransicao(){// Apenas aloca memoria para uma transicao
    Transicao *transicao = (Transicao*)malloc(sizeof(Transicao));
    return transicao;
}

void preenche_ListaAdj(Transicao **listaAdj, Transicao *transicao, int estadoAtual){// Coloca a transiçao no seu estado incial 
    transicao->prox = listaAdj[estadoAtual];
    listaAdj[estadoAtual] = transicao;
}

int verificaFinal(int *estadosFinais, int numEstadosFinais, int estadoAtual){// Faz uma busca no vetor para ver se o estado e final
    for (int i = 0; i < numEstadosFinais; i++) 
        if(estadosFinais[i] == estadoAtual)
            return 1;
    return 0;
}

void arrumaComp(Computacao *comp, int *tam, int estado_ini, char *palavra, Pilha *pilha){// Adiciona uma computaçao a um vetor
    comp[*tam].estado = estado_ini;

    if(*palavra == '\0')// Corrige para o '&' se a palavra ja tiver acabado 
        strcpy(comp[*tam].palavra, "&");  
    else 
        strcpy(comp[*tam].palavra, palavra);

    comp[*tam].pilha = copia_Pilha(pilha);// Copia o estado atual da pilha
    (*tam)++;// Aumentando a posicao no vetor
}


int Dfs_PDA(Transicao **lista_Adj, char *palavra, int estado_ini, Pilha *pilha, int *estadosFinais, int numEstadosFinais, Computacao *comp, int *tam, int *tamMax){
    char letra;
    if(*palavra == '\0' && pilha_Vazia(pilha) && verificaFinal(estadosFinais, numEstadosFinais, estado_ini)){// Se a palavra esta no fim a pilha vazia e o estado e final retorna 1 
        if(*tam == *tamMax - 1){// Se a quant de computaçoes ficar igual a tamMax aumeta o tamanho em mais 10 posiçoes
            (*tamMax) += 10;
            comp = (Computacao*)realloc(comp, *tamMax * sizeof(Computacao));
        }
        arrumaComp(comp, tam, estado_ini, palavra, pilha);// Coloca a computaçao no vetor
        return 1;
    }

    if(*palavra == '\0' && !pilha_Vazia(pilha))// Fim da palavra porem pilha nao esta vazia entao a palvra nao e aceita
        return 0;
    
    Transicao *atual = lista_Adj[estado_ini];// Pegando a lista do estado inicial

    while(atual != NULL){// Enquanto nao chegar no fim da lista do estado
        if((atual->precisaLer == *palavra || atual->precisaLer == '&') && (atual->pop == topo(pilha) || atual->pop == '&')){
            Pilha *nova_pilha = copia_Pilha(pilha);// Faz a copia da pilha antes da alterar pois se mexermos nela sem ser na copia a chamada anteriror da 
                                                   // recursao vai ter sua pilha alterada tambem

            if(atual->pop != '&') 
                letra = pop_Pilha(nova_pilha);
            

            if(strcmp(atual->push, "&") != 0)
                for (int i = strlen(atual->push) - 1; i >= 0; i--) 
                    push_Pilha(atual->push[i], nova_pilha);
                
            
            if (atual->precisaLer == '&') {
                if(Dfs_PDA(lista_Adj, palavra, atual->estado_Destino, nova_pilha, estadosFinais, numEstadosFinais, comp, tam, tamMax)){// Chama a funçao sem consumir letra
                    if(*tam == *tamMax){// Se a quant de computaçoes ficar igual a tamMax aumeta o tamanho em mais 10 posiçoes
                        (*tamMax) += 10;
                        comp = (Computacao*)realloc(comp, *tamMax * sizeof(Computacao));
                    }
                    arrumaComp(comp, tam, estado_ini, palavra, pilha);
                    libera_Pilha(nova_pilha);// Libra a copia
                    free(nova_pilha);
                    return 1;
                }
            } 
            else if(Dfs_PDA(lista_Adj, palavra + 1, atual->estado_Destino, nova_pilha, estadosFinais, numEstadosFinais, comp, tam, tamMax)){// Chama a funçao consumindo uma letra
                if(*tam == *tamMax){// Se a quant de computaçoes ficar igual a tamMax aumeta o tamanho em mais 10 posiçoes
                    (*tamMax) += 10;
                    comp = (Computacao*)realloc(comp, *tamMax * sizeof(Computacao));

                }
                arrumaComp(comp, tam, estado_ini, palavra, pilha);
                libera_Pilha(nova_pilha);// Libera a pilha
                free(nova_pilha);
                return 1;
            }

            libera_Pilha(nova_pilha);// Libera a pilha
            free(nova_pilha);
        }
        atual = atual->prox;//proxima transiçao da lista
    }
    return 0;// Retorna 0 se nao achar nenhuma transicao por esse estado
}


void liberaLista(Transicao *transicao){//Libera toda a lista 
    if(transicao == NULL) 
        return;

    liberaLista(transicao->prox);
    free(transicao);
}


void libera_ListaAdj(Transicao **listaAdj, int numEstados){// Libera a memoria da lista de adj
    for(int i = 0; i < numEstados; i++) 
        liberaLista(listaAdj[i]);
}


void printaComp(Computacao *comp, int i){// Funçao que printa a sequencia da computaçao
    if(i == 0){
        printf("(q%d, %s, ", comp[i].estado, comp[i].palavra);
        printa_Pilha(comp[i].pilha);
        printf(").\n");
        libera_Pilha(comp[i].pilha);
        free(comp[i].pilha);
    }
    else{
        printf("(q%d, %s, ", comp[i].estado, comp[i].palavra);
        printa_Pilha(comp[i].pilha);
        printf(") |-\n");
        libera_Pilha(comp[i].pilha);
        free(comp[i].pilha);
    }
}
