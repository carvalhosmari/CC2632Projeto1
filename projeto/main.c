#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main() {

    int input;
    int retornoScan;
    int qtdTarefas = tamanhoArquivo("arquivo");
    int limite = 100;
    Tarefa t;
    ListaTarefas lista;
    lista.qtd = 0;

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
                    } while ((validaInputUsuario(input, 1, qtdTarefas, retornoScan) != 1));
                    deletaTarefa(&lista, input);

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

//        switch (input) {
//            case 1: //No caso do usuario digitar 1, fluxo segue para o cadastro de uma nova tarefa
//                while (qtdTarefas < limite) {
//                    criaTarefa(&lista); //funcao que atribui valores a struct tarefa
//
//                    cadastraTarefa(&t, "arquivo"); //funcao que grava a struct no arquivo binario
//
//                    qtdTarefas++; //incremento do numero de tarefas dentro do loop
//
//                    //solicitacao e validacao do input do usuario
//                    printf("Gostaria de adicionar outra tarefa? Digite:\n1 - SIM\n0 - NAO\n");
//                    do {
//                        fgetc(stdin); //limpa o buffer do teclado
//                        retornoScan = scanf("%d", &input);
//                    } while ((validaInputUsuario(input, 0, 1, retornoScan) != 1));
//
//                    //se usuario digita 0, a funcionalidade de cadastrar tarefas e interrompida
//                    if (input == 0) {
//                        break;
//                    }
//                }
//
//                //caso o numero maximo de tarefas seja atingido, o usuario e alertado
//                if (qtdTarefas == limite) {
//                    printf("ERRO: o numero maximo de tarefas foi atingido!\nDelete alguma tarefa existente para conseguir cadastrar uma nova..\n\n");
//                    system("pause");
//                }
//                //main(); //caso o usuario nao deseje cadastrar uma nova tarefa ou o numero maximo seja atingido, a main() e chamada para que o usuario retorne ao menu principal
//
//            case 2: //No caso do usuario digitar 2, fluxo segue para a lista de todas as tarefas cadastradas
//
//                listaTarefas(&lista);
//                printf("entrou aqui\n");
//            //caso nao haja nenhuma, o usuario e alertado e orientado a retornar ao menu principal
//            if (lista.qtd == 0) {
//                printf("No momento voce nao possui tarefas cadastradas..\n");
//
//                //solicitacao e validacao do input do usuario
//                printf("\nPressione 0 para retornar ao menu principal\n");
//                do {
//                    fgetc(stdin); //limpa o buffer do teclado
//                    retornoScan = scanf("%d", &input);
//                } while ((validaInputUsuario(input, 0, 0, retornoScan) != 1) && input != 0);
//
//            } else {
//                do {
//                    listaTarefas(&lista); //funcao que lista todas as tarefas cadastradas
//
//                    //solicitacao e validacao do input do usuario
//                    printf("\nPressione 0 para retornar ao menu principal\n");
//                    do {
//                        fgetc(stdin); //limpa o buffer do teclado
//                        retornoScan = scanf("%d", &input);
//                    } while ((validaInputUsuario(input, 0, 0, retornoScan) != 1));
//
//                } while (input != 0);
//            }
//            main();//a main() e chamada para que o usuario retorne ao menu principal
//
//            case 3: //No caso do usuario digitar 3, fluxo segue para a opcao de deletar uma tarefa
//                //caso nao haja nenhuma tarefa, o usuario e alertado e orientado a retornar ao menu principal
//                if (qtdTarefas == 0) {
//                    printf("No momento voce nao possui tarefas cadastradas..\n");
//
//                    //solicitacao e validacao do input do usuario
//                    printf("\nPressione 0 para retornar ao menu principal\n");
//                    do {
//                        fgetc(stdin); //limpa o buffer do teclado
//                        retornoScan = scanf("%d", &input);
//                    } while ((validaInputUsuario(input, 0, 0, retornoScan) != 1) && input != 0);
//
//                } else {
//                    do {
//                        //listaTarefas("arquivo"); //funcao que lista todas as tarefas para o usuario verificar a relacao das cadastradas anter de solicitar remocao
//
//                        //solicitacao e validacao do input do usuario
//                        printf("Digite o numero da tarefa que voce gostaria de deletar: ");
//                        do {
//                            fgetc(stdin); //limpa o buffer do teclado
//                            retornoScan = scanf("%d", &input);
//                        } while ((validaInputUsuario(input, 1, qtdTarefas, retornoScan) != 1));
//
//                        deletaTarefa(input, "arquivo"); //funcao que deleta a tarefa especificada
//
//                        //solicitacao e validacao do input do usuario
//                        printf("Gostaria de deletar outra tarefa? Digite:\n1 - SIM\n0 - NAO\n");
//                        do {
//                            fgetc(stdin); //limpa o buffer do teclado
//                            retornoScan = scanf("%d", &input);
//                        } while ((validaInputUsuario(input, 0, 1, retornoScan) != 1));
//
//                    } while (input != 0);
//                }
//                main();//a main() e chamada para que o usuario retorne ao menu principal
//
//            case 0: //No caso do usuario digitar 0, o programa e encerrado
//                exit(0);
//        }
    } while (input != 0);


}
