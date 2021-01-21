#include <vector>
#include <iomanip>
#include "lista.h"
#include "string.h"
#include <sstream>

using namespace std;

/**
 * @author Thiago de Oliveira Abreu 201965566C
**/

Lista::Lista(int size){
    this->tam = size;
    this->pos = 0;
    this->vet = new No*[this->tam];

}
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
     * ENCONTRA O NUMERO DE LINHAS DO ARQUIVO
    **/
    string line;
    int size = 0;
    while( getline(file,line) )
        size++;

    /**
     * INICIA AS VARIAVEIS DA CLASSE
    **/
    file.clear(ios_base::goodbit);
    file.seekg(0, file.beg);
    this->tam = size;
    this->pos = 0;
    this->vet = new No*[this->tam];

    /**
     * REALIZA A LEITURA DOS DADOS SALVANDO EM FORMA DE NÓS
     * ESSES NÓS SÃO OBJETOS QUE ARMAZENAM OS DADOS DE CADA CIDADE
    **/
    getline(file,line); // ( LÊ E JOGA A PRIMEIRA LINHA FORA )

    while( getline(file,line) ){
        if( this->pos >= this->tam )
        {
            this->pos++;
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

    this->pos--;
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

void Lista::print_tamanho()
{
    cout << "A lista possui " << this->pos << " dados" << endl;
}

void Lista::max_heapify(No** vet, int i, int n)
{
    int m = i;
    int l = i*2;
    int r = i*2+1;

    // <-- ORDENA A HEAP DE ACORDO COM O ESTADO -> CIDADE -> DATA
    if( l <= n )
        if( vet[l]->getEstado().compare(vet[i]->getEstado()) > 0 )
            m = l;
        else if( vet[l]->getEstado().compare(vet[i]->getEstado()) == 0 )
            if( vet[l]->getCidade().compare(vet[i]->getCidade()) > 0 )
                m = l;
            else if( vet[l]->getCidade().compare(vet[i]->getCidade()) == 0 )
                if( vet[l]->getData().compare(vet[i]->getData()) > 0 )
                    m = l;

    if( r <= n )
        if( vet[r]->getEstado().compare(vet[m]->getEstado()) > 0 )
            m = r;
        else if( vet[r]->getEstado().compare(vet[m]->getEstado()) == 0 )
            if( vet[r]->getCidade().compare(vet[m]->getCidade()) > 0 )
                m = r;
            else if( vet[r]->getCidade().compare(vet[m]->getCidade()) == 0 )
                if( vet[r]->getData().compare(vet[m]->getData()) > 0 )
                 m = r;

    // -->

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

    // CONSTROI A HEAP
    for( int i = this->pos/2; i >= 0; i-- )
        this->max_heapify(this->vet, i, this->pos);

    // ORDENA A HEAP
    for( int i = this->pos; i > 0; i-- )
    {
        No* aux = this->vet[0];
        this->vet[0] = this->vet[i];
        this->vet[i] = aux;
        this->max_heapify(this->vet, 0, i-1);
    }

}
void Lista::save_to_csv(string filename){
    /* Salva a lista no formato .csv
     */
    ofstream file(filename);
    file  << "date,state,name,code,cases,deaths" << std::endl;
    for(int i = 0; i < this->pos; i++){
        file << this->no_to_line(this->vet[i]);
    }
    file.close();
}
string Lista::no_to_line(No* no){
/* retorna uma string contendo:
 * data,estado,nomeDaCidade,codigo,nCasos,mortes\n
 * do Noh passado por parametro.
 */
    stringstream ss;
    ss  << no->getData()   << ","
        << no->getEstado() << ","
        << no->getCidade() << ","
        << std::fixed << std::setprecision(1) << no->getCodigo() << ","
        << no->getCasos()  << ","
        << no->getMortes()
        << std::endl;
    return ss.str();
}
Lista* Lista::subListaAleatoria(int n){
    srand(n); // claro que nao ta aleatorio, posteriormente vou mudar pra ir de acordo com o tempo
    int size = this->pos;
    Lista* lista = new Lista(n*n*n);
    std::vector<int> jaFoi;
    int index;
    for(int i = 0; i < n; i++){
        index = (rand()%(size - jaFoi.size())); // escolher um index aleatorio entre 0 e o numero de indexes nao escolhidos ainda. exemplo: se na lista tem 100 itens e ja foram escolhiidos 3, entao devo escolher entre os 97 restantes
        // cout << index;
        for(int j = 0; j < jaFoi.size(); j++){
            if(i >= jaFoi[j]){
                index++;
            }
        }
        jaFoi.push_back(index);
        lista->append(this->vet[index]);
    }
    return lista;
}
int Lista::append(No* no){
    if(this->pos >= this->tam)
        return -1;
    this->vet[pos] = no;
    this->pos++;
    return 0;
}
