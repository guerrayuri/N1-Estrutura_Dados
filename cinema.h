#ifndef CINEMA_H
#define CINEMA_H

#define ROWS 5
#define COLS 5
#define MAX_TICKETS 100
#define MAX_FILMES 5

typedef struct {
    int numero;
    char cliente[50];
    char filme[50];
    int linha;
    int coluna;
    char tipoIngresso[10];
    int idFilme;
} Bilhete;

typedef struct {
    char nome[50];
    int anoLancamento;
} Filme;

void inicializarSistema();
void exibirSala(int filmeIndex);
void listarFilmes();
void reservarLugar();
void imprimirBilhete(int numero);
void listarBilhetes();
void menu();

#endif // CINEMA_H
