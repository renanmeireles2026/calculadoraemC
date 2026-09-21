//façam funcionar em linux e IOS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define TOTAL_OPCOES 13

// Códigos das teclas do teclado no Windows
#define TECLA_CIMA 72
#define TECLA_BAIXO 80
#define TECLA_ENTER 13

void limparTela() {
    system("cls");
}

void soma() {
    limparTela();
    double valor1, valor2, valornovo, resultado;
    int opcao;

    printf("--- OPERAÇÃO DE SOMA ---\n");
    printf("Digite o primeiro valor: ");
    scanf("%lf", &valor1);
    printf("Digite o segundo valor: ");
    scanf("%lf", &valor2);

    resultado = valor1 + valor2;
    printf("Resultado: %.2f\n", resultado);

    do {
        printf("\nDigite 1 para somar mais um valor ou 0 para voltar ao menu: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Digite o valor a somar: ");
            scanf("%lf", &valornovo);
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
    scanf("%lf", &valor1);
    printf("Digite o segundo valor: ");
    scanf("%lf", &valor2);

    resultado = valor1 - valor2;
    printf("Resultado: %.2f\n", resultado);

    do {
        printf("\nDigite 1 para subtrair mais um valor ou 0 para voltar ao menu: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Digite o valor a subtrair: ");
            scanf("%lf", &valornovo);
            resultado = resultado - valornovo;
            printf("Resultado parcial: %.2f\n", resultado);
        }
    } while (opcao != 0);
}

int main() {
    // Configura o terminal para aceitar acentuação/caracteres UTF-8 no Windows
    SetConsoleOutputCP(65001);

    int selecao = 0;
    int tecla;
    int piscando = 1;

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
        // Redesenha a tela
        limparTela();

        printf("===============================\n          CALCULADORA \n===============================\n");
        printf("Use as setas (▲/▼) e pressione ENTER:\n\n");

        for (int i = 0; i < TOTAL_OPCOES; i++) {
            if (i == selecao) {
                // Se for a opção selecionada, alterna o caractere para criar o efeito piscando
                if (piscando) {
                    printf("  [>] %s <\n", opcoes[i]);
                } else {
                    printf("   >  %s\n", opcoes[i]);
                }
            } else {
                printf("      %s\n", opcoes[i]);
            }
        }

        // Verifica se há alguma tecla pressionada no teclado sem interromper o loop
        if (_kbhit()) {
            tecla = _getch();

            // Teclas de seta no Windows retornam um caractere nulo (0 ou 224) primeiro
            if (tecla == 0 || tecla == 224) {
                tecla = _getch(); // Lê o segundo código real da tecla
                if (tecla == TECLA_CIMA) {
                    selecao--;
                    if (selecao < 0) selecao = TOTAL_OPCOES - 1; // Volta ao final se passar do topo
                } else if (tecla == TECLA_BAIXO) {
                    selecao++;
                    if (selecao >= TOTAL_OPCOES) selecao = 0; // Volta ao topo se passar do final
                }
            } else if (tecla == TECLA_ENTER) {
                // Ações do menu baseadas na seleção do usuário
                if (selecao == 0) {
                    soma();
                } else if (selecao == 1) {
                    subtracao();
                } else if (selecao == TOTAL_OPCOES - 1) { // Posição do "Sair"
                    limparTela();
                    printf("Encerrando a calculadora...\n");
                    break;
                } else {
                    limparTela();
                    printf("Opção \"%s\" ainda não implementada.\n", opcoes[selecao]);
                    printf("Pressione qualquer tecla para voltar ao menu...");
                    _getch();
                }
            }
        }

        // Altera o estado do marcador a cada 200 milissegundos (efeito de piscar)
        Sleep(200);
        piscando = !piscando;
    }

    return 0;
}
