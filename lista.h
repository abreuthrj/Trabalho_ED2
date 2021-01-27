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
        void max_heapify_cases(int i, int n, int& comps, int& movs);
        void max_heapify(No** vet, int begin, int i, int end, int& comps, int& movs);
        int introSortLoop(int begin, int end, int depthLimit, int& comps, int& movs);
        int partition(int begin, int end, int pivot);
        int partition(int begin, int end, int pivot, int& comps, int& movs);
        int medianOf3(int a, int b, int c);

    public:
        Lista(ifstream& file);
        Lista(int size);
        ~Lista();

        void heap_sort();
        void insertionSort(int begin, int end, int& comps, int& movs);
        int introSort(int begin, int end, int& time, int& comps, int& movs);
        void heap_sort(int& time, int& comp, int& mov);
        void heap_sort(int begin, int end, int& comps, int& movs);
        void print();
        int get_tamanho(){ return this->tam; };
        int get_pos(){ return this->pos; };
        void cases_to_daily();
        void analisa_algoritmo(char algoritmo, int n, int m, string arq_nome);

        int append(No* no);
        void save_to_csv(string filename);
        Lista* subListaAleatoria(int n);
        Lista* subListaAleatoriaOld(int n);
};

#endif
