#ifndef LISTA_H
#define LISTA_H

#include "no.h"
#include <fstream>
#include <vector>

using namespace std;

class Lista
{
    private:
        int tam;
        int pos;
        No** vet;

        string no_to_line(No* no);
        void max_heapify(No** vet, int i, int n, int& comps, int& movs);

    public:
        Lista(ifstream& file);
        Lista(int size);
        ~Lista();

        void heap_sort();
        void heap_sort(int& time, int& comp, int& mov);
        void print();
        int get_tamanho(){ return this->tam; };
        void cases_to_daily();
        void analisa_algoritmo(char algoritmo, int n, int m, string arq_nome);

        int append(No* no);
        void save_to_csv(string filename);
        Lista* subListaAleatoria(int n);
        Lista* subListaAleatoriaOld(int n);
};

#endif
