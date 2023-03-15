#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Cliente
{
	int id;
	char nome[75];
	long long int cpf;
	long long int telefone;
	char email[50];
	bool ehTitular;
	int idTitular;
};

FILE *arquivo;

Cliente novoCliente;

void adicionarCliente()
{
    // Procurar próximo ID disponível
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    int qtdClientes = (tamanho / sizeof(Cliente));
    int proximoId = qtdClientes + 1;
    // Verificar se já existe cliente com o mesmo CPF
    rewind(arquivo);
    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1)
    {
        if (cliente.cpf == novoCliente.cpf)
        {
            printf("Erro: já existe cliente com CPF %lld.\n", novoCliente.cpf);
            return;
        }
    }

    // Adicionar cliente
    novoCliente.id = proximoId;
    fwrite(&novoCliente, sizeof(Cliente), 1, arquivo);
    printf("Cliente adicionado com sucesso. ID: %d\n", proximoId);
}

void cadastrarCliente()
{
	printf("Digite o nome do cliente: ");
	scanf(" %[^\n]s", novoCliente.nome);
	printf("Digite o CPF do cliente (somente números): ");
	scanf("%lld", &novoCliente.cpf);
	printf("Digite o telefone do cliente (somente números): ");
	scanf("%lld", &novoCliente.telefone);
	printf("Digite o e-mail do cliente: ");
	scanf(" %s", novoCliente.email);
	novoCliente.ehTitular = false;
	novoCliente.idTitular = 0; 
  	adicionarCliente();
}



int main()
{
    arquivo = fopen("clientes.dat", "rb+");
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
        printf("\nMenu de Opções:\n");
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
                //Chamar função para excluir cliente
                break;
            case 3:
                //Chamar função para modificar cliente
                break;
            case 4:
                //Chamar função para visualizar cliente
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("A opção digitada é inválida.\n");
                break;
        }
    } while (opcao != 0);

    fclose(arquivo);
    return 0;
}
