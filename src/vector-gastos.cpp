

#include "gasto-diario.hpp"
#include "fecha.hpp"
#include <iostream>

using namespace std;

void diaMasBarato(const GastoDiario regsDiarios[], const unsigned numRegs, Fecha& dia, double& precioMedioMinimo){
    double minimo = costeMedio(regsDiarios[0]);
    unsigned minimoDia = 0;
    for (unsigned i=1; i<numRegs; i++){
        double medio = costeMedio(regsDiarios[i]);
        if (medio < minimo){
            minimo = medio;
            minimoDia = i;
        }
    }
    precioMedioMinimo = minimo;
    dia = regsDiarios[minimoDia].dia;

}

void horaMasCara(const GastoDiario regsDiarios[], const unsigned numRegs, Fecha& dia, unsigned& hora, double& precioMaximo){
    unsigned maximoDia;
    for (unsigned i=0; i<numRegs; i++){
        int horaBuscada = horaMasCara(regsDiarios[i]);

        if (regsDiarios[i].precios[horaBuscada] > precioMaximo){

            precioMaximo = regsDiarios[i].precios[horaBuscada];
            hora = horaBuscada;
            maximoDia = i;
        }
    }
    dia = regsDiarios[maximoDia].dia;
}



double costeTerminoVariable(const GastoDiario regsDiarios[], const unsigned numRegs){

    double acc = 0.0;
    for (unsigned i=0; i<numRegs; i++){
        acc += costeDiario(regsDiarios[i]);
    }
    return acc;
}



double costeMinimoPosible(const GastoDiario regsDiarios[], const unsigned numRegs){
    double acc = 0.0;

    for (unsigned i=0; i<numRegs; i++){
        acc += costeDiarioMinimo(regsDiarios[i]);
    }
    return acc;
}