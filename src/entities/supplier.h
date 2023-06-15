/**
 * @file supplier.h
 * @brief functions and structs related to the management of the Supplier entity
 * @author Luca Azalim
*/

#include "../constants.h"

typedef struct {
    int id;
    char name[SUPPLIER_NAME_LENGTH];
    char phone[PHONE_LENGTH];
} Supplier;

/**
 * @brief scans necessary information and creates a new supplier
 * @param supplier supplier pointer
 */
void scanSupplier(Supplier *supplier);

/**
 * @brief creates a new supplier
 * @param supplier supplier pointer
 * @return 1 if the supplier was created successfully, 0 otherwise
 */
int createSupplier(Supplier *supplier);

/**
 * @brief prints all the information of a supplier
*/
void printSupplier(Supplier supplier);