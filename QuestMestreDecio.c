#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10

// Estruturas de Dados
typedef struct PistaNode {
    char conteudo[50];
    struct PistaNode *esq, *dir;
} PistaNode;

typedef struct HashNode {
    char pista[50];
    char suspeito[50];
    struct HashNode *proximo;
} HashNode;

typedef struct Sala {
    char nome[50];
    char pista[50];
    struct Sala *esquerda, *direita;
} Sala;

// --- FUNÇÕES DE DOCUMENTAÇÃO OBRIGATÓRIA ---

/* criarSala() – Cria dinamicamente um cômodo com nome e sua pista fixa. */
Sala* criarSala(char* nome, char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = nova->direita = NULL;
    return nova;
}

/* inserirPista() – Insere a pista coletada na árvore BST de forma ordenada. */
PistaNode* inserirPista(PistaNode* raiz, char* conteudo) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->conteudo, conteudo);
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (strcmp(conteudo, raiz->conteudo) < 0) raiz->esq = inserirPista(raiz->esq, conteudo);
    else if (strcmp(conteudo, raiz->conteudo) > 0) raiz->dir = inserirPista(raiz->dir, conteudo);
    return raiz;
}

/* inserirNaHash() – Insere associação pista/suspeito na tabela hash (tratando colisões). */
void inserirNaHash(HashNode* tabela[], char* pista, char* suspeito) {
    int indice = strlen(pista) % HASH_SIZE;
    HashNode* novo = (HashNode*)malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->proximo = tabela[indice];
    tabela[indice] = novo;
}

/* encontrarSuspeito() – Consulta a Hash para saber quem a pista incrimina. */
char* encontrarSuspeito(HashNode* tabela[], char* pista) {
    int indice = strlen(pista) % HASH_SIZE;
    HashNode* atual = tabela[indice];
    while (atual) {
        if (strcmp(atual->pista, pista) == 0) return atual->suspeito;
        atual = atual->proximo;
    }
    return "Desconhecido";
}

/* verificarSuspeitoFinal() – Conta pistas na BST via Hash e valida a acusação. */
void contarPistasDoSuspeito(PistaNode* raiz, HashNode* tabela[], char* acusado, int* contador) {
    if (raiz == NULL) return;
    contarPistasDoSuspeito(raiz->esq, tabela, acusado, contador);
    if (strcmp(encontrarSuspeito(tabela, raiz->conteudo), acusado) == 0) (*contador)++;
    contarPistasDoSuspeito(raiz->dir, tabela, acusado, contador);
}

void exibirInOrder(PistaNode* raiz) {
    if (raiz == NULL) return;
    exibirInOrder(raiz->esq);
    printf("- %s\n", raiz->conteudo);
    exibirInOrder(raiz->dir);
}

/* explorarSalas() – Navega pela árvore, exibe e coleta pistas. */
void explorarSalas(Sala* raiz, HashNode* tabela[]) {
    Sala* atual = raiz;
    PistaNode* inventario = NULL;
    char escolha, acusado[50];
    int pistasCulpado = 0;

    while (atual) {
        printf("\n[SALA]: %s\n", atual->nome);
        if (strlen(atual->pista) > 0) {
            printf("[PISTA ENCONTRADA]: %s\n", atual->pista);
            inventario = inserirPista(inventario, atual->pista);
        }
        printf("Comandos: (e)sq, (d)ir, (s)air: ");
        scanf(" %c", &escolha);
        if (escolha == 's') break;
        if (escolha == 'e' && atual->esquerda) atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita) atual = atual->direita;
    }

    printf("\n--- JULGAMENTO FINAL ---\nSuas pistas:\n");
    exibirInOrder(inventario);
    printf("\nQuem voce acusa? ");
    scanf("%s", acusado);

    contarPistasDoSuspeito(inventario, tabela, acusado, &pistasCulpado);

    if (pistasCulpado >= 2) printf("\n[SUCESSO] %s foi preso(a)! Voce encontrou %d pistas determinantes.\n", acusado, pistasCulpado);
    else printf("\n[FALHA] Provas insuficientes contra %s. O culpado escapou!\n", acusado);
}

int main() {
    HashNode* tabelaSuspeitos[HASH_SIZE] = {NULL};
    
    // Configuração da Tabela Hash (Pista -> Suspeito)
    inserirNaHash(tabelaSuspeitos, "Veneno", "Cozinheiro");
    inserirNaHash(tabelaSuspeitos, "Faca Amolada", "Cozinheiro");
    inserirNaHash(tabelaSuspeitos, "Livro Raro", "Bibliotecario");
    inserirNaHash(tabelaSuspeitos, "Oculos", "Bibliotecario");

    // Montagem da Mansão
    Sala* hall = criarSala("Hall", "");
    hall->esquerda = criarSala("Cozinha", "Veneno");
    hall->direita = criarSala("Biblioteca", "Livro Raro");
    hall->esquerda->esquerda = criarSala("Despensa", "Faca Amolada");
    hall->direita->direita = criarSala("Sala de Leitura", "Oculos");

    printf("Detective Quest: Edicao Final\n");
    explorarSalas(hall, tabelaSuspeitos);

    return 0;
}