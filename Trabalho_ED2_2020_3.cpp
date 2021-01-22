#include <iostream>
#include <fstream>
#include "lista.h"
#include "interface.h"

using namespace std;

int main(int argc, char** argv)
{
    string fname;
    if( argc > 1 )
        fname = argv[1]; 
    else
        fname = "brazil_covid19_cities.csv";
    ifstream file(fname);
    Lista* lista = new Lista(file);
    Lista* sublista = nullptr;

    menu(lista,sublista);

    return 0;
}
