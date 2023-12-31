//
// Created by Mariane on 19/09/2023.
//

#include "lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * funcao responsavel por imprimir as informacoes e opcoes do menu principal**/
void imprimeMenu() {
    printf("********************************************\n");
    printf("********** GERENCIADOR DE TAREFAS **********\n");
    printf("********************************************\n");
    printf("\n");
    printf("O que voce gostaria de fazer?\n");
    printf("\n");
    printf("\t1 - cadastrar nova tarefa;\n");
    printf("\t2 - listar todas as tarefas;\n");
    printf("\t3 - deletar tarefa;\n");
    printf("\t0 - sair da aplicacao.\n\n");
    printf("digite sua opcao: ");
}

/*
 * Funcao que recebe os inputs do usuario com as informacos da tarefa a ser cadastrada e atribui a uma struct Tarefa.*/
void criaTarefa(ListaTarefas *lt) {
    char desc[300], categ[100];
    int input, retornoScan;
    Tarefa *t = &lt->tarefas[lt->qtd];

    printf("Digite a prioridade da tarefa (0 a 10): ");
    do {
        fgetc(stdin); //limpa o buffer do teclado
        retornoScan = scanf("%d", &input);
    } while ((validaInputUsuario(input, 0, 10, retornoScan) != 1));
    t->prioridade = input;

    printf("\nDigite a categoria a qual esta tarefa pertence: ");
    fgetc(stdin); //limpa o buffer do teclado
    scanf("%[^\n]", categ);
    strcpy(t->categoria, categ);

    printf("\nDigite uma breve descricao desta tarefa: ");
    fgetc(stdin); //limpa o buffer do teclado
    scanf("%[^\n]", desc);
    strcpy(t->descricao, desc);
    printf("\n");

    lt->qtd++;
}

/*Funcao responsavel por gravar a tarefa no arquivo binario.
 * Recebe uma struct do tipo Tarefa como parametro e o nome do arquivo na qual sera gravada*/
void cadastraTarefa(ListaTarefas *lt, char *arquivo){
    FILE *f = fopen(arquivo, "wb");

    if (f == NULL) {
        erroArquivo();
        }

    fwrite(lt, sizeof (ListaTarefas), 1, f);

    fclose(f);
}

/*Funcao que lista todas as tarefas gravadas no arquivo binario*/
void listaTarefas(ListaTarefas *lt) {

    for (int i = 0; i < lt->qtd; i++) {
        printf("Tarefa [%d]:\n", (i + 1));
        printf("\tprioridade: %d\n\tcategoria: %s\n\tdescricao: %s\n\n", lt->tarefas[i].prioridade, lt->tarefas[i].categoria, lt->tarefas[i].descricao);
    }
}

/*Funcao que deleta a tarefa de acordo com um ID passado pelo usuario.
 * O ID e utilizado como um indice (i + 1) a partir do qual sera feita a varredura no array de tarefas em busca da qual devera ser deletada
 * Uma vez encontrada, a tarefa a ser apagada recebe os dados da tarefa subssequente e assim por diante, ate o fim do arquivo
 * O arquivo é subscrito com o array de tarefas atualizado*/
void deletaTarefa(ListaTarefas *lt, int indice) {
    int indiceReal = indice - 1;

    for (int i = 0; i < lt->qtd; i++) {
        if (indiceReal <= i) {
            lt->tarefas[i] = lt->tarefas[(i + 1)];
        }
    }

    lt->qtd--;
}

/*Funcao utilizada para validar os inputs numericos coletados durante a execucao do programa
 * Recebe como parametro o input do usuario, os valores minimos e maximos que serao aceitos e tambem se a funcao scanf conseguiu fazer a conversao para inteiro
 * E verificado se o input do usuario esta entre o intervalo e se o retorno do scanf e diferente de 0, afim de evitar que o usuario digite algum caracter nao numerico
 * A funcao retorna 1 caso o input seja valido e 0 no caso contrario, juntamente com uma mensagem alertando o usuario*/
int validaInputUsuario(int input, int min, int max, int retorno) {
    if ((input >= min && input <= max) && (retorno !=0)) {
        return 1;
    } else {
        printf("Opcao invalida! Digite novamente..\n");
        return 0;
    }
}

/*Funcao que imprime uma mensagem de alerta ao usuario caso ocorra algum erro na tentativa de abertura do arquivo binario*/
void erroArquivo() {
    int input, retornoScan;
    printf("Erro! O arquivo de destino nao pode ser aberto..\n");
    printf("Digite 0 para encerrar a aplicacao e tente novamente em instantes..\n");
    do {
        fgetc(stdin); //limpa o buffer do teclado
        retornoScan = scanf("%d", &input);
    } while ((validaInputUsuario(input, 0, 0, retornoScan) != 1));
    exit(0);
}

int carregaTarefas(ListaTarefas *lt, char *arquivo) {
    FILE *f = fopen(arquivo, "rb");

    if (f == NULL) {
        return 1;
    }

    fread(lt, sizeof(ListaTarefas), 1, f);

    fclose(f);

    return 0;
}

