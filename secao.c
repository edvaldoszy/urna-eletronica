#include "secao.h"

Secao ler_secao(int codigo) {
    FILE *arquivo;
    Secao secao;

    char nome[100];
    sprintf(nome, "db/secao_%d.bin", codigo);

    arquivo = fopen(nome, "r");
    fread(&secao, sizeof(secao), 1, arquivo);
    fclose(arquivo);

    return secao;
}

void validar_senha(int codigo, char *senha) {
    Secao secao = ler_secao(codigo);
    if (strlen(senha) > 0 && strcmp(secao.senha, senha) != 0) {
        printf("A senha informada e invalida\n");
        exit(-1);
    }
}

void gravar_secao(Secao secao) {
    FILE *arquivo;

    char nome[100];
    sprintf(nome, "db/secao_%d.bin", secao.codigo);

    arquivo = fopen(nome, "w");
    fwrite(&secao, sizeof(secao), 1, arquivo);
    fclose(arquivo);
}

void criar_secao(int codigo, char *senha) {
    int o = mkdir("db", 0777);
    switch (o) {
        case EACCES:
            printf("Voce nao tem permissao para criar arquivos\n");
            exit(-1);
            break;
        
        case EEXIST:
            printf("O diretorio db ja existe\n");
            break;
    }

    char nome[100];
    sprintf(nome, "db/secao_%d.bin", codigo);

    Secao secao;
    secao.codigo = codigo;
    secao.quantidade = 0;
    strcpy(secao.senha, senha);

    gravar_secao(secao);
    printf("Seção \"%d\" criada com sucesso!\n", codigo);
}

int contar_votos(Secao secao) {
    int total_votos = 0;

    for (int i = 0; i < secao.quantidade; i++) {
        Candidato c = secao.candidatos[i];
        total_votos = total_votos + c.votos;
    }

    return total_votos;
}

void resultado_secao(int codigo) {
    Secao secao = ler_secao(codigo);
    printf("Total de votos da seção \"%d\" e %d\n", codigo, contar_votos(secao));
}

void adicionar_candidato(int codigo, Candidato candidato) {
    Secao secao = ler_secao(codigo);
    secao.candidatos[secao.quantidade] = candidato;
    secao.quantidade++;
    gravar_secao(secao);
}

void mostrar_candidatos(int codigo) {
    Secao secao = ler_secao(codigo);

    printf("A secao \"%d\" possui os candidatos: ", codigo);
    for (int i = 0; i < secao.quantidade; i++) {
        Candidato c = secao.candidatos[i];
        printf("%s%s", c.nome, ((i + 1) < secao.quantidade ? ", " : ""));
    }
    printf("\n");
}

void votar(int codigo, char *nome) {
    Secao secao = ler_secao(codigo);
    for (int i = 0; i < secao.quantidade; i++) {
        Candidato c = secao.candidatos[i];
        if (strcmp(c.nome, nome) == 0) {
            secao.candidatos[i].votos += 1;
            gravar_secao(secao);
            break;
        }
    }
}