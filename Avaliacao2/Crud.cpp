#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

struct Cliente {
    int id;
    string nome;
    int idade;
    bool titular; 
    int id_titular; 
};

FILE *arquivo;

void cadastrarCliente() {
    Cliente cliente;
    cout << "ID do cliente: ";
    cin >> cliente.id;
    cout << "Nome do cliente: ";
    cin >> cliente.nome;
    cout << "Idade do cliente: ";
    cin >> cliente.idade;
    cout << "Titular (1) ou dependente (0): ";
    cin >> cliente.titular;
    
    if (!cliente.titular) {
        cout << "ID do titular correspondente: ";
        cin >> cliente.id_titular;
    }
    
    FILE *arquivo = fopen("clientes.dat", "ab");
    fwrite(&cliente, sizeof(cliente), 1, arquivo);
    fclose(arquivo);
}

int main()
{
	FILE *arquivo = fopen("clientes.dat", "rb+");
	if (arquivo == NULL)
	{
		arquivo = fopen("clientes.dat", "wb+");
		if (arquivo == NULL)
		{
			printf("Erro ao criar arquivo.\n");
			return 1;
		}
	}

	int opcao;
	do {
		printf("\nMenu:\n");
		printf("1 - Cadastrar cliente\n");
		printf("2 - Excluir cliente\n");
		printf("3 - Modificar cliente\n");
		printf("4 - Visualizar clientes\n");
		printf("0 - Sair\n");
		scanf("%d", &opcao);

		switch (opcao)
		{
			case 1:
				cadastrarCliente();
				break;
			case 2:
				
			case 3:
				
			case 4:
				
			case 0:
				printf("Saindo...\n");
				break;
			default:
				printf("Opção inválida.\n");
				break;
		}
	} while (opcao != 0);

	fclose(arquivo);
	return 0;
}
