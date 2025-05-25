#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"
#include "structs.h"
#include <ctype.h>
#include "pontuacao.h"

void inputs_setas_espaco(Rectangle *player, int largura_tela, int velocidade_player,Raio raios_jogador[], int maximo_raios_tela_player, Sound laser_player) {
    if (IsKeyDown(KEY_RIGHT)) {
        player->x += velocidade_player;
        if (player->x + player->width > largura_tela) {
            player->x = largura_tela - player->width;
        }
    }
    if (IsKeyDown(KEY_LEFT)) {
        player->x -= velocidade_player;
        if (player->x < 0) {
            player->x = 0;
        }
    }

    if (IsKeyPressed(KEY_SPACE)) {
        for (int i = 0; i < maximo_raios_tela_player; i++) {
            if (!raios_jogador[i].ativo) {
                raios_jogador[i].ativo = 1;
                raios_jogador[i].posicao = (Vector2){player->x + player->width / 2, player->y};
                PlaySound(laser_player);
                break;
            }
        }
    }
}

void inputs_alpha(char nome_player[], int *letra_atual,Pontuacao_Player **pontuacoes, int nivel, int *game_over){
    int tecla = GetKeyPressed();
        if (isalpha(tecla)) {
            if (*letra_atual < LEN_NOME - 1) {
                nome_player[(*letra_atual)++] = (char) toupper(tecla);
            }
        }       
        else if (tecla == KEY_BACKSPACE) {
            if (*letra_atual > 0) {
                (*letra_atual)--;
                nome_player[*letra_atual] = '\0';
            }
        }
        else if (tecla == KEY_ENTER) {
            if (*letra_atual > 0) {
            nome_player[*letra_atual] = '\0'; 
            *pontuacoes = Adicionar_pontuacao(*pontuacoes, nome_player, nivel * 100);
            FILE *file = fopen("high_scores.txt", "w");
            if (file != NULL) {
                Pontuacao_Player *atual = *pontuacoes;
                while(atual != NULL){
                    fprintf(file, "%s %d\n", atual->nome, atual->pontuacao);
                    atual = atual->prox;
                }
                fclose(file);
            }
            *game_over = 2; 
        }
    }
}
#endif 