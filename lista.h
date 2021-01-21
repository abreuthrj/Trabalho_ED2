#ifndef LISTA_H
#define LISTA_H

#include "no.h"
#include <fstream>

class Lista
{
    private:
        int tam;
        int pos;
        No** vet;
        string no_to_line(No* no);

        void max_heapify(No** vet, int i, int n);
    public:
        Lista(ifstream& file);
        ~Lista();

        void heap_sort();
        void save_to_csv(string filename="brazil_covid19_cities_processado.csv");
        void print();
        void print_tamanho();
};

#endif
