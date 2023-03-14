#include <stdio.h>
#include <string.h>

struct Cliente
{
	int id;
	char nome[50];
    	int idade;
	bool ehTitular;
	int idTitular;
};

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
