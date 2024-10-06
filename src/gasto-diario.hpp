/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autor: Miguel Ángel Latre
 * Ultima revisión: 5-12-2021
 * Resumen: Fichero de interfaz «gasto-diario.hpp» del módulo
 *          «gasto-diario» que contiene tipos registro y funciones para la
 *          gestión de datos horarios de consumo y precios de un día concreto.
\******************************************************************************/
#include "fecha.hpp"
#pragma once

/*
 * Número de horas de un día
 */
const unsigned NUM_HORAS = 24;

/*
 * Número máximo de días de un año
 */
const unsigned MAX_DIAS = 366;

/*
 * Año actual considerado en el enunciado
 */
const unsigned AGNO_ACTUAL = 2021;

/*
 * Primer mes con datos del año actual según el enunciado
 */
const unsigned PRIMER_MES = 1;

/*
 * Último mes con datos del año actual según el enunciado
 */
const unsigned ULTIMO_MES = 11;

/*
 * Tipo registro que agrupa los 24 datos de consumo eléctrico registrados en un
 * día (en kWh), junto con los 24 precios horarios de ese mismo día (en €/kWh)
 */
struct GastoDiario {
    double precio[NUM_HORAS];   
    double consumo[NUM_HORAS];
    Fecha fecha;
};  // hacer vector regsDiarios


/*
 * Pre:  ---
 * Post: Devuelve la hora en la que el precio de la electricidad según los datos
 *       de precios horarios del registro «gasto» fue más cara.
 */
unsigned horaMasCara(const GastoDiario& gasto);


/*
 * Pre:  ---
 * Post: Devuelve el precio medio de la electricidad según los datos de precios
 *       horarios del registro «gasto».
 */
double costeMedio(const GastoDiario& gasto);


/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto».
 */
double costeDiario(const GastoDiario& gasto);


/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto» suponiendo que todo el 
 *       consumo eléctrico reflejado en el registro «gasto» hubiera tenido lugar
 *       en la hora con el precio más barato del registro «gasto».
 */
double costeDiarioMinimo(const GastoDiario& gasto);
