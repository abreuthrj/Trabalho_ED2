#include <iostream>

using namespace std;

class No
{
    private:
        string data;
        string estado;
        string cidade;
        string codigo;
        float casos;
        int mortes;

        No* prox_no;
        No* ant_no;
    public:
        No();
        No(string data, string estado, string cidade, string codigo, float casos, int mortes);
        ~No();

        void set_prox(No* no);
        void set_ant(No* no);
        No* get_prox();
        No* get_ant();
};