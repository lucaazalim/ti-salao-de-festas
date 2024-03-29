/**
 * @file party.h
 * @brief functions and structs related to the management of the Party entity
 * @author Luca Azalim
*/

#pragma once

#include "../constants.h"
#include "../utils/datetime.h"

/**
 * @brief enum containing the possible payment statuses
 */
enum PaymentStatus
{
    PAYABLE,
    PAID,
    CANCELLED
};

extern const int PAYMENT_STATUSES_LENGTH;
extern const enum PaymentStatus PAYMENT_STATUSES[];
extern const char PAYMENT_STATUSES_NAMES[][30];

typedef struct
{
    int id;
    int customerId;
    int supplierId;

    int invitedAmount;

    Date date;
    int weekDay;
    int startHour;

    char theme[PARTY_THEME_LENGTH];

    int installments;
    enum PaymentStatus paymentStatus;

} Party;

/**
 * @brief scans the necessary information and creates a new customer
 * @param party party pointer
 */
void scanParty(Party *party);

/**
 * @brief creates a new party
 * @param party party pointer
 * @return 1 if the party was created successfully, 0 otherwise
 */
int createParty(Party *party);

/**
 * @brief prints all the information of a party
 * @param party party to be printed
 */
void printParty(Party party);

/**
 * @brief calculates the value (price) of a party based on the invited amount and the appliable discounts
 * @param party party to be analyzed
 * @return the value (price) of the party
 */
float calculatePartyValue(int weekDay, int invitedAmount, int installments);