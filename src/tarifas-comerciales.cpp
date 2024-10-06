#include <fstream>
#include <iostream>
#include <string>
#include "fecha.hpp"
#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"
#include "tarifas-comerciales.hpp"
using namespace std;

/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto» suponiendo que se han
 *       aplicado los costes especificados por la tarifa del parámetro «tarifa».
 */
double costeDiarioTarifaPlanaTramos(const GastoDiario& gasto,
                                    const TarifaPlanaTramos tarifa){
    
    double precioValle=0;
    double precioLlano=0;
    double precioPunta=0;

    for(unsigned i=0;i<24;i++){

        if(i<=7){
            precioValle=gasto.consumo[i]*tarifa.valle+precioValle;
        }

        else if((i>=8 && i<10) || (i>=14 && i<18) || (i>=22 && i<24)) {
            precioLlano=gasto.consumo[i]*tarifa.llano+precioLlano;
        } 
        else{
            precioPunta=gasto.consumo[i]*tarifa.punta+precioPunta;
        }
    }
    
    return precioValle+precioLlano+precioPunta;
}


/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos de las «numRegs» primeras componentes del
 *       vector «regDiario» suponiendo que se han aplicado en cada uno de los
 *       días de dichas componentes los costes especificados por la tarifa del
 *       parámetro «tarifa».
 */
double costeTarifaPlanaTramos(const GastoDiario regDiario[],
                        const unsigned numRegs, const TarifaPlanaTramos tarifa){
    
    double precioTotal;
    
    for(unsigned i=0;i<numRegs;i++){
        precioTotal+=costeDiarioTarifaPlanaTramos(regDiario[i],tarifa);
    }

    return precioTotal;
}