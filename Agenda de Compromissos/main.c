#include <stdio.h>
#include <stdlib.h>


int main() {
    int escolha;
    int indice;
    int acao;
    char compromisso[20][120]; // 5 strings de até 119 caracteres cada 
    char data[20][11];
    char hora[20][9];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Verificar Compromisso\n");
        printf("2. Buscar Compromisso\n");
        printf("3. Inserir Novo Compromisso\n");
        printf("4. Mostrar Numero de compromissos")
        printf("5. Reinicializar Agenda\n");
        printf("6. Editar/Remover Compromisso\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                exibirElementos();
                break;
            case 2:
                printf("Digite o índice a ser consultado: ");
                scanf("%d", &indice);
                printf("Elemento na posição %d: %s\n", indice, consultarElemento(indice));
                break;
            case 3:
                printf("Digite o Seu novo compromsso: ");
                scanf("%s", &compromisso);
                addCompromisso(compromisso);
                break;
            case 4:
                comprimentoAgenda();
                break;
            case 5:
                exibirElementos();
                printf("Digite o índice do compromisso: ");
                scanf("%d", &indice);
                printf("1. Editar \n");
                printf("2. Remover \n");
                scanf("%d", &acao);
                switch(acao)
                {
                    case 1:
                        editarCompromisso(indice);
                        printf("Compromisso Editado")
                        break;
                    case 2:
                        RemoverCompromisso(indice);
                        printf("Compromisso Removido");
                        break
                }
            case 6:
                limparAgenda();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}