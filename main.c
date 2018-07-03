#include <stdio.h>
#include <stdlib.h>
#include "no.h"
#include "lista_enc.h"
#include "arvore.h"
#include "fila.h"
//#define DEBUG
#define Exit 0
int main()
{


    lista_enc_t *lista;
    lista = leitura_arquivo("flavors_of_cacao.csv");
    no_t *p = obter_cabeca(lista);
    fila_t* fila = cria_fila();
    chocolate_t* chocolate;
    float rating;
    int escolha_usuario;

   //Loop de varredura da lista de chocolate e passa para a fila

    while(p != NULL){
        chocolate_t *dados = obter_dado(p);
        enqueue_chocolate(dados, fila);
        p = obter_proximo(p);
    }
    //Debug para impressao da lista
    #ifdef DEBUG
	imprime_lista_chocolate(lista);
    #endif

    //menu

    printf("Bem vindo a fila de prioridade com busca binaria!\n\n");

   //entrada do usuario

    while(1){
    printf("Gostaria de retirar o maior ou menor elemento: \n1 - Maior\n2 - Menor\n0 - Sair do programa\n");
    scanf("%d", &escolha_usuario);

    switch(escolha_usuario){

        case 1:
            chocolate = dequeue_max(fila);
            imprime_chocolate(chocolate);
            break;
        case 2:
            chocolate = dequeue_min(fila);
            imprime_chocolate(chocolate);
            break;
        case Exit:
            goto exit_switch;
        default:
            printf("entrada_invalida\n");
            exit(EXIT_FAILURE);

    }
    }
    exit_switch:           //label para sair do switch
    exportar_arvore_dot("teste.dot", fila_get_arvore(fila));
    libera_chocolate(lista);
    libera_fila(fila);


    return 0;
}
