#include <iostream>
#include <fstream>
#include "cities.h"

using namespace std;

int main()
{
    string fname = "brazil_covid19_cities.csv";
    ifstream file(fname);
    Cities* cities = new Cities(file);

    return 0;
}