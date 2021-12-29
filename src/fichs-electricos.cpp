

#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include "fecha.hpp"
#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"

using namespace std;

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