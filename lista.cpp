#include "no.h"

class Lista
{
    private:
        int tam;
        int pos;
        No** vet;
    public:
        Lista(ifstream& file);
        ~Lista();

        void printa_lista();
};