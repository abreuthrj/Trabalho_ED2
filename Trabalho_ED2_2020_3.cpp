#include <iostream>
#include <fstream>
#include <chrono>
#include "lista.h"
#include "interface.h"

using namespace std;

int main(int argc, char** argv)
{
    /**
     * Processa argumentos
    **/
    string fname = "brazil_covid19_cities.csv";
    if( argc > 1 )
        fname = argv[1]; 
    
    /**
     * Le arquivos e inicializa variaveis da lista
    **/
    cout << "Lendo arquivo: " << fname << endl;

    ifstream file(fname);
    Lista* lista = new Lista(file);
    Lista* sublista = nullptr;

    /**
     * Realiza ETAPA 01
    **/
    cout << "Aguarde, processando Etapa 01" << endl;
    lista->heap_sort();
    lista->save_to_csv("brazil_covid19_cities_processado");
    cout << endl;

    /**
     * Inicializa Menu
    **/
    menu(lista,sublista);

    return 0;
}
