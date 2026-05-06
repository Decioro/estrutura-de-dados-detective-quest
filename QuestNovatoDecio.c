#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura que representa cada cômodo da mansão
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/* 
 * Função: criarSala
 * Propósito: Aloca dinamicamente um novo nó (sala) na memória, 
 * define seu nome e inicializa os caminhos como nulos.
 */
Sala* criarSala(char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala != NULL) {
        strcpy(novaSala->nome, nome);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}

/* 
 * Função: explorarSalas
 * Propósito: Gerencia a interação com o jogador, permitindo a navegação 
 * pelos caminhos da árvore até que um nó-folha seja alcançado.
 */
void explorarSalas(Sala* raiz) {
    Sala* atual = raiz;
    char escolha;

    printf("\n--- Inicio da Investigacao ---\n");

    while (atual != NULL) {
        printf("\nVoce esta na sala: %s\n", atual->nome);

        // Verifica se é um nó-folha (fim da linha)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Nao ha mais caminhos a seguir. Voce chegou ao fim da mansao!\n");
            break;
        }

        printf("Caminhos disponiveis:\n");
        if (atual->esquerda != NULL) printf("[e] Esquerda: %s\n", atual->esquerda->nome);
        if (atual->direita != NULL) printf("[d] Direita: %s\n", atual->direita->nome);
        printf("[s] Sair do jogo\n");

        printf("Escolha sua direcao: ");
        scanf(" %c", &escolha);

        if (escolha == 's') {
            printf("Encerrando investigacao...\n");
            break;
        } else if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else {
            printf("\n[!] Escolha invalida ou caminho inexistente. Tente novamente.\n");
        }
    }
    printf("\n--- Investigacao Finalizada ---\n");
}

/* 
 * Função: main
 * Propósito: Monta a estrutura da mansão automaticamente e inicia o fluxo do jogo.
 */
int main() {
    // Montagem do Mapa (Árvore Binária)
    Sala* hall = criarSala("Hall de entrada");
    
    // Nível 1
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Biblioteca");
    
    // Nível 2
    hall->esquerda->esquerda = criarSala("Cozinha");
    hall->esquerda->direita = criarSala("Lavanderia");
    
    hall->direita->esquerda = criarSala("Escritorio");
    hall->direita->direita = criarSala("Jardim de Inverno");

    // Início da exploração interativa
    printf("Bem-vindo ao Detective Quest da Enigma Studios!\n");
    explorarSalas(hall);

    // Nota: Em um sistema completo, deve-se liberar a memória alocada antes de encerrar.
    return 0;
}