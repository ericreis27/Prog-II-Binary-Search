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
//#define DEBUG


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

	fprintf(file, "graph {\n");
    preordem_recursiva(arvore->raiz, file);
	fprintf(file, "}\n");
	fclose(file);
}

//----------------------------------------------------------------------------------------------------------------------------
subarvore_t* arvore_achar_min(arvore_t* arvore){


    subarvore_t* aux = arvore->raiz;
    while(subarvore_get_esq(aux) != NULL){                   // loop de varredura

        #ifdef DEBUG                    //mostra o caminho percorrido ate o menor elemento e as avaliacoes.
        float rating;                   //Obs: ele mostra 2 vezes porque a funcao eh chamada 2 vezes ao deletar um elemento.
        chocolate_t*dado;
        int id = 0;
         dado = subarvore_get_dados(aux);
       rating = chocolate_get_rating(dado);
        id = subarvore_get_id(aux);
        printf("\n\nid:%d", id);
        printf("\nnota: %.2f", rating);
        #endif

        aux = subarvore_get_esq(aux);
    }
        return aux;
}


//--------------------------------------------------------------------------------------------------------------------------------
subarvore_t* arvore_achar_max(arvore_t* arvore){

    subarvore_t* aux = arvore->raiz;

    while(subarvore_get_dir(aux) != NULL){                   // loop de varredura


        #ifdef DEBUG                    //mostra o caminho percorrido ate o maior elemento e as avaliacoes.
        float rating;                   //Obs: ele mostra 2 vezes porque a funcao eh chamada 2 vezes ao deletar um elemento.
        chocolate_t*dado;
        int id = 0;
        dado = subarvore_get_dados(aux);
        rating = chocolate_get_rating(dado);
        id = subarvore_get_id(aux);
        printf("\n\nid:%d", id);
        printf("\nnota: %.2f", rating);
        #endif

        aux = subarvore_get_dir(aux);

    }

        return aux;
}

//-----------------------------------------------------------------------------------------------------------------------------
void arvore_deleta_elemento_min(arvore_t* arvore){
    subarvore_t* aux_subarvore;
    subarvore_t* aux_pai_subarvore;
    subarvore_t* subarvore = arvore_achar_min(arvore);

    #ifdef DEBUG
    int id = subarvore_get_id(subarvore);
    printf("\n\nID menor numero:%d\n", id);
    #endif //Debug

    if((subarvore_get_dir(subarvore) == NULL) && (subarvore_get_esq(subarvore) == NULL)){
        #ifdef DEBUG
        printf("\nQuantidade de filhos: sem filhos\n");
        #endif //Debug

        aux_pai_subarvore = subarvore_get_pai(subarvore);   //salva na subarvore
        subarvore_set_esq(aux_pai_subarvore, NULL);
    }

    if((subarvore_get_dir(subarvore) != NULL)){
        #ifdef DEBUG
        printf("\nQuantidade de filhos: 1 filho direita\n");
        #endif //Debug

        aux_subarvore = subarvore;   //salva a subarvore atual
        aux_pai_subarvore = subarvore_get_pai(subarvore);
        subarvore = subarvore_get_dir(subarvore);
        subarvore_set_dir(aux_pai_subarvore, subarvore);
        subarvore_set_pai(subarvore, aux_pai_subarvore);
        subarvore_set_esq(aux_pai_subarvore, NULL);
        subarvore_set_dir(aux_subarvore, NULL);
        subarvore_set_pai(aux_subarvore, NULL);

    }

}
//------------------------------------------------------------------------------------------------------------------------------

void arvore_deleta_elemento_max(arvore_t* arvore){
    subarvore_t* aux_subarvore;
    subarvore_t* aux_pai_subarvore;
    subarvore_t* subarvore = arvore_achar_max(arvore);

        #ifdef DEBUG
        int id = subarvore_get_id(subarvore);
        printf("\n\nID maior numero:%d\n", id);
        #endif //Debug

    if((subarvore_get_dir(subarvore) == NULL) && (subarvore_get_esq(subarvore) == NULL)){
        #ifdef DEBUG
        printf("\nQuantidade de filhos: sem filhos\n");
        #endif //Debug

        aux_pai_subarvore = subarvore_get_pai(subarvore);   //salva na subarvore
        subarvore_set_dir(aux_pai_subarvore, NULL);
    }

    if((subarvore_get_esq(subarvore) != NULL)){
        #ifdef DEBUG
        printf("\nQuantidade de filhos: 1 filho esquerda\n");
        #endif //Debug

        aux_subarvore = subarvore;   //salva a subarvore atual
        aux_pai_subarvore = subarvore_get_pai(subarvore);
        subarvore = subarvore_get_esq(subarvore);
        subarvore_set_dir(aux_pai_subarvore, subarvore);
        subarvore_set_pai(subarvore, aux_pai_subarvore);
        subarvore_set_esq(aux_subarvore, NULL);
        subarvore_set_pai(aux_subarvore, NULL);

    }
}

void arvore_inserir_chocolate(arvore_t* arvore, float rating_1, subarvore_t* aux, subarvore_t* subarvore){
    chocolate_t* chocolate_aux2;
    float rating_2;

    if(arvore_get_raiz(arvore) == NULL){
        arvore_set_raiz(arvore, subarvore);
        return;
    }

    while(1){

        chocolate_aux2 = subarvore_get_dados(aux);
        rating_2= chocolate_get_rating(chocolate_aux2);
        if(rating_1 > rating_2)
        {

            if(subarvore_get_dir(aux) == NULL) {
                subarvore_set_dir(aux, subarvore);
                subarvore_set_pai(subarvore, aux);
                break;
            }
            else {
                aux = subarvore_get_dir(aux);

            }
        }
        else
        {

            if(subarvore_get_esq(aux) == NULL) {
                subarvore_set_esq(aux, subarvore);
                subarvore_set_pai(subarvore, aux);
                break;
            }
            else {
                aux = subarvore_get_esq(aux);
            }
        }

    }

 }

subarvore_t* arvore_get_raiz(arvore_t* arvore){


    if (arvore == NULL){
        fprintf(stderr, "subarvore_get_raiz: arvore invalida\n");
		exit(EXIT_FAILURE);
	}

    return arvore->raiz;

}






