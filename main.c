#include <stdio.h>
#include <stdlib.h>
#include "no.h"
#include "lista_enc.h"
int main()
{
   lista_enc_t *lista;
   lista = leitura_arquivo("flavors_of_cacao.csv");
  // imprime_arquivo(lista);
   libera_arquivo(lista);

   return 0;
}
