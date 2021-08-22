//
// Created by daraw on 06/12/2018.
//
#include "Priority.h"
 struct priority{
    int candidateId;
    int priority;
};
Element copyPriority(Element element)
{
 if(element==NULL)return NULL;
 Priority newPriority=malloc(sizeof(*newPriority));
 if(newPriority==NULL)return NULL;
 newPriority->candidateId=((Priority)element)->candidateId;
 newPriority->priority=((Priority)element)->priority;
 return newPriority;
}
void freePriority(Element element)
{
 free(element);
}
bool isEqualPriority(Element el,Element e2)
{
 return ((Priority)el)->candidateId==((Priority)e2)->candidateId;
}
bool greaterPriority(Element e1,Element e2)
{
 return ( ((Priority)e1)->priority >= ((Priority)e2)->candidateId);
}
Priority createPriority(int candidateId,int priority)
{
 Priority newPriority=malloc(sizeof(*newPriority));
 if(newPriority==NULL)return NULL;
 newPriority->candidateId=candidateId;
 newPriority->priority=priority;
 return newPriority;
}
bool getPriorityOrNot(Priority priority,int candidateId)
{
 if(priority==NULL)return false;
 if(priority->candidateId==candidateId)return true;
 return false;
}
bool samePriority(Priority pr,int priority)
{
 if(pr->priority==priority)return true;
 return false;
}
Priority setPriority(Priority pr,int rate)
{
 pr->priority=rate;
 return pr;
}
int getIdOfPriority(Priority priority)
{
 return priority->candidateId;
}