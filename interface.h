using namespace std;

void print_menu();
void processa_menu(Lista* lista);

/**
 * Implementação da interface e da funcionalidade do menu
 * @author Thiago de Oliveira Abreu
**/

void menu(Lista* lista)
{
    print_menu();
    processa_menu(lista);
}

void print_menu()
{
    cout << "== Interface de Apoio ===" << endl;
    cout << "h - Ordenar lista com HeapSort" << endl;
    cout << "p - Printar lista (Esse processo pode demorar alguns minutos)" << endl;
    cout << "t - Printar tamanho da lista" << endl;
    cout << "s - Fechar programa" << endl;
}

void processa_menu(Lista* lista)
{
    char comando;
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
            lista->print_tamanho();
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
            menu(lista);
        break;

        case 'n':
            return;
        break;

        default:
            goto naoentendi2;
    }

}