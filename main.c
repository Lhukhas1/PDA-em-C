#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha.h"
#include "pda.h"

int main(){

    int numEstados,// Quant estados
        numTransicoes,// Quant transiçoes
        numEstadoFinal,// Quant estados finais
        estadoAtual;// Estado final

    char palavra[101];
    Transicao *transicao;
    Computacao *comp = (Computacao*)malloc(sizeof(Computacao) * 100);

    int tam,// Quant de computaçao dps
        tamMax = 100;// tamamnho max do vetor de computacao, porem se precisar ele da realloc de 10 em 10

    Pilha *pilha = cria_Pilha();// Cria a pilha e ja coloca o Z nela
    inicia_Pilha(pilha);

    scanf("%d %d", &numEstados, &numTransicoes);

    Transicao **listaAdj = cria_listaAdj(numEstados);// Cria lista de adj

    for(int i = 0; i < numTransicoes; i++){// Cria as transiçoes preenche e ja coloca na lista de adj
        transicao = criaTransicao();
        scanf("%d %c %c %s %d", &estadoAtual, &transicao->precisaLer, &transicao->pop, transicao->push, &transicao->estado_Destino);

        preenche_ListaAdj(listaAdj, transicao, estadoAtual);
    }

    scanf("%d", &numEstadoFinal);
    int *vetFinais = (int*)malloc(sizeof(int) * numEstadoFinal);// Cria um vetor para armazenar os finais

    for(int i = 0; i < numEstadoFinal; i++)// Preenche o vetor com os elementos finais
        scanf("%d", &vetFinais[i]);
    

    scanf("%s", palavra);
    while(strcmp(palavra, "*")){
        tam = 0;
        if(Dfs_PDA(listaAdj, palavra, 0, pilha, vetFinais, numEstadoFinal, comp, &tam, &tamMax)){// Se a palavra for aceita printa sim e a computaçao dela
            printf("%s: sim\n", palavra);

            for (int i = tam - 1; i >= 0; i--)// Faz o print do vetor de compuçao 
                printaComp(comp, i);
        } 
        else 
            printf("%s: nao\n", palavra);
        
        scanf("%s", palavra);
    }

    libera_Pilha(pilha);// Caso n esteja vazia retira os elementos o 'Z'
    free(pilha);
    libera_ListaAdj(listaAdj, numEstados);
    free(listaAdj);
    free(vetFinais);
    free(comp);

    return 0;
}

