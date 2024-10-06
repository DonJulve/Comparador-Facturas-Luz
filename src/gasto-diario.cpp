#include <fstream>
#include <iostream>
#include <string>
#include "fecha.hpp"
#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"
using namespace std;

/*
 * Pre:  ---
 * Post: Devuelve la hora en la que el precio de la electricidad según los datos
 *       de precios horarios del registro «gasto» fue más cara.
 */
unsigned horaMasCara(const GastoDiario& gasto){
    double precioMayor=0;
    unsigned posicionMayor=0;
    for(unsigned i=0;i<NUM_HORAS;i++){
        if(gasto.precio[i]>precioMayor){
            precioMayor=gasto.precio[i];
            posicionMayor=i;
        }
    }
    return posicionMayor;
}

/*
 * Pre:  ---
 * Post: Devuelve el precio medio de la electricidad según los datos de precios
 *       horarios del registro «gasto».
 */
double costeMedio(const GastoDiario& gasto){

    double costeTotal=0;
    
    for (unsigned i=0;i<NUM_HORAS;i++){
        costeTotal+=gasto.precio[i];
    }
    
    return costeTotal/NUM_HORAS;
}

/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto».
 */
double costeDiario(const GastoDiario& gasto){
    double precioDiario=0;
    for(unsigned i=0;i<NUM_HORAS;i++){
        precioDiario=gasto.precio[i]*gasto.consumo[i]+precioDiario;
    }
    return precioDiario;
}

/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto» suponiendo que todo el 
 *       consumo eléctrico reflejado en el registro «gasto» hubiera tenido lugar
 *       en la hora con el precio más barato del registro «gasto».
 */
double costeDiarioMinimo(const GastoDiario& gasto){
    double precioMenor=1000;

    for(unsigned i=0;i<NUM_HORAS;i++){
        if(gasto.precio[i]<precioMenor){
            precioMenor=gasto.precio[i];
        }
    }
    
    double consumoTotal=0;
    for(unsigned i=0;i<NUM_HORAS;i++){
        consumoTotal+=gasto.consumo[i];
    }
    return consumoTotal*precioMenor;

}