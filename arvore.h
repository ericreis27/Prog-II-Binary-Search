#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED
#include "lista_enc.h"
#include "subarvore.h"

typedef struct arvore arvore_t;

arvore_t *cria_arvore (int id);

subarvore_t * arvore_adicionar_subarvore_id(arvore_t *arvore, int id, chocolate_t *chocolate);
subarvore_t *procura_subarvore (arvore_t *arvore, int id);
void libera_arvore (arvore_t *arvore);
void arvore_adiciona_filhos(arvore_t *arvore, subarvore_t *filho, int esq, int dir);
void arvore_set_raiz (arvore_t * arvore, subarvore_t *subarvore);
lista_enc_t *arvore_obter_subarvores (arvore_t *arvore);
void exportar_arvore_dot(const char *filename, arvore_t *arvore);

//percorrendo arvores: profundidade
void preordem_recursiva(subarvore_t *subarvore, FILE *file);
void posordem_recursiva (subarvore_t *subarvore);
void emordem_recursiva (subarvore_t *subarvore);
void arvore_montar_arvore(arvore_t *arvore);
//percorrendo arvores: largura
void largura (arvore_t *arvore);

#endif // ARVORE_H_INCLUDED
