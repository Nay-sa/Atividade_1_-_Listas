#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
} Lista;

// Funções da lista
Lista* criarLista() {
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    lista->inicio = NULL;
    return lista;
}

void inserirLista(Lista *lista, int valor) {
    No *novoNo = (No*) malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->prox = lista->inicio;
    lista->inicio = novoNo;
    printf("Elemento %d inserido na lista.\n", valor);
}

void exibirLista(Lista *lista) {
    No *atual = lista->inicio;
    printf("Lista: ");
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

int verificarVazia(Lista *lista) {
    return lista->inicio == NULL;
}

No* buscarLista(Lista *lista, int valor) {
    No *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->valor == valor) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void excluirLista(Lista *lista, int valor) {
    No *atual = lista->inicio;
    No *anterior = NULL;

    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Elemento %d não encontrado na lista.\n", valor);
        return;
    }

    if (anterior == NULL) { // Elemento está no início
        lista->inicio = atual->prox;
    } else { // Elemento está no meio ou final
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Elemento %d excluído da lista.\n", valor);
}

void liberarLista(Lista *lista) {
    No *atual = lista->inicio;
    No *temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    lista->inicio = NULL;
    printf("Lista liberada.\n");
}

void inserirOrdenado(Lista *lista, int valor) {
    No *novoNo = (No*) malloc(sizeof(No));
    novoNo->valor = valor;

    if (lista->inicio == NULL || lista->inicio->valor > valor) {
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
    } else {
        No *atual = lista->inicio;
        while (atual->prox != NULL && atual->prox->valor < valor) {
            atual = atual->prox;
        }
        novoNo->prox = atual->prox;
        atual->prox = novoNo;
    }
    printf("Elemento %d inserido em ordem crescente na lista.\n", valor);
}

// Função principal de exemplo
int main() {
    Lista *lista = criarLista();
    printf("Lista criada com sucesso.\n");

    // Testando a inserção em ordem
    inserirOrdenado(lista, 15);
    inserirOrdenado(lista, 3);
    inserirOrdenado(lista, 10);
    inserirOrdenado(lista, 7);
    exibirLista(lista); // Esperado: 3 -> 7 -> 10 -> 15 -> NULL

    // Testando a inserção sem ordem (no início)
    inserirLista(lista, 20);
    inserirLista(lista, 1);
    exibirLista(lista); // Esperado: 1 -> 20 -> 3 -> 7 -> 10 -> 15 -> NULL

    // Testando busca
    int valorBusca = 10;
    No *busca = buscarLista(lista, valorBusca);
    if (busca) {
        printf("Elemento %d encontrado na lista.\n", valorBusca);
    } else {
        printf("Elemento %d não encontrado na lista.\n", valorBusca);
    }

    // Verificando se a lista está vazia
    if (verificarVazia(lista)) {
        printf("A lista está vazia.\n");
    } else {
        printf("A lista não está vazia.\n");
    }

    // Testando exclusão
    excluirLista(lista, 7); // Elemento no meio da lista
    exibirLista(lista); // Esperado: 1 -> 20 -> 3 -> 10 -> 15 -> NULL
    excluirLista(lista, 1); // Elemento no início
    exibirLista(lista); // Esperado: 20 -> 3 -> 10 -> 15 -> NULL
    excluirLista(lista, 100); // Elemento que não está na lista

    // Liberando lista
    liberarLista(lista);
    if (verificarVazia(lista)) {
        printf("A lista está vazia após liberar.\n");
    }

    // Liberar memória da estrutura da lista
    free(lista);
    return 0;
}