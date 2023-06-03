#include <stdio.h>

#include "supplier.h"
#include "constants.h"
#include "scan-utils.h"
#include "file-utils.h"

void createSupplier(Supplier *supplier) {

    printf("Informe o nome do fornecedor: ");
    scanText(supplier->name, SUPPLIER_NAME_LENGTH);

    printf("Informe o telefone do fornecedor: ");
    scanText(supplier->phone, PHONE_LENGTH);

    Supplier *lastSupplier = getLastStructFromFile(SUPPLIER_DATA_FILENAME, sizeof(Supplier));

    supplier->id = lastSupplier == NULL ? 1 : lastSupplier->id + 1;

    if(appendStructToFile(SUPPLIER_DATA_FILENAME, supplier, sizeof(Supplier))) {
        printf("Fornecedor cadastrado com sucesso. (ID: %d)\n", supplier->id);
    } else {
        printf("Erro ao cadastrar fornecedor!\n");
    }

}

void printSupplier(Supplier supplier) {
    printf("\tID: %d\n", supplier.id);
    printf("\t\tNome: %s\n", supplier.name);
    printf("\t\tTelefone: %s\n", supplier.phone);
}