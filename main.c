#include <stdio.h>
#include <stdlib.h>

/**
 * Simpletron Machine Language (SML)
 */

// E/S
#define READ 10  // Lê uma variável do dispositivo de entrada e coloca em uma posição da memória
#define WRITE 11 // Coloca na saída (terminal, monitor, etc) o valor de uma posição de memória

// CARREGAMENTO/ARMAZENAMENTO
#define LOAD 20  // coloca no ACC (Acumulador) o valor passado como argumento: 2011 coloca no acc o valor da posição de memória 11
#define STORE 21 // Armazena uma palavra do acumulador para uma posição da memória: 2110 coloca o valor de acc na posição 10 da memória

// com as duas operações acima, podemos criar operações matemáticas sucessivas por exemplo

// ARITMÉTICA
//
/**
 * As operações aritméticas sempre operam baseado no acumulador
 * Pegam o valor que está no acumulador e aplica o operando com o valor que vem na operação:
 *  Exemplos:
 *  * 3010 => ACC + valor da posição de memória 10
 *  * 3111 => ACC - valor da posição de memória 11
 */
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33

// TRANSFERÊNCIA DE CONTROLE
#define BRANCH 40     // desvia para uma posição de memória específica: 4023 vai para a posição 23 da memória
#define BRANCHNEG 41  // desvia para uma posição de memória específica se o valor que estiver no acc for negativo
#define BRANCHZERO 42 // desvia para uma posição de memória específica se o valor que estiver no acc for zero
#define HALT 43       // encerra o programa (4300)

/**
 * accumulator: é o registrador acumulador
 * instructionCounter: registrar o local na memória que contém  a instrução que está sendo executada (endereço)
 * instructionRegister: registra o valor em memória obtido através do endereço instructionCounter
 * operationCode: código da instrução atualmente em execução
 * operand: local da memória sendo executado
 */

void showInitialMenu()
{
    printf("*** Bem vindo ao Simpletron! ***\n");
    printf("*** Favor digitar seu programa, uma instrução ***\n");
    printf("*** (ou palavra de dados) por vez. Mostrarei ***\n");
    printf("*** o número do local e uma interrogação (?). ***\n");
    printf("*** Você, então, deverá digitar a palavra para esse ***\n");
    printf("*** local. Digite a sentinela -99999 para ***\n");
    printf("*** encerrar a entrada do seu programa. ***\n");
}

/**
 * TODO: melhorar esse modelo para incluir demais registradores presentes numa cpu atual
 */
int main()
{

    // int memory[] = {1009, 1010, 2009, 3110, 4107, 1109, 4300, 1110, 4300, 0000, 0000}; // memória
    int *memory = calloc(0, sizeof(int) * 100);
    const int arraySize = sizeof(memory) / sizeof(int);
    int Register;

    int accumulator = 0;         // acc => inicialmente 0000
    int instructionCounter = 0;  // ic => icicialmente 00
    int instructionRegister = 0; // ir => inicialmente 0000
    int operationCode = 0;       // opCode => inicialmente 00
    int operand = 0;             // 00

    showInitialMenu();

    // int *ptrMem;

    // ptrMem = memory;

    // ptrMem = ptrMem + 1; // incrementar de 1 em um move o ponteiro

    for (int instructionCounter = 0; instructionCounter < arraySize; instructionCounter++)
    {
        instructionRegister = memory[instructionCounter];

        operationCode = instructionRegister / 100;
        operand = instructionRegister % 100;

        switch (operationCode)
        {
        case READ:
            scanf("%d", &memory[operand]);
            break;

        case WRITE:
            printf("%d\n", memory[operand] % 100);
            break;

        case LOAD:
            accumulator = memory[operand];
            break;

        case STORE:
            break;

        case ADD:
            accumulator += memory[operand];
            break;

        case SUBTRACT:
            accumulator -= memory[operand];
            break;

        case DIVIDE:
            accumulator /= memory[operand];
            break;

        case MULTIPLY:
            accumulator *= memory[operand];
            break;

        case BRANCH:
            instructionCounter = operand;
            break;

        case BRANCHNEG:
            if (accumulator < 0)
            {
                instructionCounter = operand;
            }
            break;

        case BRANCHZERO:
            if (accumulator == 0)
            {
                instructionCounter = operand;
            }
            break;

        case HALT:
            printf("*** Execução do Simpletron encerrada ***");
            break;
        }
    }

    return 0;
}