#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// -------------------------------------------
// Estrutura da peça
// -------------------------------------------
typedef struct {
    char nome;  // Tipo: I, O, T, L
    int id;     // Identificador único
} Peca;

// -------------------------------------------
// Configurações
// -------------------------------------------
#define TAM_FILA 5
#define TAM_PILHA 3

// Fila circular
Peca fila[TAM_FILA];
int inicio = 0;
int fim = 0;
int quantidade = 0;

// Pilha
Peca pilha[TAM_PILHA];
int topo = -1;

// Controle de IDs
int proxID = 0;

// -------------------------------------------
// Gera peças automaticamente
// -------------------------------------------
Peca gerarPeca() {
    char tipos[4] = {'I','O','T','L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = proxID++;
    return nova;
}

// -------------------------------------------
// Insere peça no fim da fila
// -------------------------------------------
void enqueue() {
    if (quantidade == TAM_FILA) return; // fila cheia (não deveria acontecer)
    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAM_FILA;
    quantidade++;
}

// -------------------------------------------
// Remove peça do início da fila
// -------------------------------------------
Peca dequeue() {
    Peca vazia = {'?', -1};

    if (quantidade == 0)
        return vazia;

    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;

    return removida;
}

// -------------------------------------------
// Empilha peça na reserva
// -------------------------------------------
int push(Peca x) {
    if (topo == TAM_PILHA - 1)
        return 0; // pilha cheia

    pilha[++topo] = x;
    return 1;
}

// -------------------------------------------
// Desempilha peça da reserva
// -------------------------------------------
Peca pop() {
    Peca vazia = {'?', -1};
    if (topo == -1)
        return vazia;
    return pilha[topo--];
}

// -------------------------------------------
// Exibe fila
// -------------------------------------------
void exibirFila() {
    printf("Fila de peças: ");

    if (quantidade == 0) {
        printf("(vazia)");
        return;
    }

    int i = inicio;
    for (int c = 0; c < quantidade; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
}

// -------------------------------------------
// Exibe pilha
// -------------------------------------------
void exibirPilha() {
    printf("Pilha de reserva (Topo -> Base): ");

    if (topo == -1) {
        printf("(vazia)");
        return;
    }

    for (int i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
}

// -------------------------------------------
// Exibe estado geral
// -------------------------------------------
void exibirEstado() {
    printf("\n==============================\n");
    exibirFila();
    printf("\n");
    exibirPilha();
    printf("\n==============================\n");
}

// -------------------------------------------
// Função principal
// -------------------------------------------
int main() {
    srand(time(NULL));

    // Inicializa fila com 5 peças
    while (quantidade < TAM_FILA)
        enqueue();

    int opcao;

    do {
        exibirEstado();

        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: { // Jogar peça da fila
                Peca jogada = dequeue();
                if (jogada.id == -1) {
                    printf("\nA fila está vazia!\n");
                } else {
                    printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);
                }
                enqueue(); // mantém a fila cheia
            } break;

            case 2: { // Reservar peça
                if (topo == TAM_PILHA - 1) {
                    printf("\nA pilha está cheia! Não é possível reservar.\n");
                } else {
                    Peca reservada = dequeue();
                    if (reservada.id == -1) {
                        printf("\nA fila está vazia!\n");
                    } else {
                        push(reservada);
                        printf("\nPeça reservada: [%c %d]\n", reservada.nome, reservada.id);
                    }
                    enqueue();
                }
            } break;

            case 3: { // Usar peça reservada
                if (topo == -1) {
                    printf("\nA pilha está vazia! Não há peça reservada.\n");
                } else {
                    Peca usada = pop();
                    printf("\nPeça usada: [%c %d]\n", usada.nome, usada.id);
                }
                enqueue();
            } break;

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}