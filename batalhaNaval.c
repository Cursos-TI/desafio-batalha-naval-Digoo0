#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Para 'abs' (valor absoluto)

// Constantes do jogo
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Constantes para tamanhos das habilidades
#define TAM_HABILIDADE_CONE 5
#define TAM_HABILIDADE_CRUZ 5
#define TAM_HABILIDADE_OCTAEDRO 5

// Direções de navios
typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_PRINCIPAL,
    DIAGONAL_SECUNDARIA
} DirecaoNavio;

// Inicializa o tabuleiro com 0
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Checa se a posição é válida no tabuleiro
bool ehPosicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAM_TABULEIRO && coluna >= 0 && coluna < TAM_TABULEIRO);
}

// Verifica se navio pode ser posicionado (limites e sobreposição)
bool podePosicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, DirecaoNavio direcao, int tamanho_navio) {
    for (int k = 0; k < tamanho_navio; k++) {
        int l = linha;
        int c = coluna;
        switch (direcao) {
            case HORIZONTAL: c += k; break;
            case VERTICAL: l += k; break;
            case DIAGONAL_PRINCIPAL: l += k; c += k; break;
            case DIAGONAL_SECUNDARIA: l += k; c -= k; break;
        }
        if (!ehPosicaoValida(l, c) || tabuleiro[l][c] == 3) {
            return false;
        }
    }
    return true;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, DirecaoNavio direcao, int tamanho_navio) {
    for (int k = 0; k < tamanho_navio; k++) {
        int l = linha;
        int c = coluna;
        switch (direcao) {
            case HORIZONTAL: c += k; break;
            case VERTICAL: l += k; break;
            case DIAGONAL_PRINCIPAL: l += k; c += k; break;
            case DIAGONAL_SECUNDARIA: l += k; c -= k; break;
        }
        tabuleiro[l][c] = 3;
    }
}

// --- Habilidades Especiais ---

// Cria matriz do efeito Cone
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE_CONE][TAM_HABILIDADE_CONE]) {
    for (int i = 0; i < TAM_HABILIDADE_CONE; i++) {
        for (int j = 0; j < TAM_HABILIDADE_CONE; j++) {
            habilidade[i][j] = 0;
            int centro = TAM_HABILIDADE_CONE / 2;
            int inicio_coluna = centro - i;
            int fim_coluna = centro + i;

            if (j >= inicio_coluna && j <= fim_coluna && inicio_coluna >= 0 && fim_coluna < TAM_HABILIDADE_CONE) {
                 habilidade[i][j] = 1;
            }
        }
    }
}

// Cria matriz do efeito Cruz
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE_CRUZ][TAM_HABILIDADE_CRUZ]) {
    for (int i = 0; i < TAM_HABILIDADE_CRUZ; i++) {
        for (int j = 0; j < TAM_HABILIDADE_CRUZ; j++) {
            habilidade[i][j] = 0;
            int centro = TAM_HABILIDADE_CRUZ / 2;
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Cria matriz do efeito Octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE_OCTAEDRO][TAM_HABILIDADE_OCTAEDRO]) {
    for (int i = 0; i < TAM_HABILIDADE_OCTAEDRO; i++) {
        for (int j = 0; j < TAM_HABILIDADE_OCTAEDRO; j++) {
            habilidade[i][j] = 0;
            int centro = TAM_HABILIDADE_OCTAEDRO / 2;
            int dist_manhattan = abs(i - centro) + abs(j - centro);
            if (dist_manhattan <= centro) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Sobrepõe habilidade Cone no tabuleiro
void sobreporHabilidadeConeNoTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE_CONE][TAM_HABILIDADE_CONE], int origem_linha, int origem_coluna) {
    int metade_habilidade = TAM_HABILIDADE_CONE / 2;
    for (int i = 0; i < TAM_HABILIDADE_CONE; i++) {
        for (int j = 0; j < TAM_HABILIDADE_CONE; j++) {
            int tab_linha = origem_linha - metade_habilidade + i;
            int tab_coluna = origem_coluna - metade_habilidade + j;
            if (habilidade[i][j] == 1 && ehPosicaoValida(tab_linha, tab_coluna) && tabuleiro[tab_linha][tab_coluna] != 3) {
                tabuleiro[tab_linha][tab_coluna] = 5;
            }
        }
    }
}

// Sobrepõe habilidade Cruz no tabuleiro
void sobreporHabilidadeCruzNoTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE_CRUZ][TAM_HABILIDADE_CRUZ], int origem_linha, int origem_coluna) {
    int metade_habilidade = TAM_HABILIDADE_CRUZ / 2;
    for (int i = 0; i < TAM_HABILIDADE_CRUZ; i++) {
        for (int j = 0; j < TAM_HABILIDADE_CRUZ; j++) {
            int tab_linha = origem_linha - metade_habilidade + i;
            int tab_coluna = origem_coluna - metade_habilidade + j;
            if (habilidade[i][j] == 1 && ehPosicaoValida(tab_linha, tab_coluna) && tabuleiro[tab_linha][tab_coluna] != 3) {
                tabuleiro[tab_linha][tab_coluna] = 5;
            }
        }
    }
}

// Sobrepõe habilidade Octaedro no tabuleiro
void sobreporHabilidadeOctaedroNoTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE_OCTAEDRO][TAM_HABILIDADE_OCTAEDRO], int origem_linha, int origem_coluna) {
    int metade_habilidade = TAM_HABILIDADE_OCTAEDRO / 2;
    for (int i = 0; i < TAM_HABILIDADE_OCTAEDRO; i++) {
        for (int j = 0; j < TAM_HABILIDADE_OCTAEDRO; j++) {
            int tab_linha = origem_linha - metade_habilidade + i;
            int tab_coluna = origem_coluna - metade_habilidade + j;
            if (habilidade[i][j] == 1 && ehPosicaoValida(tab_linha, tab_coluna) && tabuleiro[tab_linha][tab_coluna] != 3) {
                tabuleiro[tab_linha][tab_coluna] = 5;
            }
        }
    }
}

// Exibe o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval com Habilidades:\n");
    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%c ", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0)      printf(". "); // Água
            else if (tabuleiro[i][j] == 3) printf("N "); // Navio
            else if (tabuleiro[i][j] == 5) printf("X "); // Habilidade
            else                           printf("? "); // Inesperado
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int habilidade_cone[TAM_HABILIDADE_CONE][TAM_HABILIDADE_CONE];
    int habilidade_cruz[TAM_HABILIDADE_CRUZ][TAM_HABILIDADE_CRUZ];
    int habilidade_octaedro[TAM_HABILIDADE_OCTAEDRO][TAM_HABILIDADE_OCTAEDRO];

    inicializarTabuleiro(tabuleiro);

    // Posiciona navios
    if (podePosicionarNavio(tabuleiro, 2, 3, HORIZONTAL, TAM_NAVIO)) posicionarNavio(tabuleiro, 2, 3, HORIZONTAL, TAM_NAVIO);
    else printf("Erro ao posicionar Navio 1 (Horizontal).\n");

    if (podePosicionarNavio(tabuleiro, 6, 5, VERTICAL, TAM_NAVIO)) posicionarNavio(tabuleiro, 6, 5, VERTICAL, TAM_NAVIO);
    else printf("Erro ao posicionar Navio 2 (Vertical).\n");

    if (podePosicionarNavio(tabuleiro, 0, 0, DIAGONAL_PRINCIPAL, TAM_NAVIO)) posicionarNavio(tabuleiro, 0, 0, DIAGONAL_PRINCIPAL, TAM_NAVIO);
    else printf("Erro ao posicionar Navio 3 (Diagonal Principal).\n");

    if (podePosicionarNavio(tabuleiro, 1, 8, DIAGONAL_SECUNDARIA, TAM_NAVIO)) posicionarNavio(tabuleiro, 1, 8, DIAGONAL_SECUNDARIA, TAM_NAVIO);
    else printf("Erro ao posicionar Navio 4 (Diagonal Secundaria).\n");

    // Cria e sobrepõe habilidades
    criarHabilidadeCone(habilidade_cone);
    criarHabilidadeCruz(habilidade_cruz);
    criarHabilidadeOctaedro(habilidade_octaedro);

    sobreporHabilidadeConeNoTabuleiro(tabuleiro, habilidade_cone, 4, 4);
    sobreporHabilidadeCruzNoTabuleiro(tabuleiro, habilidade_cruz, 7, 2);
    sobreporHabilidadeOctaedroNoTabuleiro(tabuleiro, habilidade_octaedro, 3, 8);

    exibirTabuleiro(tabuleiro);

    return 0;
}
