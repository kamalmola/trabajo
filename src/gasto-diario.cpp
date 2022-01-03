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

/*
 * Pre:  ---
 * Post: Devuelve la hora en la que el precio de la electricidad según los datos
 *       de precios horarios del registro «gasto» fue más cara.
 */
unsigned horaMasCara(const GastoDiario& gasto){
    unsigned horaCara;
    for(unsigned i = 0;i<=NUM_HORAS-1;i++){
        if(gasto.precios[i]<gasto.precios[i+1]){
            horaCara = i+1;
        }
    }
    return horaCara;

}
/*
 * Pre:  ---
 * Post: Devuelve el precio medio de la electricidad según los datos de precios
 *       horarios del registro «gasto».
 */
double costeMedio(const GastoDiario& gasto){
    double acumuladorPrecios = 0;

    for(unsigned i = 0;i<=NUM_HORAS;i++){
        acumuladorPrecios += gasto.precios[i];
    }

    return acumuladorPrecios/NUM_HORAS;
}
/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto».
 */
double costeDiario(const GastoDiario& gasto){
    double importe;
    for(unsigned i = 0; i<=NUM_HORAS;i++){
        importe += gasto.consumos[i] * gasto.precios[i];
                
    }
    return importe;
}
/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto» suponiendo que todo el 
 *       consumo eléctrico reflejado en el registro «gasto» hubiera tenido lugar
 *       en la hora con el precio más barato del registro «gasto».
 */
double costeDiarioMinimo(const GastoDiario& gasto){
    double precioMin;
    double consumoMin;
    for(unsigned i = 0;i<=NUM_HORAS-1;i++){
        if(gasto.precios[i]<gasto.precios[i+1]){
            precioMin = gasto.precios[i];
        }
        if(gasto.consumos[i]<gasto.consumos[i+1]){
            consumoMin = gasto.consumos[i];
        }
        
    }


    return precioMin * consumoMin;
    
}




