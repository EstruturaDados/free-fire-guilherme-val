#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao = -1;
    char linha[128];

    do {
        printf("\n==============================================\n");
        printf("      MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("==============================================\n");
        printf("Itens na Mochila: %d/%d\n", total, MAX_ITENS);
        printf("----------------------------------------------\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("0. Sair\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (!fgets(linha, sizeof(linha), stdin)) break;
        sscanf(linha, "%d", &opcao);

        switch (opcao) {
            case 1:
                if (total >= MAX_ITENS) {
                    printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
                } else {
                    printf("\n--- Adicionar Novo Item ---\n");

                    printf("Nome do item: ");
                    fgets(mochila[total].nome, sizeof(mochila[total].nome), stdin);
                    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';

                    printf("Tipo do item (arma, municao, cura, etc.): ");
                    fgets(mochila[total].tipo, sizeof(mochila[total].tipo), stdin);
                    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

                    printf("Quantidade: ");
                    if (fgets(linha, sizeof(linha), stdin)) {
                        mochila[total].quantidade = atoi(linha);
                    } else {
                        mochila[total].quantidade = 0;
                    }

                    total++;
                    printf("\nItem adicionado com sucesso!\n");
                }
                break;

            case 2:
                if (total == 0) {
                    printf("\nNenhum item para remover.\n");
                } else {
                    char nomeRemover[30];
                    int encontrado = 0;

                    printf("\n--- Remover Item ---\n");
                    printf("Digite o nome do item: ");
                    fgets(nomeRemover, sizeof(nomeRemover), stdin);
                    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

                    for (int i = 0; i < total; i++) {
                        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                            for (int j = i; j < total - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            total--;
                            encontrado = 1;
                            printf("\nItem removido com sucesso!\n");
                            break;
                        }
                    }
                    if (!encontrado)
                        printf("\nItem não encontrado.\n");
                }
                break;

            case 3:
                if (total == 0) {
                    printf("\nNenhum item cadastrado na mochila.\n");
                } else {
                    printf("\n--- Itens na Mochila ---\n");
                    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
                    printf("------------------------------------------------\n");
                    for (int i = 0; i < total; i++) {
                        printf("%-20s %-15s %-10d\n",
                            mochila[i].nome,
                            mochila[i].tipo,
                            mochila[i].quantidade);
                    }
                }
                break;

            case 0:
                printf("\nEncerrando sistema de mochila...\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
