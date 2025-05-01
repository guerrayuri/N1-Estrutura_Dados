#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cinema.h"

char salas[MAX_FILMES][ROWS][COLS];
Bilhete bilhetes[MAX_TICKETS];
int totalBilhetes = 0;
int contadorBilhete = 1;
Filme filmes[MAX_FILMES] = {
    {"Ainda estou aqui", 2024},
    {"Divertidamente 2", 2024},
    {"A forja", 2024},
    {"Deadpool e Wolverine", 2024},
    {"Duna: Parte 2", 2024}
};

void inicializarSalas() {
    for (int f = 0; f < MAX_FILMES; f++) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                salas[f][i][j] = 'D';
            }
        }
    }
}

void inicializarSistema() {
    inicializarSalas();
}

void exibirSala(int filmeIndex) {
    printf("\nSala do filme: %s\n", filmes[filmeIndex].nome);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("[%c] ", salas[filmeIndex][i][j]);
        }
        printf("\n");
    }
}

void listarFilmes() {
    printf("\nFilmes disponiveis (ordenados por ano de lancamento):\n");
    for (int i = 0; i < MAX_FILMES - 1; i++) {
        for (int j = 0; j < MAX_FILMES - i - 1; j++) {
            if (filmes[j].anoLancamento > filmes[j + 1].anoLancamento) {
                Filme temp = filmes[j];
                filmes[j] = filmes[j + 1];
                filmes[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < MAX_FILMES; i++) {
        printf("%d. %s (%d)\n", i + 1, filmes[i].nome, filmes[i].anoLancamento);
    }
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void reservarLugar() {
    int escolhaFilme;
    char cliente[50];
    int linha, coluna;
    int tipo;

    listarFilmes();
    printf("\nEscolha o filme (1-%d): ", MAX_FILMES);
    scanf("%d", &escolhaFilme);

    if (escolhaFilme < 1 || escolhaFilme > MAX_FILMES) {
        printf("Filme invalido!\n");
        return;
    }

    int filmeIndex = escolhaFilme - 1;
    exibirSala(filmeIndex);

    printf("Escolha a linha (0-%d): ", ROWS - 1);
    scanf("%d", &linha);
    printf("Escolha a coluna (0-%d): ", COLS - 1);
    scanf("%d", &coluna);

    if (salas[filmeIndex][linha][coluna] == 'X') {
        printf("Assento ja reservado!\n");
        return;
    }

    printf("Digite o nome do cliente: ");
    limparBuffer();
    fgets(cliente, sizeof(cliente), stdin);
    cliente[strcspn(cliente, "\n")] = 0;

    printf("Tipo de ingresso (1 - Inteira / 2 - Meia): ");
    scanf("%d", &tipo);

    salas[filmeIndex][linha][coluna] = 'X';

    Bilhete novoBilhete;
    novoBilhete.numero = contadorBilhete++;
    strcpy(novoBilhete.cliente, cliente);
    strcpy(novoBilhete.filme, filmes[filmeIndex].nome);
    novoBilhete.linha = linha;
    novoBilhete.coluna = coluna;
    novoBilhete.idFilme = filmeIndex;
    strcpy(novoBilhete.tipoIngresso, tipo == 1 ? "Inteira" : "Meia");

    bilhetes[totalBilhetes++] = novoBilhete;

    printf("Bilhete gerado com sucesso! Numero do bilhete: %d\n", novoBilhete.numero);
}

void ordenarBilhetesPorNumero(int crescente) {
    for (int i = 0; i < totalBilhetes - 1; i++) {
        for (int j = 0; j < totalBilhetes - i - 1; j++) {
            if ((crescente && bilhetes[j].numero > bilhetes[j + 1].numero) ||
                (!crescente && bilhetes[j].numero < bilhetes[j + 1].numero)) {
                Bilhete temp = bilhetes[j];
                bilhetes[j] = bilhetes[j + 1];
                bilhetes[j + 1] = temp;
            }
        }
    }
}

void ordenarBilhetesPorTipo() {
    for (int i = 0; i < totalBilhetes - 1; i++) {
        for (int j = 0; j < totalBilhetes - i - 1; j++) {
            if (strcmp(bilhetes[j].tipoIngresso, bilhetes[j + 1].tipoIngresso) > 0) {
                Bilhete temp = bilhetes[j];
                bilhetes[j] = bilhetes[j + 1];
                bilhetes[j + 1] = temp;
            }
        }
    }
}

void imprimirBilhete(int numero) {
    ordenarBilhetesPorNumero(1);
    int inicio = 0, fim = totalBilhetes - 1, meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (bilhetes[meio].numero == numero) {
            printf("\n=== Bilhete Encontrado ===\n");
            printf("Numero: %d\n", bilhetes[meio].numero);
            printf("Cliente: %s\n", bilhetes[meio].cliente);
            printf("Filme: %s\n", bilhetes[meio].filme);
            printf("Lugar: Linha %d, Coluna %d\n", bilhetes[meio].linha, bilhetes[meio].coluna);
            printf("Tipo: %s\n", bilhetes[meio].tipoIngresso);
            return;
        } else if (bilhetes[meio].numero < numero) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("Bilhete nao encontrado.\n");
}

void listarBilhetes() {
    int opcao;
    printf("\nEscolha a ordenacao:\n");
    printf("1. Numero do bilhete (crescente)\n");
    printf("2. Numero do bilhete (decrescente)\n");
    printf("3. Tipo de ingresso (Inteira/Meia)\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            ordenarBilhetesPorNumero(1);
            break;
        case 2:
            ordenarBilhetesPorNumero(0);
            break;
        case 3:
            ordenarBilhetesPorTipo();
            break;
        default:
            printf("Opcao invalida! Listando sem ordenacao.\n");
    }

    printf("\nLista de Bilhetes:\n");
    for (int i = 0; i < totalBilhetes; i++) {
        printf("Numero: %d, Cliente: %s, Filme: %s, Tipo: %s\n",
               bilhetes[i].numero, bilhetes[i].cliente,
               bilhetes[i].filme, bilhetes[i].tipoIngresso);
    }
}

void menu() {
    int opcao;
    int numero;
    do {
        printf("\n===== Sistema de Bilheteria =====\n");
        printf("1. Reservar lugar\n");
        printf("2. Exibir sala de cinema\n");
        printf("3. Imprimir bilhete\n");
        printf("4. Listar bilhetes\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                reservarLugar();
                break;
            case 2: {
                listarFilmes();
                int filmeEscolhido;
                printf("Escolha o filme (1-%d): ", MAX_FILMES);
                scanf("%d", &filmeEscolhido);
                if (filmeEscolhido >= 1 && filmeEscolhido <= MAX_FILMES)
                    exibirSala(filmeEscolhido - 1);
                else
                    printf("Filme invalido!\n");
                break;
            }
            case 3:
                printf("Digite o numero do bilhete: ");
                scanf("%d", &numero);
                imprimirBilhete(numero);
                break;
            case 4:
                listarBilhetes();
                break;
            case 0:
                printf("Encerrando o sistema.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}
