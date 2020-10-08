#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "DiagnosisMessage.h"
#include "global.h"

PatientInfo constructPatientInfo(const char * name, int age, int registerId) {
  PatientInfo patientInfo;
  strcpy(patientInfo.name, name);
  patientInfo.age = age;
  patientInfo.registerId = registerId;
  return patientInfo;
}

Section constructSection(int sectionId, DiagnosisRecord* nowDiagnosis,
  DoctorInfo* DoctorsOfSectionHead, Section* next) {
  Section section;
  section.sectionId = sectionId;
  section.nowDiagnosis = nowDiagnosis;
  section.DoctorsOfSectionHead = DoctorsOfSectionHead;
  section.next = next;
  return section;
}

DoctorInfo constructDoctorInfo(const char * name, int level,
  int sectionId, bool consultTime[7], int id,
  bool doctorStatus, int busyDegree) {
  DoctorInfo doctorInfo;
  strcpy(doctorInfo.name, name);
  doctorInfo.level = level;
  doctorInfo.sectionId = sectionId;
  doctorInfo.busyDegree = busyDegree;
  for (int i = 0; i < 7; i++) {
    doctorInfo.consultTime[i] = consultTime[i];
  }
  doctorInfo.id = id;
  doctorInfo.doctorStatus = doctorStatus;
  return doctorInfo;
}


DoctorNode constructDoctorNode(DoctorInfo doctorInfo, DoctorNode* next) {
  DoctorNode doctorNode;
  doctorNode.doctorInfo = doctorInfo;
  doctorNode.next = next;
  return doctorNode;
}


SingleCost constructSingleCost(int yuan, int jiao, int fen) {
  SingleCost singleCost;
  singleCost.yuan = yuan;
  singleCost.jiao = jiao;
  singleCost.fen = fen;
  return singleCost;
}

char* convertSingleCostToString(SingleCost singleCost) {
  char *buf = (char*)calloc(20, sizeof(char));
  int pos = 0;
  if (singleCost.yuan == 0) {
    buf[pos++] = '0';
  } else {
    int bit = 0, base = 1;
    while (singleCost.yuan >= base * 10) {
      bit++, base *= 10;
    }
    while (bit >= 0) {
      buf[pos++] = singleCost.yuan / base + '0';
      bit--, singleCost.yuan %= base, base /= 10;;
    }
  }
  buf[pos++] = '.';
  buf[pos++] = singleCost.jiao + '0';
  buf[pos++] = singleCost.fen + '0';
  buf[pos++] = 0;
  return buf;
}

SingleCost constructSingleCost(char *costStr) {
  SingleCost singleCost;
  singleCost.yuan = 0;
  singleCost.jiao = 0;
  singleCost.fen = 0;
  int len = strlen(costStr);
  int position = 0;
  while (costStr[position] != '.'&& position < len)
    position++;
  for (int i = 0; i < position; i++) {
    singleCost.yuan = singleCost.yuan * 10 + (costStr[i] - '0');
  }
  if (position < len - 1)singleCost.jiao =
                                  costStr[position + 1] - '0';
  if (position < len - 2)singleCost.fen =
                                  costStr[position + 2] - '0';
  return singleCost;
}

CheckInfo constructCheckInfo(int checkId, SingleCost singleCost,
  CheckInfo* next) {
  CheckInfo checkInfo;
  checkInfo.singleCost = singleCost;
  checkInfo.next = next;
  return checkInfo;
}


CheckRecord constructCheckRecord(CheckInfo* checkInfoHead,
  int typeNumber, SingleCost totalCost) {
  CheckRecord checkRecord;
  checkRecord.checkInfoHead = checkInfoHead;
  checkRecord.typeNumber = typeNumber;
  checkRecord.totalCost = totalCost;
  return checkRecord;
}


PrescribeInfo constructPrescribeInfo(int drugId, 
  int drugNumber, PrescribeInfo* next) {
  PrescribeInfo prescribeInfo;
  prescribeInfo.drugId = drugId;
  prescribeInfo.drugNumber = drugNumber;
  prescribeInfo.next = next;
  return prescribeInfo;
}


PrescribeRecord constructPrescribeRecord(PrescribeInfo* prescribeInfoHead,
  int typeNumber, SingleCost totalCost) {
  PrescribeRecord prescribeRecord;
  prescribeRecord.totalCost = totalCost;
  prescribeRecord.typeNumber = typeNumber;
  prescribeRecord.prescribeInfoHead = prescribeInfoHead;
  return prescribeRecord;
}


TimeRecord constructTimeRecord(int month, int day, int hour, int minute) {
  TimeRecord timeRecord;
  timeRecord.month = month;
  timeRecord.day = day;
  timeRecord.hour = hour;
  timeRecord.minute = minute;
  return timeRecord;
}

InHospitalRecord constructInHospitalRecord(TimeRecord hospitalizedDate,
  TimeRecord predictedLeaveDate, TimeRecord leaveDate, int sickBedNumber,
  SingleCost deposit, SingleCost costByNow) {
  InHospitalRecord inHospitalRecord;
  inHospitalRecord.hospitalizedDate = hospitalizedDate;
  inHospitalRecord.predictedLeaveDate = predictedLeaveDate;
  inHospitalRecord.deposit = deposit;
  inHospitalRecord.leaveDate = leaveDate;
  inHospitalRecord.sickBedNumber = sickBedNumber;
  inHospitalRecord.costByNow = costByNow;
  return inHospitalRecord;
}


DiagnosisSituation constructDiagnosisSituation(int setFlag,
  DiagnosisSituationUnion diagnosisSituationInfo) {
  DiagnosisSituation diagnosisSituation;
  diagnosisSituation.setFlag = setFlag;
  diagnosisSituation.diagnosisSituationInfo = diagnosisSituationInfo;
  return diagnosisSituation;
}

DiagnosisRecord constructDiagnosisRecord(TimeRecord recordTime,
  PatientInfo patientInfo,
  DoctorInfo doctorInfo, DiagnosisSituation diagnosisSituation,
  DiagnosisRecord* next) {
  DiagnosisRecord diagnosisRecord;
  diagnosisRecord.recordTime = recordTime;
  diagnosisRecord.patientInfo = patientInfo;
  diagnosisRecord.doctorInfo = doctorInfo;
  diagnosisRecord.diagnosisSituation = diagnosisSituation;
  diagnosisRecord.next = next;
  return diagnosisRecord;
}

DiagnosisRecord* initDiagnosisRecord() {
  DiagnosisRecord* DiagnosisRecordPtr =
    (DiagnosisRecord*)malloc(sizeof(DiagnosisRecord));
  DiagnosisRecordPtr->next = NULL;
  DiagnosisRecordPtr->patientInfo = constructPatientInfo("$", -1, -1);
  bool initConsultTime[] = {0, 0, 0, 0, 0, 0, 0};
  DiagnosisRecordPtr->doctorInfo = constructDoctorInfo("$", -1, -1,
    initConsultTime, -1, 0, -1);
  DiagnosisRecordPtr->doctorInfo.vacationLeft = 0;
  DiagnosisRecordPtr->recordTime = constructTimeRecord(-1, -1, -1, -1);
  DiagnosisSituationUnion tempUnion;
  tempUnion.checkRecord = constructCheckRecord(NULL, -1,
    constructSingleCost(-1, -1, -1));
  DiagnosisRecordPtr->diagnosisSituation =
    constructDiagnosisSituation(-1, tempUnion);
  return DiagnosisRecordPtr;
}

Ward constructWard(int wardId, int nursingType,
  int bedType, int totalBedNum, int occupiedBedNum,
  bool bedSituation[10], Ward* next) {
  Ward ward;
  ward.wardId = wardId;
  ward.nursingType = nursingType;
  ward.bedType = bedType;
  ward.totalBedNum = totalBedNum;
  ward.occupiedBedNum = occupiedBedNum;
  ward.next = next;
  for (int i = 0; i < 10; i++)
    ward.bedSituation[i] = bedSituation[i];
  return ward;
}


SingleCost costAdd(SingleCost costA, SingleCost costB) {
  costA.fen += costB.fen;
  costA.jiao += costB.jiao;
  costA.yuan += costB.yuan;
  while (costA.fen >= 100) {
    costA.fen -= 100;
    costA.jiao++;
  }
  while (costA.jiao >= 100) {
    costA.jiao -= 100;
    costA.yuan++;
  }
  return costA;
}

TimeRecord convertStringToTimeRecord(const char *str) {
  TimeRecord timeRecord;
  char buf[20];
  int pos = 0, cnt = 0, p1, p2, p3, p4;
  while (str[pos] != '-') pos++;
  p1 = pos;
  pos++;
  while (str[pos] != '-') pos++;
  p2 = pos;
  for (int i = p1 + 1; i < p2; i++)
    buf[cnt++] = str[i];
  buf[cnt] = 0, cnt = 0;
  timeRecord.month = atoi(buf);
  while (str[pos] != ' ')
    pos++;
  p3 = pos;
  for (int i = p2 + 1; i < p3; i++)
    buf[cnt++] = str[i];
  buf[cnt] = 0, cnt = 0;
  timeRecord.day = atoi(buf);
  while (str[pos] != ':')
    pos++;
  p4 = pos;
  for (int i = p3 + 1; i < p4; i++)
    buf[cnt++] = str[i];
  buf[cnt] = 0, cnt = 0;
  timeRecord.hour = atoi(buf);
  int p5 = strlen(str);
  for (int i = p4 + 1; i < p5; i++)
    buf[cnt++] = str[i];
  buf[cnt] = 0, cnt = 0;
  timeRecord.minute = atoi(buf);
  return timeRecord;
}

char* convertTimeRecordToString(const TimeRecord timeRecord) {
  char *str = (char*)calloc(100, sizeof(char));
  int pos = 5, num = 0;
  str[0] = '2', str[1] = '0', str[2] = '2', str[3] = '0', str[4] = '-';
  str[pos++] = '0' + timeRecord.month / 10;
  str[pos++] = '0' + timeRecord.month % 10;
  str[pos++] = '-';
  str[pos++] = '0' + timeRecord.day / 10;
  str[pos++] = '0' + timeRecord.day % 10;
  str[pos++] = ' ';
  str[pos++] = '0' + timeRecord.hour / 10;
  str[pos++] = '0' + timeRecord.hour % 10;
  str[pos++] = ':';
  str[pos++] = '0' + timeRecord.minute / 10;
  str[pos++] = '0' + timeRecord.minute % 10;
  str[pos++] = 0;
  return str;
}
