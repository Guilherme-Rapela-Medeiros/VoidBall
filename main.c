#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "structs.h"
#include "pontuacao.h"
#include "inputs.h"

#define LEN_NOME 4
#define MAX_RAIOS_TELA_PLAYER 100
#define MAX_RAIOS_TELA_INIMIGO 100

float mais_velocidade(float velocidade){
      if (velocidade > 0) {
        return velocidade + 0.25f;
    } else {
        return velocidade - 0.25f;
    }
}

int main(){
    
    float dados_niveis[100][2] = {
    {3, 3.00}, {3, 3.35}, {3, 3.70}, {3, 4.05}, {3, 4.40},
    {4, 4.75}, {4, 5.10}, {4, 5.45}, {4, 5.80}, {4, 6.15},
    {5, 6.50}, {5, 6.85}, {5, 7.20}, {5, 7.55}, {5, 7.90},
    {6, 8.25}, {6, 8.60}, {6, 8.95}, {6, 9.30}, {6, 9.65},
    {7, 10.00}, {7, 10.35}, {7, 10.70}, {7, 11.05}, {7, 11.40},
    {8, 11.75}, {8, 12.10}, {8, 12.45}, {8, 12.80}, {8, 13.15},
    {9, 13.50}, {9, 13.85}, {9, 14.20}, {9, 14.55}, {9, 14.90},
    {10, 15.25}, {10, 15.60}, {10, 15.95}, {10, 16.30}, {10, 16.65},
    {11, 17.00}, {11, 17.35}, {11, 17.70}, {11, 18.05}, {11, 18.40},
    {12, 18.75}, {12, 19.10}, {12, 19.45}, {12, 19.80}, {12, 20.15},
    {13, 20.50}, {13, 20.85}, {13, 21.20}, {13, 21.55}, {13, 21.90},
    {14, 22.25}, {14, 22.60}, {14, 22.95}, {14, 23.30}, {14, 23.65},
    {15, 24.00}, {15, 24.35}, {15, 24.70}, {15, 25.05}, {15, 25.40},
    {16, 25.75}, {16, 26.10}, {16, 26.45}, {16, 26.80}, {16, 27.15},
    {17, 27.50}, {17, 27.85}, {17, 28.20}, {17, 28.55}, {17, 28.90},
    {18, 29.25}, {18, 29.60}, {18, 29.95}, {18, 30.30}, {18, 30.65},
    {19, 31.00}, {19, 31.35}, {19, 31.70}, {19, 32.05}, {19, 32.40},
    {20, 32.75}, {20, 33.10}, {20, 33.45}, {20, 33.80}, {20, 34.15},
    {21, 34.50}, {21, 34.85}, {21, 35.20}, {21, 35.55}, {21, 35.90},
    {22, 36.25}, {22, 36.60}, {22, 36.95}, {22, 37.30}, {22, 37.65}};
    int i;
    int largura_tela = 900;
    int altura_tela = 700;
    int vidas_player = 3;
    int raio_bola = 10;
    int nivel = 1;
    int nivel_maximo = 99;
    int vidas_inimigo = dados_niveis[0][0];
    int direcao_inimigo = 1;
    int velocidade_player = 8;
    int velocidade_inimigo = dados_niveis[0][1];
    int game_over = 0;
    int maximo_raios_tela_player = 5;
    int maximo_raios_tela_inimigo = 5;
    int letra_atual = 0;
    int largura_inimigo = 80;
    int altura_inimigo = 20;
    int largura_player = 100;
    int altura_player = 20;

    float timer_raio_inimigo = 0;
    float intervalo_raio_inimigo = 1.5f;

    char nome_player[LEN_NOME] = {0};

    InitWindow(largura_tela, altura_tela, "VoidBall");
    InitAudioDevice();
    SetTargetFPS(60);

    Sound laser_player = LoadSound("sounds/laser_player.ogg");

    Sound level_up = LoadSound("sounds/level_up.mp3");

    Sound sound_explosion = LoadSound("sounds/sound_explosion.ogg");

    Sound sound_game_over = LoadSound("sounds/sound_game_over.mp3");

    Texture2D background = LoadTexture("images/void_imagem.png");

    Pontuacao_Player *pontuacoes = carregar_pontuacoes("high_scores.txt");

    Rectangle player = { largura_tela / 2, altura_tela - 20, largura_player, altura_player };

    Bola bola = {{ largura_tela / 2, altura_tela / 2},{4,-4}};

    Rectangle inimigo = { largura_tela / 2, 50, largura_inimigo, altura_inimigo};

    Raio raios_jogador[MAX_RAIOS_TELA_PLAYER] = {0};

    Raio raios_inimigo[MAX_RAIOS_TELA_INIMIGO] = {0};

    while(!WindowShouldClose()){
        if(game_over == 0 ){
            inimigo.x += velocidade_inimigo * direcao_inimigo;
            if(inimigo.x < 0 || inimigo.x + largura_inimigo >= largura_tela){
                direcao_inimigo = direcao_inimigo * -1;
            }

            inputs_setas_espaco(&player, largura_tela, velocidade_player,raios_jogador, maximo_raios_tela_player,laser_player);
         
            bola.posicao.x = bola.posicao.x + bola.velocidade.x;
            bola.posicao.y = bola.posicao.y + bola.velocidade.y;

            if(bola.posicao.x >= largura_tela - raio_bola || bola.posicao.x <= raio_bola){
                bola.velocidade.x = bola.velocidade.x * -1;
            }
            if(bola.posicao.y <= raio_bola){
                bola.velocidade.y = bola.velocidade.y * -1;
            }

            if(bola.posicao.y >= altura_tela + raio_bola){
                vidas_player = vidas_player - 1;
                bola.posicao = (Vector2){largura_tela/2, altura_tela/2};
                bola.velocidade = (Vector2){4,-4};
                if(vidas_player == 0){
                    game_over = 1;
                    letra_atual = 0;
                    PlaySound(sound_game_over);
                    memset(nome_player, '\0', LEN_NOME);
                }
            }

            if(CheckCollisionCircleRec(bola.posicao, raio_bola, player)){
                bola.velocidade.y = bola.velocidade.y * -1; 
                bola.posicao.y = player.y - raio_bola;
            }
            if(CheckCollisionCircleRec(bola.posicao, raio_bola, inimigo)){
                bola.velocidade.y =  bola.velocidade.y * -1;
                bola.posicao.y = inimigo.y + inimigo.height + raio_bola;

                vidas_inimigo = vidas_inimigo - 1;

                if(vidas_inimigo == 0){
                    nivel = nivel + 1;
                    intervalo_raio_inimigo -= 0.01f;
                    PlaySound(level_up);
                
                    if (nivel > nivel_maximo){
                        game_over = 1;
                        PlaySound(sound_game_over);
                        
                    }else{
                        vidas_inimigo = dados_niveis[nivel - 1][0];
                        velocidade_inimigo = dados_niveis[nivel - 1][1];
                    }    
                    bola.velocidade.x = mais_velocidade(bola.velocidade.x);
                    bola.velocidade.y = mais_velocidade(bola.velocidade.y);
                }
            }
            
            if(GetTime() - timer_raio_inimigo >= intervalo_raio_inimigo){
                for( i = 0; i < maximo_raios_tela_inimigo; i++){
                    if(raios_inimigo[i].ativo == 0){
                        raios_inimigo[i].ativo = 1;
                        raios_inimigo[i].posicao = (Vector2){inimigo.x + inimigo.width/2, inimigo.y + inimigo.height};
                        break;
                    }
                }
                timer_raio_inimigo = GetTime();
            }
            
            for(i = 0; i < maximo_raios_tela_player; i++){
                if(raios_jogador[i].ativo == 1){
                    raios_jogador[i].posicao.y -=7;

                    if(raios_jogador[i].posicao.y<0){
                        raios_jogador[i].ativo = 0;
                    }
                    if(CheckCollisionPointRec(raios_jogador[i].posicao, inimigo)){
                        raios_jogador[i].ativo = 0;
                        vidas_inimigo = vidas_inimigo - 1;
                        if(vidas_inimigo == 0 ){
                            nivel= nivel +1;
                            intervalo_raio_inimigo -= 0.01f;
                            PlaySound(level_up);

                            vidas_inimigo = dados_niveis[nivel - 1][0];
                            velocidade_inimigo = dados_niveis[nivel - 1][1];

                            if (nivel > nivel_maximo){
                                game_over = 1;
                                PlaySound(sound_game_over);
                                
                            }    
                            bola.velocidade.x = mais_velocidade(bola.velocidade.x);
                            bola.velocidade.y = mais_velocidade(bola.velocidade.y);
                        }
                    }
                }
            }
            for(i = 0; i <maximo_raios_tela_inimigo; i++){
                if(raios_inimigo[i].ativo == 1){
                    raios_inimigo[i].posicao.y += 5;

                    if(raios_inimigo[i].posicao.y > altura_tela){
                        raios_inimigo[i].ativo = 0;
                    }
                    if(CheckCollisionPointRec(raios_inimigo[i].posicao, player)){
                        raios_inimigo[i].ativo = 0;
                        vidas_player--;
                        PlaySound(sound_explosion);
                        if( vidas_player == 0){
                            game_over = 1;
                            PlaySound(sound_game_over);
                            memset(nome_player, '\0', LEN_NOME);
                        }
                    }
                }
            }
        }
        else if(game_over == 1){
            inputs_alpha(nome_player, &letra_atual, &pontuacoes, nivel, &game_over);                     
        }
        else if (game_over == 2 ){
            if(IsKeyPressed(KEY_R)){
                player.x = largura_tela/2;
                player.y = altura_tela - 20;
                
                bola.posicao.x = largura_tela/2;
                bola.posicao.y = altura_tela/2;
                bola.velocidade.x = 4;
                bola.velocidade.y = -4;

                inimigo.x = largura_tela /2 ;
                inimigo.y = 50;

                vidas_player = 3;
                vidas_inimigo = 3;
                nivel = 1;
                velocidade_inimigo = 3;
                direcao_inimigo = 1;
                timer_raio_inimigo = 0;
                intervalo_raio_inimigo = 1.5f;
                letra_atual = 0;

                for(i = 0; i < maximo_raios_tela_inimigo; i++){
                    raios_jogador[i].ativo = 0;
                }
                for( i = 0; i < maximo_raios_tela_inimigo; i++){
                    raios_inimigo[i].ativo = 0;
                }
                game_over = 0;
            }
        } 
        BeginDrawing();
        DrawTexture(background, 0, 0, WHITE);

        if(game_over == 0){
            DrawRectangleRec(player, BLUE);
            DrawRectangleRec(inimigo, RED);
            DrawCircleV(bola.posicao,raio_bola, WHITE);
            for(i = 0; i < maximo_raios_tela_player; i++){
                if(raios_jogador[i].ativo) {
                    DrawCircleV(raios_jogador[i].posicao,5, GREEN);
                }
            }
            for(i = 0; i < maximo_raios_tela_inimigo; i++){
                if(raios_inimigo[i].ativo) {
                    DrawCircleV(raios_inimigo[i].posicao, 5, ORANGE);
                }
            }
            DrawText(TextFormat("Vidas: %d", vidas_player), 10, altura_tela - 30, 20, GREEN);
            DrawText(TextFormat("Vidas Inimigo: %d", vidas_inimigo), 10, 10, 20, RED);
            DrawText(TextFormat("Nivel: %d", nivel), largura_tela - 120, 10, 20, WHITE);
        }
        else if (game_over == 1) {
            DrawText("GAME OVER", largura_tela / 2 - 100, 100, 50, RED);
            DrawText("Digite seu nome (3 letras):", largura_tela / 2 - 150, 160, 20, WHITE);

            int posX = largura_tela / 2 - 40;

            for ( i = 0; i < LEN_NOME - 1; i++) {
                Color cor = WHITE;
                if (i == letra_atual) {
                    cor = YELLOW;
                }
                char letra = '_';
                if (nome_player[i] != '\0') letra = nome_player[i];
                DrawText(TextFormat("%c", letra), posX + i * 40, 200, 40, cor);                
            }
        }else{
            DrawText("GAME OVER", largura_tela / 2 - 100, 100, 50, RED);
            DrawText("Pressione R para reiniciar", largura_tela / 2 - 140, 160, 20, WHITE);

            DrawText("High Scores:", largura_tela / 2 - 70, 220, 25, GOLD);
            Pontuacao_Player *atual = pontuacoes;
            int yPos = 260;
            int contador = 0;
            while (atual != NULL && contador < 5) {
                DrawText(TextFormat("%s - %d", atual->nome, atual->pontuacao), largura_tela / 2 - 50, yPos, 20, WHITE);
                atual = atual->prox;
                yPos += 30;
                contador+=1;
            }
        }
        EndDrawing();
    }

    Pontuacao_Player *atual = pontuacoes;
    while(atual != NULL){
        Pontuacao_Player *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    UnloadTexture(background);
    UnloadSound(laser_player);
    UnloadSound(sound_explosion);
    UnloadSound(sound_game_over);
    UnloadSound(level_up);
    CloseAudioDevice();
    CloseWindow();
    return 0;          
}   

