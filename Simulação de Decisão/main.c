#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct do dispositivo
typedef struct {
    char nome[50];
    float consumo;     // Consumo estimado (kWh)
    int prioridade;    // 1 = Alta, 2 = Média, 3 = Baixa
    int ligado;        // 1 = ligado, 0 = desligado
} Dispositivo;

// Função de cadastro
void cadastrarDispositivos(Dispositivo *d, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nCadastro do dispositivo %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", d[i].nome);

        printf("Consumo estimado (kWh): ");
        scanf("%f", &d[i].consumo);

        printf("Prioridade (1 = Alta, 2 = Média, 3 = Baixa): ");
        scanf("%d", &d[i].prioridade);

        if (d[i].prioridade < 1 || d[i].prioridade > 3) {
            printf("Prioridade inválida! Definida como Média (2).\n");
            d[i].prioridade = 2;
        }

        d[i].ligado = 0;
    }
}

// Função de exibição
void exibirDispositivos(Dispositivo *d, int qtd) {
    printf("\n--- Lista de Dispositivos ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nDispositivo %d:\n", i + 1);
        printf("Nome: %s\n", d[i].nome);
        printf("Consumo: %.2f kWh\n", d[i].consumo);
        printf("Prioridade: %d\n", d[i].prioridade);
        printf("Status: %s\n", d[i].ligado ? "Ligado" : "Desligado");
    }
}

// Função de comparação: primeiro pela prioridade, depois pelo consumo (ascendente)
int compararPrioridadeConsumo(const void *a, const void *b) {
    Dispositivo *da = (Dispositivo *)a;
    Dispositivo *db = (Dispositivo *)b;

    if (da->prioridade != db->prioridade)
        return da->prioridade - db->prioridade;
    else
        return (da->consumo > db->consumo) - (da->consumo < db->consumo); // menor consumo primeiro
}

// Função de simulação de consumo inteligente
void simularConsumo(Dispositivo *d, int qtd, float energiaDisponivel) {
    float consumoTotal = 0;

    // Ordenar dispositivos por prioridade (e consumo)
    qsort(d, qtd, sizeof(Dispositivo), compararPrioridadeConsumo);

    printf("\n>>> Simulando consumo com %.2f kWh disponíveis...\n", energiaDisponivel);

    for (int i = 0; i < qtd; i++) {
        if (consumoTotal + d[i].consumo <= energiaDisponivel) {
            d[i].ligado = 1;
            consumoTotal += d[i].consumo;
        } else {
            d[i].ligado = 0;
        }
    }

    // Resultado da simulação
    printf("\n--- Resultado da Simulação ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("Dispositivo: %-20s | Status: %-8s | Prioridade: %d | Consumo: %.2f kWh\n",
               d[i].nome,
               d[i].ligado ? "Ligado" : "Desligado",
               d[i].prioridade,
               d[i].consumo);
    }

    printf("\nTotal de consumo permitido: %.2f kWh\n", consumoTotal);
    printf("Energia restante: %.2f kWh\n", energiaDisponivel - consumoTotal);
}

int main() {
    int qtd;
    float energiaDisponivel;
    Dispositivo *dispositivos = NULL;

    printf("Quantos dispositivos deseja cadastrar? ");
    scanf("%d", &qtd);

    // Alocar memória
    dispositivos = (Dispositivo *) malloc(qtd * sizeof(Dispositivo));
    if (dispositivos == NULL) {
        printf("Erro de memória!\n");
        return 1;
    }

    // Cadastro
    cadastrarDispositivos(dispositivos, qtd);

    // Entrada da energia disponível
    printf("\nInforme a energia disponível (kWh): ");
    scanf("%f", &energiaDisponivel);

    // Simulação
    simularConsumo(dispositivos, qtd, energiaDisponivel);

    // Exibição final
    exibirDispositivos(dispositivos, qtd);

    // Liberação de memória
    free(dispositivos);

    return 0;
}

