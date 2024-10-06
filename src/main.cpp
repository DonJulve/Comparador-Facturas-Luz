/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: Alejandro Benedí,Javier Julve
 * Ultima revisión: 14/01/2022
 * Resumen: ¡¡¡!!!
 * Nota: El código de este programa está repartido en varios módulos.
 *       Para compilarlo, hay que ejecutar el comando
 *           make all
 *       o, en Windows,
 *           mingw32-make all
 *       o ejecutar la tarea "Compilar «electricidad»" de VSC.
 * 
 *       Para ejecutarlo, una vez compilado, hay que ejecutar el comando
 *           bin/electricidad
 *       o, en Windows,
 *           bin\electricidad.exe
 *       o ejecutar la tarea "Ejecutar «electricidad»" de VSC.
\******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"
#include "vector-gastos.hpp"
#include "tarifas-comerciales.hpp"
#include "fecha.hpp"
using namespace std;

/*
 * Pre:  
 * Post: Actualiza <cliente> con el nombre del cliente,<mesInicial> con el mesInicial,
 *       <mesFinal> con el mes final y <numRegs> con el numero de días.
 *       
 */
void pedirDatos(string& cliente,unsigned &mesInicial,unsigned &mesFinal,unsigned &numRegs){
    bool cumplido;
    cout<<"Escriba el nombre del usuario: ";
    cin>>cliente;

    do{
        cumplido=true;
        cout<<"Escriba el mes inicial y el final: ";
        cin>>mesInicial>>mesFinal;

        if(mesInicial>mesFinal){
            cout<<"El mes inicial tiene que ser menor o igual que el mes final."<<endl;
            cumplido=false;
        }
        
        if(mesInicial<1||mesInicial>11){
            cout<<"El mes inicial tiene que estar entre 1 y 11."<<endl;
            cumplido=false;
        }

        if(mesFinal<1||mesFinal>11){
            cout<<"El mes final tiene que estar entre 1 y 11."<<endl;
            cumplido=false;
        }

    }while(cumplido==false);

    Fecha Inicial={1,mesInicial,AGNO_ACTUAL};
    Fecha Final={1,mesFinal+1,AGNO_ACTUAL};
    numRegs=diasTranscurridos(Inicial,Final);
}


/*
 * Pre:  «f» es «cout» o un flujo de la clase «ofstream» asociado con un fichero
 *       externo abierto para escritura. Las «numRegs» primeras componentes
 *       del vector «regDiarios» contienen datos diarios de precios y consumo
 *       eléctricos de un determinado cliente de nombre «nombreCliente» entre
 *       los meses «mesInicial» y «mesFinal».
 * Post: Ha escrito en el flujo «f» el informe sobre consumo eléctrico indicado
 *       en el enunciado de este trabajo.
 */
void escribirInforme(ostream& f,
                     const GastoDiario regDiarios[], const unsigned numRegs,
                     const string nombreCliente, 
                     const unsigned mesInicial, const unsigned mesFinal) {
    double precio;
    unsigned hora; 
    Fecha dia;

    f<<"\nINFORME DEL CLIENTE "<<nombreCliente<<" ENTRE LOS MESES "<<mesInicial<<" Y "<<mesFinal<<" DE "<<AGNO_ACTUAL<<endl;
    f<<"-----------------------------------------------------------------------------"<<endl;
    diaMasBarato(regDiarios,numRegs,dia,precio);
    f<<"El dia completo mas barato fue "; mostrar(f,dia); f<<".  Precio medio: "<<fixed<<setprecision(5)<<precio/1000<<" €/kWh"<<endl;

    horaMasCaraGeneral(regDiarios,numRegs,dia,hora,precio);
    f<<"La hora mas cara tuvo lugar el "; mostrar(f,dia); f<<" a las "<<hora<<":00.  Precio: "<<fixed<<setprecision(5)<<precio/1000<<" €/kWh"<<endl;

    double costeVariable=costeTerminoVariable(regDiarios,numRegs);
    f<<"\nEl importe del consumo eléctrico en el periodo considerado ha sido de "<<fixed<<setprecision(2)<<costeVariable/1000<<endl;

    double costeMinimo=costeMinimoPosible(regDiarios,numRegs);
    f<<"El importe mínimo concentrando todo el consumo diario en la hora más barata"<<endl;
    f<<"habría sido de "<<fixed<<setprecision(2)<<costeMinimo/1000<<" €  (un "<<fixed<<setprecision(2)<<((costeVariable-costeMinimo)/costeVariable)*100<<"% menor)"<<endl;

    f<<"\nCOSTE CON TARIFAS COMERCIALES"<<endl;
    f<<"------------------------------------------"<<endl;
    f<<"Coste"<<"     "<<"Nombre de la tarifa"<<endl;
    for(unsigned i=0;i<NUM_TARIFAS_COMERCIALES;i++){
        f<<costeTarifaPlanaTramos(regDiarios,numRegs,TARIFAS_COMERCIALES[i])<<"     "<<TARIFAS_COMERCIALES[i].nombre<<endl;
    
    }
}

/*
 * Pre:  <regDiarios[]> contiene los elementos de los ficheros "tarifas" y "consumos",
 *       <nombreCliente> contiene el usuario, <mesInical> contiene el mesInicial,
 *       <mesFinal> contiene el mes final y <numregs> contiene el numero de dias. 
 * Post: Indica al programa si tiene que escribir en pantalla o tiene que crear un 
 *       fichero.
 *       
 */
void salida(const string nombreCliente,const unsigned mesInicial, const unsigned mesFinal,GastoDiario regDiarios[], const unsigned numregs){
    
    string ruta;
    cout<<"Escriba el nombre del fichero del informe "<<endl<<"(presione solo ENTRAR para escribirlo en la pantalla): ";
    cin.ignore(1, '\n');
    getline(cin, ruta);
    if(ruta.empty()){
        escribirInforme(cout,regDiarios,numregs,nombreCliente,mesInicial,mesFinal);
    }
    else{
        ofstream f(ruta);
        escribirInforme(f,regDiarios,numregs,nombreCliente,mesInicial,mesFinal);
        if(f.fail()){
            cout<<"No se ha podido escribir en el fichero: "<<ruta;
        }
        else{
            cout<<"Se ha creado el fichero: "<<ruta;
        }
    }


}

/*
 * Este programa te hace un informe sobre el precio y consumo de la luz
 * segun los ficheros correspodientes a las taridas y los consumos o gastos.
 * El programa inicialmente te pide que introduzcas el usuario (a o b,sino no funciona)
 * lugos te pide un mes inicial o final y comprueba si estos son correctos.Con estos 
 * datos el programa ya tiene todo lo necesario para coger los datos de los ficheros,
 * comentado anteriormente.Luego te pide que introduzcas una ruta de salida.Si pulsas 
 * unicamente al enter el informe se imprimirá en la pantalla,en cambio si escribes una ruta
 * te creara un fichero con el nombre y formata que hayas escrito en la ruta.
 * Si cualquiera de los ficheros fallas en leerse o abrirse mostrara un error en la pantalla 
 * con el nombre del fichero que no se haya podido leer o escribir.
 */
int main() {

    unsigned mesInicial;
    unsigned mesFinal;
    unsigned numRegs;
    string nombreCliente;

    pedirDatos(nombreCliente,mesInicial,mesFinal,numRegs);
    GastoDiario regDiarios[366];

    leerConsumos(nombreCliente,mesInicial,mesFinal,regDiarios);
    leerPrecios(RUTA_DATOS+"tarifas-2021-ene-nov.csv",mesInicial,mesFinal,regDiarios);
    if(nombreCliente == "a" || nombreCliente == "b"){
        salida(nombreCliente,mesInicial,mesFinal,regDiarios,numRegs);
    }
    return 0;
}
