

#include "gasto-diario.hpp"
#include "fecha.hpp"


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
    double precio = 0;
    int horaMaxima;
    unsigned maximoDia;
    for (unsigned i=0; i<numRegs; i++){
        int horaBuscada = horaMasCara(regsDiarios[i]);
        if (regsDiarios[i].precios[horaBuscada] > precio){
            precio = regsDiarios[i].precios[horaBuscada];
            horaMaxima = horaBuscada;
            maximoDia = i;
        }
    }
    precioMaximo = precio;
    hora = horaMaxima;
    dia = regsDiarios[maximoDia].dia;
    

<<<<<<< HEAD
=======
}



double costeTerminoVariable(const GastoDiario regsDiarios[], const unsigned numRegs){

    double acc = 0;

    for (int i=0; i<numRegs; i++){
        acc += costeDiario(regsDiarios[i]);
    }
    return acc;

}



double costeMinimoPosible(const GastoDiario regsDiarios[], const unsigned numRegs){
    double acc = 0;

    for (int i=0; i<numRegs; i++){
        acc += costeDiarioMinimo(regsDiarios[i]);
    }
    return acc;
>>>>>>> a79fd5df22e81091841aa3cc35719b97b0ffff63
}