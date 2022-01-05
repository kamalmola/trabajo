/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autor: Miguel Ángel Latre
 * Ultima revisión: 5-12-2021
 * Resumen: Fichero de implementación «gasto-diario.cpp» del módulo
 *          que contiene tipos registro y funciones para la gestión de datos 
 *          horarios de consumo y precios de un día concreto.
\******************************************************************************/
#include <iostream>
#include "gasto-diario.hpp"
#include <fstream>


unsigned horaMasCara(const GastoDiario& gasto){
    unsigned horaCara = 0;
    double precioMasCaro = gasto.precios[0];
    for(unsigned i = 1;i<NUM_HORAS;i++){
        if (gasto.precios[i] > precioMasCaro){
            horaCara = i;
            precioMasCaro = gasto.precios[i];
        }
    }
    return horaCara;
}

double costeMedio(const GastoDiario& gasto){
    double acumuladorPrecios = 0;

    for(unsigned i = 0;i<=NUM_HORAS;i++){
        acumuladorPrecios += gasto.precios[i];
    }

    return acumuladorPrecios/NUM_HORAS;
}

double costeDiario(const GastoDiario& gasto){
    double importe = 0.0;
    for(unsigned i = 0; i<NUM_HORAS;i++){
        //clog << "Hora " << i+1 << " Consumo: " << gasto.consumos[i] << " Precio: " << gasto.precios[i] << endl;
        importe += (gasto.consumos[i] * gasto.precios[i]);
                
    }
    return importe;
}

double costeDiarioMinimo(const GastoDiario& gasto){
    double precioMin = gasto.precios[0];
    double coste = 0.0;
    
    for(unsigned i=1; i<NUM_HORAS; i++){
        if(precioMin > gasto.precios[i]){
            precioMin = gasto.precios[i];
        }
    }
    
    for (unsigned i=0; i<NUM_HORAS; i++){
        coste += (precioMin*gasto.consumos[i]);
    }

    return coste;
    
}




