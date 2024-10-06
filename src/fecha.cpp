/******************************************************************************\
 * Curso de Programación 1. Tema 11 (Registros) y trabajo obligatorio 2021-22
 * Autores: Javier Martínez y Miguel Ángel Latre
 * Última revisión: 5 de diciembre de 2021
 * Resumen: Fichero de implementación «fecha.cpp» del módulo «fecha».
\******************************************************************************/

#include "fecha.hpp"
#include <iostream>
using namespace std;

/*
 * Pre:  ---
 * Post: Ha escrito la fecha «dia» en el flujo «f».
 */
void mostrar(ostream& f, const Fecha dia) {
    f << dia.dia << "-" << dia.mes << "-" << dia.agno;
}


/*
 * Pre:  agno > 1582.
 * Post: Ha devuelto true si y solo si el año «agno» es bisiesto de
 *       acuerdo con las reglas del calendario gregoriano.
 */
bool esBisiesto(unsigned agno) {
    bool multiplo4   = (agno %   4 == 0);
    bool multiplo100 = (agno % 100 == 0);
    bool multiplo400 = (agno % 400 == 0);
    return multiplo400 || (multiplo4 && !multiplo100);
}


/*
 * Pre:  1 ≤ mes ≤ 12 y agno > 1582.
 * Post: Ha devuelto el número de días del mes correspondiente al parámetro «mes»
 *       del año correspondiente al parámetro «agno».
 *       Por ejemplo: diasDelMes(10, 2018) devuelve 31,
 *                    diasDelMes(2, 2018) devuelve 28 y
 *                    diasDelMes(2, 2020) devuelve 29.
 */
unsigned diasDelMes(unsigned mes, unsigned agno) {
    if (mes == 2) {
        if (esBisiesto(agno)) {
            return 29;
        }
        else {
            return 28;
        }
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        return 30;
    }
    else {
        return 31;
    }
}


/*
 * Pre:  agno > 1582.
 * Post: Ha devuelto el número de días que tiene el año «agno».
 *       Por ejemplo: diasDelAgno(2018) devuelve 365 y
 *                    diasDelAgno(2020) devuelve 366.
 */
unsigned diasDelAgno(unsigned agno) {
    if (esBisiesto(agno)) {
        return 366;
    }
    else {
        return 365;
    }
}


/*
 * Pre:  «inicial» es igual o anterior cronológicamente a «final».
 * Post: Ha devuelto el número de días transcurridos entre las fechas «inicial»
 *       y «final».
 */
unsigned diasTranscurridos(const Fecha inicial, const Fecha final) {
    if (inicial.agno == final.agno) {
        if (inicial.mes == final.mes) {
            return final.dia - inicial.dia;
        }
        else {
            unsigned dias = diasDelMes(inicial.mes, inicial.agno) - inicial.dia;
            for (unsigned mes = inicial.mes + 1; mes < final.mes; mes++) {
                dias += diasDelMes(mes, inicial.agno);
            }
            dias += final.dia;
            return dias;
        }
    }
    else {
        unsigned dias = diasTranscurridos(inicial, {31, 12, inicial.agno}) + 1;
        for (unsigned agno = inicial.agno + 1; agno < final.agno; agno++) {
            dias += diasDelAgno(agno);
        }
        dias += diasTranscurridos({1, 1, final.agno}, final);
        return dias;
    }
}