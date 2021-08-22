//
// Created by daraw on 06/12/2018.
//
#include "Citizen.h"
#include <string.h>
char* copyString(const char* s) {
    char* str = malloc(strlen(s) + 1);
    if (str == NULL) return NULL;
    return strcpy(str, s);
}
 struct citizen{
    char* citizenName;
    int citizenAge;
    int citizenId;
    int yearsOfEducation;
    bool isCandidate;
    UniqueOrderedList priorities;
};
Element copyCitizen(Element element )
{
    if (element == NULL) return NULL;
    Citizen newCitizen = malloc(sizeof(*newCitizen));
    if (newCitizen == NULL)return NULL;
    newCitizen->citizenAge = ((Citizen) element)->citizenAge;
    newCitizen->citizenId = ((Citizen) element)->citizenId;
    newCitizen->citizenName = copyString(((Citizen) element)->citizenName);
    if (newCitizen->citizenName == NULL) return NULL;
    newCitizen->isCandidate = ((Citizen) element)->isCandidate;
    newCitizen->yearsOfEducation = ((Citizen) element)->yearsOfEducation;
    newCitizen->priorities = uniqueOrderedListCopy(((Citizen) element)->priorities);
    return newCitizen;
}

void freeCitizen(Element element)
{
    uniqueOrderedListClear(((Citizen)element)->priorities);
    free(element);
}
bool equalCitizenId(Element e1,Element e2)
{
    return ((Citizen)e1)->citizenId==((Citizen)e2)->citizenId;
}
bool citizenGreaterThan(Element e1,Element e2)
{
    return(((Citizen)e1)->citizenId > ((Citizen)e2)->citizenId);
}
Citizen createCitizen(int citizenId,int citizenAge,const char* citizenName,int yearsOfEducation)
{
    Citizen newCitizen = malloc(sizeof(*newCitizen));
    if (newCitizen == NULL)return NULL;
    newCitizen->citizenId = citizenId;
    newCitizen->citizenAge = citizenAge;
    newCitizen->yearsOfEducation = yearsOfEducation;
    newCitizen->isCandidate = false;
    newCitizen->citizenName =copyString(citizenName);
    newCitizen->priorities=uniqueOrderedListCreate(copyPriority,freePriority,isEqualPriority,greaterPriority);
    return newCitizen;
}
bool GetCitizenOrNot(Citizen citizen,int citizenId)
{
    if(citizen->citizenId==citizenId)return true;
    return false;
}
Priority getPriority(Citizen citizen,int candidateId)
{
    if(citizen==NULL)return NULL;
    Priority priority=uniqueOrderedListGetLowest(citizen->priorities);
    if(priority==NULL)return NULL;
    if(getPriorityOrNot(priority,candidateId))return priority;
    while(priority)
    {
        priority=uniqueOrderedListGetNext(citizen->priorities);
        if(getPriorityOrNot(priority,candidateId))return priority;

    }
    return NULL;


}

bool priorityExists(Citizen citizen,int priority)
{

    if(citizen==NULL)return NULL;
    Priority pr=uniqueOrderedListGetLowest(citizen->priorities);
    if(pr==NULL)return false;
    if(samePriority(pr,priority))return true;
    while(pr)
    {
        pr=uniqueOrderedListGetNext(citizen->priorities);
        if(pr==NULL)return false;
        if(samePriority(pr,priority))return true;

    }


}
int getYearsOfEdu(Citizen citizen)
{
    return citizen->yearsOfEducation;
}
int getAgeOfCitizen(Citizen citizen)
{
    return citizen->citizenAge;
}
bool priorityToDelete(int candidateToRemove,Citizen citizen)
{
    Priority priority=uniqueOrderedListGetLowest(citizen->priorities);
    while(priority)
    {
        if(getPriorityOrNot(priority,candidateToRemove))
        {
            uniqueOrderedListRemove(citizen->priorities,priority);
            return true ;
        }
        priority=uniqueOrderedListGetNext(citizen->priorities);
    }
    return false;
}
char** getNameOfCitizen(Citizen citizen)
{
    return &citizen->citizenName;
}
bool citizenIsCandidate(Citizen citizen)
{
    return citizen->isCandidate;
}
Citizen citizenForPrisednt(Citizen citizen)
{
    citizen->isCandidate=true;
    uniqueOrderedListClear(citizen->priorities);
    Priority priority=createPriority(citizen->citizenId,1);
    uniqueOrderedListInsert(citizen->priorities,priority);
    return  citizen;
}
Citizen citizenWithdrawPresidency(Citizen citizen)
{
    citizen->isCandidate=false;
    uniqueOrderedListClear(citizen->priorities);
    return citizen;
}
UniqueOrderedListResult insertPriority(Citizen citizen,Priority pr)
{
    return uniqueOrderedListInsert(citizen->priorities,pr);
}
void ClearPriorities(Citizen citizen)
{
    uniqueOrderedListClear(citizen->priorities);
}
bool citizenIsEqualLex(Element e1,Element e2)
{
    if(strcmp(((Citizen)e1)->citizenName,((Citizen)e2)->citizenName)==0)return true;
    return false;
}
bool citizenIsGreaterLex(Element e1,Element e2)
{
    if(strcmp(((Citizen)e1)->citizenName,((Citizen)e2)->citizenName)>=0)return true;
    return  false;

}
int citizenGetfirstPriority(Citizen citizen)
{
    Priority priority=uniqueOrderedListGetLowest(citizen->priorities);
    return getIdOfPriority(priority);
}
int getCitizenId(Citizen citizen)
{
    return citizen->citizenId;
}
bool citizenGreaterThanlexAndId (Element e1,Element e2)
{
    if(strcmp(((Citizen)e1)->citizenName,((Citizen)e2)->citizenName)==0)return citizenGreaterThan(e1,e2);

    return citizenIsGreaterLex(e1,e2);


}
Priority getFirstPriority(Citizen citizen)
{
    return uniqueOrderedListGetLowest(citizen->priorities);
}