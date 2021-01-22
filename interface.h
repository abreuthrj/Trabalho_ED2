#include "lista.h"
using namespace std;

void print_menu();
void processa_menu(Lista* lista, Lista* sublista);

/**
 * Implementação da interface e da funcionalidade do menu
 * @author Thiago de Oliveira Abreu
**/

void menu(Lista* lista, Lista* sublista)
{
    print_menu();
    processa_menu(lista,sublista);
}

void print_menu()
{
    cout << "== Interface de Apoio ===" << endl;
    cout << "a - Armazenar a lista/sublista em arquivo .csv" << endl;
    cout << "g - Gerar sublista de N dados aleatórios" << endl;
    cout << "h - Ordenar lista com HeapSort" << endl;
    cout << "p - Printar lista (Esse processo pode demorar alguns minutos)" << endl;
    cout << "t - Printar tamanho da lista" << endl;
    cout << "s - Fechar programa" << endl;
}

void processa_menu(Lista* lista, Lista* sublista)
{
    char comando;
    string arq_saida;
    naoentendi1:
    cin >> comando;

    switch( comando )
    {
        case 'h':
            lista->heap_sort();
        break;

        case 'p':
            lista->print();
        break;

        case 't':
            cout << "A lista possui " << lista->get_tamanho() << " dados." << endl;
        break;

        case 'a':
            aerror:
            cout << "Digite se deseja salvar a lista ou a sublista [l/s]: ";
            cin >> comando;
            if( comando != 's' && comando != 'l' ) goto aerror;
            if( comando == 's' && sublista == nullptr )
            {
                cout << "Voce não gerou nenhuma sublista" << endl;
                break;
            }
            cout << "Digite o nome do arquivo a ser salvo: ";
            cin >> arq_saida;
            if( comando == 'l' ) lista->save_to_csv(arq_saida);
            else sublista->save_to_csv(arq_saida);
        break;

        case 'g':
            int n;
            cout << "Digite o valor de N: ";
            cin >> n;
            sublista = lista->subListaAleatoria(n);
        break;

        case 's':
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
            menu(lista,sublista);
        break;

        case 'n':
            return;
        break;

        default:
            goto naoentendi2;
    }

}
