#include "constants.h"
#include "datetime.h"

/**
 * @brief Customer structure
 */
typedef struct
{
    int id;
    char name[CUSTOMER_NAME_LENGTH];
    char address[ADDRESS_LENGTH];
    char phone[PHONE_LENGTH];
    Date birthDate;
} Customer;

/**
 * @brief scans the necessary information and creates a new customer
*/
void scanCustomer(Customer *customer);

/**
 * @brief creates a new customer
 * @param customer customer pointer
 * @return 1 if the customer was created successfully, 0 otherwise
 */
int createCustomer(Customer *customer);

/**
 * @brief prints all the information of a customer
 * @param customer customer to be printed
 */
void printCustomer(Customer customer);