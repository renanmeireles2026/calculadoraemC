#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

// Maior posição aceita no Fibonacci recursivo: o número de chamadas cresce
// de forma exponencial, então valores muito grandes deixariam o programa lento
#define LIMITE_FIBONACCI 35

// Nó da lista simplesmente encadeada que guarda cada multiplicação realizada
typedef struct nomultiplicacao {
    float valor1;
    float valor2;
    float resultado;
    struct nomultiplicacao *proximo;
} nomultiplicacao;

// Início da lista de multiplicações (vazia no começo)
nomultiplicacao *lista_multiplicacoes = NULL;

// Cria um nó com a operação e o resultado e o insere no final da lista,
// mantendo a ordem em que os cálculos foram realizados
void inserir_multiplicacao(float valor1, float valor2, float resultado) {
    nomultiplicacao *novo = (nomultiplicacao *) malloc(sizeof(nomultiplicacao));

    if (novo == NULL) {
        printf("Erro ao alocar memória para o histórico!\n");
        return;
    }

    novo->valor1 = valor1;
    novo->valor2 = valor2;
    novo->resultado = resultado;
    novo->proximo = NULL;

    if (lista_multiplicacoes == NULL) {
        lista_multiplicacoes = novo;
    } else {
        nomultiplicacao *atual = lista_multiplicacoes;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}

// Percorre a lista e apresenta todas as multiplicações realizadas
void listar_multiplicacoes() {
    nomultiplicacao *atual = lista_multiplicacoes;
    int contador = 1;

    if (atual == NULL) {
        printf("Nenhuma multiplicação foi realizada ainda.\n");
    } else {
        while (atual != NULL) {
            printf("%d) %.2f x %.2f = %.2f\n", contador, atual->valor1, atual->valor2, atual->resultado);
            atual = atual->proximo;
            contador++;
        }
    }

    printf("\nPressione ENTER para voltar ao menu...");
    getchar(); // limpa buffer
    getchar(); // aguarda enter
}

// Libera a memória de todos os nós da lista
void liberar_multiplicacoes() {
    nomultiplicacao *atual = lista_multiplicacoes;

    while (atual != NULL) {
        nomultiplicacao *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista_multiplicacoes = NULL;
}

void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Descarta o que sobrou na linha de entrada para não atrapalhar a próxima leitura.
// Retorna 1 se só havia espaços até o fim da linha e 0 se havia mais caracteres
// (por exemplo, o ".5" de "2.5" quando o programa esperava um inteiro).
int limpar_buffer() {
    int c, so_espacos = 1;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c != ' ' && c != '\t' && c != '\r') {
            so_espacos = 0;
        }
    }
    return so_espacos;
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
    inserir_multiplicacao(valor1, valor2, resultado);

    do {
        printf("\nDigite 1 para multiplicar o resultado por mais um valor ou 0 para voltar ao menu: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Digite o valor a multiplicar: ");
            scanf("%f", &valornovo);
            salvar_no_arquivo(3, "multiplicacao", resultado, valornovo, resultado * valornovo, 2);
            inserir_multiplicacao(resultado, valornovo, resultado * valornovo);
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

// Função recursiva de potenciação (expoente deve ser inteiro e >= 0)
//   Caso-base:     base^0 = 1
//   Caso recursivo: base^expoente = base * base^(expoente - 1)
// Cada chamada reduz o expoente em 1, então a recursão sempre chega ao caso-base.
double potencia(double base, int expoente) {
    if (expoente == 0) {            // caso-base: qualquer número elevado a 0 vale 1
        return 1;
    }
    return base * potencia(base, expoente - 1);   // caso recursivo
}

void exponenciacao(){
    double base, resultado;
    int expoente, lido, opcao;
    FILE *arquivo;

    do {
        printf("Digite a base: ");
        lido = scanf("%lf", &base);
        if (!limpar_buffer() && lido == 1) {
            lido = 0;               // sobrou texto na linha (ex.: "2abc"): entrada inválida
        }
        while (lido != 1) {
            if (lido == EOF) {
                return;             // entrada encerrada: volta ao menu
            }
            printf("Base inválida! Digite um número: ");
            lido = scanf("%lf", &base);
            if (!limpar_buffer() && lido == 1) {
                lido = 0;
            }
        }

        // Validação do expoente: precisa ser um inteiro maior ou igual a 0
        printf("Digite o expoente (inteiro maior ou igual a 0): ");
        lido = scanf("%d", &expoente);
        if (!limpar_buffer() && lido == 1) {
            lido = 0;               // ex.: "2.5" não é um inteiro
        }
        while (lido != 1 || expoente < 0) {
            if (lido == EOF) {
                return;
            }
            printf("Expoente inválido! O expoente deve ser um inteiro maior ou igual a 0.\n");
            printf("Digite o expoente novamente: ");
            lido = scanf("%d", &expoente);
            if (!limpar_buffer() && lido == 1) {
                lido = 0;
            }
        }

        resultado = potencia(base, expoente);

        // %.10g mostra 2 em vez de 2.00 e 8 em vez de 8.00 (formato: 2 ^ 3 = 8)
        printf("\n%.10g ^ %d = %.10g\n", base, expoente, resultado);

        arquivo = fopen("numero.txt", "a");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo numero.txt\n");
        } else {
            fprintf(arquivo, "%.10g ^ %d = %.10g\n", base, expoente, resultado);
            fclose(arquivo);
        }

        printf("\nDigite 1 para calcular outra potência ou 0 para voltar ao menu: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = 0;              // entrada inválida ou encerrada: volta ao menu
        }
        limpar_buffer();
        printf("\n");
    } while (opcao != 0);
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

// Retorna o n-ésimo número da sequência de Fibonacci (0, 1, 1, 2, 3, 5, 8, ...)
//   Caso-base:     fibonacci(0) = 0  e  fibonacci(1) = 1
//   Caso recursivo: fibonacci(n) = fibonacci(n - 1) + fibonacci(n - 2), para n >= 2
// Observação: cada chamada com n >= 2 gera duas novas chamadas, por isso o
// custo cresce de forma exponencial (as mesmas posições são recalculadas várias vezes).
long long fibonacci(int n) {
    if (n == 0) {                   // caso-base 1
        return 0;
    }
    if (n == 1) {                   // caso-base 2
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);   // caso recursivo
}

// Opção 8 do menu: lê a posição n, mostra a sequência até n e o valor de Fibonacci(n)
void calcular_fibonacci(){
    int n, lido, i;
    long long resultado;
    FILE *arquivo;

    printf("Digite a posição n (inteiro entre 0 e %d): ", LIMITE_FIBONACCI);
    lido = scanf("%d", &n);
    if (!limpar_buffer() && lido == 1) {
        lido = 0;
    }
    while (lido != 1 || n < 0 || n > LIMITE_FIBONACCI) {
        if (lido == EOF) {
            return;
        }
        printf("Valor inválido! Digite um inteiro entre 0 e %d: ", LIMITE_FIBONACCI);
        lido = scanf("%d", &n);
        if (!limpar_buffer() && lido == 1) {
            lido = 0;
        }
    }

    // Mostra os termos de Fibonacci(0) até Fibonacci(n)
    printf("\nSequência: ");
    for (i = 0; i <= n; i++) {
        printf("%lld", fibonacci(i));
        if (i < n) {
            printf(", ");
        }
    }

    resultado = fibonacci(n);
    printf("\n\nFibonacci(%d) = %lld\n", n, resultado);

    arquivo = fopen("numero.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo numero.txt\n");
    } else {
        fprintf(arquivo, "Fibonacci(%d) = %lld\n", n, resultado);
        fclose(arquivo);
    }

    printf("\nPressione ENTER para voltar ao menu...");
    getchar(); // aguarda enter (o buffer já foi limpo)
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
        printf("13 - Listar multiplicações\n");
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
            case 8:
                exibir_cabecalho("OPÇÃO 8: SEQUÊNCIA DE FIBONACCI");
                calcular_fibonacci();
                break;
            case 13:
                exibir_cabecalho("OPÇÃO 13: LISTAR MULTIPLICAÇÕES");
                listar_multiplicacoes();
                break;
            case 0:
                liberar_multiplicacoes();
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
