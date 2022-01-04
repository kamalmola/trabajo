/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autor: Miguel Ángel Latre
 * Ultima revisión: 5-12-2021
 * Resumen: Fichero de impementación «fichs-electricos.hpp» del módulo
 *          «fichs-electricos» que contiene funciones para la extracción de los
 *          datos relevantes de los ficheros de precios y consumo eléctrico.
\******************************************************************************/
#include <fstream>
#include <iostream>
#include <istream>
#include "fichs-electricos.hpp"
#include "fecha.hpp"

using namespace std;

bool leerPrecioHorario(istream& f, Fecha& fecha, unsigned& hora, double& precio){
    string ignorar;
    getline(f, ignorar, ';'); // id 
    getline(f, ignorar, ';'); // name
    getline(f, ignorar, ';'); // geoid
    getline(f, ignorar, ';'); // geoname
    f >> precio;
    precio = precio/1000;
    getline(f,ignorar,';');
    f >> fecha.agno;
    getline(f,ignorar,'-');
    f >> fecha.mes;
    getline(f,ignorar,'-');
    f >> fecha.dia;
    f.ignore();
    f >> hora;
    getline(f,ignorar); 

    return true;

}

bool leerConsumoHorario(istream& f,Fecha& fecha, unsigned& hora, double& consumo){
    string ignorar;

    getline(f,ignorar,';');
    f >> fecha.dia;
    f.ignore();
    f >> fecha.mes;
    f.ignore();
    f >> fecha.agno;
    getline(f,ignorar,';');
    f >> hora;
    getline(f,ignorar,';');
    f >> consumo;
    getline(f, ignorar, ';');
    return !f.eof();

}


bool leerPrecios(const string nombreFichero, const unsigned mesInicial, const unsigned mesFinal, GastoDiario registros[]) {
    
    ifstream f(nombreFichero);

    if (!f.is_open()){
        cerr << "No se pudo abrir el fichero " << nombreFichero;
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
    unsigned mesesRepetidos[12] = {0};
    while (leerPrecioHorario(f, fecha, hora, precio) && fecha.mes <= mesFinal && fecha.mes >= mesInicial && !mesesRepetidos[fecha.mes-1]){
        if (f.eof()){
            f.close();
            f.clear();
            f.open(nombreFichero);
            getline(f, _);
        }
        
        if (hora == 0){
            unsigned mes = registros[dia].dia.mes;
            dia++;
            registros[dia].dia = fecha;
            if (mes != fecha.mes) mesesRepetidos[mes-1] = 1;
        }

        registros[dia].precios[hora] = precio;

    }
    return true;
}
bool leerConsumos(const string nombreCliente, const unsigned mesInicial, const unsigned mesFinal, GastoDiario registros[]) {

    for (unsigned i=mesInicial; i<=mesFinal; i++){
        string fichero = "datos/" + nombreCliente + "-2021-" + (i<10 ? "0"+to_string(i): to_string(i)) + ".csv";
        ifstream f(fichero);
        if (!f.is_open()){
            cerr << "No se pudo abrir el fichero " << fichero;
            return false;
        }
        string _;
        getline(f, _);
    

        Fecha fecha;
        unsigned hora;
        double consumo;

        int dia = 0;
        registros[0].consumos[0] = leerConsumoHorario(f, fecha, hora, consumo);

        while (leerConsumoHorario(f, fecha, hora, consumo)){
            if (hora == 1){
                dia++;
            }
            registros[dia].consumos[hora-1] = consumo;

        }
    }
    return true;
}
