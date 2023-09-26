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
void criaTarefa(Tarefa *t) {
    char desc[300], categ[100];
    int input, retornoScan;

    printf("Digite a prioridade da tarefa (0 a 10): ");
    do {
        fgetc(stdin); //limpa o buffer do teclado
        retornoScan = scanf("%d", &input);
    } while ((validaInputUsuario(input, 0, 10, retornoScan) != 1));
    t->prioridade = input;

    printf("\nDigite a categoria a qual esta tarefa pertence: ");
    fgetc(stdin); //limpa o buffer do teclado
    scanf("%[^\n]", &categ);
    strcpy(t->categoria, categ);

    printf("\nDigite uma breve descricao desta tarefa: ");
    fgetc(stdin); //limpa o buffer do teclado
    scanf("%[^\n]", &desc);
    strcpy(t->descricao, desc);
    printf("\n");
}

/*Funcao responsavel por gravar a tarefa no arquivo binario.
 * Recebe uma struct do tipo Tarefa como parametro e o nome do arquivo na qual sera gravada*/
void cadastraTarefa(Tarefa *t, char *arquivo){
    FILE *f = fopen(arquivo, "ab");

    if (f == NULL) {
        erroArquivo();
        }

    fwrite(t, sizeof (Tarefa), 1, f);

    fclose(f);
}

/*Funcao que faz a leitura do arquivo binario onde as tarefaz estao armazenadas.
 *Retorna o ponteiro da primeira tarefa*/
Tarefa *leBinario(char *arquivo, int tamanho) {
    Tarefa *pont = (Tarefa *) malloc(tamanho * sizeof (Tarefa));
    FILE *f = fopen(arquivo, "rb");

    if (f == NULL) {
        erroArquivo();
    }

    fread(pont, sizeof(Tarefa), tamanho, f);

    fclose(f);

    return pont;
}

/*Funcao que retorna o numero de registros gravados no arquivo binario.*/
int tamanhoArquivo(char *arquivo) {
    int tamanho;
    size_t fSize;
    FILE *f = fopen(arquivo, "ab");

    if (f == NULL) {
        erroArquivo();
    }

    //funcao que joga o ponteiro para o fim do arquivo
    fseek(f, 0L, SEEK_END);

    //funcao que diz o tamanho do arquivo em bytes
    fSize = ftell(f);

    //dividindo o tamanho do arquivo pelo tamanho de uma estrutura do tipo Tarefa, temos o numero de registros
    tamanho = fSize/sizeof (Tarefa);

    fclose(f);

    return tamanho;
}

/*Funcao que lista todas as tarefas gravadas no arquivo binario*/
void listaTarefas(char *arquivo) {
    int tamanho = tamanhoArquivo(arquivo);
    Tarefa *tarefas = leBinario(arquivo, tamanho);

    for (int i = 0; i < tamanho; i++) {
        printf("Tarefa [%d]:\n", (i + 1));
        printf("\tprioridade: %d\n\tcategoria: %s\n\tdescricao: %s\n\n", (tarefas + i)->prioridade, (tarefas + i)->categoria, (tarefas + i)->descricao);
    }
}

/*Funcao que deleta a tarefa de acordo com um ID passado pelo usuario.
 * O ID e utilizado como um indice (i + 1) a partir do qual sera feita a varredura no array de tarefas em busca da qual devera ser deletada
 * Uma vez encontrada, a tarefa a ser apagada recebe os dados da tarefa subssequente e assim por diante, ate o fim do arquivo
 * O arquivo é subscrito com o array de tarefas atualizado*/
void deletaTarefa(int indice, char *arquivo) {
    int tamanho = tamanhoArquivo(arquivo);
    Tarefa *tarefas = leBinario(arquivo, tamanho);
    int indiceReal = indice - 1;
    FILE *f = fopen(arquivo, "wb");

    if (f == NULL) {
        erroArquivo();
    }

    for (int i = 0; i < tamanho; i++) {
        if (indiceReal <= i) {
            tarefas[i] = tarefas[(i + 1)];
        }
    }

    fwrite(tarefas, sizeof(Tarefa), (tamanho - 1), f);

    fclose(f);
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

