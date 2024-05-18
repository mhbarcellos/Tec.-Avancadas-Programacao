#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DESC 256
#define ARQUIVO_TAREFAS "tarefas.txt"

void obter_data_atual(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void adicionar_tarefa() {
    char data[11];
    char descricao[MAX_DESC];

    printf("Digite a data da tarefa (AAAA-MM-DD): ");
    scanf("%10s", data);
    getchar();

    printf("Digite a descrição da tarefa: ");
    fgets(descricao, MAX_DESC, stdin);
    descricao[strcspn(descricao, "\n")] = 0;

    FILE *arquivo = fopen(ARQUIVO_TAREFAS, "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fprintf(arquivo, "%s - %s\n", data, descricao);
    fclose(arquivo);

    printf("Tarefa adicionada com sucesso!\n");
}

void mostrar_tarefas_do_dia() {
    char hoje[11];
    obter_data_atual(hoje);

    printf("Tarefas para hoje (%s):\n", hoje);

    FILE *arquivo = fopen(ARQUIVO_TAREFAS, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char linha[MAX_DESC + 12];
    int encontrou_tarefas = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strncmp(linha, hoje, 10) == 0) {
            printf("%s", linha);
            encontrou_tarefas = 1;
        }
    }

    if (!encontrou_tarefas) {
        printf("Não há tarefas para hoje.\n");
    }

    fclose(arquivo);
}

void menu() {
    int opcao;
    while (1) {
        printf("\n1. Adicionar Tarefa\n");
        printf("2. Mostrar Tarefas do Dia\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                adicionar_tarefa();
                break;
            case 2:
                mostrar_tarefas_do_dia();
                break;
            case 3:
                printf("Saindo do programa.\n");
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
