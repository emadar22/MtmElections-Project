//
// Created by daraw on 06/12/2018.
//

#ifndef MTMELECTIONS_CITY_H
#define MTMELECTIONS_CITY_H

#include "uniqueOrderedlist.h"
#include "Citizen.h"
#include "Candidate.h"
#include <strings.h>
typedef struct city *City;

char* copyString(const char* s) ;
UniqueOrderedList getCandidateList(City city);

Element copyCity(Element element);

void freeCity(Element element);

bool cityGreaterThan(Element e1,Element e2);

bool cityEquals(Element e1,Element e2);

City createCity(int cityId,const char* cityName);

bool getCityOrNot(City city,int cityId);

Citizen  getCitizen(City city,int citizen_id);

Candidate getCandidate(City city,int candidateId);

UniqueOrderedListResult insertCitizen(City city,Citizen citizen);

int getCityIdOrNot(City city,Citizen citizen);

UniqueOrderedListResult insertCandidate(City city,Candidate candidate);

Citizen getLowestCitizen(City city);

Citizen getNextCitizen(City city);

void removeCandidate(City city,Candidate candidate);

void removeCitizen(City city,Citizen citizen);

UniqueOrderedList getCitizensList(City city);

int numOfCandidates(City city);

char** getCityName(City city);


#endif //MTMELECTIONS_CITY_H
