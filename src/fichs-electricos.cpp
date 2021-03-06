<<<<<<< HEAD
/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autor: Miguel Ángel Latre
 * Ultima revisión: 5-12-2021
 * Resumen: Fichero de impementación «fichs-electricos.hpp» del módulo
 *          «fichs-electricos» que contiene funciones para la extracción de los
 *          datos relevantes de los ficheros de precios y consumo eléctrico.
\******************************************************************************/
#include <fstream>
#include "fichs-electricos.hpp"
#include <istream>

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
=======


#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include "fecha.hpp"
#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"

using namespace std;

>>>>>>> man1
bool leerPrecioHorario(istream& f, Fecha& fecha, unsigned& hora, double& precio){
    string numPrecio;
    f.ignore(76);
    /*Lo que hace es eliminar los 76 primeros caractéres, si, he contado cuantos había hasta el precio. 
    Seguro que hay formas mas eficientes, pero no veo como leer saltándose todos los delimitadores sin hacer varias veces getline.
    Buenas tardes.
    */
    f >> precio;
    precio = precio/1000;
    getline(f,numPrecio,';');
    f >> fecha.agno;
    getline(f,numPrecio,'-');
    f >> fecha.mes;
    getline(f,numPrecio,'-');
    f >> fecha.dia;
    f.ignore();
    f >> hora;
    getline(f,numPrecio);

}
<<<<<<< HEAD
/*
 * Pre:  «f» está asociado con un fichero externo que cumple con la sintaxis de
 *       la regla <fichero-consumos> establecida en el enunciado y está en
 *       disposición de leer desde el principio de una línea que cumple con la
 *       regla <consumo-horario>.
 * Post: Ha extraido de «f» la línea a la que hacía referencia la precondición
 *       y ha asignado a los parámetros «fecha», «hora» y «consumo»,
 *       respectivamente, los datos sobre la fecha, hora y consumo horario
 *       correspondientes a la línea que se ha extraído del flujo «f». 
 *       El flujo «f» continua asociado con el fichero externo y en disposición
 *       de extraer datos a partir de la siguiente línea.
 *       La función ha devuelto «true» si no se han terminado los datos del
 *       fichero en el intento de lectura y «false» en caso contrario.
 */
=======

>>>>>>> man1
bool leerConsumoHorario(istream& f,Fecha& fecha, unsigned& hora, double& consumo){
    string numFecha;

    getline(f,numFecha,';');
    f >> fecha.dia;
    getline(f,numFecha,'/');
    f >> fecha.mes;
    getline(f,numFecha,'/');
    f >> fecha.agno;
    getline(f,numFecha,'/');
    f.ignore();
    f >> hora;
    getline(f,numFecha,';');
    f.ignore();
    f >> consumo;
    getline(f,numFecha);


}

<<<<<<< HEAD














=======
bool leerPrecios(const string nombreFichero, const unsigned mesInicial, const unsigned mesFinal, GastoDiario registros[]) {

    ifstream f(nombreFichero);

    if (!f.is_open()){
        cerr << "No se pudo abrir el fichero " << nombreFichero << ":unicorn:";
        return false;
    }
    string _;
    getline(f, _);

    Fecha fecha;
    unsigned hora;
    double precio;

    while (leerPrecioHorario(f, fecha, hora, precio)){
        if(fecha.mes == mesInicial){
            break;
        }
    }


    
    registros[0].dia = fecha;
    registros[0].precios[0] = precio;

    int dia = 0;

    while (leerPrecioHorario(f, fecha, hora, precio) && fecha.mes <= mesFinal){
        if (hora == 1){
            dia++;
            registros[dia].dia = fecha;
        }

        registros[dia].precios[hora-1] = precio;

    }
    return true;
}
bool leerConsumos(const string nombreCliente, const unsigned mesInicial, const unsigned mesFinal, GastoDiario registros[]) {

    for (int i=mesInicial; i<=mesFinal; i++){
        string fichero = "datos/" + nombreCliente + "-2021-" + (i<10 ? "0 "+to_string(i): to_string(i)) + ".csv";
        ifstream f(fichero);
        if (!f.is_open()){
            cerr << "No se pudo abrir el fichero " << fichero << ":unicorn:";
            return false;
        }
        string _;
        getline(f, _);
    

        Fecha fecha;
        unsigned hora;
        double consumo;

        while (leerConsumoHorario(f, fecha, hora, consumo)){
            if(fecha.mes == mesInicial){
                break;
            }
        }
        
        registros[0].consumos[0] = consumo;

        int dia = 0;

        while (leerConsumoHorario(f, fecha, hora, consumo) && fecha.mes <= mesFinal){
            if(fecha.dia != registros[dia].dia.dia){
                cerr << "Fechas distintas entre mismos dias";
                return false;
            }
            if (hora == 1){
                dia++;
                registros[dia].dia = fecha;
            }

            registros[dia].precios[hora-1] = consumo;

        }
    }
    return true;
}
>>>>>>> man1
