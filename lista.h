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

        void max_heapify(No** vet, int i, int n);
    public:
        Lista(ifstream& file);
        ~Lista();

        void heap_sort();
        void print();
        void print_tamanho();
};

#endif
