#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "compartimento_hash.h"

int main() {
    FILE* tabHash;
    FILE* clientes;

    // Abre os arquivos no modo r+b
    tabHash = fopen("tabHash.dat", "r+b");
    clientes = fopen("clientes.dat", "r+b");

    if (tabHash == NULL || clientes == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        exit(1);
    }

    // Inicializa a tabela hash (você pode implementar essa parte)

    // Exemplo de inserção de cliente
    Cliente* novoCliente1 = criarCliente(1, "Cliente1");
    Cliente* novoCliente2 = criarCliente(2, "Cliente2");

    inserir(tabHash, NULL, clientes, novoCliente1);
    inserir(tabHash, NULL, clientes, novoCliente2);

    // Exemplo de tentativa de inserir um cliente com o mesmo código
    Cliente* clienteExistente = criarCliente(1, "ClienteExistente");
    inserir(tabHash, NULL, clientes, clienteExistente);

    // Teste de zerar
    zerar(tabHash, clientes);

    // Fechar os arquivos
    fclose(tabHash);
    fclose(clientes);

    // Liberar a memória alocada para os clientes
    free(novoCliente1->codCliente);
    free(novoCliente1->nome);
    free(novoCliente1);
    free(novoCliente2->codCliente);
    free(novoCliente2->nome);
    free(novoCliente2);
    free(clienteExistente->codCliente);
    free(clienteExistente->nome);
    free(clienteExistente);

    return 0;
}