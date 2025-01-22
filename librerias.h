#ifndef LIBRERIAS_H
#define LIBRERIAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaraciones de funciones
void mostrarCaratula();
int ingresarNumeroDeVariables();
void generarTablaDeVerdad(int variables, int tabla[][3]);
void ingresarValoresDeSalida(int variables, int tabla[][3]);
void generarExpresionBooleana(int variables, int tabla[][3], char* expresion);
void mostrarTablaDeVerdadConExpresion(int variables, int tabla[][3], const char* expresion);

#endif

