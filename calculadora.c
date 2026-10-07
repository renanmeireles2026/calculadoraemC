#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // Substitui o Sleep (usando usleep)
#include <termios.h>    // Necessário para manipular o terminal (substitui conio.h)
#include <fcntl.h>      // Necessário para leitura não-bloqueante do teclado

#define TOTAL_OPCOES 13

// Códigos das teclas de seta e enter no padrão POSIX/ANSI
#define TECLA_CIMA 65
#define TECLA_BAIXO 66
#define TECLA_ENTER 10

void limparTela() {
    // Sequência de escape ANSI para limpar a tela e resetar o cursor (mais rápido e seguro)
    printf("\e[1H\e[2J");
    fflush(stdout);
}

// Função equivalente ao _kbhit() do Windows para Linux/iOS
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// Função equivalente ao _getch() do Windows para Linux/iOS
int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void soma() {
    limparTela();
    double valor1, valor2, valornovo, resultado;
    int opcao;

    printf("--- OPERAÇÃO DE SOMA ---\n");
    printf("Digite o primeiro valor: ");
    if (scanf("%lf", &valor1) != 1) return;
    printf("Digite o segundo valor: ");
    if (scanf("%lf", &valor2) != 1) return;

    resultado = valor1 + valor2;
    printf("Resultado: %.2f\n", resultado);

    do {
        printf("\nDigite 1 para somar mais um valor ou 0 para voltar ao menu: ");
        if (scanf("%d", &opcao) != 1) opcao = 0;

        if (opcao == 1) {
            printf("Digite o valor a somar: ");
            if (scanf("%lf", &valornovo) != 1) continue;
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
    if (scanf("%lf", &valor1) != 1) return;
    printf("Digite o segundo valor: ");
    if (scanf("%lf", &valor2) != 1) return;

    resultado = valor1 - valor2;
    printf("Resultado: %.2f\n", resultado);

    do {
        printf("\nDigite 1 para subtrair mais um valor ou 0 para voltar ao menu: ");
        if (scanf("%d", &opcao) != 1) opcao = 0;

        if (opcao == 1) {
            printf("Digite o valor a subtrair: ");
            if (scanf("%lf", &valornovo) != 1) continue;
            resultado = resultado - valornovo;
            printf("Resultado parcial: %.2f\n", resultado);
        }
    } while (opcao != 0);
}

int main() {
    // Linux e iOS já usam UTF-8 nativamente no terminal, SetConsoleOutputCP não é necessário.

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
        limparTela();

        printf("===============================\n          CALCULADORA \n===============================\n");
        printf("Use as setas (▲/▼) e pressione ENTER:\n\n");

        for (int i = 0; i < TOTAL_OPCOES; i++) {
            if (i == selecao) {
                if (piscando) {
                    printf("  [>] %s <\n", opcoes[i]);
                } else {
                    printf("   >  %s\n", opcoes[i]);
                }
            } else {
                printf("      %s\n", opcoes[i]);
            }
        }

        // Verifica se há alguma tecla pressionada
        if (kbhit()) {
            tecla = getch();

            // No Linux/iOS, as setas enviam uma sequência de escape de 3 caracteres: 27, depois 91, e o código final
            if (tecla == 27) { 
                getch(); // Ignora o caractere '[' (91)
                tecla = getch(); // Pega o código real da seta
                
                if (tecla == TECLA_CIMA) {
                    selecao--;
                    if (selecao < 0) selecao = TOTAL_OPCOES - 1;
                } else if (tecla == TECLA_BAIXO) {
                    selecao++;
                    if (selecao >= TOTAL_OPCOES) selecao = 0;
                }
            } else if (tecla == TECLA_ENTER) {
                if (selecao == 0) {
                    soma();
                } else if (selecao == 1) {
                    subtracao();
                } else if (selecao == TOTAL_OPCOES - 1) {
                    limparTela();
                    printf("Encerrando a calculadora...\n");
                    break;
                } else {
                    limparTela();
                    printf("Opção \"%s\" ainda não implementada.\n", opcoes[selecao]);
                    printf("Pressione qualquer tecla para voltar ao menu...");
                    getch();
                }
            }
        }

        // usleep usa microssegundos (200ms = 200.000 microssegundos)
        usleep(200000);
        piscando = !piscando;
    }

    return 0;
}
