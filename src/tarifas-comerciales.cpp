
#include "tarifas-comerciales.hpp"
#include "gasto-diario.hpp"

enum horarios {
    punta = 1,
    llano = 2,
    valle = 3
};


int tramoHorario(int hora){
    if (9 <= hora && hora < 13 || 17 <= hora && hora < 21) return 1;
    else if (7 <= hora && hora < 9 || 21 <= hora && hora < 23) return 2;
    else return 3;
}


double costeDiarioTarifaPlanaTramos(const GastoDiario& gasto, const TarifaPlanaTramos tarifa){
    double costeTotal = 0;
    for (int i=0; i<NUM_HORAS; i++){
        if (tramoHorario(i) == punta ){
            costeTotal += (gasto.consumos[i] * tarifa.punta);
        }
        else if (tramoHorario(i) == valle){
            costeTotal += (gasto.consumos[i] + tarifa.valle);
        }
        else {
            costeTotal += (gasto.consumos[i] + tarifa.llano);
        }
    }
    return costeTotal;
}

double costeTarifaPlanaTramos(const GastoDiario regDiario[], const unsigned numRegs, const TarifaPlanaTramos tarifa){
    double costeTotal = 0;
    for (int i=0; i<numRegs; i++){
        costeTotal += costeDiarioTarifaPlanaTramos(regDiario[i], tarifa);
    }
    return costeTotal;
    
}