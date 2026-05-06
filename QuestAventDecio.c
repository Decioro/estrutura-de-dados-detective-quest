#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para os nós da Árvore de Pistas (BST)
typedef struct PistaNode {
    char conteudo[50];
    struct PistaNode *esq, *dir;
} PistaNode;

// Estrutura para os cômodos da Mansão (Árvore Binária)
typedef struct Sala {
    char nome[30];
    char pista[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/* 
 * criarSala() – Cria dinamicamente um cômodo.
 * Recebe o nome da sala e a descrição da pista nela contida.
 */
Sala* criarSala(char* nome, char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    if (nova) {
        strcpy(nova->nome, nome);
        strcpy(nova->pista, pista);
        nova->esquerda = NULL;
        nova->direita = NULL;
    }
    return nova;
}

/* 
 * inserirPista() – Insere uma nova pista na BST de forma ordenada (alfabética).
 */
PistaNode* inserirPista(PistaNode* raiz, char* conteudo) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->conteudo, conteudo);
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (strcmp(conteudo, raiz->conteudo) < 0)
        raiz->esq = inserirPista(raiz->esq, conteudo);
    else
        raiz->dir = inserirPista(raiz->dir, conteudo);
    return raiz;
}

/* 
 * exibirPistas() – Percorre a BST (In-Order) para imprimir as pistas em ordem alfabética.
 */
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esq);
        printf("- %s\n", raiz->conteudo);
        exibirPistas(raiz->dir);
    }
}

/* 
 * explorarSalasComPistas() – Gerencia a navegação e a coleta automática de pistas.
 */
void explorarSalasComPistas(Sala* mapa) {
    Sala* atual = mapa;
    PistaNode* inventarioPistas = NULL;
    char escolha;

    printf("\n--- Inicio da Investigacao: Detective Quest ---\n");

    while (atual != NULL) {
        printf("\n[LOCALIZACAO]: %s\n", atual->nome);
        
        // Coleta automática de pista se houver
        if (strlen(atual->pista) > 0) {
            printf("[!] Pista encontrada: %s\n", atual->pista);
            inventarioPistas = inserirPista(inventarioPistas, atual->pista);
        }

        printf("Opcoes: ");
        if (atual->esquerda) printf("(e) Ir para %s | ", atual->esquerda->nome);
        if (atual->direita) printf("(d) Ir para %s | ", atual->direita->nome);
        printf("(s) Sair e analisar pistas\n");
        
        printf("Escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 's') break;
        if (escolha == 'e' && atual->esquerda) atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita) atual = atual->direita;
        else printf("[!] Caminho invalido.\n");
    }

    printf("\n--- RELATORIO FINAL DE PISTAS (Ordem Alfabetica) ---\n");
    if (inventarioPistas == NULL) printf("Nenhuma pista coletada.\n");
    else exibirPistas(inventarioPistas);
}

/* 
 * main() – Monta o mapa pré-definido e inicia a jornada.
 */
int main() {
    // Montagem da mansão com pistas associadas
    Sala* hall = criarSala("Hall de Entrada", "Chave enferrujada");
    hall->esquerda = criarSala("Cozinha", "Anotacao sobre veneno");
    hall->direita = criarSala("Biblioteca", "Livro com fundo falso");
    
    hall->esquerda->esquerda = criarSala("Despensa", "Pegadas de lama");
    hall->direita->direita = criarSala("Jardim", "Arame cortado");

    explorarSalasComPistas(hall);

    return 0;
}