#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define RAIO_BOLA 10
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

    if(head == NULL || pontuacao > head->pontuacao){
        novo_no->prox = head;
        return novo_no;
    }

    Pontuacao_Player *atual = head;
    while(atual->prox != NULL && atual->prox->pontuacao >= pontuacao){
        atual = atual->prox;
    }
    novo_no->prox = atual->prox;
    atual->prox = novo_no;
    return head;
}

void salvar_pontuacoes(Pontuacao_Player *head, const char *arq){
    FILE *file = fopen(arq, "w");
    if (file == NULL){
        return;
    }
    Pontuacao_Player *atual = head;
    while(atual != NULL){
        fprintf(file, "%s %d\n", atual->nome, atual->pontuacao);
        atual = atual->prox;
    }
    fclose(file);
}

Pontuacao_Player *carregar_pontuacoes(const char *arq){
    FILE *file = fopen(arq, "r");
    if(file == NULL){
        return NULL;
    }

    Pontuacao_Player* head = NULL;
    char nome[LEN_NOME];
    int pontuacao;

    while( fscanf(file, "%s %d", nome, &pontuacao) == 2){
        head = Adicionar_pontuacao(head, nome, pontuacao);
    }
    fclose(file);
    return head;
}

int main(){
    int largura_tela = 900;
    int altura_tela = 700;
    int vidas_player = 3;
    int nivel = 1;
    int vidas_inimigo = 3;
    int direcao_inimigo = 1;
    int velocidade_player = 8;
    int velocidade_inimigo = 3;
    int game_over = 0;
    int digita_nome = 0;
    int letra_atual = 0;
    int timer_raio_inimigo = 0; 

    char nome_player[LEN_NOME] = {0};


    InitWindow(largura_tela, altura_tela, "VoidBall");
    SetTargetFPS(60);

    Pontuacao_Player *pontuacoes = carregar_pontuacoes("high_scores.txt");

    Rectangle player = { largura_tela / 2, altura_tela - 20, 100, 20 };

    Bola bola = {{ largura_tela / 2, altura_tela / 2},{4,-4}};

    Rectangle inimigo = { largura_tela / 2, 50, 80, 20};

    Raio raios_jogador[MAXIMO_RAIOS_TELA_PLAYER] = {0};

    Raio raios_inimigo[MAXIMO_RAIOS_TELA_INIMIGO] = {0};



    while(!WindowShouldClose()){
        if(game_over != 0 && digita_nome != 0){
            if(IsKeyPressed(KEY_SPACE)){
                for(int i = 0; i < MAXIMO_RAIOS_TELA_PLAYER; i++){
                    if(raios_jogador[i].ativo == 0){
                        raios_jogador[i].ativo = 1;
                        raios_jogador[i].posicao = (Vector2){player.x + player.width /2, player.y};
                    }
                }
            }           
            if(IsKeyDown(KEY_RIGHT)){
                player.x = player.x + velocidade_player;
            }
            if(IsKeyDown(KEY_LEFT)){
                player.x = player.x - velocidade_player;
            }
         
            bola.posicao.x = bola.posicao.x + bola.velocidade.x;
            bola.posicao.y = bola.posicao.y + bola.velocidade.y;

            
        }
    }


}   

