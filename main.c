#include <stdio.h>
#include <stdlib.h>
#include "no.h"
#include "lista_enc.h"
#include "arvore.h"
int main()
{
    lista_enc_t *lista;
    lista = leitura_arquivo("flavors_of_cacao.csv");
    arvore_t *arvore = cria_arvore(1);               //cria a arvore
    no_t *p = obter_cabeca(lista);
    int count_id = 0;                               //variavel auxiliar para colocar os ids

   //----------------Loop de varredura da lista de chocolate e passa para a arvore
    while(p != NULL){
        chocolate_t *dados = obter_dado(p);
        arvore_adicionar_subarvore_id(arvore, count_id, dados);
        count_id++;
        p = obter_proximo(p);
    }

    //--------------Montagem da arvore
    arvore_montar_arvore(arvore);
    arvore_deleta_elemento_min(arvore);
    arvore_deleta_elemento_min(arvore);
    arvore_deleta_elemento_min(arvore);
    arvore_deleta_elemento_min(arvore);
    arvore_deleta_elemento_min(arvore);
   // arvore_achar_min(arvore);
    subarvore_t *teste = arvore_achar_min(arvore);
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

    exportar_arvore_dot("teste.dot", arvore);


    return 0;
}
