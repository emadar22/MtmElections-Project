//
// Created by daraw on 06/12/2018.
//

#ifndef MTMELECTIONS_CITIZEN_H
#define MTMELECTIONS_CITIZEN_H

#include "uniqueOrderedList.h"
#include "Priority.h"

typedef struct citizen *Citizen;
Element copyCitizen(Element element );

void freeCitizen(Element element);

bool equalCitizenId(Element e1,Element e2);

bool citizenGreaterThan(Element e1,Element e2) ;

Citizen createCitizen(int citizenId,int citizenAge,const char* citizenName,int yearsOfEducation);

bool GetCitizenOrNot(Citizen citizen,int citizenId);

Priority getPriority(Citizen citizen,int candidateId);


bool priorityExists(Citizen citizen,int priority);

int getYearsOfEdu(Citizen citizen);

int getAgeOfCitizen(Citizen citizen);

bool priorityToDelete(int candidateToRemove,Citizen citizen);

char** getNameOfCitizen(Citizen citizen);

bool citizenIsCandidate(Citizen citizen);

Citizen citizenForPrisednt(Citizen citizen);

Citizen citizenWithdrawPresidency(Citizen citizen);

UniqueOrderedListResult insertPriority(Citizen citizen,Priority pr);

void ClearPriorities(Citizen citizen);

bool citizenIsEqualLex(Element e1,Element e2);

bool citizenIsGreaterLex(Element e1,Element e2);

int citizenGetfirstPriority(Citizen citizen);

int getCitizenId(Citizen citizen);

bool citizenGreaterThanlexAndId (Element e1,Element e2);

Priority getFirstPriority(Citizen citizen);

    #endif //MTMELECTIONS_CITIZEN_H
