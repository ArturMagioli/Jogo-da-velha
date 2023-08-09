#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define TAM 3

///Reveza a vez entre os dois jogadores.
int vezDoJogador(int option){
    if (option == 1)
        return 5;
    else
        return 1;
}

///Printa o tabuleiro.
void printTabuleiro(int tab[TAM][TAM], int p1, int p2, int ganhou) {
    int i, j;
    system("cls");
    printf("JOGO DA VELHA\n\n");
    printf("+-----+-----+-----+\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            if ( (i == p1) && (j == p2) && (ganhou == 0) )
                printf("|  #  ");

                else if (tab[i][j] == 0)
                    printf("|     ");

                    else if (tab[i][j] == 1)
                        printf("|  X  ");

                        else if (tab[i][j] == 5)
                            printf("|  O  ");
        }
        printf("|\n+-----+-----+-----+\n");
    }
}

///Funções de movimento do cursor para cima, baixo, esquerda e direita, respectivamente.
int cima(int tab[TAM][TAM], int posicaoAtualLinha, int posicaoAtualColuna, int resultados1) {
    posicaoAtualLinha--;
    return posicaoAtualLinha;
}

int baixo(int tab[TAM][TAM], int posicaoAtualLinha, int posicaoAtualColuna, int resultados1) {
    posicaoAtualLinha++;
    return posicaoAtualLinha;
}

int esquerda(int tab[TAM][TAM], int posicaoAtualLinha, int posicaoAtualColuna, int resultados1) {
    posicaoAtualColuna--;
    return posicaoAtualColuna;
}

int direita(int tab[TAM][TAM], int posicaoAtualLinha, int posicaoAtualColuna, int resultados1) {
    posicaoAtualColuna++;
    return posicaoAtualColuna;
}

///Estabelece o limite da movimentação "esquerda" e "cima".
int verificaPraTras(int limite) {
    if (limite == 0)
        return 0;
    else
        return 1;
}

///Estabelece o limite da movimentação "direita" e "baixo".
int verificaPraFrente(int limite) {
    if (limite == 2)
        return 0;
    else
        return 1;
}

///Verifica se o quadrado escolhido não está ocupado.
int verificaEscolha(int tab[TAM][TAM], int posicaoLinhaAtual, int posicaoColunaAtual) {
    if (tab[posicaoLinhaAtual][posicaoColunaAtual] == 0)
        return 1;
    else
        return 0;
}

///Verifica se houve alguma vitória
int condicaoDeVitoria(int tab[TAM][TAM]) {
    int i, j, somaPorLinha, somaPorColuna, somaDiagonalPrincipal = 0, somaDiagonalSecundaria = 0;

    for (i = 0; i < TAM; i++) {
        somaPorColuna = 0;
        somaPorLinha = 0;
        for (j = 0; j < TAM; j++) {
            somaPorLinha += tab[i][j];
            somaPorColuna += tab[j][i];
            if (i == j)
                somaDiagonalPrincipal += tab[i][j];
            if (i + j == TAM - 1)
                somaDiagonalSecundaria += tab[i][j];
        }
        if ( (somaPorLinha == 3) || (somaPorColuna == 3) || (somaDiagonalPrincipal == 3) || (somaDiagonalSecundaria == 3) )
            return 1;
        else if ( (somaPorLinha == 15) || (somaPorColuna == 15) || (somaDiagonalPrincipal == 15) || (somaDiagonalSecundaria == 15) )
            return 2;
    }
    return 0;
}

int main() {

    int tabuleiro[TAM][TAM] = {0, 0, 0,
                               0, 0, 0,
                               0, 0, 0,};

    int p1 = 1, p2 = 1, rodada = 1, movimentoValido, quadradosDisponiveis = 9, resultado = 0;

    printTabuleiro(tabuleiro, p1, p2, resultado);

    while (quadradosDisponiveis != 0) {
        if (rodada == 1)
            printf("Jogador 1: \n\n");
        else
            printf("Jogador 2: \n\n");

        int movimento = _getch();
        if (movimento == 13) {
            movimentoValido = verificaEscolha(tabuleiro, p1, p2);
            if (movimentoValido == 1) {
                tabuleiro[p1][p2] = rodada;
                rodada = vezDoJogador(rodada);
                printTabuleiro(tabuleiro, p1, p2, resultado);
                quadradosDisponiveis--;
                resultado = condicaoDeVitoria(tabuleiro);
                if (resultado == 1) {
                    printTabuleiro(tabuleiro, p1, p2, resultado);
                    printf("Jogador 1 venceu!");
                    break;
                }
                else if (resultado == 2) {
                    printTabuleiro(tabuleiro, p1, p2, resultado);
                    printf("Jogador 2 venceu!");
                    break;
                }
            } else
                printf("Aqui não pode");

        }
        else if (movimento == 0 || movimento == 224) {
            movimento = _getch();

            switch (movimento) {
                case 72:
                    movimentoValido = verificaPraTras(p1);
                    if (movimentoValido == 1)
                        p1 = cima(tabuleiro, p1, p2, resultado);
                    printTabuleiro(tabuleiro, p1, p2, resultado);
                    break;

                case 80:
                    movimentoValido = verificaPraFrente(p1);
                    if (movimentoValido == 1)
                        p1 = baixo(tabuleiro, p1, p2, resultado);
                    printTabuleiro(tabuleiro, p1, p2, resultado);
                    break;

                case 75:
                    movimentoValido = verificaPraTras(p2);
                    if (movimentoValido == 1)
                        p2 = esquerda(tabuleiro, p1, p2, resultado);
                    printTabuleiro(tabuleiro, p1, p2, resultado);
                    break;

                case 77:
                    movimentoValido = verificaPraFrente(p2);
                    if (movimentoValido == 1)
                        p2 = direita(tabuleiro, p1, p2, resultado);
                    printTabuleiro(tabuleiro, p1, p2, resultado);
                    break;
            }
          }
    }
    if (resultado == 0)
        printf("\nDeu velha!");
    return 0;
}
