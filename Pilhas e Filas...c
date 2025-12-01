#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --------------------------------------------------
// Estrutura da peça
// --------------------------------------------------
typedef struct {
    char nome;
    int id;
} Peca;

// --------------------------------------------------
// Configurações
// --------------------------------------------------
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

// --------------------------------------------------
// Gera uma nova peça aleatória
// --------------------------------------------------
Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = proxID++;
    return p;
}

// --------------------------------------------------
// Inserir peça na fila
// --------------------------------------------------
void enqueue() {
    if (quantidade == TAM_FILA) return;
    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAM_FILA;
    quantidade++;
}

// --------------------------------------------------
// Remover peça da fila
// --------------------------------------------------
Peca dequeue() {
    Peca vazia = {'?', -1};
    if (quantidade == 0) return vazia;

    Peca r = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;
    return r;
}

// --------------------------------------------------
// Empilhar peça na pilha
// --------------------------------------------------
int push(Peca p) {
    if (topo == TAM_PILHA - 1) return 0;
    pilha[++topo] = p;
    return 1;
}

// --------------------------------------------------
// Desempilhar peça da pilha
// --------------------------------------------------
Peca pop() {
    Peca vazia = {'?', -1};
    if (topo == -1) return vazia;
    return pilha[topo--];
}

// --------------------------------------------------
// Exibir fila
// --------------------------------------------------
void exibirFila() {
    printf("Fila de Peças: ");

    int i = inicio;
    for (int c = 0; c < quantidade; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
}

// --------------------------------------------------
// Exibir pilha
// --------------------------------------------------
void exibirPilha() {
    printf("Pilha de Reserva (Topo -> Base): ");

    for (int i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
}

// --------------------------------------------------
// Exibir estado atual
// --------------------------------------------------
void exibirEstado() {
    printf("\n=== Estado Atual ===\n");
    exibirFila();
    printf("\n");
    exibirPilha();
    printf("\n");
}

// --------------------------------------------------
// Troca simples: frente da fila <-> topo da pilha
// --------------------------------------------------
void trocarSimples() {
    if (topo == -1) {
        printf("\nNão há peça na pilha para trocar!\n");
        return;
    }

    // troca
    Peca temp = fila[inicio];
    fila[inicio] = pilha[topo];
    pilha[topo] = temp;

    printf("\nTroca realizada entre a peça da frente da fila e o topo da pilha.\n");
}

// --------------------------------------------------
// Troca múltipla: 3 da fila <-> 3 da pilha
// --------------------------------------------------
void trocarTres() {
    if (topo < 2) {
        printf("\nA pilha não possui 3 peças para realizar a troca!\n");
        return;
    }

    printf("\nTroca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");

    for (int i = 0; i < 3; i++) {
        int posFila = (inicio + i) % TAM_FILA;

        Peca temp = fila[posFila];
        fila[posFila] = pilha[topo - i];
        pilha[topo - i] = temp;
    }
}

// --------------------------------------------------
// Programa principal
// --------------------------------------------------
int main() {
    srand(time(NULL));

    // Preenche a fila inicialmente
    while (quantidade < TAM_FILA) enqueue();

    int op;

    do {
        exibirEstado();

        printf("\nOpções:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para reserva (pilha)\n");
        printf("3 - Usar peça da reserva (pilha)\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &op);

        switch (op) {

            case 1: {
                Peca j = dequeue();
                printf("\nPeça jogada: [%c %d]\n", j.nome, j.id);
                enqueue();
            } break;

            case 2: {
                if (topo == TAM_PILHA - 1)
                    printf("\nA pilha está cheia!\n");
                else {
                    Peca r = dequeue();
                    push(r);
                    printf("\nPeça reservada: [%c %d]\n", r.nome, r.id);
                    enqueue();
                }
            } break;

            case 3: {
                if (topo == -1)
                    printf("\nA pilha está vazia!\n");
                else {
                    Peca u = pop();
                    printf("\nPeça usada: [%c %d]\n", u.nome, u.id);
                }
                enqueue();
            } break;

            case 4:
                trocarSimples();
                break;

            case 5:
                trocarTres();
                break;

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (op != 0);

    return 0;
}