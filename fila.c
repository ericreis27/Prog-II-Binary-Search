#include <stdlib.h>
#include <stdio.h>

#include "lista_enc.h"
#include "no.h"
#include "fila.h"
#include "arvore.h"
#include "subarvore.h"
#define FALSO 0
#define VERDADEIRO 1

struct filas {
	arvore_t* arvore;
	int count_id;
};


//cria uma pilha generica
fila_t * cria_fila (void)
{
	fila_t *p = (fila_t*)malloc(sizeof(fila_t));

    if (p == NULL) {
        fprintf(stderr, "Erro alocando dados em cria_fila!\n");
        exit(EXIT_FAILURE);
    }
    p->count_id = 0;
    p->arvore = cria_arvore(1);
    return p;
}





//adiciona elemento
void enqueue_chocolate(chocolate_t* chocolate, fila_t *fila){

     if (fila == NULL) {
        fprintf(stderr, "push: pilha invalida\n");
        exit(EXIT_FAILURE);
    }
    subarvore_t* subarvore = arvore_adicionar_subarvore_id(fila->arvore,fila->count_id, chocolate);


    arvore_inserir_chocolate(fila->arvore, chocolate_get_rating(chocolate), arvore_get_raiz(fila->arvore), subarvore);
    fila->count_id++;
}


chocolate_t* dequeue_max(fila_t *fila)
{
    chocolate_t* chocolate;
    subarvore_t* subarvore;
    if (fila == NULL){
        fprintf(stderr, "dequeue: fila invalida!\n");
        exit(EXIT_FAILURE);
    }

    subarvore = arvore_achar_max(fila->arvore);
    chocolate = subarvore_get_dados(subarvore);

    if(subarvore == arvore_get_raiz(fila->arvore)){
        arvore_set_raiz(fila->arvore, NULL);
    }
    arvore_deleta_elemento_max(fila->arvore);
    return chocolate;
}

chocolate_t* dequeue_min(fila_t *fila){
    subarvore_t* subarvore;
    chocolate_t* chocolate;
    if (fila == NULL){
        fprintf(stderr, "dequeue: fila invalida!\n");
        exit(EXIT_FAILURE);
    }

    subarvore = arvore_achar_min(fila->arvore);
    chocolate = subarvore_get_dados(subarvore);
    if(subarvore == arvore_get_raiz(fila->arvore)){
        arvore_set_raiz(fila->arvore, NULL);
    }
    arvore_deleta_elemento_min(fila->arvore);

    return chocolate;
}

void libera_fila(fila_t* fila){
    if (fila == NULL) {
        fprintf(stderr, "Erro em liberar_fila\n");
        exit(EXIT_FAILURE);
    }
    libera_arvore(fila->arvore);
    free(fila);

}

int fila_vazia(fila_t *fila)
{
    if (arvore_get_raiz(fila->arvore) == NULL) {
        fprintf(stderr, "fila_vazia: fila invalida\n");
        exit(EXIT_FAILURE);
    }

    if (arvore_get_raiz(fila->arvore) == NULL){
        return 1;
    }
    else{
        return 0;
    }
}


arvore_t* fila_get_arvore(fila_t* fila){

     if (fila == NULL){
        fprintf(stderr, "dequeue: fila invalida!\n");
        exit(EXIT_FAILURE);
    }

    return fila->arvore;

}
