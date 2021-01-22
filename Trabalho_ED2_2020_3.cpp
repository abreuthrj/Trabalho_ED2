#include <iostream>
#include <fstream>
#include "lista.h"
#include "interface.h"

using namespace std;

string fname = "brazil_covid19_cities.csv";
ifstream file(fname);
Lista* lista = new Lista(file);
Lista* sublista = nullptr;

int main()
{
    menu(lista,sublista);

    return 0;
}
