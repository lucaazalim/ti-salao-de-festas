#include <stdio.h>
#include <string.h>

#include "munit.h"
#include "../utils/file-utils.h"
#include "../entities/customer.h"
#include "../entities/supplier.h"
#include "../entities/party.h"

Customer testCustomerCreation()
{

    Customer customer;

    strcpy(customer.name, "Luca Ferrari Azalim");
    strcpy(customer.address, "Rua das Flores, 123");
    strcpy(customer.phone, "31912345678");

    customer.birthDate.day = 27;
    customer.birthDate.month = 1;
    customer.birthDate.year = 2000;

    munit_assert_int(createCustomer(&customer), ==, 1);
    return customer;
}

Supplier testSupplierCreation()
{
    Supplier supplier;

    strcpy(supplier.name, "Casa do Sol");
    strcpy(supplier.phone, "31923456789");

    munit_assert_int(createSupplier(&supplier), ==, 1);
    return supplier;
}

void testPartyCreation(int expectedOutput, int customerId, int supplierId, int day, int month, int year, int startHour)
{
    Party party;

    party.customerId = customerId;
    party.supplierId = supplierId;
    party.invitedAmount = 50;

    party.date.day = day;
    party.date.month = month;
    party.date.year = year;

    party.startHour = startHour;
    strcpy(party.theme, "Fundo do Mar");

    party.installments = 2;

    munit_assert_int(createParty(&party), ==, expectedOutput);
}

void testPartyValueCalculation(float expectedValue, int weekDay, int invitedAmount, int installments)
{
    float partyValue = calculatePartyValue(weekDay, invitedAmount, installments);
    munit_assert_float(partyValue, ==, expectedValue);
}

void testCustomerSearchById(int customerId)
{
    Customer *customer = (Customer *)getStructByIndexFromFile(CUSTOMER_DATA_FILENAME, customerId - 1, sizeof(Customer));
    munit_assert_ptr_not_null(customer);
}

int main()
{
    // Run the tests with no previous data
    system("rm -rf data/*.dat");

    // Test Case #1
    printf("Test Case #1\n");
    Customer customer = testCustomerCreation();

    // Test Case #2
    printf("Test Case #2\n");
    Supplier supplier = testSupplierCreation();

    // Test Case #3
    printf("Test Case #3\n");
    testPartyCreation(1, customer.id, supplier.id, 27, 2, 2024, 17);

    // Test Case #4
    printf("Test Case #4\n");
    testPartyCreation(0, 1000, supplier.id, 27, 2, 2024, 19);

    // Test Case #5
    printf("Test Case #5\n");
    testPartyCreation(0, customer.id, 1000, 27, 2, 2024, 19);

    // Test Case #6
    printf("Test Case #6\n");
    testPartyCreation(0, customer.id, supplier.id, 27, 1, 2024, 19);

    // Test Case #7
    printf("Test Case #7\n");
    testPartyCreation(0, customer.id, supplier.id, 27, 2, 2024, 19);

    // Test Case #8
    printf("Test Case #8\n");
    testPartyValueCalculation(2069.1, 6, 50, 1);

    // Test Case #9
    printf("Test Case #9\n");
    testPartyValueCalculation(3799.05, 0, 100, 2);

    // Test Case #10
    printf("Test Case #10");
    testCustomerSearchById(customer.id);

}