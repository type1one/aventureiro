#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Estrutura que representa um território do jogo */
typedef struct {
    char nome[30];   // nome do território
    char cor[10];    // cor/dono (ex: Vermelho, Azul)
    int tropas;      // quantidade de tropas
} Territorio;

/* Função que realiza um ataque entre dois territórios */
void atacar(Territorio *atacante, Territorio *defensor) {
    // Sorteia valores de 1 a 6 para cada lado (como rolar um dado)
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\n>>> Ataque de %s (%s) contra %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado Atacante: %d  |  Dado Defensor: %d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        // Se o atacante vencer, transfere metade das tropas
        int transf = atacante->tropas / 2;
        if (transf < 1) transf = 1; // garante pelo menos 1 tropa
        printf("Atacante venceu! %s agora pertence a %s\n",
               defensor->nome, atacante->cor);

        // Atualiza cor e tropas do defensor
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = transf;

        // Reduz tropas do atacante
        atacante->tropas -= transf;
        if (atacante->tropas < 1) atacante->tropas = 1; // mantém mínimo de 1 tropa
    } else {
        // Se o defensor vencer ou empatar, atacante perde 1 tropa
        printf("Defensor venceu! %s perde 1 tropa.\n", atacante->nome);
        atacante->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    int n;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &n);
    getchar(); // limpa o \n que ficou no buffer

    // Alocação dinâmica de memória para os territórios
    Territorio *mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro de cada território
    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d:\n", i);
        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0; // remove quebra de linha

        printf("Cor/dono: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }

    int opc;
    do {
        // Menu simples
        printf("\n--- MENU ---\n");
        printf("1 - Mostrar territorios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opc);
        getchar();

        if (opc == 1) {
            // Mostra os territórios cadastrados
            for (int i = 0; i < n; i++) {
                printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
                       i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
            }
        } else if (opc == 2) {
            // Escolha de atacante e defensor
            int ia, id;
            printf("Indice atacante: ");
            scanf("%d", &ia);
            printf("Indice defensor: ");
            scanf("%d", &id);
            getchar();

            // Validações básicas
            if (ia == id || ia < 0 || id < 0 || ia >= n || id >= n) {
                printf("Escolha invalida!\n");
                continue;
            }
            if (strcmp(mapa[ia].cor, mapa[id].cor) == 0) {
                printf("Nao pode atacar territorio da mesma cor!\n");
                continue;
            }
            if (mapa[ia].tropas < 2) {
                printf("Atacante precisa de pelo menos 2 tropas!\n");
                continue;
            }

            // Chama a função de ataque usando ponteiros
            atacar(&mapa[ia], &mapa[id]);
        }

    } while (opc != 0);

    // Libera a memória alocada antes de encerrar
    free(mapa);
    printf("Programa encerrado. Memoria liberada.\n");
    return 0;
}
