#include <iostream>
#include <list>
using namespace std;

struct Cliente
{
    int id;
    string nome;
    int idade;
    Cliente* titular;
    
};

list<Cliente*> clientes;

static int autoId = 1;

void cadastrarCliente()
{
    Cliente *cliente = new Cliente;
    cout << "Digite o nome do cliente: ";
    cin >> cliente->nome;
    cout << "Digite a idade do cliente: ";
    cin >> cliente->idade;
    cliente->id = autoId++;
    cliente->titular = cliente;
    clientes.push_back(cliente);
    cout << "Cliente cadastrado com sucesso! ID: " << cliente->id << endl;
}

void cadastrarDependente()
{
    int titular_id;
    cout << "Digite o ID do cliente titular: ";
    cin >> titular_id;
    Cliente *titular = nullptr;

    for (auto it = clientes.begin(); it != clientes.end(); it++)
    {
        if ((*it)->id == titular_id && (*it)->titular == (*it))
        {
            titular = (*it);
            break;
        }
    }

    if (titular == nullptr)
    {
        cout << "Titular não encontrado ou não é um titular!" << endl;
        return;
    }

    Cliente *dependente = new Cliente;
    cout << "Digite o nome do dependente: ";
    cin >> dependente->nome;
    cout << "Digite a idade do dependente: ";
    cin >> dependente->idade;
    dependente->id = autoId++;
    dependente->titular = titular;
    clientes.push_back(dependente);
    cout << "Dependente cadastrado com sucesso! ID: " << dependente->id << endl;
}

void alterarCliente()
{
    int id;
    cout << "Digite o ID do cliente que deseja alterar: ";
    cin >> id;

    Cliente *cliente = nullptr;
    for (auto it = clientes.begin(); it != clientes.end(); it++)
    {
        if ((*it)->id == id)
        {
            cliente = (*it);
            break;
        }
    }

    if (cliente == nullptr)
    {
        cout << "Cliente não encontrado!" << endl;
        return;
    }

    cout << "Digite o novo nome do cliente: ";
    cin >> cliente->nome;
    cout << "Digite a nova idade do cliente: ";
    cin >> cliente->idade;

    cout << "Cliente alterado com sucesso!" << endl;
}

void listarClientes()
{
    if (clientes.empty())
    {
        cout << "Nenhum cliente cadastrado." << endl;
    }
    else
    {
        cout << "Lista de clientes:" << endl;
        
        for (auto cliente : clientes)
        {
            cout << "ID: " << cliente->id << endl;
            cout << "Nome: " << cliente->nome << endl;
            cout << "Idade: " << cliente->idade << " anos" << endl;
            
            if (cliente->titular == cliente)
            {
            	cout << "Titular: N/A" << endl;
            }
            else
            {
                cout << "Titular: " << cliente->titular->nome << endl;
            }

            cout << endl;
        }
    }
}

void excluirCliente()
{
	int id;
	cout << "Digite o ID do cliente a ser excluído: ";
	cin >> id;
	bool encontrado = false;
	for (auto it = clientes.begin(); it != clientes.end(); it++)
	{
		if ((*it)->id == id)
		{
			encontrado = true;
			cout << "Cliente encontrado! Deseja realmente excluí-lo? (S/N) ";
			char confirmacao;
			cin >> confirmacao;
			if (confirmacao == 'S' || confirmacao == 's')
			{
				delete(*it);
				it = clientes.erase(it);
				cout << "Cliente excluído com sucesso!" << endl;
			}
			else
			{
				cout << "Operação cancelada pelo usuário." << endl;
			}

			break;
		}
	}

	if (!encontrado)
	{
		cout << "Cliente não encontrado." << endl;
	}
}

int main()
{
	int opcao;
	do {
		cout << endl;
		cout << "1 - Cadastrar cliente(TITULAR)" << endl;
		cout << "2 - Excluir cliente" << endl;
		cout << "3 - Alterar cliente" << endl;
		cout << "4 - Lista de cliente" << endl;
		cout << "5 - Cadastrar cliente(DEPENDENTE)" << endl;
		cout << "0 - Sair" << endl;
		cout << "Digite a opção desejada: ";
		cin >> opcao;
		switch (opcao)
		{
			case 1:
				cadastrarCliente();
				break;
			case 2:
				excluirCliente();
				break;
			case 3:
				alterarCliente();
				break;
			case 4:
				listarClientes();
				break;
			case 5:
				cadastrarDependente();
				break;
			case 0:
				cout << "Saindo..." << endl;
				break;
			default:
				cout << "Opção inválida!" << endl;
				break;
		}
	} while (opcao != 0);
	return 0;
}
