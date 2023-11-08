#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ALUNOS 100
#define MAX_OCORRENCIAS 100


typedef int TIPOCHAVE;
typedef char dataRef[11];

typedef struct {
    TIPOCHAVE chave;
    dataRef data[20];
    char matricula[20];
    char tipoOcorrencia[10];
} Acesso;

typedef struct {
    char matricula[20];
    char nome[50];
    char periodo[20];
} Aluno;

typedef struct {
    char matricula[20];
    char tipoOcorrencia[10];
} Ocorrencia;


bool validarData(const char *data) {
    int anos, meses, dias;
    if (sscanf(data, "%d-%d-%d", &anos, &meses, &dias) != 3) {
        return false;
    }

    if (meses <= 0 || meses > 12 || dias <= 0 || dias > 31) {
        return false;
    }

    return true;
}

void obterData(char *data) {
    do {
        printf("Digite a data de hoje (aaaa-mm-dd): ");
        scanf("%s", data);
    } while (!validarData(data));
}

int contarAlunos(const Aluno lista[], int tamanhoLista) {
    int contador = 0;
    for (int i = 0; i < tamanhoLista; i++) {
        if (lista[i].matricula[0] != '\0') {
            contador++;
        }
    }
    return contador;
}


void registrarOcorrencia(const char *matricula, const char *tipoOcorrencia) {
    Acesso acesso;
    acesso.chave = 1; // Defina a chave como desejado
    strcpy(acesso.matricula, matricula);
    strcpy(acesso.tipoOcorrencia, tipoOcorrencia);
    printf("Ocorr�ncia registrada para a matr�cula: %s - Tipo: %s\n", acesso.matricula, acesso.tipoOcorrencia);
}

void obterTipoOcorrencia(char *tipoOcorrencia) {
    printf("Selecione o tipo de ocorr�ncia:\n");
    printf("1. Esqueceu\n");
    printf("2. Perdeu\n");
    printf("3. N�o Possui\n");
    printf("4. Outros\n");
    printf("Escolha uma op��o: ");
    int tipoEscolhido;
    scanf("%d", &tipoEscolhido);

    switch (tipoEscolhido) {
        case 1:
            strcpy(tipoOcorrencia, "Esqueceu");
            break;
        case 2:
            strcpy(tipoOcorrencia, "Perdeu");
            break;
        case 3:
            strcpy(tipoOcorrencia, "N�o Possui");
            break;
        case 4:
            strcpy(tipoOcorrencia, "Outros");
            break;
        default:
            printf("Op��o inv�lida. A ocorr�ncia ser� registrada como 'Outros'.\n");
            strcpy(tipoOcorrencia, "Outros");
            break;
    }
}

//Variaveis Globais
Aluno listaAlunos[MAX_ALUNOS];
Ocorrencia listaOcorrencias[MAX_ALUNOS];
int tamanhoLista = 0;
int tamanhoOcorrencias = 0;

void chamadaGeral(const char *matricula) {
    for (int i = 0; i < tamanhoLista; i++) {
        if (strcmp(listaAlunos[i].matricula, matricula) == 0) {
            char tipoOcorrencia[10];
            printf("Matr�cula: %s, Nome: %s, Per�odo: %s\n", listaAlunos[i].matricula, listaAlunos[i].nome, listaAlunos[i].periodo);
            printf("Gostaria de adicionar uma ocorr�ncia para este aluno? (1 para Sim, 0 para N�o): ");
            int escolha;
            scanf("%d", &escolha);
            if (escolha == 1) {
                obterTipoOcorrencia(tipoOcorrencia);
                registrarOcorrencia(matricula, tipoOcorrencia);
                printf("Ocorr�ncia registrada com sucesso.\n");
            }
            return;
        }
    }
    printf("Aluno com matr�cula %s n�o encontrado.\n", matricula);
}


bool validarPeriodo(char *periodo) {
    printf("%s", periodo);
    if (strcmp(periodo, "M") == 0 || strcmp(periodo, "V") == 0 || strcmp(periodo, "N") == 0)
    {
        printf("Entrou");
        return true;
    }
    return false;
}

void obterInformacaoAluno(char *matricula, char *nome, char *periodo) {
    printf("Digite a matr�cula do novo aluno: ");
    scanf("%s", matricula);
    printf("Digite o nome do novo aluno: ");
    scanf("%s", nome);
    do
    {
        printf("Digite o periodo do novo aluno: \n");
        printf("Digite M para matutino\n");
        printf("Digite V para vespertino\n");
        printf("Digite N para noturno\n");
        scanf("%s", periodo);
    } while(!validarPeriodo(periodo));
    fflush(stdin);
}

void cadastrarAluno(const char *matricula, const char *nome, const char *periodo) {
    if (tamanhoLista < MAX_ALUNOS) {
        strcpy(listaAlunos[tamanhoLista].matricula, matricula);
        strcpy(listaAlunos[tamanhoLista].nome, nome);
        strcpy(listaAlunos[tamanhoLista].periodo, periodo);
        tamanhoLista++;
        printf("Aluno cadastrado com sucesso!\n");
    } else {
        printf("A lista de alunos est� cheia. N�o � poss�vel cadastrar mais alunos.\n");
    }
}

bool buscarAlunoPorMatricula(const char *matricula, Aluno *alunoEncontrado) {
    for (int i = 0; i < tamanhoLista; i++) {
        if (strcmp(listaAlunos[i].matricula, matricula) == 0) {
            *alunoEncontrado = listaAlunos[i];
            return true;
        }
    }
    return false;
}

void editarOuRemoverAluno(Aluno *aluno) {
    printf("O que voc� deseja fazer?\n");
    printf("1. Editar nome\n");
    printf("2. Remover aluno\n");
    printf("Escolha uma op��o: ");
    int opcao;
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Digite o novo nome do aluno: ");
            scanf("%s", aluno->nome);
            printf("Nome do aluno atualizado com sucesso.\n");
            break;
        case 2:
            // Implemente a remo��o do aluno aqui
            printf("Aluno removido com sucesso.\n");
            break;
        default:
            printf("Op��o inv�lida.\n");
            break;
    }
}

void mostrarOcorrenciasPorMatricula(const char *matricula) {
    printf("Ocorr�ncias do aluno com matr�cula %s:\n", matricula);
    for (int i = 0; i < tamanhoOcorrencias; i++) {
        if (strcmp(listaOcorrencias[i].matricula, matricula) == 0) {
            printf("Tipo de ocorr�ncia: %s\n", listaOcorrencias[i].tipoOcorrencia);
        }
    }
}

int main() {
    int escolha;
    int app = 1;
    char matricula[20];
    char nome[50];
    char tipoOcorrencia[10];
    char data[20];
    char periodo[20];

    Aluno alunoEncontrado;

    while (app == 1) {
        printf("\nMenu:\n");
        printf("1. Chamada\n");
        printf("2. Buscar Aluno\n");
        printf("3. Cadastrar Novo Aluno\n");
        printf("4. Inserir Ocorr�ncia\n");
        printf("5. Mostrar N�mero de Alunos Cadastrados\n");
        printf("6. Editar/Remover Aluno\n");
        printf("7. Mostrar Ocorr�ncias\n");
        printf("8. Reiniciar Ocorr�ncias\n");
        printf("9. Reiniciar Programa\n");
        printf("0. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                if (tamanhoLista == 0) {
                    printf("Voc� n�o possui alunos cadastrados.\n");
                } else {
                    obterData(data);
                    chamadaGeral(matricula);
                }
                break;
            case 2:
                if (tamanhoLista == 0) {
                    printf("Voc� n�o possui alunos cadastrados.\n");
                } else {
                    printf("Digite a matr�cula do aluno a ser buscado: ");
                    scanf("%s", matricula);
                    Aluno alunoEncontrado;

                    if (buscarAlunoPorMatricula(matricula, &alunoEncontrado)) {
                        printf("Aluno encontrado: Matr�cula: %s, Nome: %s, Per�odo: %s\n", alunoEncontrado.matricula, alunoEncontrado.nome, alunoEncontrado.periodo);
                    } else {
                        printf("Aluno com matr�cula %s n�o encontrado.\n", matricula);
                    }
                }
                break;
            case 3:
                if (tamanhoLista < MAX_ALUNOS) {
                    obterInformacaoAluno(matricula, nome, periodo);
                    cadastrarAluno(matricula, nome, periodo);
                } else {
                    printf("A lista de alunos est� cheia. N�o � poss�vel cadastrar mais alunos.\n");
                }
                break;
            case 4:
                if (tamanhoLista == 0) {
                    printf("Voc� n�o possui alunos cadastrados.\n");
                } else {
                    printf("Digite a matr�cula do aluno: ");
                    scanf("%s", matricula);
                    printf("Digite o tipo de ocorr�ncia: ");
                    scanf("%s", tipoOcorrencia);
                    registrarOcorrencia(matricula, tipoOcorrencia);
                }
                break;
            case 5:
                printf("N�mero de alunos cadastrados: %d\n", contarAlunos(listaAlunos, tamanhoLista));
                break;
            case 6:
                if (tamanhoLista == 0) {
                    printf("Voc� n�o possui alunos cadastrados.\n");
                }  else {
                    char matricula[20];
                    printf("Digite a matr�cula do aluno a ser editado: ");
                    scanf("%s", matricula);
                    Aluno alunoEncontrado;

                    if (buscarAlunoPorMatricula(matricula, &alunoEncontrado)) {
                        printf("Aluno encontrado: Matr�cula: %s, Nome: %s, Per�odo: %s\n", alunoEncontrado.matricula, alunoEncontrado.nome, alunoEncontrado.periodo);
                        editarOuRemoverAluno(&alunoEncontrado);
                    } else {
                        printf("Aluno com matr�cula %s n�o encontrado.\n", matricula);
                    }
                }

                break;
            case 7:
                if (tamanhoLista == 0) {
                    printf("Voc� n�o possui alunos cadastrados.\n");
                } else {
                    char matricula[20];
                    printf("Digite a matr�cula do aluno para mostrar as ocorr�ncias: ");
                    scanf("%s", matricula);

                    if (buscarAlunoPorMatricula(matricula, &alunoEncontrado)) {
                        mostrarOcorrenciasPorMatricula(matricula);
                    } else {
                        printf("Aluno com matr�cula %s n�o encontrado.\n", matricula);
                    }
                }
                break;
            case 8:
                printf("N�mero de alunos cadastrados: %d\n", contarAlunos(listaAlunos, tamanhoLista));
                break;
            case 9:
                printf("N�mero de alunos cadastrados: %d\n", contarAlunos(listaAlunos, tamanhoLista));
                break;
            case 0:
                printf("Encerrando o programa.\n");
                app = 0;
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    }

    return 0;
}
