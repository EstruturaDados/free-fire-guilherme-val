#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

void limparEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void adicionarItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\n⚠️  Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n=== ADICIONAR COMPONENTE ===\n");
    printf("Nome do item: ");
    limparEntrada();
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Tipo (Estrutural, Eletronico, Energia): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);
    if (novo.prioridade < 1 || novo.prioridade > 5) novo.prioridade = 1;

    mochila[*total] = novo;
    (*total)++;

    printf("\n✅ Item adicionado com sucesso!\n");
}

void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\n⚠️  Nenhum item na mochila para remover.\n");
        return;
    }

    char nome[30];
    printf("\n=== DESCARTAR COMPONENTE ===\n");
    printf("Nome do item a remover: ");
    limparEntrada();
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("\n🗑️  Item '%s' removido com sucesso!\n", nome);
            return;
        }
    }

    printf("\n❌ Item não encontrado!\n");
}

void listarItens(Item mochila[], int total) {
    printf("\n=== INVENTARIO ATUAL ===\n");
    if (total == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("%-20s %-15s %-12s %-10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%-20s %-15s %-12d %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }

    printf("\nTotal de componentes: %d/%d\n", total, MAX_ITENS);
}

void ordenarPorNome(Item mochila[], int total) {
    for (int i = 1; i < total; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].nome, chave.nome) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
    printf("\n✅ Mochila organizada por NOME!\n");
}

void ordenarPorTipo(Item mochila[], int total) {
    for (int i = 1; i < total; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].tipo, chave.tipo) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
    printf("\n✅ Mochila organizada por TIPO!\n");
}

void ordenarPorPrioridade(Item mochila[], int total) {
    for (int i = 1; i < total; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && mochila[j].prioridade > chave.prioridade) {
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
    printf("\n✅ Mochila organizada por PRIORIDADE!\n");
}

void organizarMochila(Item mochila[], int total, bool *ordenadoPorNome) {
    int opcao;
    printf("\n=== ORGANIZAR MOCHILA ===\n");
    printf("1. Ordenar por NOME\n");
    printf("2. Ordenar por TIPO\n");
    printf("3. Ordenar por PRIORIDADE\n");
    printf("0. Cancelar\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            ordenarPorNome(mochila, total);
            *ordenadoPorNome = true;
            break;
        case 2:
            ordenarPorTipo(mochila, total);
            *ordenadoPorNome = false;
            break;
        case 3:
            ordenarPorPrioridade(mochila, total);
            *ordenadoPorNome = false;
            break;
        case 0:
            printf("\nOperacao cancelada.\n");
            break;
        default:
            printf("\nOpcao invalida.\n");
    }
}

void buscaBinaria(Item mochila[], int total, bool ordenadoPorNome) {
    if (!ordenadoPorNome) {
        printf("\n⚠️  A mochila precisa estar ordenada por NOME para usar a busca binaria.\n");
        return;
    }

    if (total == 0) {
        printf("\n⚠️  Nenhum item para buscar.\n");
        return;
    }

    char nome[30];
    printf("\n=== BUSCA BINARIA ===\n");
    printf("Digite o nome do item: ");
    limparEntrada();
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    int inicio = 0, fim = total - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nome, mochila[meio].nome);
        if (cmp == 0) {
            printf("\n🔍 Item encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            return;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf("\n❌ Item nao encontrado.\n");
}

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    bool ordenadoPorNome = false;
    int opcao;

    printf("===============================================\n");
    printf("   PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
    printf("===============================================\n");

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarItem(mochila, &total); break;
            case 2: removerItem(mochila, &total); break;
            case 3: listarItens(mochila, total); break;
            case 4: organizarMochila(mochila, total, &ordenadoPorNome); break;
            case 5: buscaBinaria(mochila, total, ordenadoPorNome); break;
            case 0: printf("\n🚀 Torre de Fuga ativada! Fim da missao.\n"); break;
            default: printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
