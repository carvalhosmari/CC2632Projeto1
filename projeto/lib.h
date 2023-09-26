//
// Created by Mariane on 17/09/2023.
//

#ifndef PROJETO_LIB_H
#define PROJETO_LIB_H
typedef struct {
    int prioridade;
    char categoria[100];
    char descricao[300];
} Tarefa;
void imprimeMenu();
void criaTarefa(Tarefa *t);
void cadastraTarefa(Tarefa *t, char *arquivo);
void deletaTarefa(int indice, char *arquivo);
void listaTarefas(char *arquivo);
Tarefa *leBinario(char *arquivo, int tamanho);
int tamanhoArquivo(char *arquivo);
int validaInputUsuario(int input, int min, int max, int retorno);
void erroArquivo();
#endif //PROJETO_LIB_H
