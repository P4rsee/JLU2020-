#pragma once
#include "DiagnosisMessage.h"
#include <stdlib.h>


int actualExpense(TimeRecord startDate, TimeRecord endDate, int bedtype, int nursingtype);

SingleCost getTotalCost(DiagnosisRecord *head);

void timePass(DiagnosisRecord *head, int day30, int day, int hour, int minute);