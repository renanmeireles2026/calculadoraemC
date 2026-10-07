#include <stdio.h>
#include <math.h>

void salvar_no_arquivo(char operacao[], float valor1, float valor2, float resultado, int qtd_valores){
    FILE *arquivo = fopen("numero.txt", "a");

    if (arquivo == NULL) {
        printf("erro ao abrir o arquivo numero.txt\n");
        return;
    }

    if (qtd_valores == 1) {
        fprintf(arquivo, "Operacao: %s | Numero: %.2f | Resultado: %.2f\n", operacao, valor1, resultado);
    } else {
        fprintf(arquivo, "Operacao: %s | Numeros: %.2f e %.2f | Resultado: %.2f\n", operacao, valor1, valor2, resultado);
    }

    fclose(arquivo);
}

void soma(){
    float valor1, valor2, valornovo, resultado;
    int opcao;

    printf("digitar primeiro valor:");
    scanf("%f", &valor1);
    printf("Digite o segundo valor:");
    scanf("%f", &valor2);

    resultado = valor1 + valor2;
    printf("resultado: %.2f\n", resultado);
    salvar_no_arquivo("soma", valor1, valor2, resultado, 2);

    do {
        printf("Digite 1 para somar mais um valor ou 0 pra voltar pro menu: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Digite o valor a somar: ");
            scanf("%f", &valornovo);
            salvar_no_arquivo("soma", resultado, valornovo, resultado + valornovo, 2);
            resultado = resultado + valornovo;
            printf("Resultado: %.2f\n", resultado);
        }
    } while (opcao != 0);
}

void subtracao(){
    float valor1, valor2, valornovo, resultado;
    int opcao;

    printf("digite o primeiro valor:");
    scanf("%f", &valor1);
    printf("digite o segundo valor:");
    scanf("%f", &valor2);

    resultado = valor1 - valor2;
    printf("resultado: %.2f\n", resultado);
    salvar_no_arquivo("subtracao", valor1, valor2, resultado, 2);

    do {
        printf("digite 1 para subtrair mais um valor do resultado ou 0 para voltar ao menu");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("digite o valor a subtrair: ");
            scanf("%f", &valornovo);
            salvar_no_arquivo("subtracao", resultado, valornovo, resultado - valornovo, 2);
            resultado = resultado - valornovo;
            printf("resultado: %.2f\n", resultado);
        }
    } while (opcao != 0);
}

void exponenciacao(){
    float base, expoente, resultado;

    printf("digite a base:");
    scanf("%f", &base);
    printf("digite o expoente:");
    scanf("%f", &expoente);

    resultado = pow(base, expoente);
    printf("resultado: %.2f\n", resultado);
    salvar_no_arquivo("exponenciacao", base, expoente, resultado, 2);
}

void raiz_quadrada(){
    float valor, resultado;

    printf("digite o valor:");
    scanf("%f", &valor);

    if (valor < 0) {
        printf("não existe raiz quadrada real de número negativo\n");
        return;
    }

    resultado = sqrt(valor);
    printf("resultado: %.2f\n", resultado);
    salvar_no_arquivo("raiz quadrada", valor, 0, resultado, 1);
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
            case 5:
                exponenciacao();
                break;
            case 6:
                raiz_quadrada();
                break;
            case 0:
                break;
            default:
                printf("nao existe");
                break;
        }
    } while (opcao != 0);

    return 0;
}
