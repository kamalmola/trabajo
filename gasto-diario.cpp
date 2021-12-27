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
    for(int i = 0;i<=NUM_HORAS;i++){
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
    double promedioPrecios = 0;

    for(int i = 0;i<=NUM_HORAS;i++){
        acumuladorPrecios += gasto.precios[i];
    }
    promedioPrecios = acumuladorPrecios/NUM_HORAS;

    return promedioPrecios;
}
/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto».
 */
double costeDiario(const GastoDiario& gasto){
    double importe;
    for(int i = 1; i<=MAX_DIAS;i++){
        gasto.gastoDias[i];
        /*Como hago para que se asigne a cada día un precio específico, siendo que 
        el vector de precios es de una dimensión de 24, ¿Otro bucle for?
        */
        
    }

}




