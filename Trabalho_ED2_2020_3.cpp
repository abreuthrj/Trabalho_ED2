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

    menu(lista);

    // lista->heap_sort();
    // lista->print();

    return 0;
}