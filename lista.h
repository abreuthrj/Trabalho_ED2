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
        Lista(int size);
        ~Lista();

        void heap_sort();
        int append(No* no);
        void save_to_csv(string filename="brazil_covid19_cities_processado.csv");
        Lista* subListaAleatoria(int n);
        void print();
        void print_tamanho();
};

#endif
