#include <string>
#include "gasto-diario.hpp"
#pragma once
using namespace std;

/*
 * Registro que representa una tarifa comercial por tramos. El campo «nombre»
 * combina el nombre de la compañía comercializadora y el de la tarifa.
 * El campo «punta» representa el precio en €/kWh de la energía eléctrica en los
 * periodos más caros (de 10:00 a 13:59 y de 18:00 a 21:59). El campo «llano»
 * representa el precio en €/kWh de la energía eléctrica en los periodos
 * intermedios (de 8:00 a 9:59, de 14:00 a 17:59 y de 22:00 a 23:59). El campo
 * «valle» representa el precio en €/kWh de la energía eléctrica en los periodos
 * más baratos (de 0:00 a 7:59). 
 */ 
struct TarifaPlanaTramos {
    string nombre;
    double punta, llano, valle;
};

/*
 * Número de tarifas comerciales que se van a analizar en el prototipo de este
 * programa
 */
const unsigned NUM_TARIFAS_COMERCIALES = 8;

/*
 * Datos de las tarifas «NUM_TARIFAS_COMERCIALES» comerciales que se van a
 * analizar en el prototipo de este programa. Los datos proceden el comparador
 * de tarifas de la CNMC. Los nombres de las empresas comercializadoras y de las
 * tarifas se han modificado.
 */ 
const TarifaPlanaTramos TARIFAS_COMERCIALES[NUM_TARIFAS_COMERCIALES] = {
    {"Compañía NUF: Un precio 24h", 0.15999, 0.15999, 0.15999},
    {"Compañía NUF: Tres precios", 0.243315, 0.146762, 0.104837},
    {"Compañía END: UNA Light", 0.168978, 0.168978, 0.168978},
    {"Compañía END: UNA 3 Periods", 0.18993, 0.172728, 0.145951},
    {"Compañía END: Tiempo 3 Periods", 0.22801425, 0.2108126, 0.193722},
    {"Compañía LOG: Alfa Hogar 2.0", 0.332118, 0.304713, 0.268656},
    {"Compañía LOG: Alfa Fijo Único Hogar", 0.297195, 0.297195, 0.297195},
    {"Compañía E21: Precio Fijo en Mercado Regulado", 0.180601, 0.162434, 0.135912},
};


/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto» suponiendo que se han
 *       aplicado los costes especificados por la tarifa del parámetro «tarifa».
 */
double costeDiarioTarifaPlanaTramos(const GastoDiario& gasto,
                                    const TarifaPlanaTramos tarifa);


/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos de las «numRegs» primeras componentes del
 *       vector «regDiario» suponiendo que se han aplicado en cada uno de los
 *       días de dichas componentes los costes especificados por la tarifa del
 *       parámetro «tarifa».
 */
double costeTarifaPlanaTramos(const GastoDiario regDiario[],
                        const unsigned numRegs, const TarifaPlanaTramos tarifa);
