#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main() {

    int input, retornoScan;
    ListaTarefas lista;
    int cod = carregaTarefas(&lista, "arquivo");

    if (cod != 0) {
        lista.qtd = 0;
    }

    do {
        imprimeMenu();

        //primeira interacao com o usuario, onde ele seleciona a acao desejada
        do {
            retornoScan = scanf("%d", &input);
        } while ((validaInputUsuario(input, 0, 3, retornoScan) != 1));

        if (input == 0) {
        } else if (input == 1) {
            while (lista.qtd < 100) {
                criaTarefa(&lista); //funcao que atribui valores a struct tarefa
                cadastraTarefa(&lista, "arquivo");
                //solicitacao e validacao do input do usuario
                printf("Gostaria de adicionar outra tarefa? Digite:\n1 - SIM\n2 - NAO\n");
                do {
                    fgetc(stdin); //limpa o buffer do teclado
                    retornoScan = scanf("%d", &input);
                } while ((validaInputUsuario(input, 1, 2, retornoScan) != 1));

                if (input == 2) {
                    break;
                }
            }

            if (lista.qtd == 99) {
                printf("ERRO: o numero maximo de tarefas foi atingido!\nDelete alguma tarefa existente para conseguir cadastrar uma nova..\n\n");
                system("pause");
            }

        } else if (input == 2) {
            if (lista.qtd == 0) {
                printf("Nenhuma tarefa cadastrada no momento!\n");
                system("pause");
            } else {
                listaTarefas(&lista);
                system("pause");
            }
        } else if (input == 3) {
            if (lista.qtd == 0) {
                printf("Nenhuma tarefa cadastrada no momento!\n");
                system("pause");
            } else {
                while (lista.qtd != 0) {
                    printf("Digite o numero da tarefa que voce gostaria de deletar: ");
                    do {
                        fgetc(stdin); //limpa o buffer do teclado
                        retornoScan = scanf("%d", &input);
                    } while ((validaInputUsuario(input, 1, lista.qtd, retornoScan) != 1));
                    deletaTarefa(&lista, input);
                    cadastraTarefa(&lista, "arquivo");

                    printf("Gostaria de deletar outra tarefa? Digite:\n1 - SIM\n2 - NAO\n");
                    do {
                        fgetc(stdin); //limpa o buffer do teclado
                        retornoScan = scanf("%d", &input);
                    } while ((validaInputUsuario(input, 1, 2, retornoScan) != 1));

                    if (input == 2) {
                        break;
                    }
                }
            }
        }
    } while (input != 0);
}
