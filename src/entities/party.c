#include <stdio.h>

#include "party.h"
#include "customer.h"
#include "supplier.h"

#include "../constants.h"
#include "../utils/datetime.h"
#include "../utils/scan-utils.h"
#include "../utils/file-utils.h"

const int PAYMENT_STATUSES_LENGTH = 3;
const enum PaymentStatus PAYMENT_STATUSES[] = {PAYABLE, PAID, CANCELLED};
const char PAYMENT_STATUSES_NAMES[][30] = {"Pagável", "Pago", "Cancelado"};

int hasPartyTimeConflict(Date date, int startTimeHour)
{

    int amountOfParties;
    Party *parties = getAllStructsFromFile(PARTY_DATA_FILENAME, sizeof(Party), &amountOfParties);

    for (int i = 0; i < amountOfParties; i++)
    {

        Party party = parties[i];

        if (!dateEquals(party.date, date))
        {
            continue;
        }

        int blockedWindowStartTime = party.startHour - PARTY_DURATION_HOURS;
        int blockedWindowEndTime = party.startHour + PARTY_DURATION_HOURS;

        if (startTimeHour >= blockedWindowStartTime && startTimeHour <= blockedWindowEndTime)
        {
            return 1;
        }
    }

    return 0;
}

void scanParty(Party *party)
{

    printf("Informe o ID do cliente: ");
    scanf("%d", &party->customerId);

    printf("Informe o ID do fornecedor: ");
    scanf("%d", &party->supplierId);

    printf("Informe o número de convidados: ");
    scanf("%d", &party->invitedAmount);

    printf("Informe a data: \n");
    createDate(&party->date);

    printf("Informe o horário de início: [8 - 19] ");
    scanf("%d", &party->startHour);

    clearInputBuffer();

    printf("Informe o tema: ");
    scanText(party->theme, PARTY_THEME_LENGTH);

    printf("Informe a quantidade de parcelas para pagamento: ");
    scanf("%d", &party->installments);

    if (createParty(party))
    {
        printf("Festa cadastrada com sucesso. (ID: %d)\n", party->id);
    }
    
}

int createParty(Party *party)
{

    Customer *customerPointer = getStructByIndexFromFile(CUSTOMER_DATA_FILENAME, party->customerId - 1, sizeof(Customer));

    if (customerPointer == NULL)
    {
        printf("O cliente correspondente ao ID informado não existe.\n");
        return 0;
    }

    Supplier *supplierPointer = getStructByIndexFromFile(SUPPLIER_DATA_FILENAME, party->supplierId - 1, sizeof(Supplier));

    if (supplierPointer == NULL)
    {
        printf("O fornecedor correspondente ao ID informado não existe.\n");
        return 0;
    }

    party->weekDay = getWeekDayFromDate(party->date);

    // Restrição para que festas só iniciem entre 08:00 e 19:00
    if (party->startHour < 8 || party->startHour > 19)
    {
        printf("As festas devem iniciar entre 8h e 19h.\n");
        return 0;
    }

    // Restrição para que festas aos sábados só ocorram às 12:00 ou às 18:00
    if (party->weekDay == 6 && !(party->startHour == 12 || party->startHour == 18))
    {
        printf("Aos sábados, o horário de início das festas deve ser às 12h ou às 18h.\n");
        return 0;
    }

    // Restrição para que festas não ocorram ao mesmo tempo
    if (hasPartyTimeConflict(party->date, party->startHour))
    {
        printf("Já existe uma festa marcada para essa data e horário.\n");
        return 0;
    }

    party->paymentStatus = PAYABLE;

    Party *lastParty = getLastStructFromFile(PARTY_DATA_FILENAME, sizeof(Party));

    party->id = lastParty == NULL ? 1 : lastParty->id + 1;

    return appendStructToFile(PARTY_DATA_FILENAME, party, sizeof(Party));
}

void printParty(Party party)
{
    printf("\tID: %d\n", party.id);
    printf("\t\tID do cliente: %d\n", party.customerId);
    printf("\t\tID do fornecedor: %d\n", party.supplierId);
    printf("\t\tNúmero de convidados: %d\n", party.invitedAmount);
    printf("\t\tData: %d/%d/%d\n", party.date.day, party.date.month, party.date.year);
    printf("\t\tDia da semana: %s\n", WEEK_DAYS_NAMES[party.weekDay]);
    printf("\t\tHorário de início: %02d:00\n", party.startHour);
    printf("\t\tTema: %s\n", party.theme);
    printf("\t\tQuantidade de parcelas: %d\n", party.installments);
    printf("\t\tStatus de pagamento: %s\n", PAYMENT_STATUSES_NAMES[party.paymentStatus]);
    printf("\t\tValor: R$ %.2f\n", calculatePartyValue(party.weekDay, party.invitedAmount, party.installments));
}

float calculatePartyValue(int weekDay, int invitedAmount, int installments)
{

    float value;
    int fromFridayToSunday = weekDay == 0 || weekDay > 5;

    if (invitedAmount >= 100)
    {
        value = fromFridayToSunday ? 3999 : 3799;
    }
    else if (invitedAmount >= 80)
    {
        value = fromFridayToSunday ? 3499 : 3199;
    }
    else if (invitedAmount >= 50)
    {
        value = fromFridayToSunday ? 2299 : 2199;
    }
    else if (invitedAmount >= 30)
    {
        value = fromFridayToSunday ? 2099 : 1899;
    }
    else
    {
        value = 1000; // Não está no enunciado, mas é preciso um valor de fallback.
    }

    // Desconto baseado no número de parcelas
    float discount = 0.1 / installments;
    value *= (1.0 - discount);

    return value;
}