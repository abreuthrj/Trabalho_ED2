#include <iostream>

using namespace std;

class No
{
    private:
        string date;
        string state;
        string name;
        string code;
        float cases;
        int deaths;

        No* prox_no;
        No* ant_no;
    public:
        No();
        ~No();

        void set_prox(No* no);
        void set_ant(No* no);
        No* get_prox();
        No* get_ant();
};