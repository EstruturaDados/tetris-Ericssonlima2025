#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ------------------------------
// Definição da estrutura da peça
// ------------------------------
typedef struct {
    char nome;  // Tipo da peça: I, O, T, L
    int id;     // Identificador único
} Peca;

// ------------------------------
// Configurações da fila
// ------------------------------
#define TAM_FILA 5

Peca fila[TAM_FILA];
int inicio = 0;    // Índice do primeiro elemento
int fim = 0;       // Índice onde será inserido o próximo elemento
int quantidade = 0; // Total de elementos na fila

int proxID = 0; // Usado para gerar ids únicos

// ------------------------------
// Gera uma nova peça automaticamente
// ------------------------------
Peca gerarPeca() {
    char tipos[4] = {'I','O','T','L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = proxID++;
    return nova;
}

// ------------------------------
// Insere uma peça no fim da fila
// ------------------------------
void enqueue() {
    if (quantidade == TAM_FILA) {
        printf("\nA fila está cheia! Não é possível inserir.\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAM_FILA;
    quantidade++;

    printf("\nPeça inserida com sucesso!\n");
}

// ------------------------------
// Remove uma peça do início da fila
// ------------------------------
void dequeue() {
    if (quantidade == 0) {
        printf("\nA fila está vazia! Não há peça para jogar.\n");
        return;
    }

    Peca retirada = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;

    printf("\nPeça jogada: [%c %d]\n", retirada.nome, retirada.id);
}

// ------------------------------
// Exibe o estado atual da fila
// ------------------------------
void exibirFila() {
    printf("\n=== Fila de peças ===\n");

    if (quantidade == 0) {
        printf("(vazia)\n");
        return;
    }

    int idx = inicio;
    for (int i = 0; i < quantidade; i++) {
        printf("[%c %d] ", fila[idx].nome, fila[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");
}

// ------------------------------
// Programa principal
// ------------------------------
int main() {
    srand(time(NULL));

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue();
    }

    int opcao;

    do {
        exibirFila();

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;
            case 2:
                enqueue();
                break;
            case 0:
                printf("\nEncerrando...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
