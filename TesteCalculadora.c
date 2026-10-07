#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função para limpar a tela e exibir o cabeçalho com o nome da opção escolhida
void exibir_cabecalho(const char *titulo) {
    limpar_tela();
    printf("===============================\n");
    printf("  %s\n", titulo);
    printf("===============================\n\n");
}

void salvar_no_arquivo(int opcao, char operacao[], float valor1, float valor2, float resultado, int qtd_valores){
    FILE *arquivo = fopen("numero.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo numero.txt\n");
        return;
    }

    if (qtd_valores == 1) {
        fprintf(arquivo, "Opcao: %d - %s | Numero: %.2f | Resultado: %.2f\n", opcao, operacao, valor1, resultado);
    } else {
        fprintf(arquivo, "Opcao: %d - %s | Numeros: %.2f e %.2f | Resultado: %.2f\n", opcao, operacao, valor1, valor2, resultado);
    }

    fclose(arquivo);
}

void soma(){
    float valor1, valor2, valornovo, resultado;
    int opcao;

    printf("Digitar primeiro valor: ");
    scanf("%f", &valor1);
    printf("Digite o segundo valor: ");
    scanf("%f", &valor2);

    resultado = valor1 + valor2;
    printf("\nResultado: %.2f\n", resultado);
    salvar_no_arquivo(1, "soma", valor1, valor2, resultado, 2);

    do {
        printf("\nDigite 1 para somar mais um valor ou 0 para voltar ao menu: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Digite o valor a somar: ");
            scanf("%f", &valornovo);
            salvar_no_arquivo(1, "soma", resultado, valornovo, resultado + valornovo, 2);
            resultado = resultado + valornovo;
            printf("Resultado atualizado: %.2f\n", resultado);
        }
    } while (opcao != 0);
}

void subtracao(){
    float valor1, valor2, valornovo, resultado;
    int opcao;

    printf("Digite o primeiro valor: ");
    scanf("%f", &valor1);
    printf("Digite o segundo valor: ");
    scanf("%f", &valor2);

    resultado = valor1 - valor2;
    printf("\nResultado: %.2f\n", resultado);
    salvar_no_arquivo(2, "subtracao", valor1, valor2, resultado, 2);

    do {
        printf("\nDigite 1 para subtrair mais um valor do resultado ou 0 para voltar ao menu: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Digite o valor a subtrair: ");
            scanf("%f", &valornovo);
            salvar_no_arquivo(2, "subtracao", resultado, valornovo, resultado - valornovo, 2);
            resultado = resultado - valornovo;
            printf("Resultado atualizado: %.2f\n", resultado);
        }
    } while (opcao != 0);
}

void multiplicacao(){
    float valor1, valor2, valornovo, resultado;
    int opcao;

    printf("Digite o primeiro valor: ");
    scanf("%f", &valor1);
    printf("Digite o segundo valor: ");
    scanf("%f", &valor2);

    resultado = valor1 * valor2;
    printf("\nResultado: %.2f\n", resultado);
    salvar_no_arquivo(3, "multiplicacao", valor1, valor2, resultado, 2);

    do {
        printf("\nDigite 1 para multiplicar o resultado por mais um valor ou 0 para voltar ao menu: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Digite o valor a multiplicar: ");
            scanf("%f", &valornovo);
            salvar_no_arquivo(3, "multiplicacao", resultado, valornovo, resultado * valornovo, 2);
            resultado = resultado * valornovo;
            printf("Resultado atualizado: %.2f\n", resultado);
        }
    } while (opcao != 0);
}

void divisao(){
    float valor1, valor2, valornovo, resultado;
    int opcao;

    printf("Digite o dividendo: ");
    scanf("%f", &valor1);
    printf("Digite o divisor: ");
    scanf("%f", &valor2);

    while (valor2 == 0) {
        printf("Não é possível dividir por zero! Digite outro divisor: ");
        scanf("%f", &valor2);
    }

    resultado = valor1 / valor2;
    printf("\nResultado: %.2f\n", resultado);
    salvar_no_arquivo(4, "divisao", valor1, valor2, resultado, 2);

    do {
        printf("\nDigite 1 para dividir o resultado por mais um valor ou 0 para voltar ao menu: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Digite o divisor: ");
            scanf("%f", &valornovo);

            while (valornovo == 0) {
                printf("Não é possível dividir por zero! Digite outro divisor: ");
                scanf("%f", &valornovo);
            }

            salvar_no_arquivo(4, "divisao", resultado, valornovo, resultado / valornovo, 2);
            resultado = resultado / valornovo;
            printf("Resultado atualizado: %.2f\n", resultado);
        }
    } while (opcao != 0);
}

void exponenciacao(){
    float base, expoente, resultado;

    printf("Digite a base: ");
    scanf("%f", &base);
    printf("Digite o expoente: ");
    scanf("%f", &expoente);

    resultado = pow(base, expoente);
    printf("\nResultado: %.2f\n", resultado);
    salvar_no_arquivo(5, "exponenciacao", base, expoente, resultado, 2);

    printf("\nPressione ENTER para voltar ao menu...");
    getchar(); // limpa buffer
    getchar(); // aguarda enter
}

void raiz_quadrada(){
    float valor, resultado;

    printf("Digite o valor: ");
    scanf("%f", &valor);

    if (valor < 0) {
        printf("\nNão existe raiz quadrada real de número negativo!\n");
    } else {
        resultado = sqrt(valor);
        printf("\nResultado: %.2f\n", resultado);
        salvar_no_arquivo(6, "raiz quadrada", valor, 0, resultado, 1);
    }

    printf("\nPressione ENTER para voltar ao menu...");
    getchar(); // limpa buffer
    getchar(); // aguarda enter
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    do {
        exibir_cabecalho("CALCULADORA");
        printf("Escolha a operação desejada:\n");
        printf(" 1 - Soma\n");
        printf(" 2 - Subtração\n");
        printf(" 3 - Multiplicação\n");
        printf(" 4 - Divisão\n");
        printf(" 5 - Exponenciação\n");
        printf(" 6 - Raiz Quadrada\n");
        printf(" 7 - Soma de N valores\n");
        printf(" 8 - Cálculo da Sequência de Fibonacci\n");
        printf(" 9 - Área do círculo\n");
        printf("10 - Área do triângulo\n");
        printf("11 - Volume do cubo\n");
        printf("12 - Volume do cilindro\n");
        printf(" 0 - Sair\n\n");
        printf("Opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibir_cabecalho("OPÇÃO 1: SOMA");
                soma();
                break;
            case 2:
                exibir_cabecalho("OPÇÃO 2: SUBTRAÇÃO");
                subtracao();
                break;
            case 3:
                exibir_cabecalho("OPÇÃO 3: MULTIPLICAÇÃO");
                multiplicacao();
                break;
            case 4:
                exibir_cabecalho("OPÇÃO 4: DIVISÃO");
                divisao();
                break;
            case 5:
                exibir_cabecalho("OPÇÃO 5: EXPONENCIAÇÃO");
                exponenciacao();
                break;
            case 6:
                exibir_cabecalho("OPÇÃO 6: RAIZ QUADRADA");
                raiz_quadrada();
                break;
            case 0:
                limpar_tela();
                printf("Programa finalizado. Até logo!\n");
                break;
            default:
                exibir_cabecalho("OPÇÃO INVÁLIDA");
                printf("A opção digitada não existe!\n");
                printf("\nPressione ENTER para tentar novamente...");
                getchar();
                getchar();
                break;
        }
    } while (opcao != 0);

    return 0;
}
