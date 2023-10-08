#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"

#define HASH_SIZE 7
#define CLIENTS_FILENAME "clientes.dat"
#define HASH_FILENAME "tabHash.dat"

// Função para criar novo cliente
Cliente* criarCLiente(int codCliente, char* nome){
    Cliente *cliente = (Cliente*) malloc(sizeof(Cliente));
    cliente->codCliente - (char*) malloc(strlen(codCliente)+1);
    cliente->nome - (char*) malloc(strlen(nome)+1);
    strcpy(cliente->codCliente, codCliente);
    strcpy(cliente->nome, nome);
    cliente->status = 1;
    cliente->prox = -1;

    return cliente;
}

// Função para buscar um cliente pelo código
Cliente* buscar(FILE* hash, FILE* clientes, int codCliente) {
    int pos;
    rewind(hash);

    // Calcula a posição na tabela hash com base no código do cliente
    pos = codCliente % 7;

    // Move o ponteiro para a posição na tabela hash
    fseek(hash, sizeof(int) * pos, SEEK_SET);

    // Lê o valor na posição da tabela hash
    fread(&pos, sizeof(int), 1, hash);

    if (pos == -1) {
        // Não há cliente com esse código
        return NULL;
    }

    // Move o ponteiro para a posição do cliente nos registros
    fseek(clientes, sizeof(Cliente) * pos, SEEK_SET);

    // Lê o cliente na posição especificada
    Cliente* cliente = (Cliente*)malloc(sizeof(Cliente));
    fread(cliente->codCliente, sizeof(int), 1, clientes);
    fread(cliente->nome, sizeof(char), strlen(cliente->nome) + 1, clientes);
    fread(&cliente->status, sizeof(int), 1, clientes);
    fread(&cliente->prox, sizeof(int), 1, clientes);

    return cliente;
}


// Função para inserir um novo cliente
void inserir(FILE* hash, FILE* fimFila, FILE* clientes, Cliente* valorChave){
    int pos, cont;
    
    // Verificar se existe um cliente com essa chave
    Cliente *existeCliente = (Cliente*) malloc(sizeof(Cliente));

    pos = valorChave->codCliente % 7; // Posição inicial dentro da hash

    existeCliente = buscar(hash, cliente, valorChave->codCliente);
    if(existeCliente->codCliente == valorChave->codCliente){ // codCliente já está sendo utilizado
        // Pode possuir um printf
        free(existeCliente);

        return 0;
    }

    // Resetando o ponteiro para o início e busca a posição objetivo
    rewind(hash);
    fseek(hash, sizeof(int)* (pos), SEEK_SET);
    fread(&pos, sizeof(int), 1, hash);

    rewind(fimFila);
    fread(&cont, sizeof(int), 1, fimFila);
    
    int auxiliar = 0;
    if(pos != -1){
        while(auxiliar == 0){
            rewind(cliente);
            fseek(clientes, sizeof(Cliente)* pos, SEEK_SET);

            fread(&existeCliente->codCliente, sizeof(int), 1, clientes);
            fread(existeCliente->nome, sizeof(char), sizeof(existeCliente->codCliente), clientes);
            fread(&existeCliente->status, sizeof(int), 1, clientes);
            fread(&existeCliente->prox, sizeof(int), 1, clientes);

            if(existeCliente->status == 0){ // Local vazio
                auxiliar = 2;
            } else if(existeCliente->prox == -1){ // Fim da fila
                auxiliar = 1;
                fseek(clientes, sizeof(int)*-1, SEEK_SET);
                fwrite(&cont, sizeof(int), 1, clientes);
            } else {
                pos = existeCliente->prox; // Recebe o ponteiro para o próximo
            }

            rewind(clientes);

            fseek(clientes, sizeof(Cliente)*pos, SEEK_SET);
            fwrite(&valorChave->codCliente, sizeof(int), 1, clientes);
            fwrite(valorChave->nome, sizeof(char), sizeof(valorChave->nome), clientes);
            fwrite(&info->status, sizeof(int), 1, clientes);

            if(auxiliar != 2){
                fwrite(&valorChave->prox, sizeof(int), 1, clientes);
                contador++;
                // Pode incluir um printf
            }

        }

    }

}

void zerar() {
    FILE *nhash;
    FILE *nmeta;

    int a = -1;
    int b;

    if ((nhash = fopen(HASH_FILENAME, "wb")) == NULL) {
        printf("Erro ao abrir o arquivo da tabela hash\n");
        exit(1);
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        fwrite(&a, sizeof(int), 1, nhash);
    }
    fclose(nhash);

    if ((nhash = fopen(HASH_FILENAME, "ab")) == NULL) {
        printf("Erro ao abrir o arquivo da tabela clientes\n");
        exit(1);
    }

    rewind(nhash);
    for (int i = 0; i < HASH_SIZE; i++) {
        fread(&b, sizeof(int), 1, nhash);
        printf("hash: %d \n", b);
    }
    printf("Arquivo hash zerado\n");

    if ((nmeta = fopen("meta.dat", "wb")) == NULL) {
        printf("Erro ao abrir o arquivo da tabela meta\n");
        exit(1);
    }

    rewind(nmeta);
    int cont = 0;
    fwrite(&cont, sizeof(int), 1, nmeta);

    fclose(nmeta);

    if ((nmeta = fopen("meta.dat", "ab")) == NULL) {
        printf("Erro ao abrir o arquivo da tabela meta\n");
        exit(1);
    }

    rewind(nmeta);

    fread(&cont, sizeof(int), 1 ,nmeta);
    printf("Contador zerado %d ", cont);

    fclose(nhash);
    fclose(nmeta);
}