#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "candidato.c"
#include "secao.c"

int main(int argc, char *argv[]) {

    char *parte = argv[1];
    if (strcmp(parte, "secao") == 0) {
        int codigo = atoi(argv[2]);
        char *operacao = argv[3];

        char senha[100];
        if (strcmp(operacao, "criar") == 0) {
            printf("Digite uma senha para a seção: ");
            scanf("%s", senha);
            criar_secao(codigo, senha);
        }

        if (strcmp(operacao, "resultado") == 0) {
            printf("Digite a senha da seção: ");
            scanf("%s", senha);
            validar_senha(codigo, senha);
            resultado_secao(codigo);
        }

        if (strcmp(operacao, "ac") == 0) {
            printf("Digite a senha da seção: ");
            scanf("%s", senha);
            validar_senha(codigo, senha);
            ler_secao(codigo);

            Candidato candidato;
            strcpy(candidato.nome, argv[4]);
            candidato.votos = 0;

            adicionar_candidato(codigo, candidato);
            printf("Candidato \"%s\" adicionado a secao \"%d\"\n", argv[4], codigo);
        }

        if (strcmp(operacao, "acs") == 0) {
            printf("Digite a senha da seção: ");
            scanf("%s", senha);
            validar_senha(codigo, senha);
            ler_secao(codigo);

            printf("Digite a quantidade de candidatos (max 100): ");
            int quantidade = 0;
            scanf("%d", &quantidade);
            while (quantidade > 100) {
                printf("A quantidade maxima de candidatos e 100\n");
                printf("Digite a quantidade de candidatos (max 100): ");
                scanf("%d", &quantidade);
            }

            for (int i = 0; i < quantidade; i++) {
                char nome[100];
                printf("Digite o nome do candidato %d: ", (i + 1));
                scanf("%s", nome);

                Candidato candidato;
                strcpy(candidato.nome, nome);
                candidato.votos = 0;

                adicionar_candidato(codigo, candidato);
            }

            printf("Todos os candidatos foram adicionado a secao \"%d\"\n", codigo);
        }

        if (strcmp(operacao, "mc") == 0) {
            printf("Digite a senha da seção: ");
            scanf("%s", senha);
            validar_senha(codigo, senha);
            mostrar_candidatos(codigo);
        }

        if (strcmp(operacao, "votar") == 0) {
            votar(codigo, argv[4]);
        }
    }

    return 0;
}