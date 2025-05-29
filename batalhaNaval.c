#include <stdio.h>
#include <stdbool.h> // Para usar 'bool'

// Constantes para o tabuleiro e navios
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3 // Tamanho padrão dos navios

// Define as direções dos navios
typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_PRINCIPAL,
    DIAGONAL_SECUNDARIA
} DirecaoNavio;

// Inicializa o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Verifica se a posição está dentro do tabuleiro
bool ehPosicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAM_TABULEIRO && coluna >= 0 && coluna < TAM_TABULEIRO);
}

// Verifica se o navio pode ser posicionado
bool podePosicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, DirecaoNavio direcao, int tamanho_navio) {
    for (int k = 0; k < tamanho_navio; k++) {
        int l = linha;
        int c = coluna;

        // Calcula a próxima posição do navio
        switch (direcao) {
            case HORIZONTAL:
                c += k;
                break;
            case VERTICAL:
                l += k;
                break;
            case DIAGONAL_PRINCIPAL:
                l += k;
                c += k;
                break;
            case DIAGONAL_SECUNDARIA:
                l += k;
                c -= k;
                break;
        }

        // Checa limites e sobreposição
        if (!ehPosicaoValida(l, c) || tabuleiro[l][c] == 3) {
            return false;
        }
    }
    return true; // Posição válida e livre
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, DirecaoNavio direcao, int tamanho_navio) {
    for (int k = 0; k < tamanho_navio; k++) {
        int l = linha;
        int c = coluna;

        // Calcula a próxima posição do navio
        switch (direcao) {
            case HORIZONTAL:
                c += k;
                break;
            case VERTICAL:
                l += k;
                break;
            case DIAGONAL_PRINCIPAL:
                l += k;
                c += k;
                break;
            case DIAGONAL_SECUNDARIA:
                l += k;
                c -= k;
                break;
        }
        tabuleiro[l][c] = 3; // Marca a posição com o navio
    }
}

// Exibe o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval:\n");
    printf("   "); // Espaço para alinhar
    // Imprime letras das colunas
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2c ", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i); // Imprime números das linhas
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]); // Exibe 0 (água) ou 3 (navio)
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // --- Posicionamento dos Navios ---

    // Navio 1: Horizontal
    int navio1_linha = 2;
    int navio1_coluna = 3;
    if (podePosicionarNavio(tabuleiro, navio1_linha, navio1_coluna, HORIZONTAL, TAM_NAVIO)) {
        posicionarNavio(tabuleiro, navio1_linha, navio1_coluna, HORIZONTAL, TAM_NAVIO);
    } else {
        printf("Erro ao posicionar Navio 1 (Horizontal).\n");
    }

    // Navio 2: Vertical
    int navio2_linha = 6;
    int navio2_coluna = 5;
    if (podePosicionarNavio(tabuleiro, navio2_linha, navio2_coluna, VERTICAL, TAM_NAVIO)) {
        posicionarNavio(tabuleiro, navio2_linha, navio2_coluna, VERTICAL, TAM_NAVIO);
    } else {
        printf("Erro ao posicionar Navio 2 (Vertical).\n");
    }

    // Navio 3: Diagonal Principal
    int navio3_linha = 0;
    int navio3_coluna = 0;
    if (podePosicionarNavio(tabuleiro, navio3_linha, navio3_coluna, DIAGONAL_PRINCIPAL, TAM_NAVIO)) {
        posicionarNavio(tabuleiro, navio3_linha, navio3_coluna, DIAGONAL_PRINCIPAL, TAM_NAVIO);
    } else {
        printf("Erro ao posicionar Navio 3 (Diagonal Principal).\n");
    }

    // Navio 4: Diagonal Secundária
    int navio4_linha = 1;
    int navio4_coluna = 8;
    if (podePosicionarNavio(tabuleiro, navio4_linha, navio4_coluna, DIAGONAL_SECUNDARIA, TAM_NAVIO)) {
        posicionarNavio(tabuleiro, navio4_linha, navio4_coluna, DIAGONAL_SECUNDARIA, TAM_NAVIO);
    } else {
        printf("Erro ao posicionar Navio 4 (Diagonal Secundária).\n");
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
