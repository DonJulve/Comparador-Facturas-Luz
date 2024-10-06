#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include "fichs-electricos.hpp"
using namespace std;

/*
 * Pre:  <nombreCliente> contiene al usuario y <mes> contiene el mes inicial o el mes indicado
 * Post: Actualiza <ruta> con la ruta del mes siguiente para seguir leyendos los consumos
 */
void crearRuta(const string nombreCliente,const unsigned mes,string& ruta){
	if(mes<10){
        ruta=RUTA_DATOS+nombreCliente+'-'+to_string(AGNO_ACTUAL)+"-0"+to_string(mes)+".csv";
    }
    else{
        ruta=RUTA_DATOS+nombreCliente+'-'+to_string(AGNO_ACTUAL)+"-"+to_string(mes)+".csv";
    }
	//"../"+
}
bool leerConsumoHorario(istream& f,Fecha& fecha, unsigned& hora, double& consumo){

    string CUPS;
    string REAL;
    string leido;

    if(getline(f,CUPS,';')){

        getline(f,leido,'/');
        fecha.dia=stoi(leido);

        getline(f,leido,'/');
        fecha.mes=stoi(leido);

        getline(f,leido,';');
        fecha.agno=stoi(leido);

        getline(f,leido,';');
        hora=stoi(leido);

        getline(f,leido,';');
        consumo=stod(leido);

		getline(f,REAL);
        return true;
    }
    else{
        return false;
    }
    
}


bool leerConsumos(const string nombreCliente,const unsigned mesInicial, const unsigned mesFinal,GastoDiario registros[]){
		
	Fecha fecha;
	unsigned hora=0;
	unsigned dia=0;
	double consumo;
	string ignorar; 
    unsigned mes=mesInicial;
    string ruta;

    while(mes<=mesFinal){

		crearRuta(nombreCliente,mes,ruta);

        ifstream f(ruta);
        if (f.is_open()){

		    getline(f,ignorar);

		    while(!f.eof()){
                leerConsumoHorario(f,fecha,hora,consumo);
			    if(fecha.mes>=mesInicial && fecha.mes<=mesFinal){
					
					hora-=1;

				    registros[dia].consumo[hora]=consumo;   
					  
				    registros[dia].fecha.dia=fecha.dia;
				    registros[dia].fecha.mes=fecha.mes;
				    registros[dia].fecha.agno=fecha.agno;
					
                    if(hora==23){
						dia++;
                    }
			    }
		    }
			f.close();
			mes++;
	    }
	    else{
		    cout<<"No se ha abierto el fichero "<<ruta;
		    return false;
	    }
    }
	return true;
}


/*
 * Pre:  «f» está asociado con un fichero externo que cumple con la sintaxis de
 *       la regla <fichero-precios> establecida en el enunciado y está en
 *       disposición de leer desde el principio de una línea que cumple con la
 *       regla <precio-horario>.
 * Post: Ha extraido de «f» la línea a la que hacía referencia la precondición
 *       y ha asignado a los parámetros «fecha», «hora» y «precio»,
 *       respectivamente, los datos sobre la fecha, hora y precio horario
 *       correspondientes a la línea que se ha extraído del flujo «f».
 *       El flujo «f» continua asociado con el fichero externo y en disposición
 *       de extraer datos a partir de la siguiente línea.
 *       La función ha devuelto «true» si no se han terminado los datos del
 *       fichero en el intento de lectura y «false» en caso contrario.
 */
bool leerPrecioHorario(istream& f, Fecha& fecha, unsigned& hora, double& precio){

	string leido;
	string ignorar;

	if(getline(f,leido,';')){
		
		for (unsigned i=0;i<=2;i++){
			getline(f,ignorar,';');
		}

		getline(f,leido,';');
		precio=stod(leido);

		getline(f,leido,'-');
		fecha.agno=stoi(leido);

		getline(f,leido,'-');
		fecha.mes=stoi(leido);

		getline(f,leido,'T');
		fecha.dia=stoi(leido);

		getline(f,leido,':');
		hora=stoi(leido);

		getline(f,leido);
		return false;
	}
	else{
		return true;
	}
}

/*
 * Pre:  «nombreFichero» es el nombre de un fichero externo que cumple con la
 *       sintaxis de la regla <fichero-precios> establecida en el enunciado; 
 *       «mesInicial» y «mesFinal» están ambos entre «PRIMER_MES» y «ULTIMO_MES»
 *       y mesInicial < mesFinal.
 * Post: Ha copiado los datos de precios horarios correspondientes a fechas 
 *       entre «mesInicial» y «mesFinal» presentes en «nombreFichero» en las 
 *       componentes correspondientes a la hora del precio del campo «precios»
 *       en las primeras componentes del vector «registros», cuyos campos
 *       «fecha» se han actualizado y han quedado en orden cronológico (tal y
 *       como aparecían en el fichero). LOS DATOS DEL VECTOR CORRESPONDIENTE AL
 *       CAMPO «CONSUMO» NO SE HAN MODIFICADO.
 *       La función ha devuelto «true» si ha podido leer del fichero de nombre 
 *       «nombreFichero» correctamente, y «false» en caso contrario.
 */
bool leerPrecios(const string nombreFichero,
                 const unsigned mesInicial, const unsigned mesFinal,
                 GastoDiario registros[]){

	ifstream f(nombreFichero);
	if (f.is_open()){
		
		Fecha fecha;
		unsigned hora=0;
		double precio;
		string ignorar;
        unsigned dia=0;

		getline(f,ignorar);

		while(!f.eof()){

			leerPrecioHorario(f,fecha,hora,precio);
			if(fecha.mes>=mesInicial && fecha.mes<=mesFinal ){
				
				registros[dia].precio[hora]=precio;       
				registros[dia].fecha.dia=fecha.dia;
				registros[dia].fecha.mes=fecha.mes;
				registros[dia].fecha.agno=fecha.agno;
                if(hora==23){
					dia++;
				}
			}
		}
		return true;
		f.close();
	}
	else{
		cout<<"No se ha abierto el fichero";
		return false;
	}
}

/*
int main(){

	Fecha fecha;
	double consumos;
	double precio;
	unsigned hora;
	string ignorar;
	string nombreCliente="a";
	string ruta;
	unsigned mesFinal=3;
	unsigned mes=1;

	
	ifstream origen("../datos/tarifas-2021-ene-nov.csv");
	if(origen.is_open()){
		getline(origen,ignorar);
            while(!origen.eof()){
			   // leerConsumoHorario(origen,fecha,hora,consumos);
				leerPrecioHorario(origen,fecha,hora,precio); 
		    }
	}
	else{
		cout<<"no se ha abierto";
	}
	


	string usuario="a";
	string tarifas="../datos/tarifas-2021-ene-nov.csv";
	GastoDiario registros[365];
	leerPrecios(tarifas,1,3,registros);
	leerConsumos(usuario,1,3,registros);
	cout<<registros[0].fecha.dia<<"/"<<registros[0].fecha.mes<<"/"<<registros[0].fecha.agno<<
			" "<<23<<" "<<registros[0].consumo[23]<<endl;
			
	for(int i=0; i<89;i++){
		for(int j=0; j<24;j++){
		cout<<registros[i].fecha.dia<<"/"<<registros[i].fecha.mes<<"/"<<registros[i].fecha.agno<<
			" "<<j<<" "<<registros[i].consumo[j]<<" "<<registros[i].precio[j]<<endl;
		}
	}
	
	return 0;

}
*/