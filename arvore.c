#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include "lista_enc.h"
#include "no.h"
#include "subarvore.h"
#include "arvore.h"
#include "chocolate.h"
#define FALSE 0
#define TRUE 1

#define INFINITY INT_MAX

#define DEBUG

struct arvore{
    int id;
    subarvore_t *raiz;
    lista_enc_t *subarvores;
};
//-----------------------------------------------------------------------
arvore_t *cria_arvore (int id)
{
    arvore_t *arvore = NULL;
    arvore = (arvore_t*) malloc (sizeof (arvore_t));

	if (arvore == NULL)	{
		perror("cria_arvore:");
		exit(EXIT_FAILURE);
	}

	arvore->id = id;
	arvore->subarvores = cria_lista_enc();
	arvore->raiz = NULL;

	return arvore;

}
//-----------------------------------------------------------------------
subarvore_t * arvore_adicionar_subarvore_id(arvore_t *arvore, int id, chocolate_t *chocolate)
{
    subarvore_t *subarvore = NULL;
    no_t *no;

    #ifdef DEBUG
	printf("arvore_adicionar_subarvore_id: %d\n", id);
    #endif

    if (arvore == NULL)	{
        fprintf(stderr,"arvore_adicionar_subarvore_id: arvore invalida!");
        exit(EXIT_FAILURE);
	}

	if (procura_subarvore(arvore, id) != NULL) {
		fprintf(stderr,"arvore_adicionar_subarvore_id: subarvore duplicada!\n");
		exit(EXIT_FAILURE);
	}

	subarvore = cria_subarvore(id);
    subarvore_set_dados(subarvore, chocolate);           //inicializacao do chocolate
	no = cria_no(subarvore);
	add_cauda(arvore->subarvores, no);
	return subarvore;

}
//-----------------------------------------------------------------------
subarvore_t *procura_subarvore (arvore_t *arvore, int id)
{
    no_t *no_lista;
	subarvore_t *subarvore;
	int meu_id;

	if (arvore == NULL)	{
		fprintf(stderr,"procura_arvore: arvore invalida!");
		exit(EXIT_FAILURE);
	}

	if (lista_vazia(arvore->subarvores) == TRUE)
		return FALSE;

	no_lista = obter_cabeca(arvore->subarvores);

	while (no_lista)
	{
		//obter o endereco da lista
		subarvore = obter_dado(no_lista);

		//obterm o id do arvore
		meu_id = subarvore_get_id(subarvore);

		if (meu_id == id) {
			return subarvore;
		}

		no_lista = obter_proximo(no_lista);
	}

	return NULL;
}
//-----------------------------------------------------------------------
void arvore_adiciona_filhos(arvore_t *arvore, subarvore_t *subarvore, int esq, int dir)
{
    if (arvore == NULL)	{
		fprintf(stderr,"arvore_adiciona_filhos: arvore invalida!");
		exit(EXIT_FAILURE);
	}
	subarvore_t *direita;
	subarvore_t *esquerda;

	if (esq != -1){
		esquerda = procura_subarvore(arvore, esq);
		subarvore_set_pai(esquerda, subarvore);
		subarvore_set_esq(subarvore, esquerda);
        #ifdef DEBUG
        printf(" pai: %d, esq: %d\n", subarvore_get_id(subarvore), subarvore_get_id(subarvore_get_esq(subarvore)));
        #endif // DEBUG
	}

	if (dir != -1){
		direita = procura_subarvore(arvore, dir);
		subarvore_set_pai(direita, subarvore);
		subarvore_set_dir(subarvore, direita);
		#ifdef DEBUG
        printf(" pai: %d, dir: %d\n", subarvore_get_id(subarvore), subarvore_get_id(subarvore_get_dir(subarvore)));
        #endif // DEBUG
	}
}
//-----------------------------------------------------------------------
void libera_arvore (arvore_t *arvore)
{
    no_t *no_subarvore;
	no_t *no_proximo;
	subarvore_t *subarvore;

	if (arvore == NULL) {
		fprintf(stderr, "libera_arvore: arvore invalidao\n");
		exit(EXIT_FAILURE);
	}

	//varre todos os subarvores
	no_subarvore = obter_cabeca(arvore->subarvores);
	while (no_subarvore){
		subarvore = obter_dado(no_subarvore);
		no_proximo = obter_proximo(no_subarvore);
		free(subarvore);
		free(no_subarvore);
		no_subarvore = no_proximo;
	}
	free(arvore->subarvores);
	free(arvore);
}
//-----------------------------------------------------------------------
void arvore_set_raiz (arvore_t * arvore, subarvore_t *subarvore)
{
    if (arvore == NULL)	{
		fprintf(stderr,"arvore_set_raiz: arvore invalida!");
		exit(EXIT_FAILURE);
	}
	arvore->raiz = subarvore;
}
//-----------------------------------------------------------------------

lista_enc_t *arvore_obter_subarvores (arvore_t *arvore)
{
    if (arvore == NULL)	{
		fprintf(stderr,"arvore_obter_subarvores: arvore invalida!");
		exit(EXIT_FAILURE);
	}
	return arvore->subarvores;
}
//-----------------------------------------------------------------------
void preordem_recursiva(subarvore_t *subarvore, FILE *file)
{
    if (subarvore == NULL)	{
		return;
	}

    if (subarvore_get_esq(subarvore) != NULL)
        fprintf(file, "%d -- %d\n", subarvore_get_id(subarvore), subarvore_get_id(subarvore_get_esq(subarvore)));

    if (subarvore_get_dir(subarvore) != NULL)
        fprintf(file, "%d -- %d\n", subarvore_get_id(subarvore), subarvore_get_id(subarvore_get_dir(subarvore)));

	preordem_recursiva (subarvore_get_esq(subarvore), file);

	preordem_recursiva (subarvore_get_dir(subarvore), file);

}
//-----------------------------------------------------------------------
void posordem_recursiva (subarvore_t *subarvore)
{
    if (subarvore == NULL)	{
		return;
	}
	posordem_recursiva(subarvore_get_esq(subarvore));
	posordem_recursiva(subarvore_get_dir(subarvore));

	#ifdef DEBUG
	printf("id : %d\n", subarvore_get_id(subarvore));
	#endif // DEBUG
}
//-----------------------------------------------------------------------
void emordem_recursiva (subarvore_t *subarvore)
{
    if (subarvore == NULL)	{
		return;
	}

	emordem_recursiva(subarvore_get_esq(subarvore));
	#ifdef DEBUG
	printf("id : %d\n", subarvore_get_id(subarvore));
	#endif // DEBUG
	emordem_recursiva(subarvore_get_dir(subarvore));
}
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
void exportar_arvore_dot(const char *filename, arvore_t *arvore)
{
	FILE *file;

	if (filename == NULL || arvore == NULL){
		fprintf(stderr, "exportar_arvore_dot: ponteiros invalidos\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(filename, "w");

	if (file == NULL){
		perror("exportar_arvore_dot:");
		exit(EXIT_FAILURE);
	}

	fprintf(file, "arvore {\n");
    preordem_recursiva(arvore->raiz, file);
	fprintf(file, "}\n");
	fclose(file);
}

void arvore_montar_arvore(arvore_t *arvore){
    subarvore_t* subarvore;
    subarvore_t* aux;
    chocolate_t* chocolate_aux1;
    chocolate_t* chocolate_aux2;
    float rating_1;
    float rating_2;

    no_t* p = obter_cabeca(arvore->subarvores);
    subarvore = obter_dado(p);          //pego a primeira, seto como raiz e pulo ela e vai para a proxima
    p = obter_proximo(p);               //ja aponta para o proximo elemento e em subarvore tem o primeiro chocolate
    arvore_set_raiz(arvore, subarvore);
    while(p != NULL){                   // loop de varredura
        aux  = arvore->raiz;
        subarvore = obter_dado(p);
        chocolate_aux1 = subarvore_get_dados(subarvore);
        rating_1 = chocolate_get_rating(chocolate_aux1);

        while(1){

            chocolate_aux2 = subarvore_get_dados(aux);
            rating_2= chocolate_get_rating(chocolate_aux2);

            if(rating_1 > rating_2){

                if(subarvore_get_dir(aux) == NULL){
                    subarvore_set_dir(aux, subarvore);
                    subarvore_set_pai(subarvore, aux);
                    break;
                }
                else{
                    aux = subarvore_get_dir(aux);

                }
            }
            else{

                if(subarvore_get_esq(aux) == NULL){
                    subarvore_set_esq(aux, subarvore);
                    subarvore_set_pai(subarvore, aux);
                    break;
                }
                else{
                    aux = subarvore_get_esq(aux);
                }
            }

        }

        p = obter_proximo(p);
    }

}

subarvore_t* arvore_achar_min(arvore_t* arvore){
    float rating;
    subarvore_t* aux = arvore->raiz;
    chocolate_t* dado;
    int id = 0;
    while(subarvore_get_esq(aux) != NULL){                   // loop de varredura

        //dado = subarvore_get_dados(aux);
       //rating = chocolate_get_rating(dado);
       // id = subarvore_get_id(aux);
       // printf("\n\nid:%d", id);

        //printf("\nnota: %.2f", rating);
        aux = subarvore_get_esq(aux);
        //int id_prox_esq = subarvore_get_id(aux);
        //printf("\nid proximo esquerda: %d", id_prox_esq);
    }

        /*dado = subarvore_get_dados(aux);
        rating = chocolate_get_rating(dado);
        id = subarvore_get_id(aux);
        printf("\n\nid:%d", id);

        printf("\nnota: %.2f", rating);
        aux = subarvore_get_esq(aux);*/
        return aux;
}



subarvore_t* arvore_achar_max(arvore_t* arvore){

    subarvore_t* aux = arvore->raiz;

    while(subarvore_get_dir(aux) != NULL){                   // loop de varredura
        aux = subarvore_get_dir(aux);
    }

        return aux;
}


void arvore_deleta_elemento_min(arvore_t* arvore){
    subarvore_t* aux_subarvore;
    subarvore_t* aux_pai_subarvore;
    subarvore_t* subarvore = arvore_achar_min(arvore);
    int id = subarvore_get_id(subarvore);
    printf("\n\nid:%d\n", id);

    if(((subarvore_get_dir(subarvore) == NULL)) && ((subarvore_get_esq(subarvore)) == NULL)){
        printf("\nsem filhos\n");
        aux_subarvore = subarvore;                  //salva a subarvore atual
        subarvore = subarvore_get_pai(subarvore);   //salva na subarvore
        subarvore_set_esq(subarvore, NULL);
    }

    if((subarvore_get_dir(subarvore) != NULL)){
        printf("\n1 filho_direita");
        aux_subarvore = subarvore;   //salva a subarvore atual
        aux_pai_subarvore = subarvore_get_pai(subarvore);
        subarvore = subarvore_get_dir(subarvore);
        subarvore_set_dir(aux_pai_subarvore, subarvore);
        subarvore_set_pai(subarvore, aux_pai_subarvore);
        subarvore_set_dir(aux_subarvore, NULL);
        subarvore_set_pai(aux_subarvore, NULL);

    }

     printf("\n----------------------------------------");
}

