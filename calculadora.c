#include <stdio.h>
#include <math.h>

void soma(){
    double valor1, valor2, valornovo, resultado;
    int opcao;

    printf("digitar primeiro valor:");
    scanf("%lf", &valor1);
    printf("Digite o segundo valor:");
    scanf("%lf", &valor2);

    resultado = valor1 + valor2;
    printf("resultado: %.2f\n", resultado);

    do {
        printf("Digite 1 para somar mais um valor ou 0 pra voltar pro menu: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Digite o valor a somar: ");
            scanf("%lf", &valornovo);
            resultado = resultado + valornovo;
            printf("Resultado: %.2f\n", resultado);
        }
    } while (opcao != 0);
}

void subtracao(){
    double valor1, valor2, valornovo, resultado;
    int opcao;

    printf("digite o primeiro valor:");
    scanf("%lf", &valor1);
    printf("digite o segundo valor:");
    scanf("%lf", &valor2);

    resultado = valor1 - valor2;
    printf("resultado: %.2f\n", resultado);

    do {
        printf("digite 1 para subtrair mais um valor do resultado ou 0 para voltar ao menu");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("digite o valor a subtrair: ");
            scanf("%lf", &valornovo);
            resultado = resultado - valornovo;
            printf("resultado: %.2f\n", resultado);
        }
    } while (opcao != 0);
}

int main(){
    int opcao;

    do {
        printf("===============================\n          CALCULADORA \n===============================\n");
        printf("Escolha a operação desejada:\n");
        printf("1 - Soma\n");
        printf("2 - Subtração\n");
        printf("3 - Multiplicação\n");
        printf("4 - Divisão\n");
        printf("5 - Exponenciação\n");
        printf("6 - Raiz Quadrada\n");
        printf("7 - soma de n valores\n");
        printf("8 - Cálculo da Sequência de Fibonacci\n");
        printf("9 - Área do círculo\n");
        printf("10 - Área do triângulo\n");
        printf("11 - Volume do cubo\n");
        printf("12 - Volume do cilindro\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                soma();
                break;
            case 2:
                subtracao();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida ou ainda não implementada.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
