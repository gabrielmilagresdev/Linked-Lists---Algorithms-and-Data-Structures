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

Bool insercao(ListaLigada* lista, Elemento e, int posicao){
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = e;
    novo->proximo = NULL; //Boa prática
   
    if(posicao > lista->tamanho || posicao < 0)
        return FALSE;

    if(posicao == 0){ //Inserção no primeiro índice
        novo->proximo = lista->primeiro;
        lista->primeiro = novo;
        lista->tamanho++; //Incrementa o tamanho da lista
    }
    else{
        No *noAtual = lista->primeiro;
        No *noAnterior = NULL;
        int indice = 0;

        while(indice < posicao){ //Enquanto não achar a posição para inserir
            noAnterior = noAtual;
            noAtual = noAtual->proximo;
            indice++;
        }
        novo->proximo = noAtual;
        noAnterior->proximo = novo;
        lista->tamanho++; //Incrementa o tamanho da lista
    }
    return TRUE;
}

Bool insercaoOrdenadaCrescente(ListaLigada* lista, Elemento e){
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = e;
    novo->proximo = NULL; //Boa prática
    No* noAtual = lista->primeiro;
    No* noAnterior = NULL;

    //Caso não tenha nenhum elemento na lista
    if(lista->primeiro == NULL){
        lista->primeiro = novo;
        lista->tamanho++;
        return TRUE;
    }
    //Caso a inserção seja no primeiro elemento
    if(novo->valor < noAtual->valor){
        novo->proximo = noAtual;
        lista->primeiro = novo;
        lista->tamanho++;
        return TRUE;
    }
    //Iterar para ver onde vai inserir
    while(noAtual != NULL && noAtual->valor <= e){ //O último nó deve apontar para o NULL e o valor atual tem que ser menor ou igual que o elemento e
        noAnterior = noAtual;
        noAtual = noAtual->proximo; //Passa para o próximo nó
    }
    //Caso a inserção seja em um lugar arbitrário (incluindo a última posição)
    noAnterior->proximo = novo;
    novo->proximo = noAtual;
    lista->tamanho++;
    return TRUE;
}

Bool insercaoOrdenadaDecrescente(ListaLigada* lista, Elemento e){
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = e;
    novo->proximo = NULL; //Boa prática
    No* noAtual = lista->primeiro;
    No* noAnterior = NULL;

    //Caso não tenha nenhum elemento na lista
    if(lista->primeiro == NULL){
        lista->primeiro = novo;
        lista->tamanho++;
        return TRUE;
    }
    //Caso a inserção seja no primeiro elemento
    if(novo->valor > noAtual->valor){
        novo->proximo = noAtual;
        lista->primeiro = novo;
        lista->tamanho++;
        return TRUE;
    }
    //Iterar para ver onde vai inserir
    while(noAtual != NULL && noAtual->valor >= e){ //O último nó deve apontar para o NULL e o valor atual tem que ser menor ou igual que o elemento e
        noAnterior = noAtual;
        noAtual = noAtual->proximo; //Passa para o próximo nó
    }
    //Caso a inserção seja em um lugar arbitrário (incluindo a última posição)
    noAnterior->proximo = novo;
    novo->proximo = noAtual;
    lista->tamanho++;
    return TRUE;
}
