#include "librerias.h"

// Implementación de las funciones
void mostrarCaratula() {
    printf("\n\tMATEMATICAS DISCRETAS 1\n");
    printf("\tMartin Jimenez - Denis Rojas\n");
    printf("\tDESCRIPCION: Programa que genera una expresion SOP a partir de una tabla de verdad.\n");
    printf("\tSemestre 202510\n\n");
}

int ingresarNumeroDeVariables() {
    int variables;
    do {
        printf("Digite el numero de variables logicas (2 o 3): ");
        scanf("%d", &variables);
        if (variables != 2 && variables != 3) {
            printf("Error: Solo se permite ingresar 2 o 3.\n");
        }
    } while (variables != 2 && variables != 3);
    return variables;
}

void generarTablaDeVerdad(int variables, int tabla[][3]) {
    int filas = 1 << variables; // 2^variables
    int i, j;
    for (i = 0; i < filas; i++) {
        for (j = 0; j < variables; j++) {
            tabla[i][j] = (i >> (variables - j - 1)) & 1; // Calcula el valor binario de la fila
        }
    }
}

void ingresarValoresDeSalida(int variables, int tabla[][3]) {
    int filas = 1 << variables;
    int i;
    printf("Ingrese los valores de salida (0 o 1) para cada fila de la tabla de verdad:\n");
    for (i = 0; i < filas; i++) {
        printf("Fila %d: ", i + 1);
        scanf("%d", &tabla[i][variables]);
        while (tabla[i][variables] != 0 && tabla[i][variables] != 1) {
            printf("Error: Solo se permite ingresar 0 o 1. Intente nuevamente: ");
            scanf("%d", &tabla[i][variables]);
        }
    }
}

void generarExpresionBooleana(int variables, int tabla[][3], char* expresion) {
    int filas = 1 << variables;
    int i, j;
    strcpy(expresion, ""); // Inicializar la cadena de la expresión
    for (i = 0; i < filas; i++) {
        if (tabla[i][variables] == 1) { // Solo consideramos las salidas con valor 1
            if (strlen(expresion) > 0) {
                strcat(expresion, " + "); // Añadir el operador OR si ya hay un término
            }
            for (j = 0; j < variables; j++) {
                if (tabla[i][j] == 0) {
                    strcat(expresion, "!"); // Añadir NOT si el valor de entrada es 0
                }
                char variable = 'A' + j; // Usar 'A', 'B', 'C' como nombres de las variables
                strncat(expresion, &variable, 1);
            }
        }
    }
}

void mostrarTablaDeVerdadConExpresion(int variables, int tabla[][3], const char* expresion) {
    int filas = 1 << variables;

    // Mostrar encabezado
    printf("\nTabla de verdad de la expresion %s:\n\n", expresion);
    printf("A B\t\t!A*B\t\tA*!B\t\tA'B + AB'\tSalida\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < filas; i++) {
        int A = tabla[i][0];
        int B = tabla[i][1];
        int notA_and_B = (!A && B);
        int A_and_notB = (A && !B);
        int resultado = notA_and_B || A_and_notB;

        // Mostrar entradas
        printf("%d %d\t\t", A, B);

        // Mostrar resultados parciales sin colores
        printf("%d\t\t", notA_and_B);
        printf("%d\t\t", A_and_notB);
        printf("%d\t\t", resultado);

        // Mostrar salida final
        printf("%d\n", tabla[i][2]);
    }
}

// Función principal
int main() {
    char opcion;
    do {
        mostrarCaratula();

        int variables = ingresarNumeroDeVariables();
        int filas = 1 << variables; // Calcula 2^variables
        int tabla[filas][3]; // Tabla de verdad (máximo para 3 variables)

        generarTablaDeVerdad(variables, tabla);
        ingresarValoresDeSalida(variables, tabla);

        char expresion[256]; // Para almacenar la expresión booleana
        generarExpresionBooleana(variables, tabla, expresion);

        mostrarTablaDeVerdadConExpresion(variables, tabla, expresion);

        printf("\nDesea realizar otra operacion? (s/n): ");
        scanf(" %c", &opcion);

    } while (opcion == 's' || opcion == 'S');

    printf("\nFin del programa.\n");
    return 0;
}

