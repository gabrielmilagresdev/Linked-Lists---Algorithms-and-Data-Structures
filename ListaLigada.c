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

Bool remocaoCabecaElemento(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo;
    No* noAnterior = lista->noCabeca;

    if(noAtual == NULL) //Se a lista estiver vazia
        return FALSE;

    while(noAtual != NULL && noAtual->valor != e){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }

    if(noAtual == NULL) //Elemento não encontrado
        return FALSE;

    noAnterior->proximo = noAtual->proximo;
    lista->tamanho--;
    free(noAtual); //Desalocando o nó
    return TRUE;
}

Bool remocaoCabecaElementoOrdenadaCrescente(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo;
    No* noAnterior = lista->noCabeca;

    if(noAtual == NULL) //Se a lista estiver vazia
        return FALSE;

    while(noAtual != NULL && noAtual->valor < e){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }

    if(noAtual == NULL || noAtual->valor != e) //Elemento não encontrado
        return FALSE;

    noAnterior->proximo = noAtual->proximo;
    lista->tamanho--;
    free(noAtual); //Desalocando o nó
    return TRUE;
}

Bool remocaoCabecaElementoOrdenadaDecrescente(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo;
    No* noAnterior = lista->noCabeca;

    if(noAtual == NULL) //Se a lista estiver vazia
        return FALSE;

    while(noAtual != NULL && noAtual->valor > e){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }

    if(noAtual == NULL || noAtual->valor != e) //Elemento não encontrado
        return FALSE;

    noAnterior->proximo = noAtual->proximo;
    lista->tamanho--;
    free(noAtual); //Desalocando o nó
    return TRUE;
}

Bool remocaoCabecaIndice(ListaLigadaCabeca* lista, int indice){
    if(indice >= lista->tamanho || indice < 0) //Evita indices inválidos
        return FALSE;
    No* noAtual = lista->noCabeca->proximo;
    No* noAnterior = lista->noCabeca;
    int indiceAtual = 0;

    if(noAtual == NULL) //Se a lista estiver vazia
        return FALSE;

    while(indiceAtual < indice){
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
        indiceAtual++;
    }

    if(noAtual == NULL) //Elemento não encontrado
        return FALSE;

    noAnterior->proximo = noAtual->proximo;
    lista->tamanho--;
    free(noAtual); //Desalocando o nó
    return TRUE;
}

ListaLigadaCabeca* criarListaCabecaCircular(){
    ListaLigadaCabeca* lista = (ListaLigadaCabeca*)malloc(sizeof(ListaLigadaCabeca));
    No* cabeca = (No*) malloc(sizeof(No));
    cabeca->proximo = cabeca;
    lista->noCabeca = cabeca;

    lista->tamanho = 0;
    return lista;
}

Bool buscaCabecaCircular(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo; //A lista vazia aponta para si mesmo, então não precisa de checar se está

    while(noAtual->valor != e && noAtual != lista->noCabeca) //Irá percorrer até encontrar o elemento e ou voltar ao nó cabeça
        noAtual = noAtual->proximo;
    
    return noAtual == lista->noCabeca ? FALSE : TRUE; //Se deu uma volta e não encontrou retorna falso. Caso encontrou, retorna verdadeiro
}

Bool inserirCabecaCircular(ListaLigadaCabeca* lista, Elemento e, int indice){
    if(indice > lista->tamanho || indice < 0) //Índice inválido
        return FALSE;
    
    No* noAtual = lista->noCabeca->proximo; //A lista vazia aponta para si mesmo, então não precisa de checar se está
    No* noAnterior = lista->noCabeca;
    No* novo = (No*) malloc(sizeof(No));
    novo->valor = e;
    novo->proximo = lista->noCabeca; //Se a lista estiver vazia, aponta para o cabeça
    int indiceAtual = 0; 

    while(noAtual != lista->noCabeca && indiceAtual < indice){ //Irá percorrer até chegar no índice, essa condição já resolve a questão da lista vazia
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
        indiceAtual++;
    }
    
    novo->proximo = noAtual;
    noAnterior->proximo = novo;
    lista->tamanho++;

    return TRUE;
}

Bool inserirCabecaCircularCrescente(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo; //A lista vazia aponta para si mesmo, então não precisa de checar se está
    No* noAnterior = lista->noCabeca;
    No* novo = (No*) malloc(sizeof(No));
    novo->valor = e;
    novo->proximo = lista->noCabeca; //Se a lista estiver vazia, aponta para o cabeça

    while(noAtual != lista->noCabeca && noAtual->valor < e){ //Irá percorrer até encontrar a posição para inserir, essa condição já resolve a questão da lista vazia
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }
    
    novo->proximo = noAtual;
    noAnterior->proximo = novo;
    lista->tamanho++;

    return TRUE;
}

Bool inserirCabecaCircularDecrescente(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo; //A lista vazia aponta para si mesmo, então não precisa de checar se está
    No* noAnterior = lista->noCabeca;
    No* novo = (No*) malloc(sizeof(No));
    novo->valor = e;
    novo->proximo = lista->noCabeca; //Se a lista estiver vazia, aponta para o cabeça

    while(noAtual != lista->noCabeca && noAtual->valor > e){ //Irá percorrer até encontrar a posição para inserir, essa condição já resolve a questão da lista vazia
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }
    
    novo->proximo = noAtual;
    noAnterior->proximo = novo;
    lista->tamanho++;

    return TRUE;
}

Bool remocaoCabecaCircularIndice(ListaLigadaCabeca* lista, int indice){
    if(indice >= lista->tamanho || indice < 0  || lista->tamanho == 0) //Índice inválido ou lista vazia
        return FALSE;

    No* noAtual = lista->noCabeca->proximo; //A lista vazia aponta para si mesmo, então não precisa de checar se está
    No* noAnterior = lista->noCabeca;
    int indiceAtual = 0;

    while(indiceAtual < indice){ //Irá percorrer até encontrar a posição para remover, essa condição já resolve a questão da lista vazia
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
        indiceAtual++;
    }

    noAnterior->proximo = noAtual->proximo;
    lista->tamanho--;
    free(noAtual);
    return TRUE;
}

Bool remocaoCabecaCircularElemento(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo; //A lista vazia aponta para si mesmo, então não precisa de checar se está
    No* noAnterior = lista->noCabeca;

    while(noAtual != lista->noCabeca && noAtual->valor != e){ //Irá percorrer até encontrar a posição para inserir, essa condição já resolve a questão da lista vazia
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }
    if(noAtual == lista->noCabeca) //Não encontrou o elemento e
        return FALSE;

    noAnterior->proximo = noAtual->proximo;
    lista->tamanho--;
    free(noAtual);

    return TRUE;
}

Bool remocaoCabecaCircularElementoOrdenadaCrescente(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo; //A lista vazia aponta para si mesmo, então não precisa de checar se está
    No* noAnterior = lista->noCabeca;

    while(noAtual != lista->noCabeca && noAtual->valor < e){ //Irá percorrer até encontrar a posição para remover, essa condição já resolve a questão da lista vazia
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }
    if(noAtual == lista->noCabeca || noAtual->valor != e) //Não encontrou o elemento e
        return FALSE;

    noAnterior->proximo = noAtual->proximo;
    lista->tamanho--;
    free(noAtual);

    return TRUE;
}

Bool remocaoCabecaCircularElementoOrdenadaDecrescente(ListaLigadaCabeca* lista, Elemento e){
    No* noAtual = lista->noCabeca->proximo; //A lista vazia aponta para si mesmo, então não precisa de checar se está
    No* noAnterior = lista->noCabeca;

    while(noAtual != lista->noCabeca && noAtual->valor > e){ //Irá percorrer até encontrar a posição para remover, essa condição já resolve a questão da lista vazia
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }
    if(noAtual == lista->noCabeca || noAtual->valor != e) //Não encontrou o elemento e
        return FALSE;

    noAnterior->proximo = noAtual->proximo;
    lista->tamanho--;
    free(noAtual);

    return TRUE;
}

Bool insercaoPilha(ListaLigada* pilha, Elemento e){
    No* novo = (No*) malloc(sizeof(No));
    if(novo ==  NULL) //Não foi capaz de alocar
        return FALSE;
    novo->valor = e;

    novo->proximo = pilha->primeiro;  
    pilha->primeiro = novo;
    pilha->tamanho++;
    return TRUE;
}

Bool remocaoPilha(ListaLigada* pilha, Elemento* e){
    if(pilha->tamanho <= 0) //Lista vazia
        return FALSE;

    *e = pilha->primeiro->valor;
    No* ultimoNo = pilha->primeiro;
    pilha->primeiro = pilha->primeiro->proximo;
    pilha->tamanho--;
    free(ultimoNo); //Desalocando o nó removido
    return TRUE;
}