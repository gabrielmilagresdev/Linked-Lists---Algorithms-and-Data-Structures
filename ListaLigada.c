#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int Elemento;
typedef int Bool;

typedef struct _no_{ //Struct do Nó
    Elemento valor;
    struct _no_ *proximo;
}No;

typedef struct { //Struct da lista ligada
    No *primeiro;
    int tamanho;
}ListaLigada;

ListaLigada *criar_lista(){
    ListaLigada *lista = (ListaLigada*) malloc(sizeof(ListaLigada)); //Tem que ser alocada dinâmicamente por ser acessada e manipulada em tempo de execução
    lista->primeiro = NULL; //Primeiro não há nenhum nó, aponta para NULL
    lista->tamanho = 0; //Não há nenhum nó, tamanho zero
    return lista;
}

Bool busca(ListaLigada* lista, Elemento e){
    No* noAtual = lista->primeiro;

    while(noAtual!=NULL){ //O último nó deve apontar para o NULL
        if(noAtual->valor == e) //Se for igual ao valor, retorna que encontrou
            return TRUE;
        noAtual = noAtual->proximo; //Passa para o próximo nó
    }
    return FALSE; //Caso não encontre, retorna falso
}

Bool buscaOrdenadaCrescente(ListaLigada* lista, Elemento e){
    No* noAtual = lista->primeiro;

    while(noAtual != NULL && noAtual->valor <= e){ //O último nó deve apontar para o NULL e o valor atual tem que ser menor ou igual que o elemento e
        if(noAtual->valor == e) //Se for igual ao valor, retorna que encontrou
            return TRUE;
        noAtual = noAtual->proximo; //Passa para o próximo nó
    }
    return FALSE;
}

Bool buscaOrdenadaDecrescente(ListaLigada* lista, Elemento e){
    No* noAtual = lista->primeiro;

    while(noAtual != NULL && noAtual->valor >= e){ //O último nó deve apontar para o NULL e o valor atual tem que ser maior ou igual que o elemento e
        if(noAtual->valor == e) //Se for igual ao valor, retorna que encontrou
            return TRUE;
        noAtual = noAtual->proximo; //Passa para o próximo nó
    }
    return FALSE;
}
