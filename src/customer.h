#include "constants.h"
#include "datetime.h"

typedef struct {
    int id;
    char name[CUSTOMER_NAME_LENGTH];
    char address[ADDRESS_LENGTH];
    char phone[PHONE_LENGTH];
    Date birthDate;
} Customer;

void createCustomer(Customer *customer);

void printCustomer(Customer customer);