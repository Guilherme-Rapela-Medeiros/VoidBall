#ifndef STRUCTS_H
#define STRUCTS_H

#include "raylib.h"

#define LEN_NOME  4

typedef struct{
    Vector2 posicao;
    Vector2 velocidade;
}Bola;

typedef struct{
    Vector2 posicao;
    int ativo;
}Raio;

typedef struct Pontuacao_Player {
    int pontuacao;
    char nome[LEN_NOME];
    struct Pontuacao_Player *prox;
}Pontuacao_Player;

#endif