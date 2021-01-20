#include <iostream>

using namespace std;

class No
{
    private:
        string data;
        string estado;
        string cidade;
        float codigo;
        int casos;
        int mortes;

        No* prox_no;
        No* ant_no;
    public:
        No();
        No(string data, string estado, string cidade, float codigo, int casos, int mortes);
        ~No();

        void set_prox(No* no){ this->prox_no = no; }
        void set_ant(No* no){ this->ant_no = no; }
        No* get_prox(){ return this->prox_no; }
        No* get_ant(){ return this->ant_no; }
        string getData(){ return this->data; }
        string getEstado(){ return this->estado; }
        string getCidade(){ return this->cidade; }
        float getCodigo(){ return this->codigo; }
        int getCasos(){ return this->casos; }
        int getMortes(){ return this->mortes; }
};