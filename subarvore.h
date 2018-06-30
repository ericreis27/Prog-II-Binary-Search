#ifndef SUBARVORE_H_INCLUDED
#define SUBARVORE_H_INCLUDED
#include "chocolate.h"
typedef struct subarvore subarvore_t;

subarvore_t *cria_subarvore (int id);
void subarvore_set_pai(subarvore_t *subarvore, subarvore_t *pai);
void subarvore_set_esq(subarvore_t *subarvore, subarvore_t *esq);
void subarvore_set_dir(subarvore_t *subarvore, subarvore_t *dir);
void subarvore_set_dist (subarvore_t *subarvore, int distancia);
subarvore_t * subarvore_get_esq(subarvore_t *subarvore);
subarvore_t * subarvore_get_dir(subarvore_t *subarvore);
int subarvore_get_id(subarvore_t *subarvore);
int subarvore_get_dist(subarvore_t *subarvore);
int verifica_subarvore_e_folha(subarvore_t *subarvore);
chocolate_t* subarvore_get_dados(subarvore_t * subarvore);


#endif // SUBARVORE_H_INCLUDED
