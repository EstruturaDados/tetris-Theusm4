#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5   // tamanho fixo da fila

// -------- STRUCT DA PEÇA --------
typedef struct {
    char nome;   // tipo da peça ('I', 'O', 'T', 'L')
    int id;      // identificador único
} Peca;

// -------- FILA CIRCULAR --------
typedef struct {
    Peca itens[TAM];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// -----------------------------
//   Função que gera nova peça
// -----------------------------
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = rand() % 10000;  // id aleatório simples
    return p;
}

// -----------------------------
// Inicializa fila com 5 peças
// -----------------------------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;

    for (int i = 0; i < TAM; i++) {
        f->itens[i] = gerarPeca();
        f->fim = (f->fim + 1) % TAM;
        f->quantidade++;
    }
}

// -----------------------------
//       INSERE (enqueue)
// -----------------------------
void inserir(Fila *f) {
    if (f->quantidade == TAM) {
        printf("\nA fila está cheia! (mas é circular, então será substituído após jogar)\n");
        return;
    }

    f->itens[f->fim] = gerarPeca();
    f->fim = (f->fim + 1) % TAM;
    f->quantidade++;

    printf("\nPeça inserida com sucesso!\n");
}

// -----------------------------
//       REMOVE (dequeue)
// -----------------------------
void jogar(Fila *f) {
    if (f->quantidade == 0) {
        printf("\nA fila está vazia! Não há peça para jogar.\n");
        return;
    }

    Peca retirada = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM;
    f->quantidade--;

    printf("\nPeça jogada: [%c | id=%d]\n", retirada.nome, retirada.id);
}

// -----------------------------
//         MOSTRAR FILA
// -----------------------------
void mostrarFila(Fila *f) {
    printf("\n===== FILA DE PEÇAS =====\n");

    if (f->quantidade == 0) {
        printf("Fila vazia!\n");
        return;
    }

    int idx = f->inicio;
    for (int i = 0; i < f->quantidade; i++) {
        Peca p = f->itens[idx];
        printf("Pos %d -> Peça [%c | id=%d]\n", idx, p.nome, p.id);
        idx = (idx + 1) % TAM;
    }
}

// -----------------------------
//             MAIN
// -----------------------------
int main() {

    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("3 - Visualizar fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogar(&fila);
                break;
            case 2:
                inserir(&fila);
                break;
            case 3:
                mostrarFila(&fila);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
