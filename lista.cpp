#include <vector>
#include <iomanip>
#include "lista.h"
#include "string.h"
#include <sstream>
#include <chrono>

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
    string line;
    this->tam = -1;
    this->pos = 0;
    while( getline(file,line) )
        this->tam++;
    this->vet = new No*[this->tam];
    file.clear(ios_base::goodbit);
    file.seekg(0, file.beg);

    /**
     * REALIZA A LEITURA DOS DADOS SALVANDO EM FORMA DE NÓS
     * ESSES NÓS SÃO OBJETOS QUE ARMAZENAM OS DADOS DE CADA CIDADE
    **/
    getline(file,line); // ( LÊ E JOGA A PRIMEIRA LINHA FORA )

    while( getline(file,line) ){
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

        //vet.push_back( new No(data,estado,cidade,codigo,casos,mortes) );
        this->vet[this->pos] = new No(data,estado,cidade,codigo,casos,mortes);

        this->pos++;
    }

    //this->tam = vet.size();
}

Lista::~Lista()
{

}

void Lista::print()
{
    for( int i=0; i < this->tam; i++ )
    {
        cout << this->vet[i]->getData() << "," << this->vet[i]->getEstado() << "," << this->vet[i]->getCidade() << "," << this->vet[i]->getCodigo() << "," << this->vet[i]->getCasos() << "," << this->vet[i]->getMortes() << endl;;
    }
}

void Lista::max_heapify(No** vet, int i, int n, int& comps, int& movs)
{
    int m = i;
    int l = i*2;
    int r = i*2+1;

    // <-- ORDENA A HEAP DE ACORDO COM O ESTADO -> CIDADE -> DATA
    if( l <= n )
    {
        comps++;
        if( vet[l]->getEstado().compare(vet[i]->getEstado()) > 0 )
        {
            m = l;
            comps++;
        }
        else if( vet[l]->getEstado().compare(vet[i]->getEstado()) == 0 )
        {
            comps++;
            if( vet[l]->getCidade().compare(vet[i]->getCidade()) > 0 )
            {
                comps++;
                m = l;
            }
            else if( vet[l]->getCidade().compare(vet[i]->getCidade()) == 0 )
            {
                comps++;
                if( vet[l]->getData().compare(vet[i]->getData()) > 0 )
                {
                    comps++;
                    m = l;
                }
            }
        }
    }

    if( r <= n )
    {
        comps++;
        if( vet[r]->getEstado().compare(vet[m]->getEstado()) > 0 )
        {
            comps++;
            m = r;
        }
        else if( vet[r]->getEstado().compare(vet[m]->getEstado()) == 0 )
        {
            comps++;
            if( vet[r]->getCidade().compare(vet[m]->getCidade()) > 0 )
            {
                comps++;
                m = r;
            }
            else if( vet[r]->getCidade().compare(vet[m]->getCidade()) == 0 )
            {
                comps++;
                if( vet[r]->getData().compare(vet[m]->getData()) > 0 )
                {
                    comps++;
                    m = r;
                }
            }
        }
    }
            

    // -->
    //cout << "heapify loop: " << m << endl;

    if( m != i )
    {
        comps++;
        No* aux = vet[m];
        vet[m] = vet[i];
        vet[i] = aux;
        movs++;
        this->max_heapify(vet,m,n,comps,movs);
    }

}

void Lista::heap_sort()
{
    int comp, movs = 0;

    auto ts = chrono::high_resolution_clock::now();
    // CONSTROI A HEAP
    for( int i = (this->tam-1)/2; i >= 0; i-- )
        this->max_heapify(this->vet, i, (this->tam-1), comp, movs);

    // ORDENA A HEAP
    for( int i = (this->tam-1); i > 0; i-- )
    {
        No* aux = this->vet[0];
        this->vet[0] = this->vet[i];
        this->vet[i] = aux;
        this->max_heapify(this->vet, 0, i-1, comp, movs);
    }
    auto te = chrono::high_resolution_clock::now();

    cout << "==( HeapSort )==" << endl;
    cout << "Tempo de execução : " << chrono::duration_cast<chrono::milliseconds>(te-ts).count() << " ms" << endl;
    cout << "Número de comparações: " << comp << endl;
    cout << "Número de movimentações de chaves: " << movs << endl;
    cout << "== ( Fim )==" << endl;

}

void Lista::cases_to_daily()
{
    /**
     * RODA O VETOR A PARTIR DO SEGUNDO NÓ TRANSFORMANDO O NUMERO DE CASOS EM NUMERO DE CASOS DIARIOS
     * VERIFICA, TAMBÉM, ANTES DE REALIZAR A MUDANÇA, SE A RESPECTIVA CIDADE É A MESMA DA ANTERIOR
     **/
    for( int i = 1; i<this->tam; i++ )
        if( this->vet[i]->getCidade().compare(this->vet[i-1]->getCidade()) == 0 )
            this->vet[i]->setCasos( this->vet[i]->getCasos()-this->vet[i-1]->getCasos() );

    
}

/**
 * @author Samuel Abreu
**/
Lista::Lista(int size){
    this->tam = size;
    this->pos = 0;
    this->vet = new No*[size];
}

void Lista::save_to_csv(string filename){
    /* Salva a lista no formato .csv
     */
    ofstream file(filename+".csv");
    file  << "date,state,name,code,cases,deaths" << std::endl;
    for(int i = 0; i < this->tam; i++){
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
    srand(n); // nao ta aleatorio, posteriormente vou mudar pra ir de acordo com o tempo
    int size = this->tam;
    Lista* lista = new Lista(n); // custo espacial elevado, ja que sao criadas duas listas de tamanho N;
    int* jaFoi = new int[n];
    int jaFoiSize = 0;
    int index;
    for(int i = 0; i < n; i++){
        index = (rand()%(size - jaFoiSize)); // escolher um index aleatorio entre 0 e o numero de indexes nao escolhidos ainda. exemplo: se na lista tem 100 itens e ja foram escolhiidos 3, entao devo escolher entre os 97 restantes
        for(int j = 0; j < jaFoiSize; j++){
            if(i >= jaFoi[j]){
                index++;
            }
        }
        jaFoi[jaFoiSize] = index; // seria valido criar um TAD para esse tipo de vetor dinamico, mas por enquanto soh esta sendo utilizado aqui.
        jaFoiSize++;
        lista->append(this->vet[index]);
    }
    return lista;
}
int Lista::append(No* no){
    if(this->pos >= this->tam)
        return -1;
    this->vet[pos] = no;
    this->pos++;
    //this->vet.push_back( no );
    return 0;
}