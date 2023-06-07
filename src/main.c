#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file-utils.h"
#include "scan-utils.h"
#include "customer.h"
#include "supplier.h"
#include "party.h"

void menu()
{

    int menuOption;

    printf("\n");
    printf("Software de Gestão do Salão de Festas\n");
    printf("\n");
    printf("\t1. Cadastrar cliente\n");
    printf("\t2. Cadastrar fornecedor\n");
    printf("\t3. Cadastrar festa\n");
    printf("\t4. Calcular valor da festa\n");
    printf("\t5. Alterar status do pagamento de uma festa\n");
    printf("\t6. Pesquisar cliente ou fornecedor pelo ID\n");
    printf("\t7. Relatório de festas por cliente\n");
    printf("\t8. Relatório de festas por data\n");
    printf("\t9. Sair\n");
    printf("\n");
    printf("Informe uma opção [1 - 9]: ");

    scanf("%d", &menuOption);
    getchar();

    switch (menuOption)
    {

    case 1:
    {
        Customer customer;
        scanCustomer(&customer);
        break;
    }

    case 2:
    {
        Supplier supplier;
        createSupplier(&supplier);
        break;
    }

    case 3:
    {
        Party party;
        createParty(&party);
        break;
    }

    case 4:
    {

        int partyId;

        printf("Informe o ID da festa: ");
        scanf("%d", &partyId);

        Party *partyPointer = (Party *)getStructByIndexFromFile(PARTY_DATA_FILENAME, partyId - 1, sizeof(Party));

        if (partyPointer == NULL)
        {
            printf("A festa correspondente ao ID informado não existe.\n");
            break;
        }

        Party party = *partyPointer;
        float partyValue = calculatePartyValue(party.weekDay, party.invitedAmount, party.installments);

        printf("O valor da festa é R$ %.2f.\n", partyValue);
        break;
    }

    case 5:
    {

        int partyId, paymentStatusId;

        printf("Informe o ID da festa: ");
        scanf("%d", &partyId);

        printf("Informe o ID do novo status de pagamento: [");

        for (int i = 0; i < PAYMENT_STATUSES_LENGTH; i++)
        {

            printf("%d = %s", i + 1, PAYMENT_STATUSES_NAMES[i]);

            if (i < PAYMENT_STATUSES_LENGTH - 1)
            {
                printf(", ");
            }
        }

        printf("] ");

        scanf("%d", &paymentStatusId);

        if (paymentStatusId < 1 || paymentStatusId > PAYMENT_STATUSES_LENGTH)
        {
            printf("O ID informado não é válido.");
            break;
        }

        enum PaymentStatus paymentStatus = PAYMENT_STATUSES[paymentStatusId - 1];
        Party *partyPointer = (Party *)getStructByIndexFromFile(PARTY_DATA_FILENAME, partyId - 1, sizeof(Party));

        if (partyPointer == NULL)
        {
            printf("A festa correspondente ao ID informado não existe.");
            break;
        }

        Party party = *partyPointer;
        party.paymentStatus = paymentStatus;

        updateStructByIndexInFile(PARTY_DATA_FILENAME, &party, partyId - 1, sizeof(Party));

        printf("O status de pagamento da festa foi alterado para %s.\n", PAYMENT_STATUSES_NAMES[paymentStatusId - 1]);
        break;
    }

    case 6:
    {

        // TODO: Pesquisa por nome do cliente e nome do fornecedor.

        int whatToSearch;
        int howToSearch;

        printf("Informe o que você deseja pesquisar: [1 = Cliente, 2 = Fornecedor] ");
        scanf("%d", &whatToSearch);

        printf("Informe como você deseja pesquisar: [1 = ID, 2 = Nome] ");
        scanf("%d", &howToSearch);

        clearInputBuffer();

        if (whatToSearch == 1)
        {

            if (howToSearch == 1)
            {

                int customerId;

                printf("Informe o ID do cliente: ");
                scanf("%d", &customerId);

                Customer *customerPointer = (Customer *)getStructByIndexFromFile(CUSTOMER_DATA_FILENAME, customerId - 1, sizeof(Customer));

                if (customerPointer == NULL)
                {
                    printf("O cliente correspondente ao ID informado não existe.");
                    break;
                }

                printf("\n");
                printCustomer(*customerPointer);
                printf("\n");

                break;
            }
            else if (howToSearch == 2)
            {

                char nameSearch[CUSTOMER_NAME_LENGTH];

                printf("Informe o trecho do nome do cliente a ser pesquisado: ");
                scanText(nameSearch, CUSTOMER_NAME_LENGTH);

                int amountOfCustomers;
                Customer *customers = getAllStructsFromFile(CUSTOMER_DATA_FILENAME, sizeof(Customer), &amountOfCustomers);

                int found = 0;

                printf("\n");

                for (int i = 0; i < amountOfCustomers; i++)
                {

                    Customer customer = customers[i];

                    if (strstr(customer.name, nameSearch))
                    {
                        printCustomer(customer);
                        printf("\n");

                        found = 1;
                    }
                }

                if (!found)
                {
                    printf("Não foram encontrados clientes com o nome informado.\n");
                }

                break;
            }
        }
        else if (whatToSearch == 2)
        {

            if (howToSearch == 1)
            {

                int supplierId;

                printf("Informe o ID do fornecedor: ");
                scanf("%d", &supplierId);

                Supplier *supplierPointer = (Supplier *)getStructByIndexFromFile(SUPPLIER_DATA_FILENAME, supplierId - 1, sizeof(Supplier));

                if (supplierPointer == NULL)
                {
                    printf("O fornecedor correspondente ao ID informado não existe.");
                    break;
                }

                printf("\n");
                printSupplier(*supplierPointer);
                printf("\n");

                break;
            }
            else if (howToSearch == 2)
            {

                char nameSearch[SUPPLIER_NAME_LENGTH];

                printf("Informe o trecho do nome do fornecedor a ser pesquisado: ");
                scanText(nameSearch, SUPPLIER_NAME_LENGTH);

                int amountOfSuppliers;
                Supplier *suppliers = getAllStructsFromFile(SUPPLIER_DATA_FILENAME, sizeof(Supplier), &amountOfSuppliers);

                int found = 0;

                printf("\n");

                for (int i = 0; i < amountOfSuppliers; i++)
                {

                    Supplier supplier = suppliers[i];

                    if (strstr(supplier.name, nameSearch))
                    {
                        printSupplier(supplier);
                        printf("\n");

                        found = 1;
                    }
                }

                if (!found)
                {
                    printf("Não foram encontrados fornecedores com o nome informado.\n");
                }

                break;
            }
        }

        printf("Opção inválida.");
        break;
    }

    case 7:
    {

        int clientId;

        printf("Informe o ID do cliente: ");
        scanf("%d", &clientId);

        int amountOfParties;
        Party *parties = getAllStructsFromFile(PARTY_DATA_FILENAME, sizeof(Party), &amountOfParties);

        if (amountOfParties == 0)
        {
            printf("Não existem festas cadastradas para o cliente informado.\n");
            break;
        }

        printf("%d festa(s) encontrada(s)...\n\n", amountOfParties);

        for (int i = 0; i < amountOfParties; i++)
        {

            Party party = parties[i];

            if (party.customerId == clientId)
            {
                printParty(party);
                printf("\n");
            }
        }

        break;
    }

    case 8:
    {

        Date date;

        printf("Informe a data da festa: \n");
        createDate(&date);

        int amountOfParties;
        Party *parties = getAllStructsFromFile(PARTY_DATA_FILENAME, sizeof(Party), &amountOfParties);

        if (amountOfParties == 0)
        {
            printf("Não existem festas cadastradas para a data informada.\n");
            break;
        }

        printf("%d festa(s) encontrada(s)...\n\n", amountOfParties);

        for (int i = 0; i < amountOfParties; i++)
        {

            Party party = parties[i];

            if (dateEquals(party.date, date))
            {
                printParty(party);
                printf("\n");
            }
        }

        break;
    }

    case 9:
    {
        exit(0);
    }

    default:
    {
        printf("Opção inválida.");
        break;
    }
    }

    printf("Pressione qualquer tecla para voltar ao menu principal.\n");
    getch();
}

int main()
{
    while (1)
    {
        menu();
    }
}