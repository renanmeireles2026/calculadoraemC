#include <stdio.h>
#include <stdlib.h>

#define TOTAL_OPCOES 13

// Função para limpar o buffer de entrada do teclado (evita loops infinitos no scanf)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para limpar a tela compatível com Windows e Linux/macOS
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função para pausar a execução até o usuário pressionar Enter
void pausar() {
    printf("\nPressione ENTER para continuar...");
    limparBuffer();
    getchar();
}

void soma() {
    limparTela();
    double valor1, valor2, valornovo, resultado;
    int opcao;

    printf("--- OPERAÇÃO DE SOMA ---\n");
    printf("Digite o primeiro valor: ");
    if (scanf("%lf", &valor1) != 1) {
        limparBuffer();
        return;
    }
    printf("Digite o segundo valor: ");
    if (scanf("%lf", &valor2) != 1) {
        limparBuffer();
        return;
    }

    resultado = valor1 + valor2;
    printf("Resultado: %.2f\n", resultado);

    do {
        printf("\nDigite 1 para somar mais um valor ou 0 para voltar ao menu: ");
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = 0;
        }

        if (opcao == 1) {
            printf("Digite o valor a somar: ");
            if (scanf("%lf", &valornovo) != 1) {
                limparBuffer();
                continue;
            }
            resultado = resultado + valornovo;
            printf("Resultado parcial: %.2f\n", resultado);
        }
    } while (opcao != 0);
}

void subtracao() {
    limparTela();
    double valor1, valor2, valornovo, resultado;
    int opcao;

    printf("--- OPERAÇÃO DE SUBTRAÇÃO ---\n");
    printf("Digite o primeiro valor: ");
    if (scanf("%lf", &valor1) != 1) {
        limparBuffer();
        return;
    }
    printf("Digite o segundo valor: ");
    if (scanf("%lf", &valor2) != 1) {
        limparBuffer();
        return;
    }

    resultado = valor1 - valor2;
    printf("Resultado: %.2f\n", resultado);

    do {
        printf("\nDigite 1 para subtrair mais um valor ou 0 para voltar ao menu: ");
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = 0;
        }

        if (opcao == 1) {
            printf("Digite o valor a subtrair: ");
            if (scanf("%lf", &valornovo) != 1) {
                limparBuffer();
                continue;
            }
            resultado = resultado - valornovo;
            printf("Resultado parcial: %.2f\n", resultado);
        }
    } while (opcao != 0);
}

int main() {
    int opcao = 0;

    const char *opcoes[TOTAL_OPCOES] = {
        "Soma",
        "Subtração",
        "Multiplicação",
        "Divisão",
        "Exponenciação",
        "Raiz Quadrada",
        "Soma de N valores",
        "Cálculo da Sequência de Fibonacci",
        "Área do círculo",
        "Área do triângulo",
        "Volume do cubo",
        "Volume do cilindro",
        "Sair"
    };

    while (1) {
        limparTela();

        printf("===============================\n");
        printf("          CALCULADORA          \n");
        printf("===============================\n\n");

        for (int i = 0; i < TOTAL_OPCOES; i++) {
            printf("  [%2d] %s\n", i + 1, opcoes[i]);
        }

        printf("\nDigite o número da opção desejada: ");
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            continue;
        }

        if (opcao < 1 || opcao > TOTAL_OPCOES) {
            printf("\nOpção inválida! Tente novamente.\n");
            pausar();
            continue;
        }

        if (opcao == TOTAL_OPCOES) { // Opção 13: Sair
            limparTela();
            printf("Encerrando a calculadora...\n");
            break;
        } else if (opcao == 1) {
            soma();
        } else if (opcao == 2) {
            subtracao();
        } else {
            limparTela();
            printf("Opção \"%s\" ainda não implementada.\n", opcoes[opcao - 1]);
            pausar();
        }
    }

    return 0;
}
