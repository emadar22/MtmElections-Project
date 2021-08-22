//
// Created by daraw on 06/12/2018.
//
#include "City.h"
 struct city{
    char* cityName;
    int cityId;
    UniqueOrderedList citizensList;
    UniqueOrderedList candidatesList;
};
char* copyString(const char* s) {
    char* str = malloc(strlen(s) + 1);
    if (str == NULL) return NULL;
    return strcpy(str, s);
}

Element copyCity(Element element)
{
    if(element==NULL)return NULL;
    City newCity=malloc(sizeof(*newCity));
    if(newCity==NULL)return NULL;
    newCity->cityId= ((City)element)->cityId;
    newCity->cityName=copyString(((City)element)->cityName);
    newCity->candidatesList=uniqueOrderedListCopy(((City)element)->candidatesList);
    newCity->citizensList=uniqueOrderedListCopy(((City)element)->citizensList);
    return newCity;
}
void freeCity(Element element)
{
    assert(element!=NULL);
    uniqueOrderedListDestroy(((City)element)->citizensList);
    uniqueOrderedListDestroy(((City)element)->candidatesList);
    free(element);

}
bool cityGreaterThan(Element e1,Element e2)
{
    return ((City)e1)->cityId>((City)e2)->cityId;

}
bool cityEquals(Element e1,Element e2)
{
    return ((City)e1)->cityId==((City)e2)->cityId;
}
City createCity(int cityId,const char* cityName)
{
    City newCity = malloc(sizeof(*newCity));
    if (newCity == NULL)return NULL;
    newCity->cityId = cityId;
    newCity->cityName=copyString(cityName);
    newCity->candidatesList = uniqueOrderedListCreate(copyCandidate, freeCandidate, equalCandidates, greaterCandidate);
    newCity->citizensList = uniqueOrderedListCreate(copyCitizen, freeCitizen, equalCitizenId, citizenGreaterThan);
    return newCity;
}
bool getCityOrNot(City city,int cityId)
{
    if(city->cityId==cityId)return true;
    return false;
}
Citizen  getCitizen(City city,int citizen_id)
{
    Citizen citizenItr;
    int numOfCitizens=uniqueOrderedListSize(city->citizensList);
    if(numOfCitizens==0)return NULL;
    citizenItr=uniqueOrderedListGetLowest(city->citizensList);
    if(GetCitizenOrNot(citizenItr,citizen_id))return citizenItr;
    for(int i=1; i<numOfCitizens; i++)
    {
        citizenItr=uniqueOrderedListGetNext(city->citizensList);
        if(GetCitizenOrNot(citizenItr,citizen_id))return citizenItr;
    }
    return NULL;
}
Candidate getCandidate(City city,int candidateId)
{
    if(city==NULL)return NULL;
    Candidate cand=uniqueOrderedListGetLowest(city->candidatesList);
    if(getCandidateOrNot(cand,candidateId))return cand;
    while(city->candidatesList)
    {
        cand=uniqueOrderedListGetNext(city->candidatesList);
        if(getCandidateOrNot(cand,candidateId))return cand;

    }
    return NULL;
}
UniqueOrderedListResult insertCitizen(City city,Citizen citizen)
{
    return(uniqueOrderedListInsert(city->citizensList,citizen));
}
int getCityIdOrNot(City city,Citizen citizen)
{
    if(uniqueOrderedListContains(city->citizensList,citizen))
    {
        return city->cityId;
    }
    return 0;
}
UniqueOrderedListResult insertCandidate(City city,Candidate candidate)
{
    return uniqueOrderedListInsert(city->candidatesList,candidate);
}
Citizen getLowestCitizen(City city)
{
    return uniqueOrderedListGetLowest(city->citizensList);
}
Citizen getNextCitizen(City city)
{
    return uniqueOrderedListGetNext(city->citizensList);
}
void removeCandidate(City city,Candidate candidate)
{
    uniqueOrderedListRemove(city->candidatesList,candidate);
}
void removeCitizen(City city,Citizen citizen)
{
    uniqueOrderedListRemove(city->citizensList,citizen);
}
UniqueOrderedList getCitizensList(City city)
{
    return city->citizensList;
}
UniqueOrderedList getCandidateList(City city)
{
    return city->candidatesList;
}

int numOfCandidates(City city)
{
    return uniqueOrderedListSize(city->candidatesList);
}
char** getCityName(City city)
{
    return &city->cityName;

}