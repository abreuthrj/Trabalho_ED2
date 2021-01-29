#include <vector>
#include <math.h>
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
    srand(time(NULL));

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
    /**
     * Ordena de acordo com o par (Estado->Cidade), Data 
     * Exibe os dados produzidos pelo algoritmp
     */
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

    int duration = chrono::duration_cast<chrono::milliseconds>(te-ts).count();

    cout << "==( HeapSort )==" << endl;
    cout << "Tempo de execução : " << duration << " ms" << endl;
    cout << "Número de comparações: " << comp << endl;
    cout << "Número de movimentações de chaves: " << movs << endl;
    cout << "== ( Fim )==" << endl;
}

void Lista::max_heapify_cases(int i, int n, int& comps, int& movs)
{
    int m = i;
    int l = i*2;
    int r = i*2+1;

    /**
     *  Ordena de acordo com o Número de Casos
     */

    if( l <= n )
    {
        comps++;
        if( this->vet[l]->getCasos() > this->vet[i]->getCasos() )
        {
            comps++;
            m = l;
        }
    }

    if( r <= n )
    {
        comps++;
        if( this->vet[r]->getCasos() > this->vet[m]->getCasos() )
        {
            comps++;
            m = r;
        }
    }

    if( m != i )
    {
        comps++;
        No* aux = this->vet[i];
        this->vet[i] = this->vet[m];
        this->vet[m] = aux;
        movs++;
        this->max_heapify_cases(m,n,comps,movs);
    }

}

void Lista::heap_sort(int& time, int& comp, int& mov)
{
    /**
     * Apenas ordena, guardando os dados produzidos pelo algoritmo 
     * nas variaveis passadas por referencia 
     */
    auto ts = chrono::high_resolution_clock::now();
    // CONSTROI A HEAP
    for( int i = (this->tam-1)/2; i >= 0; i-- )
        this->max_heapify_cases(i, (this->tam-1), comp, mov);

    // ORDENA A HEAP
    for( int i = (this->tam-1); i > 0; i-- )
    {
        No* aux = this->vet[0];
        this->vet[0] = this->vet[i];
        this->vet[i] = aux;
        this->max_heapify_cases(0, i-1, comp, mov);
    }
    auto te = chrono::high_resolution_clock::now();

    int duration = chrono::duration_cast<chrono::milliseconds>(te-ts).count();

    time = duration;
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

void Lista::analisa_algoritmo(char algoritmo, int n, int m, string arq_nome = "saida")
{
    /**
     * Cria M sublistas aleatórias, baseadas na atual lista já pré processada
     * A cada sublista criada, realiza a ordenação com o algoritmo especificado
     * Computa os dados individuais de cada ordenação e suas médias
     * Salva esses dados no arquivo saida.txt
     **/
    int time, comparations, movements;
    float* individuais = new float[m*3];
    float* medias = new float[3];
    Lista* sublista;

    medias[0] = medias[1] = medias[2] = 0;

    for( int i = 0; i<m*3; i++ )
        individuais[i] = 0;

    for( int i=0; i<m*3; i+=3 )
    {
        time = comparations = movements = 0;
        sublista = this->subListaAleatoria(n);
        if( algoritmo == 'h' ) sublista->heap_sort(time,comparations,movements);
        else if( algoritmo == 'q' ) sublista->quickSort(0,sublista->tam-1, comparations, movements);
        else if( algoritmo == 'i' ) sublista->introSort(0, sublista->get_pos(), time, comparations, movements);
        individuais[i] = time;
        individuais[i+1] = comparations;
        individuais[i+2] = movements;
        medias[0] += time;
        medias[1] += comparations;
        medias[2] += movements;
        cout << "M[" << (i/3)+1 << "] concluido" << endl;
    }

    medias[0] /= m;
    medias[1] /= m;
    medias[2] /= m;

    ofstream arq_saida(arq_nome+".txt");

    for( int i=0; i < m*3; i+=3)
        arq_saida << "M = " << (i/3)+1 << endl << "Duração: " << individuais[i] << " ms" << endl << "Comparações: " << individuais[i+1] << endl << "Movimentações: " << individuais[i+2] << endl << endl;

    arq_saida << "== Médias ==" << endl << "Duração: " << medias[0] << " ms" << endl << "Comparações: " << medias[1] << endl << "Movimentações: " << medias[2] << endl;

    arq_saida.close();

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
Lista* Lista::subListaAleatoriaOld(int n){
    //mantive essa versao antiga (O(n^2)) para fins ilustrativos
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
Lista* Lista::subListaAleatoria(int n){
    /* cria um vetor I que armazena os indices do vetor da lista.
     * Para cada elemento j desse vetor I,
     *  gera um numero aleatorio 'r' entre j e o tamanho do vetor da lista ---> [j, tamanho)
     *  e troca I[j] com I[r];
     * cria uma sublista e tamanho n
     * e por fim adiciona os primeiros n elementos na sublista
     */
    int size = this->pos;
    Lista* lista = new Lista(n); // custo espacial elevado, ja que sao criadas duas listas de tamanho N;
    int index, aux;
    int* shuffledIndices = new int[this->pos];
    for(int i = 0; i < this->pos; i++){
        shuffledIndices[i] = i;
    }
    for(int i = 0; i < n; i++){
        index = rand()%(size - i) + i;
        aux = shuffledIndices[i];
        shuffledIndices[i] = shuffledIndices[index];
        lista->append(this->vet[shuffledIndices[i]]);
        shuffledIndices[index] = aux;
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

int Lista::introSort(int begin, int end, int& time, int& comps, int& movs){
    time = 0; comps = 0; movs = 0;
    // introSortLoop(v, begin, end, 2*log2(end - begin));
    auto ts = chrono::high_resolution_clock::now();
    introSortLoop(begin, end, 2*log2(end - begin), comps, movs);
    // introSortLoop(begin, end, 0, comps, movs);
    insertionSort(begin, end, comps, movs);
    auto te = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(te-ts).count();
    cout << "==( IntroSort )==" << endl;
    cout << "Tempo de execução : " << time<< " ms" << endl;
    cout << "Número de comparações: " << comps << endl;
    cout << "Número de movimentações de chaves: " << movs << endl;
    cout << "== ( Fim )==" << endl;
    return 0;
}
int Lista::introSortLoop(int beg, int end, int depthLimit, int& comps, int& movs){
    while(end - beg > 10){ // primeiro verifica se o tamanho do subvetor eh grande o suficiente para ser valido usar o quickSort ao inves do insertionSort
    // claro que para um tamanho == 1 temos o caso base do quicksort.
        if(depthLimit == 0){ // se chegar num numero de chamadas muito elevado (ao ponto de ficar O(n^2)) eh usado o heapsort, que tem como pior caso O(nlogn)
            heap_sort(beg, end, comps, movs);
            return 0;
        }

        depthLimit--;
        int pivot = partition(beg, end, this->medianOf3(this->vet[beg]->getCasos(), this->vet[(int)(end-beg)/2]->getCasos(), this->vet[end-1]->getCasos()), comps, movs);
        introSortLoop(pivot, end, depthLimit, comps, movs);
        end = pivot; /*  Ou seja, primeiro eh ordenado recursivamente todo o lado a direita do pivo, depois todo o lado esquerdo. (pivot = end)
                      *  Normalmente eh feito 2 chamadas recursivamente uma pro lado esquerdo do pivo e uma pro lado direito, uma depois da outra.
                      *  Todavia nesse caso eh feito todas as chamadas recursivas do lado direito primeiro
                      */
    }
    return 0;
}
int Lista::medianOf3(int a, int b, int c){
    if((a >= b || c >= b) && (b >= a || b >= c))
        return b;
    if((b >= a || c >= a) && (a >= b || a >= c))
        return a;
    if((a >= c || b >= c) && (c >= a || c >= b))
        return c;
    return b;
}
int Lista::partition(int beg, int end, int pivot, int& comps, int& movs){
    // particiona o subvetor, retornando a posicao final do vetor

    int size = end - beg;
    No aux; // usado para as trocas de elemento
    int i = beg, j = end - 1;
    while(i <= j)
	{
		while(this->vet[i]->getCasos() < pivot && i < end)
		{
			i++;
            comps++;
		}
		while(this->vet[j]->getCasos() > pivot && j > beg)
		{
			j--;
            comps++;
		}
		if(i <= j)
		{
			aux = *(this->vet[i]); // Nota do Autor: eu fiquei um total de 4 horas pra descobrir que "*(this->vet[i])" eh diferente de "*this->vet[i]"
			*(this->vet[i]) = *(this->vet[j]);
			*(this->vet[j]) = aux;
			i++;
			j--;
            movs++;
		}
        // std::cout<< "vetor: ";
        // for(int i = 0; i < end - beg; i++){
            // std::cout << this->vet[beg + i]->getCasos() << " ";
        // }
        // std::cout<< "vetor: ";
        // for(int k = 0; k < 20; k++){
            // if(beg == k)
                // std::cout << "b:";
            // if(end == k)
                // std::cout << "e:";
            // std::cout << this->vet[k]->getCasos() << " ";
        // }
        // std::cout << std::endl;
	}
    // std::cout << "j:" << j;
    if(j != beg - 1)
        return j+1;
    return j+2;
}
void swap(int* v, int i1, int i2){
    /* troca a posicao de 2 elementos dados seus indices
     */
    int aux = v[i1];
    v[i1] = v[i2];
    v[i2] = aux;

}
void Lista::max_heapify(No** vet, int beg, int i, int last, int& comps, int& movs)
{
    int m = i;
    int l = (i - beg)*2 + beg;
    int r = l+1;

    // <-- ORDENA A HEAP DE ACORDO COM numero de casos
    if( l <= last )
    {
        comps++;
        if( vet[l]->getCasos() > vet[i]->getCasos())
        {
            m = l;
            comps++;
        }
    }

    if( r <= last )
    {
        comps++;
        if( vet[r]->getCasos() > vet[m]->getCasos())
        {
            comps++;
            m = r;
        }
    }



    if( m != i )
    {
        comps++;
        No* aux = vet[m];
        vet[m] = vet[i];
        vet[i] = aux;
        movs++;
        this->max_heapify(vet,beg, m,last,comps,movs);
    }

}

void Lista::heap_sort(int beg, int end, int& comp, int& mov)
{
    // auto ts = chrono::high_resolution_clock::now();
    // CONSTROI A HEAP
    for( int i = (end - beg - 1)/2 + beg; i >= beg; i-- )
        this->max_heapify(this->vet, beg, i, end-1, comp, mov);

    // ORDENA A HEAP
    for( int i = end - 1; i > beg; i-- )
    {
        No* aux = this->vet[beg];
        this->vet[beg] = this->vet[i];
        this->vet[i] = aux;
        this->max_heapify(this->vet, beg, beg, i-1, comp, mov);
    }
    auto te = chrono::high_resolution_clock::now();

    // int duration = chrono::duration_cast<chrono::milliseconds>(te-ts).count();

    // time = duration;
}
void Lista::insertionSort(int beg, int end, int& comps, int& movs){

    for (int i = beg + 1; i < end; i++) {
		No* escolhido = this->vet[i];
		int j = i - 1;

		while ((j >= beg) && (this->vet[j]->getCasos() > escolhido->getCasos())) {
			this->vet[j + 1] = this->vet[j];
            movs++;
            comps++;
			j--;
		}

		this->vet[j + 1] = escolhido;
        movs++;
	}
}

/**
 * @author Gabriel Barreto Calixto
 **/

int Lista::particionar(int p, int q, int& comps, int& movs){

    int pivoIndice = (p+q)/2; // pivo como elemento do meio
    int pivo = this->vet[pivoIndice]->getCasos();
    No* aux;
    int i =p;
    int j = q;

    do{
    while(this->vet[i]->getCasos() < pivo){
        i++;
        comps++;
    } 

    while(this->vet[j]->getCasos() > pivo) {
        j--;
        comps++;
    }
    
    if(i<=j){
        comps++;
        aux = this->vet[i];
        this->vet[i] = this->vet[j];
        this->vet[j] = aux;
        i++;
        j--;
        movs ++;
    }
    }
    while(i<=j);
    return j;
}

void Lista::quickSort(int p, int q, int& comps, int& movs){

    if(q-p > 0){
        int part = particionar(p, q, comps, movs);
        if(p < part){
            quickSort(p, part-1, comps, movs);
            quickSort(part +1, q, comps, movs);
        }
    }
}

void Lista::quick_sort() {
    auto ts = chrono::high_resolution_clock::now();

    int movs, comps = 0;
    quickSort(0, this->tam-1, comps, movs);
    auto te = chrono::high_resolution_clock::now();
    int duration = chrono::duration_cast<chrono::milliseconds>(te-ts).count();

    cout << "==( QuickSort )==" << endl;
    cout << "Tempo de execução : " << duration << " ms" << endl;
    cout << "Número de comparações: " << comps << endl;
    cout << "Número de movimentações de chaves: " << movs << endl;
    cout << "== ( Fim )==" << endl;
}
