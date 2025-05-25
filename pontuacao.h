#include "structs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Pontuacao_Player *Adicionar_pontuacao(Pontuacao_Player *head, const char *nome, int pontuacao){
    Pontuacao_Player *novo_no = (Pontuacao_Player*)malloc(sizeof(Pontuacao_Player));
   
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

Pontuacao_Player *carregar_pontuacoes(const char *arq){
    FILE *file = fopen(arq, "r");

    Pontuacao_Player *head = NULL;
    char nome[LEN_NOME];
    int pontuacao;

    while( fscanf(file, "%s %d", nome, &pontuacao) == 2){
        head = Adicionar_pontuacao(head, nome, pontuacao);
    }
    fclose(file);
    return head;
}