//
// Created by daraw on 29/11/2018.
//

#include <stdio.h>
#include "uniqueOrderedList.h"
#include "mtm_elections.h"
#include "Candidate.h"
#include <stdlib.h>
#include <assert.h>
Citizen getWinner(MtmElections mtmElections,City city,RankFunc rank, void* auxilaryData)
{

    if(numOfCandidates(city)==0)return NULL;
    UniqueOrderedList candidateCitizenList=uniqueOrderedListCreate(copyCitizen,freeCitizen,equalCitizenId,citizenGreaterThanlexAndId);
    if(candidateCitizenList==NULL)return NULL;
    Citizen citizen=uniqueOrderedListGetLowest(getCitizensList(city));
    while(citizen)
    {
        if(citizenIsCandidate(citizen))
        {
            uniqueOrderedListInsert(candidateCitizenList,citizen);
        }
        citizen=uniqueOrderedListGetNext(getCitizensList(city));

    }
    int numOfCandidates=uniqueOrderedListSize(city->candidatesList);
    if(numOfCandidates==0)return NULL;
    int* arr=malloc(sizeof(int)*numOfCandidates);
    if(arr==NULL)return NULL;
    for(int i=0; i<numOfCandidates; i++)
    {
        arr[i]=0;
    }
    citizen=uniqueOrderedListGetLowest(getCitizensList(city));
    if(rank!=NULL)
    {
        while(citizen)
        {
            Priority pr=getFirstPriority(citizen);
            int IdOfCandidate=getIdOfPriority(pr);
            int citizenId=getCitizenId(citizen);
            int index=getIndexOfCandidate(candidateCitizenList,IdOfCandidate);
            int donationOfCitizen=rank(mtmElections,citizenId,auxilaryData);
            arr[index]=arr[index]+donationOfCitizen;
            citizen=uniqueOrderedListGetNext(getCitizensList(city));

        }
    }
    while(rank==NULL&&citizen)
    {
        int age=getAgeOfCitizen(citizen);
        if(age<17)
        {
            citizen=uniqueOrderedListGetNext(getCitizensList(city));
            continue;
        }
        Priority pr=getFirstPriority(citizen);
        int IdOfCandidate=getIdOfPriority(pr);
        int citizenId=getCitizenId(citizen);
        int index=getIndexOfCandidate(candidateCitizenList,IdOfCandidate);
        int donationOfCitizen=1;
        arr[index]=arr[index]+donationOfCitizen;
        citizen=uniqueOrderedListGetNext(getCitizensList(city));

    }
    int indexOfmax=getIndexOfmax(arr,numOfCandidates);
    citizen=uniqueOrderedListGetLowest(candidateCitizenList);
    for(int i=0; i<indexOfmax; i++)
    {
        citizen=uniqueOrderedListGetNext(candidateCitizenList);
    }
    Citizen winner=copyCitizen(citizen);
    uniqueOrderedListDestroy(candidateCitizenList);
    free(arr);
    return winner;

}






#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
Citizen findCitizen(MtmElections mtmElections,int citizenId)
{
    City city=uniqueOrderedListGetLowest(mtmElections->cities);
    if(!city) return NULL;
    Citizen citizen=getCitizen(city,citizenId);
    while(citizen==NULL)
    {
        city=uniqueOrderedListGetNext(mtmElections->cities);
        if(!city) return NULL;
        citizen=getCitizen(city,citizenId);
    }
    return citizen;
}
City getCity(MtmElections mtmElections,int city_Id)
{

    City cityItr;
    int numOfcities=uniqueOrderedListSize(mtmElections->cities);
    if(numOfcities==0)return NULL;
    cityItr=uniqueOrderedListGetLowest(mtmElections->cities);
    if(getCityOrNot(cityItr,city_Id))return cityItr;
    for(int i=1; i<numOfcities; i++)
    {
        cityItr=uniqueOrderedListGetNext(mtmElections->cities);
        if(getCityOrNot(cityItr,city_Id))return cityItr;
    }
    return NULL;
}




typedef struct mtm_elections_t* MtmElections;

typedef int (*RankFunc)(MtmElections, int, void*);


MtmElections mtmElectionsCreate()
{
    MtmElections newMtmElections =malloc(sizeof(*newMtmElections));
    if(newMtmElections==NULL)return NULL;
    newMtmElections->cities=uniqueOrderedListCreate(copyCity,freeCity,cityEquals,cityGreaterThan);
    return newMtmElections;
}

void mtmElectionsDestroy(MtmElections mtmElections)
{
    uniqueOrderedListDestroy(mtmElections->cities);
    free(mtmElections);

}

MtmElectionsResult mtmElectionsAddCity(MtmElections mtmElections, const char* cityName, int cityId)
{
    if (mtmElections == NULL || cityName == NULL )return MTM_ELECTIONS_NULL_ARGUMENT;
    if(cityId<0)return MTM_ELECTIONS_ILLEGAL_ID;
    City newCity = createCity(cityId,cityName);
    if(newCity==NULL)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    UniqueOrderedListResult result=uniqueOrderedListInsert(mtmElections->cities,newCity);

    if (result == UNIQUE_ORDERED_LIST_NULL_ARGUMENT)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    if (result == UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS)
    {
        return MTM_ELECTIONS_CITY_ALREADY_EXISTS;
    }
    return MTM_ELECTIONS_SUCCESS;
}

MtmElectionsResult mtmElectionsAddCitizen(MtmElections mtmElections, const char* citizenName,
                                          int citizenId, int citizenAge, int yearsOfEducation, int cityId)
{
    if (mtmElections == NULL || citizenName == NULL )
        return MTM_ELECTIONS_NULL_ARGUMENT;
    if (citizenId < 0 || cityId < 0)return MTM_ELECTIONS_ILLEGAL_ID;
    if (citizenAge <= 0)return MTM_ELECTIONS_ILLEGAL_AGE;
    if (yearsOfEducation < 0)return MTM_ELECTIONS_ILLEGAL_NUMBER_OF_YEARS;
    Citizen newCitizen=createCitizen(citizenId,citizenAge,citizenName,yearsOfEducation);
    if(newCitizen==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    int cityID = getcityId(mtmElections,newCitizen);
    if(cityID!=-1) return MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS;
    City city=getCity(mtmElections,cityId);
    if(city==NULL)
    {
        free(newCitizen);
        return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    }
    UniqueOrderedListResult result=insertCitizen(city,newCitizen);

    if (result == UNIQUE_ORDERED_LIST_NULL_ARGUMENT)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    if (result == UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS)
    {
        return MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS;
    }
    return MTM_ELECTIONS_SUCCESS;
}





MtmElectionsResult MtmElectionsCitizenGetName(MtmElections mtmElections, int citizenId, char** name)
{
    if(mtmElections==NULL||name==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(citizenId<0)return MTM_ELECTIONS_ILLEGAL_ID;
    City city_irterator=uniqueOrderedListGetLowest(mtmElections->cities);
    Citizen citizen = NULL;
    while (city_irterator!=NULL)
    {
        citizen = getCitizen(city_irterator,citizenId);
        if(citizen)
        {
            *name=getNameOfCitizen(citizen);

            return MTM_ELECTIONS_SUCCESS;
        }
        city_irterator=uniqueOrderedListGetNext(mtmElections->cities);
    }
    return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
}
int getcityId(MtmElections mtmElections,Citizen cit)
{
    City city=uniqueOrderedListGetLowest(mtmElections->cities);
    if(getCityIdOrNot(city,cit)!=0)return getCityIdOrNot(city,cit);
    while(city)
    {
        city=uniqueOrderedListGetNext(mtmElections->cities);
        if(city==NULL)return -1;
        if(getCityIdOrNot(city,cit)!=0)return getCityIdOrNot(city,cit);

    }
    return -1;
}


MtmElectionsResult MtmElectionsCitizenGetCity(MtmElections mtmElections, int citizenId, int* cityId)
{
    if(mtmElections==NULL||cityId==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(citizenId<0)return MTM_ELECTIONS_ILLEGAL_ID;
    City city_irterator=uniqueOrderedListGetLowest(mtmElections->cities);
    Citizen citizen = NULL;
    while (city_irterator!=NULL)
    {
        citizen = getCitizen(city_irterator,citizenId);
        if(citizen)
        {
            *cityId = city_irterator->cityId;
            return MTM_ELECTIONS_SUCCESS;
        }
        city_irterator=uniqueOrderedListGetNext(mtmElections->cities);
    }
    return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
}

MtmElectionsResult MtmElectionsCitizenGetAge(MtmElections mtmElections, int citizenId, int* age)
{
    if(mtmElections==NULL||age==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(citizenId<0)return MTM_ELECTIONS_ILLEGAL_ID;
    City city=uniqueOrderedListGetLowest(mtmElections->cities);
    Citizen citizen=getCitizen(city,citizenId);
    if(citizen==NULL)
    {
        while(city)
        {
            city=uniqueOrderedListGetNext(mtmElections->cities);
            if(!city) return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
            Citizen citizen=getCitizen(city,citizenId);
            if(citizen!=NULL)
            {
                *age=getAgeOfCitizen(citizen);
                return MTM_ELECTIONS_SUCCESS;
            }
        }
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    }
    *age=getAgeOfCitizen(citizen);
    return MTM_ELECTIONS_SUCCESS;

}

MtmElectionsResult MtmElectionsCitizenGetEducation(MtmElections mtmElections, int citizenId, int* yearsOfEducation)
{
    if(mtmElections==NULL||yearsOfEducation==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(citizenId<0)return MTM_ELECTIONS_ILLEGAL_ID;
    City city=uniqueOrderedListGetLowest(mtmElections->cities);
    Citizen citizen=getCitizen(city,citizenId);
    if(citizen==NULL)
    {
        while(city)
        {
            city=uniqueOrderedListGetNext(mtmElections->cities);
            if(!city) return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
            Citizen citizen=getCitizen(city,citizenId);
            if(citizen!=NULL)
            {
                *yearsOfEducation=getYearsOfEdu(citizen);
                return MTM_ELECTIONS_SUCCESS;
            }
        }
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    }
    *yearsOfEducation=getYearsOfEdu(citizen);
    return MTM_ELECTIONS_SUCCESS;

}

MtmElectionsResult mtmElectionsAddCandidate(MtmElections mtmElections, int candidateId, int cityId)
{
    if(mtmElections==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(cityId<0||candidateId<0)return MTM_ELECTIONS_ILLEGAL_ID;
    City city=getCity(mtmElections,cityId);
    if(city==NULL)return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    Citizen candidadte=getCitizen(city,candidateId);
    if(candidadte==NULL) return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    if(getAgeOfCitizen(candidadte)<21)
    {
        return MTM_ELECTIONS_AGE_NOT_APPROPRIATE;
    }
    if(!citizenIsCandidate(candidadte))
    {
        citizenForPrisednt(candidadte);
        Candidate newCandidate=createCandidate(candidateId,cityId);
        if(newCandidate==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
        insertCandidate(city,newCandidate);
        return MTM_ELECTIONS_SUCCESS;
    }
    return MTM_ELECTIONS_CANDIDATE_ALREADY_EXISTS;
}

MtmElectionsResult mtmElectionsWithdrawCandidate(MtmElections mtmElections, int candidateId, int cityId)
{
    if(mtmElections==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(candidateId<0||cityId<0) return MTM_ELECTIONS_ILLEGAL_ID;
    City city=getCity(mtmElections,cityId);
    if(city==NULL)return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    Citizen candidateToDelete=getCitizen(city,candidateId);
    if(candidateToDelete==NULL||!citizenIsCandidate(candidateToDelete))
    {
        return MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST;
    }
    citizenWithdrawPresidency(candidateToDelete);
    Citizen citizen=getLowestCitizen(city);
    priorityToDelete(candidateId,citizen);
    while(citizen)
    {
        citizen=getNextCitizen(city);
        if(citizen==NULL)break;
        priorityToDelete(candidateId,citizen);
    }
    Candidate toRemove=getCandidate(city,candidateId);
    removeCandidate(city,toRemove);
    return MTM_ELECTIONS_SUCCESS;

}

MtmElectionsResult mtmElectionsSupportCandidate(MtmElections mtmElections, int citizenId, int candidateId, int priority)
{
    if(mtmElections==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(citizenId<0||candidateId<0)return MTM_ELECTIONS_ILLEGAL_ID;
    if(priority<0)return MTM_ELECTIONS_ILLEGAL_PRIORITY;
    Citizen citizen=findCitizen(mtmElections,citizenId);
    if(citizen==NULL)return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    Citizen candidate=findCitizen(mtmElections,candidateId);
    if(candidate==NULL||!citizenIsCandidate(candidate))return MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST;
    int citizenCityId,candidateCityId;
    citizenCityId=getcityId(mtmElections,citizen);
    candidateCityId=getcityId(mtmElections,candidate);
    if(citizenCityId!=candidateCityId)return MTM_ELECTIONS_NOT_SAME_CITY;
    if(citizenIsCandidate(citizen))return MTM_ELECTIONS_CAN_NOT_SUPPORT;
    Priority pr=getPriority(citizen,candidateId);
    if(pr!=NULL)return MTM_ELECTIONS_ALREADY_SUPPORTED;
    if(priorityExists(citizen,priority))return MTM_ELECTIONS_PRIORITY_EXISTS;
    Priority newPr=createPriority(candidateId,priority);
    if(newPr==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    insertPriority(citizen,newPr);
    return MTM_ELECTIONS_SUCCESS;


}

MtmElectionsResult mtmElectionsCancelSupport(MtmElections mtmElections, int citizenId, int candidateId)
{
    if(mtmElections==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(citizenId<0||candidateId<0)return MTM_ELECTIONS_ILLEGAL_ID;
    Citizen citizen=findCitizen(mtmElections,citizenId);
    if(citizen==NULL)return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    Citizen candidate=findCitizen(mtmElections,candidateId);
    if(candidate==NULL||!citizenIsCandidate(candidate))return MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST;
    if(equalCitizenId(citizen,candidate))return MTM_ELECTIONS_MUST_SUPPORT;
    if(priorityToDelete(candidateId,citizen))
    {
        return MTM_ELECTIONS_SUCCESS;
    }
    return MTM_ELECTIONS_NOT_SUPPORTED;

}

MtmElectionsResult mtmElectionsChangeAddress(MtmElections mtmElections, int citizenId, int cityId)
{
    if(mtmElections==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(citizenId<0||cityId<0)return MTM_ELECTIONS_ILLEGAL_ID;
    Citizen citizen=findCitizen(mtmElections,citizenId);
    if(citizen==NULL)return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    int cityOfCitizenId=getcityId(mtmElections,citizen);


    City city=getCity(mtmElections,cityId);
    if(city==NULL)
        return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    if(citizenIsCandidate(citizen))
    {
        mtmElectionsWithdrawCandidate(mtmElections,citizenId,cityOfCitizenId);
    }
    ClearPriorities(citizen);
    insertCitizen(city,citizen);
    city=getCity(mtmElections,cityOfCitizenId);
    removeCitizen(city,citizen);

    return MTM_ELECTIONS_SUCCESS;


}


int mtmElectionsRankByAge(MtmElections mtmElections, int citizen, void* pAge)
{
    if(mtmElections==NULL||pAge==NULL|| *((int*)pAge)==0)return 0;
    Citizen  citizenDet=findCitizen(mtmElections,citizen);
    if(!citizenDet) return 0;
    int citizenAge=getAgeOfCitizen(citizenDet);
    return ( citizenAge/(*((int*)pAge)));
}

void mtmPrintMayorDetails(int mayorId, int age, int yearsOfEducation, char* mayorName,
                          char* cityName, int cityId, FILE* file)
{
    fprintf(file,"****************************************\n");
    fprintf(file,"The Winner of the Elections at: %s %d is:\n", cityName, cityId);
    fprintf(file,"Mayor: \n");
    fprintf(file,"	Name: %s\n", mayorName);
    fprintf(file,"	ID:   %d\n", mayorId);
    fprintf(file,"	Age:  %d\n", age);
    fprintf(file,"	Years of education:  %d\n", yearsOfEducation);
    fprintf(file,"****************************************\n");
}

void mtmPrintFileError(const char* filename, FILE* file)
{
    fprintf(file,"Error: cannot open file: %s\n",filename);
}

char** getCityName(City city)
{
    return &city->cityName;

}

void printMayorsInFile(UniqueOrderedList winnersList,MtmElections mtmElections,FILE *filename)
{
    Citizen currentWinner=uniqueOrderedListGetLowest(winnersList);
    while(currentWinner)
    {
        int cityId=getcityId(mtmElections,currentWinner);
        char* cityName=getCityName(getCity(mtmElections,cityId));
        char* mayorName=getNameOfCitizen(currentWinner);
        int mayorId=getCitizenId(currentWinner);
        int yearsOfEdu=getYearsOfEdu(currentWinner);
        int age=getAgeOfCitizen(currentWinner);
        mtmPrintMayorDetails(mayorId,age,yearsOfEdu,mayorName,cityName,cityId,filename);
        currentWinner=uniqueOrderedListGetNext(winnersList);

    }
}

UniqueOrderedList mtmElectionsPerformElections(MtmElections mtmElections, RankFunc rank, void* auxilaryData, const char* filename)
{
    if(mtmElections==NULL || filename==NULL)return NULL;
    UniqueOrderedList winnersList=uniqueOrderedListCreate(copyCitizen,freeCitizen,equalCitizenId,citizenGreaterThanlexAndId);
    if(winnersList==NULL) return NULL;

    City   city=uniqueOrderedListGetLowest(mtmElections->cities);
    while(city)
    {
        Citizen winner=getWinner(mtmElections,city,rank,auxilaryData);
        if(winner==NULL)
        {
            city=uniqueOrderedListGetNext(mtmElections->cities);
            continue;
        }
        uniqueOrderedListInsert(winnersList,winner);
        city=uniqueOrderedListGetNext(mtmElections->cities);
    }
    UniqueOrderedList winnersIdsList=uniqueOrderedListCreate(copyCandidate,freeCandidate,candidateAlwaysNotEquals,candidateAlwaysGreater);

    if(winnersIdsList==NULL) return NULL;
    Citizen winner=uniqueOrderedListGetLowest(winnersList);
    while(winner)
    {
        int winnerId=getCitizenId(winner);
        int cityId=getcityId(mtmElections,winner);
        Candidate cand=getCandidate(getCity(mtmElections,cityId),winnerId);
        uniqueOrderedListInsert(winnersIdsList,cand);
        winner=uniqueOrderedListGetNext(winnersList);
    }
    FILE* file=fopen(filename, "a");
    if (file==NULL)
    {
        mtmPrintFileError(filename, stderr);
    }
    else
    {
        printMayorsInFile(winnersList, mtmElections,file);
        fclose(file);
    }
    uniqueOrderedListDestroy(winnersList);
    return winnersIdsList;

}



MtmElectionsResult mtmElectionsMayorOfCity(MtmElections mtmElections, int cityId, int* mayor, const char* filename)
{
    if(mtmElections==NULL|| mayor==NULL || filename==NULL) return MTM_ELECTIONS_NULL_ARGUMENT;
    if(cityId<0)return MTM_ELECTIONS_ILLEGAL_ID;
    City city=getCity(mtmElections, cityId);
    if(city==NULL)return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;

    int numOfCandidates=uniqueOrderedListSize(getCandidateList(city));
    if(numOfCandidates==0)return MTM_ELECTIONS_NO_CANDIDATES_IN_CITY;

    UniqueOrderedList candidateCitizenList=uniqueOrderedListCreate(copyCitizen,freeCitizen,equalCitizenId,citizenGreaterThanlexAndId);
    if(candidateCitizenList==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    Citizen citizen=uniqueOrderedListGetLowest(getCitizensList(city));
    while(citizen)
    {
        if(citizenIsCandidate(citizen))
        {
            uniqueOrderedListInsert(candidateCitizenList,citizen);
        }
        citizen=uniqueOrderedListGetNext(getCitizensList(city));

    }
    int* arr=malloc(sizeof(int)*numOfCandidates);
    if(arr==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    for(int i=0; i<numOfCandidates; i++)
    {
        arr[i]=0;
    }
    citizen=uniqueOrderedListGetLowest(getCitizensList(city));

    while(citizen)
    {
        int age=getAgeOfCitizen(citizen);
        Priority pr=getFirstPriority(citizen);
        if(pr){
            int IdOfCandidate=getIdOfPriority(pr);
            int index=getIndexOfCandidate(candidateCitizenList,IdOfCandidate);
            if(age>=17) arr[index]++;}
        citizen=uniqueOrderedListGetNext(getCitizensList(city));

    }
    int indexOfmax=getIndexOfmax(arr,numOfCandidates);
    citizen=uniqueOrderedListGetLowest(candidateCitizenList);
    for(int i=0; i<indexOfmax; i++)
    {
        citizen=uniqueOrderedListGetNext(candidateCitizenList);
    }
    *mayor=getCitizenId(citizen);
    uniqueOrderedListDestroy(candidateCitizenList);
    free(arr);

    FILE* file=fopen(filename, "a");
    if(file==NULL)
    {
        mtmPrintFileError(filename,stderr);
        return MTM_ELECTIONS_FILE_ERROR;
    }
    else
    {
        char* cityName=getCityName(getCity(mtmElections,cityId));
        char** name;
        int mayorId=getCitizenId(citizen);
        MtmElectionsCitizenGetName(mtmElections,mayorId,name);
        int yearsOfEdu=getYearsOfEdu(citizen);
        int age=getAgeOfCitizen(citizen);
        mtmPrintMayorDetails(mayorId,age,yearsOfEdu,*name,cityName,cityId,file);
        fclose(file);
    }
    return MTM_ELECTIONS_SUCCESS;
}