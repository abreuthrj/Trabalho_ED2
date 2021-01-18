#include "lista.cpp"

using namespace std;

Lista::Lista(ifstream& file)
{
    /**
     * INICIA AS VARIAVEIS DA CLASSE
    **/
   this->primeiro_no = nullptr;
   this->ultimo_no = nullptr;

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
        No* novo_dado = new No();
        
        // SETA OS DADOS DO NO

        // --

        
    }
}

Lista::~Lista()
{

}