//
// Created by daraw on 06/12/2018.
//

#ifndef MTMELECTIONS_CANDIDATE_H
#define MTMELECTIONS_CANDIDATE_H

#include "uniqueOrderedList.h"
typedef struct candidate *Candidate;
Element copyCandidate(Element element);
void freeCandidate(Element element);
bool equalCandidates(Element e1,Element e2);
bool greaterCandidate(Element e1,Element e2);
Candidate createCandidate(int candidateId,int cityId);
bool getCandidateOrNot(Candidate candidate,int candidateId);
bool candidateAlwaysNotEquals(Element e1,Element e2);
bool candidateAlwaysGreater(Element e1,Element e2);

#endif //MTMELECTIONS_CANDIDATE_H
