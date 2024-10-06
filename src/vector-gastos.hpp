#pragma once
#include "gasto-diario.hpp"

/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios horarios de energía eléctrica.
 * Post: Asigna al parámetro «dia» el día en el que se registró el menor precio
 *       diario promedio de entre las primeras «numRegs» componentes del vector
 *       «regsDiarios» y al parámetro «precioMedioMinimo», el valor de ese precio
 *       promedio diario mínimo.
 */
void diaMasBarato(const GastoDiario regsDiarios[], const unsigned numRegs,
                  Fecha& dia, double& precioMedioMinimo);

/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios horarios de energía eléctrica.
 * Post: Asigna al parámetro «dia» el día en el que se registró el mayor precio
 *       horario de entre las primeras «numRegs» componentes del vector
 *       «regsDiarios»; al parámetro «hora», la hora de ese día en la que se
 *       registró ese mayor precio horario y al parámetro «precioMaximo», el
 *       valor de ese precio máximo.
 */
void horaMasCaraGeneral(const GastoDiario regsDiarios[], const unsigned numRegs,
                 Fecha& dia, unsigned& hora, double& precioMaximo);

/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios y consumo horarios de energía eléctrica.
 * Post: Devuelve el coste en euros de la energía eléctrica consumida según los
 *       datos de las primeras «numRegs» componentes del vector «regsDiarios».
 */
double costeTerminoVariable(const GastoDiario regsDiarios[],
                            const unsigned numRegs);

/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios y consumo horarios de energía eléctrica.
 * Post: Devuelve el coste en euros del coste de la energía eléctrica consumida 
 *       según los datos de las primeras «numRegs» componentes del vector
 *       «regsDiarios», suponiendo que TODO el consumo de cada uno de los días
 *       almacenados en las componentes de «regsDiarios» se ha producido
 *       precisamente en la hora más barata de ese día.
 */
double costeMinimoPosible(const GastoDiario regsDiarios[], 
                          const unsigned numRegs);




void actualizarFecha(const GastoDiario regsDiarios[],Fecha& dia,unsigned i);
