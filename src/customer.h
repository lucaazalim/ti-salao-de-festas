#include "constants.h"
#include "datetime.h"

typedef struct
{
    int id;
    char name[CUSTOMER_NAME_LENGTH];
    char address[ADDRESS_LENGTH];
    char phone[PHONE_LENGTH];
    Date birthDate;
} Customer;

/**
 * @brief scans necessary information and creates a new customer
 * @param customer customer pointer
 */
void createCustomer(Customer *customer);

/**
 * @brief prints all the information of a customer
 * @param customer customer to be printed
 */
void printCustomer(Customer customer);