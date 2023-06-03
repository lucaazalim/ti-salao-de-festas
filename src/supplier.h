#include "constants.h"

typedef struct {
    int id;
    char name[SUPPLIER_NAME_LENGTH];
    char phone[PHONE_LENGTH];
} Supplier;

void createSupplier(Supplier *supplier);

void printSupplier(Supplier supplier);