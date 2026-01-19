#include "pilha.h"

Pilha* cria_Pilha(){ // Aloca memoria para a pilha
    Pilha *pilha = (Pilha*)malloc(sizeof(Pilha)); 
    pilha->topo = NULL;

    return pilha;
}

void push_Pilha(char letra, Pilha *pilha){// Coloca um elemento na pilha
    nodoPilha *novo = (nodoPilha*)malloc(sizeof(nodoPilha));

    novo->letra = letra;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

void inicia_Pilha(Pilha *pilha){// Coloca o 'Z' na pilha
    push_Pilha('Z', pilha);
}

char pop_Pilha(Pilha *pilha){// Retira um elemeto da pilha
    char aux = pilha->topo->letra;   
    nodoPilha *aux2 = pilha->topo;

    pilha->topo = aux2->prox;
    free(aux2);

    return aux;
}

int pilha_Vazia(Pilha *pilha){// Verifica se a pilha so tem o Z
    pilha->topo->letra == 'Z';
}

char topo(Pilha *pilha){// Retorna o elemento do topo da pilha
    return pilha->topo->letra;
}

Pilha* copia_Pilha(Pilha *pilha){// Faz uma copia da pilha
    Pilha *Copia = cria_Pilha();
    Pilha *auxCopia = cria_Pilha();
    nodoPilha *aux = pilha->topo;

    while(aux != NULL){// Passa por uma pilha salvando os elementos invertidos na auxCopia
        push_Pilha(aux->letra, auxCopia);
        aux = aux->prox;
    }

    while(auxCopia->topo != NULL)// Passa pela auxCopia dando pop e ja dando push na Copia real
        push_Pilha(pop_Pilha(auxCopia), Copia);
    //No fim a auxCopia esta vaizia 

    free(auxCopia);
    return Copia;
}

void libera_Pilha(Pilha *pilha){// Retira todos os elementos da pilha inclusive o Z
    char aux;
    while(!pilha_Vazia(pilha)) 
        aux = pop_Pilha(pilha);
    
    if(topo(pilha) == 'Z') 
        aux = pop_Pilha(pilha); // retira o Z
}

void printa_Pilha(Pilha *pilha){// Percorre a pilha printando seus elementos
    nodoPilha *aux = pilha->topo;

    while(aux != NULL){
        printf("%c", aux->letra);
        aux = aux->prox;
    }
}