#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 100

//Variaveis Globais
Aluno listaAlunos[MAX_ALUNOS];
int tamanhoLista = 0;

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
    printf("Ocorrência registrada para a matrícula: %s - Tipo: %s\n", acesso.matricula, acesso.tipoOcorrencia);
}

void obterTipoOcorrencia(char *tipoOcorrencia) {
    printf("Selecione o tipo de ocorrência:\n");
    printf("1. Esqueceu\n");
    printf("2. Perdeu\n");
    printf("3. Não Possui\n");
    printf("4. Outros\n");
    printf("Escolha uma opção: ");
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
            strcpy(tipoOcorrencia, "Não Possui");
            break;
        case 4:
            strcpy(tipoOcorrencia, "Outros");
            break;
        default:
            printf("Opção inválida. A ocorrência será registrada como 'Outros'.\n");
            strcpy(tipoOcorrencia, "Outros");
            break;
    }
}


void chamadaGeral(const char *matricula) {
    for (int i = 0; i < tamanhoLista; i++) {
        if (strcmp(listaAlunos[i].matricula, matricula) == 0) {
            char tipoOcorrencia[10];
            printf("Matrícula: %s, Nome: %s, Período: %s\n", listaAlunos[i].matricula, listaAlunos[i].nome, listaAlunos[i].periodo);
            printf("Gostaria de adicionar uma ocorrência para este aluno? (1 para Sim, 0 para Não): ");
            int escolha;
            scanf("%d", &escolha);
            if (escolha == 1) {
                obterTipoOcorrencia(tipoOcorrencia);
                registrarOcorrencia(matricula, tipoOcorrencia);
                printf("Ocorrência registrada com sucesso.\n");
            }
            return;
        }
    }
    printf("Aluno com matrícula %s não encontrado.\n", matricula);
}


bool validarPeriodo(const char *periodo) {
    if (periodo == M ||periodo == V ||periodo == N)
    {
        return true;
    }
    return false;
}

void obterInformacaoAluno(char *matricula, char *nome, char *periodo) {
    printf("Digite a matrícula do novo aluno: ");
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
        printf("A lista de alunos está cheia. Não é possível cadastrar mais alunos.\n");
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
    printf("O que você deseja fazer?\n");
    printf("1. Editar nome\n");
    printf("2. Remover aluno\n");
    printf("Escolha uma opção: ");
    int opcao;
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Digite o novo nome do aluno: ");
            scanf("%s", aluno->nome);
            printf("Nome do aluno atualizado com sucesso.\n");
            break;
        case 2:
            // Implemente a remoção do aluno aqui
            printf("Aluno removido com sucesso.\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
}



int main() {
    int escolha;
    int app = 1;
    char matricula[20];
    char nome[50];
    char tipoOcorrencia[10];
    char data[20];

    while (app == 1) {
        printf("\nMenu:\n");
        printf("1. Chamada\n");
        printf("2. Buscar Aluno\n");
        printf("3. Cadastrar Novo Aluno\n");
        printf("4. Inserir Ocorrência\n");
        printf("5. Mostrar Número de Alunos Cadastrados\n");
        printf("6. Editar/Remover Aluno\n");
        printf("7. Mostrar Ocorrências\n");
        printf("8. Reiniciar Ocorrências\n");
        printf("9. Reiniciar Programa\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                if (tamanhoLista == 0) {
                    printf("Você não possui alunos cadastrados.\n");
                } else {
                    obterData(data)
                    chamadaGeral(matricula)
                }
                break;
            case 2:
                if (tamanhoLista == 0) {
                    printf("Você não possui alunos cadastrados.\n");
                } else {
                    printf("Digite a matrícula do aluno a ser buscado: ");
                    scanf("%s", matricula);
                    Aluno alunoEncontrado;

                    if (buscarAlunoPorMatricula(matricula, &alunoEncontrado)) {
                        printf("Aluno encontrado: Matrícula: %s, Nome: %s, Período: %s\n", alunoEncontrado.matricula, alunoEncontrado.nome, alunoEncontrado.periodo);
                    } else {
                        printf("Aluno com matrícula %s não encontrado.\n", matricula);
                    }
                }
                break;
            case 3:
                if (tamanhoLista < MAX_ALUNOS) {
                    obterInformacaoAluno(matricula, nome, periodo)
                    cadastrarAluno(matricula, nome, periodo);
                } else {
                    printf("A lista de alunos está cheia. Não é possível cadastrar mais alunos.\n");
                }
                break;
            case 4:
                if (tamanhoLista == 0) {
                    printf("Você não possui alunos cadastrados.\n");
                } else {
                    printf("Digite a matrícula do aluno: ");
                    scanf("%s", matricula);
                    printf("Digite o tipo de ocorrência: ");
                    scanf("%s", tipoOcorrencia);
                    registrarOcorrencia(matricula, tipoOcorrencia);
                }
                break;
            case 5:
                printf("Número de alunos cadastrados: %d\n", contarAlunos(listaAlunos, tamanhoLista)));
                break;
            case 6:
                if (tamanhoLista == 0) {
                    printf("Você não possui alunos cadastrados.\n");
                }  else {
                    char matricula[20];
                    printf("Digite a matrícula do aluno a ser editado: ");
                    scanf("%s", matricula);
                    Aluno alunoEncontrado;

                    if (buscarAlunoPorMatricula(matricula, &alunoEncontrado)) {
                        printf("Aluno encontrado: Matrícula: %s, Nome: %s, Período: %s\n", alunoEncontrado.matricula, alunoEncontrado.nome, alunoEncontrado.periodo);
                        editarOuRemoverAluno(&alunoEncontrado);
                    } else {
                        printf("Aluno com matrícula %s não encontrado.\n", matricula);
                    }
                }

                break;
            case 7:
                printf("Número de alunos cadastrados: %d\n", contarAlunos(listaAlunos, tamanhoLista)));
                break;
            case 8:
                printf("Número de alunos cadastrados: %d\n", contarAlunos(listaAlunos, tamanhoLista)));
                break;
            case 9:
                printf("Número de alunos cadastrados: %d\n", contarAlunos(listaAlunos, tamanhoLista)));
                break;
            case 0:
                printf("Encerrando o programa.\n");
                app = 0;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
