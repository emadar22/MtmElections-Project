//
// Created by daraw on 06/12/2018.
//
#include "Candidate.h"


 struct candidate{
    int candidateId;
    int cityId;
};

Element copyCandidate(Element element){
    if(element==NULL)return NULL;
    Candidate newCandidate=malloc(sizeof(*newCandidate));
    if(newCandidate==NULL)return NULL;
    newCandidate->candidateId=((Candidate)element)->candidateId;
    newCandidate->cityId=((Candidate)element)->cityId;
    return newCandidate;
}
void freeCandidate(Element element){
    free(element);
}

bool equalCandidates(Element e1,Element e2){
    return ((Candidate)e1)->candidateId==((Candidate)e2)->candidateId;
}
bool greaterCandidate(Element e1,Element e2){
    return ((Candidate)e1)->candidateId>((Candidate)e2)->candidateId;
}
Candidate createCandidate(int candidateId,int cityId)
{
    Candidate newCandidate=malloc(sizeof(*newCandidate));
    if(newCandidate==NULL)return NULL;
    newCandidate->candidateId=candidateId;
    newCandidate->cityId=cityId;
    return newCandidate;

}
bool getCandidateOrNot(Candidate candidate,int candidateId){
    if(candidate->candidateId==candidateId)return true;
    return false;
}
bool candidateAlwaysNotEquals(Element e1,Element e2)
{
    return false;

}
bool candidateAlwaysGreater(Element e1,Element e2)
{
    return true;

}