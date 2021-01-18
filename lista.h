#include "lista.cpp"
#include "string"

using namespace std;

Lista::Lista(ifstream& file)
{
    /**
     * INICIA AS VARIAVEIS DA CLASSE
    **/
   //this->primeiro_no = nullptr;
   //this->ultimo_no = nullptr;
   this->tam = 100000;
   this->pos = 0;
   this->vet = new No[this->tam];

    /**
     * VERIFICA SE ARQUIVO FOI ABERTO CORRETAMENTE
     * CASO NAO TENHA SIDO, FECHA O PROGRAMA COM CODIGO DE ERRO
    **/
    if( !file.is_open() ){
        cout << "Não foi possível ler o arquivo" << endl;
        exit(0);
    }

    /**
     * REALIZA A LEITURA DOS DADOS SALVANDO EM FORMA DE NÓS
     * ESSES NÓS SÃO OBJETOS QUE ARMAZENAM OS DADOS DE CADA CIDADE
    **/ 
    string line;
    getline(file,line); // ( LÊ E JOGA A PRIMEIRA LINHA FORA )

    while( getline(file,line) ){
        if( this->pos >= this->tam )
        {
            cout << "Maximo de dados suportados pela lista atingido" << endl;
            break;
        }

        string line_aux = line;

        string data = line_aux.substr(0, line_aux.find_first_of(','));
        line_aux = line_aux.substr(line_aux.find_first_of(','));

        string estado = line_aux.substr(0, line_aux.find_first_of(','));
        line_aux = line_aux.substr(line_aux.find_first_of(','));

        string cidade = line_aux.substr(0, line_aux.find_first_of(','));
        line_aux = line_aux.substr(line_aux.find_first_of(','));

        string codigo = line_aux.substr(0, line_aux.find_first_of(','));
        line_aux = line_aux.substr(line_aux.find_first_of(','));

        float casos = stof(line_aux.substr(0, line_aux.find_first_of(',')));
        line_aux = line_aux.substr(line_aux.find_first_of(','));

        int mortes = stoi(line_aux.substr(0, line_aux.find_first_of(',')));
        line_aux = line_aux.substr(line_aux.find_first_of(','));


        this->vet[pos] = new No(data,estado,cidade,codigo,casos,mortes);

        pos++;
        
    }
}

Lista::~Lista()
{
    delete [] this->vet;
}

void Lista::printa_lista()
{
    for( int i=0; i < this->pos; i++ )
    {
        cout << this->vet[i].data << "," << this->vet[i].estado << "," << this->vet[i].cidade << "," << this->vet[i].codigo << "," << this->vet[i].casos << "," << this->vet[i].mortes;
    }
}