#include <stdio.h>
#include <stdlib.h>
#include "chocolate.h"
#include "lista_enc.h"
#include "no.h"
#include <string.h>

struct chocolate_bar {
    char empresa[100];
    char nome_barra[100];
    unsigned int ref;
    unsigned int data_review;
    unsigned int percentual_cacau;
    char localizacao_empresa[100];
    float avaliacao;
    char tipo_grao[100];
    char origem_grao[100];

};

lista_enc_t *leitura_arquivo(char *arquivo){

    char empresa[100];
    char nome_barra[100];
    unsigned int ref;
    unsigned int data_review;
    unsigned int percentual_cacau;
    char localizacao_empresa;
    float avaliacao;
    char tipo_grao[100];
    char origem_grao[100];

    char buffer_aux[100];
    FILE *fp;
    chocolate_t *dados;
    lista_enc_t *lista;
    lista = cria_lista_enc();

    no_t *no;

    fp = fopen("flavors_of_cacao.csv", "r");

    if(fp == NULL){
        printf("nao foi possivel abrir o arquivo");
        return EXIT_FAILURE;
    }

    fgets(buffer_aux,sizeof(buffer_aux), fp);   //pula a primeira linha
    while(fgets(buffer_aux, sizeof(buffer_aux), fp) != NULL){
        sscanf(buffer_aux, "%[^,], %[^,], %u, %u, %u, %[^,], %f, %[^,], %[^\0]", empresa, nome_barra, &ref, &data_review, &percentual_cacau, localizacao_empresa, &avaliacao, tipo_grao, origem_grao);     //pega 1 linha
        dados = cria_chocolate_bar(empresa, nome_barra, ref, data_review, percentual_cacau, localizacao_empresa, avaliacao, tipo_grao, origem_grao);
        no = cria_no(dados);
        add_cauda(lista, no);

    }
    fclose(fp);
    return lista;
}

void imprime_arquivo(lista_enc_t *lista){
    no_t *p = obtem_cabeca(lista);
    while(p!= NULL){
        chocolate_t *dados = obtem_dado(p);
        printf("%s, %s, %u, %u, %u%%, %s, %f, %s, %s", dados->empresa, dados->nome_barra, dados->ref, dados->data_review, dados->percentual_cacau, dados->localizacao_empresa, dados->avaliacao, dados->tipo_grao, dados->origem_grao);
        p = obtem_proximo(p);
    }
    return ;
}

void libera_arquivo(lista_enc_t *lista){

    chocolate_t *dados;
    no_t *no = obtem_cabeca(lista);

    while(no){
        no_t *no_prox;
        dados = obtem_dado(no);
        free(dados);
        no_prox = obtem_proximo(no);
        free(no);
        no = no_prox;
    }
    free(lista);
}

chocolate_t* cria_chocolate_bar(char empresa[], char nome_barra[], unsigned int referencia, unsigned int data_review, unsigned int percentual_cacau, char localizacao_empresa[], unsigned int avaliacao, char tipo_grao[], char origem_grao[]){
    chocolate_t *dados = malloc(sizeof(chocolate_t));               //aloco memoria para a estrutura.

    //Inicializacao de variaveis

    strcpy(dados->empresa, empresa);
    strcpy(dados->nome_barra, nome_barra);
    dados->ref = referencia;
    dados->data_review = data_review;
    strcpy(dados->localizacao_empresa, localizacao_empresa);
    dados->percentual_cacau = percentual_cacau;
    dados->avaliacao = avaliacao;
    strcpy(dados->tipo_grao, tipo_grao);
    strcpy(dados->origem_grao,origem_grao);

    return dados;
}
