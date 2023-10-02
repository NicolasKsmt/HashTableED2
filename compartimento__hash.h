#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

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
                pos = cont; // posicao é ajustada para o final do arquivo
            } else {
                pos = existeCliente->prox; // Recebe o ponteiro para o próximo
            }
        }
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
