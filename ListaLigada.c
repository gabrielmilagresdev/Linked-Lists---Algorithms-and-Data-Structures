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

typedef struct { //Struct da lista ligada com nó cabeça
    No *noCabeca;
    int tamanho;
}ListaLigadaCabeca;

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
    while(noAtual != NULL && noAtual->valor >= e){ //O último nó deve apontar para o NULL e o valor atual tem que ser maior ou igual que o elemento e
        noAnterior = noAtual;
        noAtual = noAtual->proximo; //Passa para o próximo nó
    }
    //Caso a inserção seja em um lugar arbitrário (incluindo a última posição)
    noAnterior->proximo = novo;
    novo->proximo = noAtual;
    lista->tamanho++;
    return TRUE;
}

Bool remocaoIndice(ListaLigada* lista, int indice){
    if(indice >= lista->tamanho || indice < 0) //Evita nunca encontrar
        return FALSE;
    No* noAtual = lista->primeiro;
    No* noAnterior = NULL;
    int indiceAtual = 0;

    if(noAtual == NULL) //Caso a lista esteja vazia
        return FALSE;

    //Caso a deleção seja do primeiro nó
    if(indice == indiceAtual){
        lista->primeiro = noAtual->proximo;
        free(noAtual); //Libera o nó alocado
        lista->tamanho--; //Diminui o tamanho da lista
        return TRUE;
    }
    while(indiceAtual < indice){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
        indiceAtual++;
    }
    //Remoção de uma posição arbitrária (Incluindo a última posição)
    noAnterior->proximo = noAtual->proximo;
    free(noAtual);  //Libera o nó alocado
    lista->tamanho--; //Diminui o tamanho da lista
    return TRUE;
}

Bool remocaoElemento(ListaLigada* lista, Elemento e){
    No* noAtual = lista->primeiro;
    No* noAnterior = NULL;

    if(noAtual == NULL) //Caso a lista esteja vazia
        return FALSE;

    //Caso a deleção seja no primeiro nó
    if(noAtual->valor == e){
        lista->primeiro = noAtual->proximo;
        lista->tamanho--;
        free(noAtual);
        return TRUE;
    }
    //Buscando a posição do elemento e
    while(noAtual != NULL && noAtual->valor != e){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }
    if(noAtual == NULL) //Não encontrou o elemento e
        return FALSE;
    //Deleção em posição arbitrária (incluindo a última posição)
    noAnterior->proximo = noAtual->proximo;
    lista->tamanho--;
    free(noAtual);
    return TRUE;
}

Bool remocaoElementoOrdenadaCrescente(ListaLigada* lista, Elemento e){
    No* noAtual = lista->primeiro;
    No* noAnterior = NULL;

    if(noAtual == NULL) //Caso a lista esteja vazia
        return FALSE;

    //Caso a deleção seja no primeiro nó
    if(noAtual->valor == e){
        lista->primeiro = noAtual->proximo;
        lista->tamanho--;
        free(noAtual);
        return TRUE;
    }
    //Buscando a posição do elemento e
    while(noAtual != NULL && noAtual->valor < e){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }
    if(noAtual == NULL|| noAtual->valor != e) //Não encontrou o elemento e ou encontrou um maior que ele
        return FALSE;
    //Deleção em posição arbitrária (incluindo a última posição), caso tenha encontrado o elemento
    noAnterior->proximo = noAtual->proximo;
    lista->tamanho--;
    free(noAtual);
    return TRUE;
}

Bool remocaoElementoOrdenadaDecrescente(ListaLigada* lista, Elemento e){
    No* noAtual = lista->primeiro;
    No* noAnterior = NULL;

    if(noAtual == NULL) //Caso a lista esteja vazia
        return FALSE;

    //Caso a deleção seja no primeiro nó
    if(noAtual->valor == e){
        lista->primeiro = noAtual->proximo;
        lista->tamanho--;
        free(noAtual);
        return TRUE;
    }
    //Buscando a posição do elemento e
    while(noAtual != NULL && noAtual->valor > e){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }
    if(noAtual == NULL|| noAtual->valor != e) //Não encontrou o elemento e ou encontrou um maior que ele
        return FALSE;
    //Deleção em posição arbitrária (incluindo a última posição), caso tenha encontrado o elemento
    noAnterior->proximo = noAtual->proximo;
    lista->tamanho--;
    free(noAtual);
    return TRUE;
}

Bool buscaCabeca(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo;

    while(noAtual != NULL && noAtual->valor != e){
        noAtual = noAtual->proximo;
    }
    if(noAtual == NULL) //Não encontrou
        return FALSE;
    return TRUE; //Encontrou
}

Bool buscaCabecaCrescente(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo;

    while(noAtual != NULL && noAtual->valor < e){
        noAtual = noAtual->proximo;
    }
    if(noAtual == NULL || noAtual->valor != e) //Não encontrou
        return FALSE;
    return TRUE; //Encontrou
}

Bool buscaCabecaDecrescente(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo;

    while(noAtual != NULL && noAtual->valor > e){
        noAtual = noAtual->proximo;
    }
    if(noAtual == NULL || noAtual->valor != e) //Não encontrou
        return FALSE;
    return TRUE; //Encontrou
}

Bool insercaoCabecaIndice(ListaLigadaCabeca* lista, Elemento e, int indice){
    if(indice > lista->tamanho || indice < 0) //Evita indices inválidos
        return FALSE;
    No* noAtual = lista->noCabeca->proximo;
    No* noAnterior = lista->noCabeca;
    No* novo = (No*) malloc(sizeof(No));
    novo->valor = e;
    novo->proximo = NULL; //Boa prática
    int indiceAtual = 0; //Iniciando o contador

    while(indiceAtual < indice){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }

    novo->proximo = noAtual;
    noAnterior->proximo = novo;
    lista->tamanho++;
    return TRUE;
}

Bool insercaoCabecaOrdenadaCrescente(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo; 
    No* noAnterior = lista->noCabeca;
    No* novo = (No*) malloc(sizeof(No));
    novo->valor = e;
    novo->proximo = NULL; //Boa prática
    if(noAtual == NULL){ //Caso a lista esteja vazia
        lista->noCabeca->proximo = novo;
        lista->tamanho++;
        return TRUE;
    }
    while(noAtual != NULL && noAtual->valor < e){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }

    novo->proximo = noAtual;
    noAnterior->proximo = novo;
    lista->tamanho++;
    return TRUE;
}

Bool insercaoCabecaOrdenadaDecrescente(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo; 
    No* noAnterior = lista->noCabeca;
    No* novo = (No*) malloc(sizeof(No));
    novo->valor = e;
    novo->proximo = NULL; //Boa prática
    if(noAtual == NULL){ //Caso a lista esteja vazia
        lista->noCabeca->proximo = novo;
        lista->tamanho++;
        return TRUE;
    }
    while(noAtual != NULL && noAtual->valor > e){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }

    novo->proximo = noAtual;
    noAnterior->proximo = novo;
    lista->tamanho++;
    return TRUE;
}

