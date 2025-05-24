#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LARGURA_TELA 900
#define ALTURA_TELA 700
#define VELOCIDADE_PLAYER 8
#define RAIO_BOLA 10
#define LARGURA_INIMIGO 80
#define ALTURA_INIMIGO 200
#define MAXIMO_RAIOS_TELA_PLAYER 5
#define MAXIMO_RAIOS_TELA_INIMIGO 5
#define LEN_NOME 4
#define MAXIMO_SCORES_TELA 10

typedef struct{
    Vector2 posicao;
    Vector2 velocidade;
}Bola;

typedef struct{
    Vector2 posicao;
    int ativo;
}Raio;

typedef struct Pontuacao_Player {
    int score;
    char nome[LEN_NOME];
    struct Pontuacao_Player *prox
}Pontuacao_Player;
