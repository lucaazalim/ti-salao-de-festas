#include <stdio.h>

#include "customer.h"
#include "constants.h"
#include "scan-utils.h"
#include "file-utils.h"

void createCustomer(Customer *customer)
{

    printf("Informe o nome do cliente: ");
    scanText(customer->name, CUSTOMER_NAME_LENGTH);

    printf("Informe o endereço do cliente: ");
    scanText(customer->address, ADDRESS_LENGTH);

    printf("Informe o telefone do cliente: ");
    scanText(customer->phone, PHONE_LENGTH);

    clearInputBuffer();

    printf("Informe da data de nascimento do cliente: \n");
    createDate(&customer->birthDate);

    Customer *lastCustomer = getLastStructFromFile(CUSTOMER_DATA_FILENAME, sizeof(Customer));

    customer->id = lastCustomer == NULL ? 1 : lastCustomer->id + 1;

    if (appendStructToFile(CUSTOMER_DATA_FILENAME, customer, sizeof(Customer)))
    {
        printf("Cliente cadastrado com sucesso. (ID: %d)\n", customer->id);
    }
    else
    {
        printf("Erro ao cadastrar cliente!\n");
    }
}

void printCustomer(Customer customer)
{
    printf("\tID: %d\n", customer.id);
    printf("\t\tNome: %s\n", customer.name);
    printf("\t\tEndereço: %s\n", customer.address);
    printf("\t\tTelefone: %s\n", customer.phone);
    printf("\t\tData de nascimento: %d/%d/%d\n", customer.birthDate.day, customer.birthDate.month, customer.birthDate.year);
}