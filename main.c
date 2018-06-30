#include <stdio.h>
#include <stdlib.h>
#include "no.h"
#include "lista_enc.h"
#include "arvore.h"
int main()
{
    lista_enc_t *lista;
    lista = leitura_arquivo("flavors_of_cacao.csv");
    int x;
    //imprime_chocolate(lista);
    arvore_t *arvore = cria_arvore(x);               //cria a arvore
    no_t *p = obter_cabeca(lista);                  //loop de varredura da lista
    int count_id = 0;
    while(p != NULL){
        chocolate_t *dados = obter_dado(p);
        arvore_adicionar_subarvore_id(arvore, count_id, dados);
        count_id++;
        p = obtem_proximo(p);
    }
    arvore_montar_arvore(arvore);
    exportar_arvore_dot("teste.dot", arvore);


    return 0;
}
