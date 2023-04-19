#include <iostream>
#include <cstdio>
#include <cstring>

struct Cliente {
    int id;
    char nome[50];
    int idade;
    bool titular;
    int idTitular;
};

int gerarID() {
    FILE *file = fopen("clientes.bin", "rb");
    if (file == nullptr) {
        return 1;
    }

    Cliente cliente;
    int maxID = 0;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.id > maxID) {
            maxID = cliente.id;
        }
    }

    fclose(file);
    return maxID + 1;
}

bool titularTemDependentes(int id) {
    FILE *file = fopen("clientes.bin", "rb");
    if (file == nullptr) {
        return false;
    }

    Cliente cliente;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (!cliente.titular && cliente.idTitular == id) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

bool validarCliente(int id) {
    FILE *file = fopen("clientes.bin", "rb");
    if (file == nullptr) {
        return false;
    }

    Cliente cliente;
    bool clienteValido = false;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.id == id && cliente.titular) {
            clienteValido = true;
            break;
        }
    }

    fclose(file);
    return clienteValido;
}

void cadastrarCliente() {
    FILE *file = fopen("clientes.bin", "ab");
    Cliente cliente;
    
    cliente.id = gerarID();
    std::cout << "Digite o nome do cliente: ";
    std::cin.ignore();
    std::cin.getline(cliente.nome, 50);
    std::cout << "Digite a idade do cliente: ";
    std::cin >> cliente.idade;
    std::cout << "O cliente é titular? (1 para sim, 0 para não): ";
    std::cin >> cliente.titular;
    if (!cliente.titular) {
        std::cout << "Digite o ID do titular: ";
        std::cin >> cliente.idTitular;
        if (!validarCliente(cliente.idTitular) || !titularTemDependentes(cliente.idTitular)) {
            std::cout << "Titular inválido ou já possui dependentes." << std::endl;
            fclose(file);
            return;
        }
    }

    fwrite(&cliente, sizeof(Cliente), 1, file);
    fclose(file);
    std::cout << "Cliente cadastrado com sucesso!" << std::endl;
}


void excluirCliente() {
    int id;
    std::cout << "Digite o ID do cliente a ser excluído: ";
    std::cin >> id;

    if (titularTemDependentes(id)) {
        std::cout << "Não é possível excluir um titular com dependentes." << std::endl;
        return;
    }

    FILE *file = fopen("clientes.bin", "rb");
    if (file == nullptr) {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    FILE *tempFile = fopen("temp.bin", "wb");
    if (tempFile == nullptr) {
        std::cout << "Erro ao criar arquivo temporário." << std::endl;
        fclose(file);
        return;
    }

    Cliente cliente;
    bool clienteEncontrado = false;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.id == id) {
            clienteEncontrado = true;
        } else {
            fwrite(&cliente, sizeof(Cliente), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (clienteEncontrado) {
        remove("clientes.bin");
        rename("temp.bin", "clientes.bin");
        std::cout << "Cliente excluído com sucesso!" << std::endl;
    } else {
        remove("temp.bin");
        std::cout << "Cliente não encontrado." << std::endl;
    }
}

void modificarCliente() {
    int id;
    std::cout << "Digite o ID do cliente a ser modificado: ";
    std::cin >> id;

    FILE *file = fopen("clientes.bin", "rb+");
    if (file == nullptr) {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    Cliente cliente;
    bool clienteEncontrado = false;

    while (fread(&cliente, sizeof(Cliente), 1, file) && !clienteEncontrado) {
        if (cliente.id == id) {
            clienteEncontrado = true;

            std::cout << "Digite o novo nome do cliente (deixe em branco para não alterar): ";
            std::cin.ignore();
            std::string novoNome;
            std::getline(std::cin, novoNome);
            if (!novoNome.empty()) {
                strncpy(cliente.nome, novoNome.c_str(), sizeof(cliente.nome));
                cliente.nome[sizeof(cliente.nome) - 1] = '\0';
            }

            std::cout << "Digite a nova idade do cliente (digite -1 para não alterar): ";
            int novaIdade;
            std::cin >> novaIdade;
            if (novaIdade != -1) {
                cliente.idade = novaIdade;
            }

            fseek(file, -sizeof(Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(Cliente), 1, file);
            std::cout << "Cliente modificado com sucesso!" << std::endl;
        }
    }

    if (!clienteEncontrado) {
        std::cout << "Cliente não encontrado." << std::endl;
    }

    fclose(file);
}

void visualizarCliente() {
        FILE *file = fopen("clientes.bin", "rb");
    if (file == nullptr) {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    Cliente cliente;
    bool clienteEncontrado = false;

    std::cout << "Lista de clientes cadastrados:" << std::endl;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        clienteEncontrado = true;
        std::cout << "ID: " << cliente.id << std::endl;
        std::cout << "Nome: " << cliente.nome << std::endl;
        std::cout << "Idade: " << cliente.idade << std::endl;
        std::cout << "Titular: " << (cliente.titular ? "Sim" : "Não") << std::endl;
        if (!cliente.titular) {
            std::cout << "ID do Titular: " << cliente.idTitular << std::endl;
        }
        std::cout << std::endl;
    }

    if (!clienteEncontrado) {
        std::cout << "Nenhum cliente cadastrado." << std::endl;
    }

    fclose(file);
}



void menu() {
    int opcao;

    do {
        std::cout << "Menu de Gerenciamento de Clientes" << std::endl;
        std::cout << "1 - Cadastrar cliente" << std::endl;
        std::cout << "2 - Excluir cliente" << std::endl;
        std::cout << "3 - Modificar cliente" << std::endl;
        std::cout << "4 - Visualizar cliente" << std::endl;
        std::cout << "0 - Sair" << std::endl;
        std::cout << "Digite a opção desejada: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                excluirCliente();
                break;
            case 3:
                modificarCliente();
                break;
            case 4:
                visualizarCliente();
                break;
            case 0:
                std::cout << "Saindo do programa..." << std::endl;
                break;
            default:
                std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
        std::cout << std::endl;

    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}

