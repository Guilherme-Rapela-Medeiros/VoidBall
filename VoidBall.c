#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define VELOCIDADE_PLAYER 8
#define RAIO_BOLA 10
#define LARGURA_INIMIGO 80
#define ALTURA_INIMIGO 20
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
    int pontuacao;
    char nome[LEN_NOME];
    struct Pontuacao_Player *prox;
}Pontuacao_Player;

Pontuacao_Player *Adicionar_pontuacao(Pontuacao_Player *head, const char *nome, int pontuacao){
    Pontuacao_Player *novo_no = (Pontuacao_Player*)malloc(sizeof(Pontuacao_Player));
    if(novo_no == NULL){
        return head;
    }
    strcpy(novo_no->nome, nome);
    novo_no->pontuacao = pontuacao;
    novo_no->prox = NULL;

    if(head == NULL){
        return novo_no;
    }

    Pontuacao_Player *atual = head;
    while(atual->prox != NULL){
        atual = atual->prox;
    }
    atual->prox = novo_no;
    return head;
}

int main(){
    int largura_tela = 900;
    int altura_tela = 700;

    InitWindow(largura_tela, altura_tela, "VoidBall");
    SetTargetFPS(60);

    Rectangle player = { largura_tela / 2, altura_tela - 20, 100, 20 };
    
}