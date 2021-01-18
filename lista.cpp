#include "no.h"

class Lista
{
    private:
        No* primeiro_no;
        No* ultimo_no;
    public:
        Lista(std::ifstream& file);
        ~Lista();
};