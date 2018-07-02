#include <stdio.h>
#include <stdlib.h>
#include "no.h"
#include "lista_enc.h"
#include "arvore.h"
#include "fila.h"

int main()
{
    lista_enc_t *lista;
    lista = leitura_arquivo("flavors_of_cacao.csv");
    no_t *p = obter_cabeca(lista);
    fila_t* fila = cria_fila();
    chocolate_t* chocolate;
    float rating;

   //----------------Loop de varredura da lista de chocolate e passa para a arvore
    while(p != NULL){
        chocolate_t *dados = obter_dado(p);
        enqueue_chocolate(dados, fila);
        p = obter_proximo(p);
    }


    dequeue_min(fila);
    dequeue_min(fila);
    dequeue_min(fila);
    dequeue_min(fila);
    dequeue_min(fila);
    chocolate = dequeue_min(fila);
    rating = chocolate_get_rating(chocolate);
    printf("\n%f", rating);

    chocolate = dequeue_max(fila);
    chocolate = dequeue_max(fila);
    rating = chocolate_get_rating(chocolate);
    printf("\nrating: %f", rating);




    //--------------Montagem da arvore
    //arvore_montar_arvore(arvore);

    /*arvore_deleta_elemento_min(arvore);
    arvore_deleta_elemento_min(arvore);
    arvore_deleta_elemento_min(arvore);
    arvore_deleta_elemento_min(arvore);
    arvore_deleta_elemento_min(arvore);*/
    //arvore_deleta_elemento_max(arvore);
    //arvore_achar_max(arvore);
   // arvore_achar_min(arvore);
    //subarvore_t *teste = arvore_achar_min(arvore);
    //subarvore_t *teste2 = arvore_achar_max(arvore);
    //teste = subarvore_get_esq(teste);
    //int id = subarvore_get_id(teste);
    //printf("id proximo esquerda: %d", id);

/*
    //teste de achar maximo e minimo

    /*subarvore_t *teste = arvore_achar_min(arvore);
    int id = subarvore_get_id(teste);
    printf("\n\nid min:%d\n", id);
    teste = arvore_achar_max(arvore);
    id = subarvore_get_id(teste);
    printf("id max:%d", id);

    arvore_deleta_elemento_min(arvore);
    arvore_deleta_elemento_min(arvore);
    arvore_deleta_elemento_min(arvore);
    arvore_deleta_elemento_min(arvore);

    subarvore_t *teste = arvore_achar_min(arvore);
    int id = subarvore_get_id(teste);
    printf("\n\nid min:%d\n", id);
*/

    exportar_arvore_dot("teste.dot", fila_get_arvore(fila));


    return 0;
}
