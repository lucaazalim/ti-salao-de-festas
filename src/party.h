#pragma once

#include "constants.h"
#include "datetime.h"

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

void createParty(Party *party);

void printParty(Party party);

float calculatePartyValue(Party party);