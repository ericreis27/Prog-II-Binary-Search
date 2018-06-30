#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include "subarvore.h"

#define FALSE 0
#define TRUE 1

struct subarvore{
    int id;
    subarvore_t *pai;
    subarvore_t *direita;
    subarvore_t *esquerda;
    int dist;
    chocolate_t *dado;
};
//-----------------------------------------------------------------------


subarvore_t *cria_subarvore (int id)
{
    subarvore_t *subarvore = NULL;
    subarvore = (subarvore_t *) malloc(sizeof(subarvore_t));

    if (subarvore == NULL)	{
		perror("cria_subarvore:");
		exit(EXIT_FAILURE);
	}
	subarvore-> id = id;
	subarvore-> pai = NULL;
	subarvore-> direita = NULL;
	subarvore-> esquerda = NULL;

	return subarvore;
}
//-----------------------------------------------------------------------
void subarvore_set_pai(subarvore_t *subarvore, subarvore_t *pai)
{
    if (subarvore == NULL){
        fprintf(stderr, "subarvore_set_pai: subarvore invalido\n");
		exit(EXIT_FAILURE);
	}

    subarvore->pai = pai;
}
//-----------------------------------------------------------------------
void subarvore_set_esq(subarvore_t *subarvore, subarvore_t *esq)
{
    if (subarvore == NULL){
        fprintf(stderr, "subarvore_set_esq: subarvore invalido\n");
		exit(EXIT_FAILURE);
	}

    subarvore->esquerda = esq;
}
//-----------------------------------------------------------------------
void subarvore_set_dir(subarvore_t *subarvore, subarvore_t *dir)
{
    if (subarvore == NULL){
        fprintf(stderr, "subarvore_set_dir: subarvore invalido\n");
		exit(EXIT_FAILURE);
	}

    subarvore->direita = dir;
}
//-----------------------------------------------------------------------
void subarvore_set_dist (subarvore_t *subarvore, int distancia)
{
    if (subarvore == NULL)	{
		fprintf(stderr,"subarvore_set_dist: subarvore invalida!");
		exit(EXIT_FAILURE);
	}
	subarvore-> dist = distancia;
}
//-----------------------------------------------------------------------
subarvore_t * subarvore_get_esq(subarvore_t *subarvore)
{
    if (subarvore == NULL){
        fprintf(stderr, "subarvore_get_esq: subarvore invalido\n");
		exit(EXIT_FAILURE);
	}

    return subarvore->esquerda;
}
//-----------------------------------------------------------------------
subarvore_t * subarvore_get_dir(subarvore_t *subarvore)
{
    if (subarvore == NULL){
        fprintf(stderr, "subarvore_get_dir: subarvore invalido\n");
		exit(EXIT_FAILURE);
	}

    return subarvore->direita;
}

//-----------------------------------------------------------------------
int subarvore_get_id(subarvore_t *subarvore)
{
    if (subarvore == NULL){
        fprintf(stderr, "subarvore_get_id: subarvore invalido\n");
		exit(EXIT_FAILURE);
	}

    return subarvore->id;
}
//-----------------------------------------------------------------------
int subarvore_get_dist(subarvore_t *subarvore)
{
    if (subarvore == NULL){
        fprintf(stderr, "subarvore_get_dist: subarvore invalido\n");
		exit(EXIT_FAILURE);
	}

    return subarvore->dist;
}
//-----------------------------------------------------------------------
int verifica_subarvore_e_folha(subarvore_t *subarvore)
{
    if (subarvore == NULL){
        fprintf(stderr, "verifica_subarvore_e_folha: subarvore invalido\n");
		exit(EXIT_FAILURE);
	}
    if (subarvore_get_dir(subarvore) == NULL && subarvore_get_esq(subarvore) == NULL)
        return TRUE;
    return FALSE;
}


//-----------------------------------------------------------------------


chocolate_t* subarvore_get_dados(subarvore_t * subarvore){

    if (subarvore == NULL){
        fprintf(stderr, "subarvore_get_dados: subarvore invalido\n");
		exit(EXIT_FAILURE);
	}

    return subarvore->dado;

}


void subarvore_set_dados(subarvore_t * subarvore, chocolate_t* chocolate){

    if (subarvore == NULL){
        fprintf(stderr, "subarvore_set_dados: subarvore invalido\n");
		exit(EXIT_FAILURE);
	}

   subarvore->dado = chocolate;

}
