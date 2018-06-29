#include <stdio.h>
#include <stdlib.h>

#include "lista_enc.h"
#include "no.h"

//#define DEBUG

struct listas_enc {
    no_t *cabeca;
    no_t *cauda;
    int tamanho;
};

//cria uma lista vazia
lista_enc_t *cria_lista_enc (void) {
    lista_enc_t *p = malloc(sizeof(lista_enc_t));

    if (p == NULL){
        perror("cria_lista_enc:");
        exit(EXIT_FAILURE);
    }

    p->cabeca = NULL;
    p->cauda = NULL;
    p->tamanho = 0;

    return p;
}

void add_cauda(lista_enc_t *lista, no_t* elemento)
{
    if (lista == NULL || elemento == NULL){
        fprintf(stderr,"add_cauda: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

   #ifdef DEBUG
   printf("Adicionando %p --- tamanho: %d\n", elemento, lista->tamanho);
   #endif // DEBUG

   //lista vazia
   if (lista->tamanho == 0)
   {
        #ifdef DEBUG
        printf("add_cauda: add primeiro elemento: %p\n", elemento);
        #endif // DEBUG

        lista->cauda = elemento;
        lista->cabeca = elemento;
        lista->tamanho++;

        desliga_no(elemento);
   }
   else {
        // Remove qualquer ligacao antiga
        desliga_no(elemento);
        // Liga cauda da lista com novo elemento
        liga_nos(lista->cauda, elemento);

        lista->cauda = elemento;
        lista->tamanho++;
   }
}

void add_cabeca(lista_enc_t *lista, no_t* elemento)

{
    if (lista == NULL || elemento == NULL){
        fprintf(stderr,"add_cabeca: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    printf("Adicionando %p --- tamanho: %d\n", elemento, lista->tamanho);
    #endif // DEBUG

    //caso a lista esteja vazia
    if (lista->tamanho == 0)
   {
        #ifdef DEBUG
        printf("add_cabeca: add primeiro elemento: %p\n", elemento);
        #endif // DEBUG

        lista->cauda = elemento;
        lista->cabeca = elemento;
        lista->tamanho++;

        desliga_no(elemento);
   }
    else {

        liga_nos(elemento, lista->cabeca);      //ligo o novo nó com a cabeça antiga da lista
        lista->cabeca = elemento;               //coloca o novo elemento na cabeca da lista
        lista->tamanho ++;                      // aumenta o tamanho da lista
    }

}

no_t* remove_cabeca(lista_enc_t *lista){

    if (lista == NULL){
        fprintf(stderr,"lista vazia");
        exit(EXIT_FAILURE);
    }

    no_t *no = lista->cabeca;
    no_t *no_aux = obtem_proximo(no);
    lista->cabeca = no_aux;

    lista->tamanho--;

    if(lista->tamanho == 0){
    lista->cauda = NULL;
    }

    return no;

}

int tamanho(lista_enc_t *lista){
    int aux = lista->tamanho;
    return aux;
}

int vazia(lista_enc_t *lista){
    if (lista->tamanho == 0){
        return 1;
    }
    else{
        return 0;
    }
}

no_t* obtem_cabeca(lista_enc_t *lista){

    if (lista == NULL){
        fprintf(stderr,"lista vazia");
        exit(EXIT_FAILURE);
    }

    no_t *p = lista->cabeca;
    return p;
}


void print_lista(lista_enc_t *lista)
{
    no_t *p = lista->cabeca;

    printf("\n[cabeca] =>");
    //comeca a imprimir do inicio
    while(p != NULL){
       char * dado = obtem_dado(p);
        printf("%s =>", dado);
        p = obtem_proximo(p);
    }
    printf("[NULL]\n");

}

