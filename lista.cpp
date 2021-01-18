#include "no.h"

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

        //void print();
        //void heap_sort();
};