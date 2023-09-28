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
typedef struct {
    Tarefa tarefas[100];
    int qtd;
} ListaTarefas;
void imprimeMenu();
void criaTarefa(ListaTarefas *lt);
void cadastraTarefa(ListaTarefas *lt, char *arquivo);
void deletaTarefa(ListaTarefas *lt, int indice);
void listaTarefas(ListaTarefas *lt);
int carregaTarefas(ListaTarefas *lt, char *arquivo);
int validaInputUsuario(int input, int min, int max, int retorno);
void erroArquivo();
#endif //PROJETO_LIB_H
