#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include "subarvore.h"
#include "chocolate.h"
typedef struct filas fila_t;

fila_t * cria_fila (void);
chocolate_t* dequeue_min(fila_t *fila);
chocolate_t* dequeue_max(fila_t *fila);
void enqueue_chocolate(chocolate_t* chocolate, fila_t *fila);

int fila_vazia(fila_t *fila);
void libera_fila(fila_t* fila);

#endif // FILA_H_INCLUDED
