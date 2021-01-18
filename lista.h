#include "lista.cpp"
#include "string"

using namespace std;

/**
 * @author Thiago de Oliveira Abreu 201965566C
**/

Lista::Lista(ifstream& file)
{

    /**
     * VERIFICA SE ARQUIVO FOI ABERTO CORRETAMENTE
     * CASO NAO TENHA SIDO, FECHA O PROGRAMA COM CODIGO DE ERRO
    **/
    if( !file.is_open() ){
        cout << "Não foi possível ler o arquivo" << endl;
        exit(0);
    }

    /**
     * INICIA AS VARIAVEIS DA CLASSE
    **/
   file.seekg(0,file.end);
   this->tam = file.tellg();
   file.seekg(0);
   this->pos = 0;
   this->vet = new No*[this->tam];

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

        string data = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        string estado = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        string cidade = line_aux.substr(0, line_aux.find(','));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        float codigo = stof(line_aux.substr(0, line_aux.find(',')));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        int casos = stof(line_aux.substr(0, line_aux.find(',')));
        line_aux = line_aux.substr(line_aux.find(',')+1);

        int mortes = stoi(line_aux.substr(0, line_aux.find(',')));

        this->vet[this->pos] = new No(data,estado,cidade,codigo,casos,mortes);

        this->pos++;
        
    }
}

Lista::~Lista()
{
    delete [] this->vet;
}

void Lista::print()
{
    for( int i=0; i < this->pos; i++ )
    {
        cout << this->vet[i]->getData() << "," << this->vet[i]->getEstado() << "," << this->vet[i]->getCidade() << "," << this->vet[i]->getCodigo() << "," << this->vet[i]->getCasos() << "," << this->vet[i]->getMortes() << endl;;
    }
}

void Lista::max_heapify(No** vet, int i, int n)
{
    int m = i;
    int l = i*2;
    int r = i*2+1;

    if( l <= n && vet[l]->getEstado().compare(vet[i]->getEstado()) > 0 )
        m = l;
    else
        m = r;
    
    if( r <= n && vet[r]->getEstado().compare(vet[m]->getEstado()) > 0 )
        m = r;

    if( m != i )
    {
        No* aux = vet[m];
        vet[m] = vet[i];
        vet[i] = aux;
        this->max_heapify(vet,m,n);
    }
    
}

void Lista::heap_sort()
{

    this->max_heapify(this->vet, this->tam/2, this->tam);

    for( int i = this->pos; i > 0; i-- )
    {
        No* aux = this->vet[0];
        this->vet[0] = this->vet[this->pos];
        this->vet[this->pos] = aux;
        this->max_heapify(this->vet, 0, i-1);
        cout << "Iteração: " << i;
    }

}