#include <iostream>
#include <stdlib.h>
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
    auto t1 = chrono::high_resolution_clock::now();
    Lista* lista = new Lista(file);
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Tempo do algorítmo de leitura: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    Lista* sublista = nullptr;
    //sublista = lista->subListaAleatoria(2e5);
    //int t = 0, comps = 0, movs = 0;
    // sublista->heap_sort(5, 15, a, b, c);
    //sublista->insertionSort(0, 20, comps, movs);
    /**
     * Inicializa Menu
    **/
    menu(lista,sublista);

    return 0;
}

void etapa01(Lista* lista)
{
    /**
     * Realiza ETAPA 01
    **/
    cout << "Aguarde, processando Etapa 01" << endl;
    cout << "Ordenando..." << endl;
    lista->heap_sort();
    cout << "Casos -> Casos diários..." << endl;
    lista->cases_to_daily();
    cout << "Salvando..." << endl;
    auto t1 = chrono::high_resolution_clock::now();
    lista->save_to_csv("brazil_covid19_cities_processado");
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Tempo do alogritmo de salvar: " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " ms" << endl;
    cout << endl;
}
