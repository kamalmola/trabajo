/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: Lucas Cauhé y Kamal Bouizzy 
 * Ultima revisión: ¡¡¡!!!
 * Resumen: ¡¡¡!!!
 * Nota: El código de este programa está repartido en varios módulos.
 *       Para compilarlo, hay que ejecutar el comando
 *           make all
 *       o, en Windows,
 *           mingw32-make all
 *       o ejecutar la tarea "Compilar «electricidad»" de VSC.
 * 
 *       Para ejecutarlo, una vez compilado, hay que ejecutar el comando
 *           bin/electricidad
 *       o, en Windows,
 *           bin\electricidad.exe
 *       o ejecutar la tarea "Ejecutar «electricidad»" de VSC.
\******************************************************************************/

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <string>
#include "fichs-electricos.hpp"
#include "vector-gastos.hpp"
#include "tarifas-comerciales.hpp"
using namespace std;

struct SalidaPedirDatos {
    int accion;
    string mensajeError;
};

void tarifaPVPCGeneral(ostream& f, const GastoDiario regDiarios[], const unsigned numRegs){
    Fecha fechaBarata, fechaCara;
    unsigned hora;
    double precioMinimo, precioMaximo=0;

    diaMasBarato( regDiarios, numRegs, fechaBarata, precioMinimo);
    horaMasCara(regDiarios, numRegs, fechaCara, hora, precioMaximo);

    string fechaBaratastr = to_string(fechaBarata.dia) + "-" + to_string(fechaBarata.mes) + "-" + to_string(fechaBarata.agno);
    string fechaCarastr = to_string(fechaCara.dia) + "-" + to_string(fechaCara.mes) + "-" + to_string(fechaCara.agno);

    f << "El día completo más barato fue el " << fechaBaratastr << ". Precio medio: " << fixed << setprecision(5) << precioMinimo << " €/kWh\n";
    f << "La hora más cara tuvo lugar el " << fechaCarastr << " a las " << hora <<":00. Precio: " << fixed << setprecision(5) << precioMaximo <<" €/kWh\n\n";
}

void importeConPVPC(ostream& f, const GastoDiario regDiarios[], const unsigned numRegs){
    double costeReal = costeTerminoVariable(regDiarios, numRegs);
    double costeMinimo = costeMinimoPosible(regDiarios, numRegs);
    double diferencia = 100 - costeMinimo / costeReal * 100;
    
    f << "El importe del consumo eléctrico en el periodo considerado ha sido de "<< fixed << setprecision(2) << costeReal << " €.\n";
    f << "El importe mínimo concentrando todo el consumo diario en la hora más barata habría sido de " 
    << fixed << setprecision(2) << costeMinimo << " € (un "<< fixed << setprecision(2) <<  diferencia << " % menor).\n\n";

}
/*
 * Pre:  «f» es «cout» o un flujo de la clase «ofstream» asociado con un fichero
 *       externo abierto para escritura. Las «numRegs» primeras componentes
 *       del vector «regDiarios» contienen datos diarios de precios y consumo
 *       eléctricos de un determinado cliente de nombre «nombreCliente» entre
 *       los meses «mesInicial» y «mesFinal».
 * Post: Ha escrito en el flujo «f» cada uno de los precios que pagaría el usuario 
 *       respecto a su consumo,correspondiente a las diferentes tarifas que ofrencen 
 *       las empresas en el el mercado libre.  
 */
void mercadoLibre(ostream& f, const GastoDiario regDiarios[], const unsigned numRegs){
    string espacio = "         ";
    string cabecera = "COSTE CON TARIFAS COMERCIALES \nCoste" + espacio + "Nombre de la tarifa" +
    "\n----------------------------------------------------\n";
    f << cabecera;
    string espacio2 = "   ";
    for(unsigned i = 0;i<NUM_TARIFAS_COMERCIALES;i++){
        f << setw(8) << fixed << setprecision(2) <<  costeTarifaPlanaTramos(regDiarios,numRegs,TARIFAS_COMERCIALES[i]) << " €"; 
        f << setw(4) << "" << TARIFAS_COMERCIALES[i].nombre << "\n";
    }   
}

/*
 * Pre:  «f» es «cout» o un flujo de la clase «ofstream» asociado con un fichero
 *       externo abierto para escritura. Las «numRegs» primeras componentes
 *       del vector «regDiarios» contienen datos diarios de precios y consumo
 *       eléctricos de un determinado cliente de nombre «nombreCliente» entre
 *       los meses «mesInicial» y «mesFinal».
 * Post: Ha escrito en el flujo «f» el informe sobre consumo eléctrico indicado
 *       en el enunciado de este trabajo.
 */
void escribirInforme(ostream& f, const GastoDiario regDiarios[], const unsigned numRegs, const string nombreCliente, 
const unsigned mesInicial, const unsigned mesFinal) {
    string nombreClienteMayus = "";
    for (auto c:nombreCliente){
        nombreClienteMayus += (char)toupper(c);
    }
    string cabecera = "INFORME DEL CLIENTE \"" + nombreClienteMayus + "\" ENTRE LOS MESES "+ to_string(mesInicial) + 
    " Y " + to_string(mesFinal) + " DE 2021\n---------------------------------------------------------\n";
    f << cabecera;

    tarifaPVPCGeneral(f, regDiarios, numRegs);
    importeConPVPC(f, regDiarios, numRegs);
    mercadoLibre(f,regDiarios,numRegs);

}   

bool fueraDeFronteras(unsigned mesInicial, unsigned mesFinal){
    return (mesInicial > 11 || mesInicial < 1) || (mesFinal > 11 || mesFinal < 1);
}

SalidaPedirDatos pedirDatos(string& usuario, unsigned& mesInicial, unsigned& mesFinal, string& fichero){
    SalidaPedirDatos salida;
    cout << "Escriba el nombre del usuario: ";

    cin >> usuario;

    cout << endl;
    cout << "Escriba el mes inicial y el final: ";
    cin >> mesInicial >> mesFinal;
    
    
    while (fueraDeFronteras(mesInicial, mesFinal) || mesInicial > mesFinal){
        if (fueraDeFronteras(mesInicial, mesFinal)){
            cout << "El mes inicial tiene que estar entre 1 y 11.\n";
            cout << "El mes final tiene que estar entre 1 y 11.\n";
        }
        if (mesInicial > mesFinal){
            cout << "El mes inicial tiene que ser menor o igual que el mes final.\n" << endl;
        } 

        cout << "Escriba el mes inicial y el final: ";
        cin >> mesInicial >> mesFinal;
    }
    
    cout << endl;
    string pruebaFicheroExiste = "datos/" + usuario + "-2021-01.csv";
    ifstream f(pruebaFicheroExiste);
    if (!f.is_open()){
        salida.accion = 3;
        salida.mensajeError = "No se ha podido leer el fichero \"" + pruebaFicheroExiste + "\".";
        return salida;
    }
    

    cout << "Escriba el nombre del fichero del informe\n";
    cout << "(presione solo ENTRAR para escribirlo en la pantalla): ";
    cin.ignore();
    char crtr = cin.get();
    if (crtr == '\n') {
        salida.accion = 1;
        return salida;
    }
    getline(cin, fichero);
    fichero = crtr + fichero;
    for (auto c: fichero){
        if (c == '>'){
            salida.accion = 3;
            salida.mensajeError = "No se ha podido escribir en el fichero \"" + pruebaFicheroExiste + "\".";
            return salida;
        }
    }
    salida.accion = 2;
    return salida;
}


/*
 *
 *  Pre: 
 */
int main() {

    
    string usuario;
    unsigned mesInicial, mesFinal;
    string fichero = "";

    SalidaPedirDatos nuevoArchivo = pedirDatos(usuario, mesInicial, mesFinal, fichero);
    Fecha fechaInicio = {1, mesInicial, 2021};
    Fecha fechaFinal = {1, mesFinal+1, 2021};

    unsigned numRegs = diasTranscurridos(fechaInicio, fechaFinal);
    GastoDiario regsDiarios[numRegs];
    if (nuevoArchivo.accion == 3){
        cerr << nuevoArchivo.mensajeError;
        return 1;
    }
    else{ 
        leerPrecios("datos/tarifas-2021-ene-nov.csv", mesInicial, mesFinal, regsDiarios);
        leerConsumos(usuario, mesInicial, mesFinal, regsDiarios);
        if (nuevoArchivo.accion == 2){
            ofstream f(fichero);
            if (!f.is_open()){
                cerr << "El archivo no se pudo abrir correctamente";
                return 1;
            }
            escribirInforme(f, regsDiarios, numRegs, usuario, mesInicial, mesFinal);
            cout << "Informe \"" + fichero + "\" creado correctamente.";
            f.close();
        } else if (nuevoArchivo.accion == 1){
            escribirInforme(cout, regsDiarios, numRegs, usuario, mesInicial, mesFinal);
        } 
    }
    return 0;
}