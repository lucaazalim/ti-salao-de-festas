#include "constants.h"

typedef struct {
    int id;
    char name[SUPPLIER_NAME_LENGTH];
    char phone[PHONE_LENGTH];
} Supplier;

/**
 * @brief scans necessary information and creates a new supplier
 * @param supplier supplier pointer
 */
void createSupplier(Supplier *supplier);

/**
 * @brief prints all the information of a supplier
*/
void printSupplier(Supplier supplier);