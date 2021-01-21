#include <iostream>
#include <fstream>
#include "lista.h"
#include "interface.h"

using namespace std;

int main()
{
    string fname = "brazil_covid19_cities.csv";
    ifstream file(fname);
    Lista* lista = new Lista(file);
    Lista* listinha = lista->subListaAleatoria(100000);
    // cout << "Salvando Listinha para csv...." << endl;
    // listinha->save_to_csv("testeSeTemIgual.csv");
    // cout << "Salvando Lista para csv...." << endl;
    lista->save_to_csv();

    menu(lista);

    // lista->heap_sort();
    // lista->print();

    return 0;
}
