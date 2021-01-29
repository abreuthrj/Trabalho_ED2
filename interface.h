#include "lista.h"
using namespace std;

void print_menu(bool& lista);
void processa_menu(Lista* lista, Lista* sublista, bool& isLista);
void etapa01(Lista* lista);

/**
 * Implementação da interface e da funcionalidade do menu
 * @author Thiago de Oliveira Abreu
**/

void menu(Lista* lista, Lista* sublista, bool isLista=true)
{
    print_menu(isLista);
    processa_menu(lista,sublista,isLista);
}

void print_menu(bool& lista)
{
    cout << "== Interface de Apoio ===" << endl;
    cout << "Etapas" << endl;
    cout << "f - Realizar etapa 01" << endl;
    cout << "e - Realizar etapa 02" << endl;
    cout << endl;
    cout << "Selecionada: " << ( lista ? "Lista":"Sublista" ) << " - [/] para alternar" << endl << endl;
    cout << "a - Armazenar em arquivo .csv" << endl;
    cout << "g - Gerar sublista de N dados aleatórios" << endl;
    cout << "h - Ordenar com HeapSort" << endl;
    cout << "q - Ordenar com QuickSort" << endl;
    cout << "i - Ordenar com IntroSort" << endl;
    cout << "p - Printar lista (Esse processo pode demorar alguns minutos)" << endl;
    cout << "t - Printar tamanho da lista" << endl;
    cout << "s - Fechar programa" << endl;
}

void processa_menu(Lista* lista, Lista* sublista, bool& isLista)
{
    int time, comps, movs;
    char comando;
    string arq_saida;
    Lista* selecionada = ( isLista ? lista:sublista );

    naoentendi1:
    cin >> comando;

    switch( comando )
    {
        case 'h':
            selecionada->heap_sort();
        break;
        case 'i':
            selecionada->introSort(0, selecionada->get_pos(), time, comps, movs);
        break;

        case 'p':
            selecionada->print();
        break;

        case 't':
            cout << "A lista possui " << selecionada->get_tamanho() << " dados." << endl;
        break;

        case 'a':
            cout << "Digite o nome do arquivo a ser salvo: ";
            cin >> arq_saida;
            selecionada->save_to_csv(arq_saida);
        break;

        case 'q':
            selecionada->quick_sort();
        break;

        case 'g':
            int n;
            cout << "Digite o valor de N: ";
            cin >> n;
            sublista = lista->subListaAleatoria(n);
        break;

        case 'e':
            int mtimes,ndata;
            char alg;
            cout << "Digite o valor de N ( Número de dados aleatórios ): ";
            cin >> ndata;
            cout << "Digite o valor de M ( Número de vezes a ser ordenado ): ";
            cin >> mtimes;
            cout << "Digite o algoritmo de ordenação [h/q/i]: ";
            cin >> alg;
            cout << "Digite o nome do arquivo de saida (.txt): ";
            cin >> arq_saida;
            selecionada->analisa_algoritmo(alg,ndata,mtimes,arq_saida);
        break;

        case 'f':
            etapa01(lista);
        break;

        case 's':
            return;
        break;

        case '/':
            if( isLista && sublista == nullptr )
            {
                cout << "É necessário gerar uma Sublista [g] antes de selecioná-la" << endl;
                goto naoentendi1;
            }
            isLista = !isLista;
            menu(lista,sublista,isLista);
            return;
        break;

        default:
            goto naoentendi1;
    }

    naoentendi2:
    cout << endl << "Voce deseja realizar outra ação ? [s/n]" << endl;
    cin >> comando;

    switch( comando )
    {
        case 's':
            menu(lista,sublista,isLista);
        break;

        case 'n':
            return;
        break;

        default:
            goto naoentendi2;
    }

}
