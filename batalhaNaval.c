#include <stdio.h>

// Definindo constantes para o tamanho do tabuleiro e dos navios
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

int main() {
    // definindo tamanho do tabuleiro
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    
    // Coordenadas iniciais dos navios 
    int navio1_linha = 2;  
    int navio1_coluna = 3;  
    int navio2_linha = 6;   
    int navio2_coluna = 5;  
    
    // Inicializando o tabuleiro com 0 
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
    
    // Posicionando o navio horizontal
    for (int j = navio1_coluna; j < navio1_coluna + TAM_NAVIO; j++) {
        tabuleiro[navio1_linha][j] = 3;
    }
    
    // Posicionando o navio vertical 
    for (int i = navio2_linha; i < navio2_linha + TAM_NAVIO; i++) {
        tabuleiro[i][navio2_coluna] = 3;
    }
    
    // Exibindo o tabuleiro
    printf("\nTabuleiro de Batalha Naval:\n");
    printf("  "); // Espaço 
    // Imprimindo letras como colunas 
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2c ", 'A' + j); // Converte j para letra
    }
    printf("\n");
    
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i); // Imprime as linhas
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]); // Exibe 0 para água e 3 para navio
        }
        printf("\n");
    }
    
    return 0;
}
