#include "no.h"

class Lista
{
    private:
        int tam;
        int pos;
        No** vet;

        void max_heapify();
    public:
        Lista(ifstream& file);
        ~Lista();

        void print();
        void heap_sort();
};