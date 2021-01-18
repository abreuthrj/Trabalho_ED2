#include <iostream>
#include <fstream>
#include "lista.h"

using namespace std;

int main()
{
    string fname = "brazil_covid19_cities.csv";
    ifstream file(fname);
    Lista* lista = new Lista(file);

    return 0;
}