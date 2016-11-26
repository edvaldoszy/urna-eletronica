#ifndef URNA_S
#define URNA_S

typedef struct {
    int codigo;
    char senha[100];
    int quantidade;
    Candidato candidatos[100];
} Secao;

void criar_secao(int codigo, char *senha);
void validar_senha(int codigo, char *senha);
void resultado_secao(int codigo);
void adicionar_candidato(int codigo, Candidato candidatos);
void mostrar_candidatos(int codigo);
void votar(int codigo, char *nome);

#endif
