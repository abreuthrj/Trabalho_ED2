#include "no.h"

using namespace std;

No::No()
{

}

No::No(string data, string estado, string cidade, float codigo, int casos, int mortes)
{
    this->prox_no = nullptr;
    this->ant_no = nullptr;

    this->data = data;
    this->estado = estado;
    this->cidade = cidade;
    this->codigo = codigo;
    this->casos = casos;
    this->mortes = mortes;
}

No::~No()
{

}
