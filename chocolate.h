#ifndef CHOCOLATE_H_INCLUDED
#define CHOCOLATE_H_INCLUDED

#include "lista_enc.h"
#include "no.h"

typedef struct chocolate_bar chocolate_t;
lista_enc_t *leitura_arquivo(char *arquivo);
void imprime_arquivo(lista_enc_t *lista);
void libera_arquivo(lista_enc_t *lista);
chocolate_t* cria_chocolate_bar(char empresa[], char nome_barra[], unsigned int referencia, unsigned int data_review, unsigned int percentual_cacau, char localizacao_empresa[], unsigned int avaliacao, char tipo_grao[], char origem_grao[]);

#endif // CHOCOLATE_H_INCLUDED
