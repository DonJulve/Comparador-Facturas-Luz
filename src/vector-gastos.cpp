#include <fstream>
#include <iostream>
#include <string>
#include "fecha.hpp"
#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"
using namespace std;

/*
 * Pre:  GastoDiario regsDiarios[] contiene los datos de los ficheros:
 *       "tarifas-2021-ene-nov" y el que contiene los consumos.
 * Post: Asigna a la variable <Fecha> <fecha> el dia,mes y año que contiene 
 *       <regsDiario[i]>    
 */
void actualizarFecha(const GastoDiario regsDiarios[],Fecha& dia,unsigned i){

    dia.dia=regsDiarios[i].fecha.dia;
    dia.mes=regsDiarios[i].fecha.mes;
    dia.agno=regsDiarios[i].fecha.agno;
}


/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios horarios de energía eléctrica.
 * Post: Asigna al parámetro «dia» el día en el que se registró el menor precio
 *       diario promedio de entre las primeras «numRegs» componentes del vector
 *       «regsDiarios» y al parámetro «precioMedioMinimo», el valor de ese precio
 *       promedio diario mínimo.
 */
void diaMasBarato(const GastoDiario regsDiarios[], const unsigned numRegs,
                  Fecha& dia, double& precioMedioMinimo){

    double costeDia=0;
    precioMedioMinimo=10000;
    for(unsigned i=0;i<numRegs;i++){
        costeDia=costeMedio(regsDiarios[i]);
        if(costeDia<precioMedioMinimo){
            precioMedioMinimo=costeDia;
            actualizarFecha(regsDiarios,dia,i);
        }
    }
}


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
                 Fecha& dia, unsigned& hora, double& precioMaximo){
    
    precioMaximo=0;
    double precioHora=0;
    unsigned posHora=0;
    hora=0;
    for(unsigned i=0;i<numRegs;i++){
        posHora=horaMasCara(regsDiarios[i]);
        precioHora=regsDiarios[i].precio[posHora];
        if(precioHora>precioMaximo){
            hora=posHora;
            precioMaximo=precioHora;
            actualizarFecha(regsDiarios,dia,i);
        }
    }
}


/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios y consumo horarios de energía eléctrica.
 * Post: Devuelve el coste en euros de la energía eléctrica consumida según los
 *       datos de las primeras «numRegs» componentes del vector «regsDiarios».
 */
double costeTerminoVariable(const GastoDiario regsDiarios[],
                            const unsigned numRegs){
    
    double costeTotal=0;
    for(unsigned i=0;i<numRegs;i++){
        costeTotal+=costeDiario(regsDiarios[i]);
    }
    return costeTotal;
}

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
                          const unsigned numRegs){

    double costeTotal=0;
    for(unsigned i=0;i<numRegs;i++){
        costeTotal+=costeDiarioMinimo(regsDiarios[i]);
    }
    return costeTotal;
}


