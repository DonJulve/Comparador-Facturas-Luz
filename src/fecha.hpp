/******************************************************************************\
 * Curso de Programación 1. Tema 11 (Registros) y trabajo obligatorio 2021-22
 * Autores: Javier Martínez y Miguel Ángel Latre
 * Última revisión: 5 de diciembre de 2021
 * Resumen: Fichero de interfaz «fecha.hpp» del módulo «fecha».
\******************************************************************************/
#pragma once
#include <ostream>
using namespace std;

/*
 * Definición del tipo de dato Fecha
 */
struct Fecha {
    unsigned dia, mes, agno;
};


/*
 * Pre:  ---
 * Post: Ha escrito la fecha «dia» en el flujo «f».
 */
void mostrar(ostream& f, const Fecha dia);


/*
 * Pre:  «inicial» es igual o anterior cronológicamente a «final».
 * Post: Ha devuelto el número de días transcurridos entre las fechas «inicial»
 *       y «final».
 */
unsigned diasTranscurridos(const Fecha inicial, const Fecha final);


