//
// Created by daraw on 06/12/2018.
//

#ifndef MTMELECTIONS_PRIORITY_H
#define MTMELECTIONS_PRIORITY_H

#include "uniqueOrderedList.h"
typedef struct priority *Priority;
Element copyPriority(Element element);
bool isEqualPriority(Element el,Element e2);
void freePriority(Element element);
bool greaterPriority(Element e1,Element e2);
Priority createPriority(int candidateId,int priority);
bool getPriorityOrNot(Priority priority,int candidateId);
Priority setPriority(Priority pr,int rate);
bool samePriority(Priority pr,int priority);

#endif //MTMELECTIONS_PRIORITY_H
