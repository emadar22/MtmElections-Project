//
// Created by daraw on 24/11/2018.
//

#include "uniqueOrderedList/uniqueOrderedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.>
typedef struct node
{
    Element e;
    struct node* next_node;
}*Node;

struct uniqueOrderedList_t
{
    copyElements copy;
    freeElements free;
    elementGreaterThan Greater;
    elementsEquals  Equal;
    Node head;
    Node iterator;
};
UniqueOrderedList uniqueOrderedListCreate(copyElements copy, freeElements free, elementsEquals Equal, elementGreaterThan Greater)
{
    if(copy==NULL||free==NULL||Equal==NULL||Greater==NULL)return NULL;
    UniqueOrderedList new_list=malloc(sizeof(*new_list));
    if(new_list==NULL)
    {
        return NULL;
    }
    new_list->copy=copy ;
    new_list->free=free ;
    new_list->Equal=Equal ;
    new_list->Greater=Greater ;
    new_list->head=NULL;
    new_list->iterator=NULL;
    return new_list;

}
UniqueOrderedListResult uniqueOrderedListInsert(UniqueOrderedList uniqueOrderedList, Element element)
{
    if(uniqueOrderedList==NULL||element==NULL)
    {
        return UNIQUE_ORDERED_LIST_NULL_ARGUMENT;
    }
    if(uniqueOrderedListContains(uniqueOrderedList,element))
    {
        return UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS;
    }
    Node newNode=malloc(sizeof(*newNode));
    if(newNode == NULL)
    {
        return UNIQUE_ORDERED_LIST_NULL_ARGUMENT;
    }
    newNode->e=uniqueOrderedList->copy(element);
    newNode->next_node=NULL;

    if(uniqueOrderedList->head==NULL)
    {
        uniqueOrderedList->head=newNode;
        uniqueOrderedList->iterator=uniqueOrderedList->head;
        return UNIQUE_ORDERED_LIST_SUCCESS;
    }
    if(uniqueOrderedList->Greater(uniqueOrderedList->head->e,element))
    {
        newNode->next_node=uniqueOrderedList->head;
        uniqueOrderedList->head=newNode;
        return UNIQUE_ORDERED_LIST_SUCCESS;
    }
    if(uniqueOrderedList->head->next_node==NULL)
    {
        uniqueOrderedList->head->next_node=newNode;
        return UNIQUE_ORDERED_LIST_SUCCESS;
    }
    if(uniqueOrderedList->Greater(element,uniqueOrderedListGetGreatest(uniqueOrderedList)))
    {
        uniqueOrderedList->iterator->next_node=newNode;
        return UNIQUE_ORDERED_LIST_SUCCESS;
    }
    uniqueOrderedList->iterator=uniqueOrderedList->head;

    Node nodeafter=uniqueOrderedList->head;
    Node prev=uniqueOrderedList->head;
    while(uniqueOrderedList->iterator!=NULL)
    {
        if(uniqueOrderedList->Greater(uniqueOrderedList->iterator->e,element))
        {
            nodeafter=uniqueOrderedList->iterator;
            break;
        }
        prev=uniqueOrderedList->iterator;
        uniqueOrderedList->iterator=uniqueOrderedList->iterator->next_node;
    }
    prev->next_node=newNode;
    newNode->next_node=nodeafter;
    return UNIQUE_ORDERED_LIST_SUCCESS;
}
////
////f(uniqueOrderedList->head==NULL||uniqueOrderedList->Greater(((uniqueOrderedList->head)->e),element)){
//      newNode->next_node=uniqueOrderedList ->head;
//      uniqueOrderedList->head=newNode;
//      printf("Allah");
//
//
//  }
//        else{
//    uniqueOrderedList->iterator=uniqueOrderedList->head;
//    printf("falafel");
//    while (uniqueOrderedList->iterator!=NULL&&uniqueOrderedList->Greater(newNode->e ,uniqueOrderedList->iterator->e)){
//        uniqueOrderedList ->iterator=uniqueOrderedList ->iterator->next_node;
//    }
//    newNode->next_node = uniqueOrderedList ->iterator->next_node;
//    uniqueOrderedList->iterator->next_node = newNode;
// }
/////
int uniqueOrderedListSize(UniqueOrderedList uniqueOrderedList)
{
    int size=0;
    if(uniqueOrderedList==NULL)
    {
        return -1;
    }
    if(uniqueOrderedList->head==NULL)return 0;
    uniqueOrderedList ->iterator=uniqueOrderedList->head;
    while(uniqueOrderedList ->iterator!=NULL)
    {
        size++;
        uniqueOrderedList->iterator=uniqueOrderedList->iterator->next_node;
    }
    return size;
}
bool uniqueOrderedListContains(UniqueOrderedList uniqueOrderedList, Element element)
{
    if(uniqueOrderedList==NULL||element==NULL)return NULL;
    if(uniqueOrderedList->head==NULL)return false;
    if(uniqueOrderedList->Equal(uniqueOrderedList->head->e,element))return true;
    uniqueOrderedList->iterator=uniqueOrderedList->head;

    while(uniqueOrderedList->iterator->next_node!=NULL)
    {
        uniqueOrderedList->iterator=uniqueOrderedList->iterator->next_node;
        if(uniqueOrderedList->Equal(uniqueOrderedList->iterator->e,element))
        {
            return true;
        }
    }
    if(uniqueOrderedList->Equal(uniqueOrderedList->iterator->e,element))
    {
        return true;
    }
    return false;
}
UniqueOrderedList uniqueOrderedListCopy(UniqueOrderedList uniqueOrderedList)
{
    if(uniqueOrderedList==NULL)return NULL;
    UniqueOrderedList new_list=uniqueOrderedListCreate(uniqueOrderedList->copy,uniqueOrderedList->free
            ,uniqueOrderedList->Equal,uniqueOrderedList->Greater);
    if(new_list==NULL) return NULL;
    if(uniqueOrderedList->head==NULL) return new_list;

    Node tmp = uniqueOrderedList->iterator;
    int numofUol=uniqueOrderedListSize(uniqueOrderedList);
    uniqueOrderedListGetLowest(uniqueOrderedList);
    int i=0;
    while(uniqueOrderedList->iterator!=NULL&&i<numofUol)
    {
        if(uniqueOrderedListInsert(new_list,uniqueOrderedList->iterator->e)==UNIQUE_ORDERED_LIST_NULL_ARGUMENT)
        {

            uniqueOrderedList->iterator = tmp;
            uniqueOrderedListDestroy(new_list);
            i++;
            return NULL;
        }
        uniqueOrderedListGetNext(uniqueOrderedList);
        i++;
    }
    uniqueOrderedList->iterator=tmp;
    return new_list;
}
void uniqueOrderedListDestroy(UniqueOrderedList uniqueOrderedList)
{
    uniqueOrderedListClear(uniqueOrderedList);
    free(uniqueOrderedList);
}
Element uniqueOrderedListGetNext(UniqueOrderedList uniqueOrderedList)
{
    if(uniqueOrderedList==NULL||uniqueOrderedList->head==NULL||uniqueOrderedList->iterator->next_node==NULL)
    {
        return NULL;
    }
    uniqueOrderedList->iterator=uniqueOrderedList->iterator->next_node;

    return uniqueOrderedList->iterator->e;
}
void uniqueOrderedListClear(UniqueOrderedList uniqueOrderedList)
{
    if(uniqueOrderedList==NULL||uniqueOrderedList->head==NULL)return;
    while(uniqueOrderedList->head!=NULL)
    {
        Node next=uniqueOrderedList->head;
        uniqueOrderedList->head=uniqueOrderedList->head->next_node;
        uniqueOrderedList->free(next->e);
        free(next);

    }

    uniqueOrderedList->iterator=NULL;
    uniqueOrderedList->head=NULL;

}
Element uniqueOrderedListGetGreatest(UniqueOrderedList uniqueOrderedList)
{
    if(uniqueOrderedList==NULL||uniqueOrderedList->head==NULL)
    {
        return NULL;
    }
    if(uniqueOrderedList->head->next_node==NULL)
    {
        return uniqueOrderedList->head->e;
    }
    uniqueOrderedList->iterator=uniqueOrderedList->head;
    while(uniqueOrderedList->iterator->next_node!=NULL)
    {
        uniqueOrderedList->iterator=uniqueOrderedList->iterator->next_node;
    }
    return uniqueOrderedList->iterator->e;
}
Element uniqueOrderedListGetLowest(UniqueOrderedList uniqueOrderedList)
{
    if(uniqueOrderedList==NULL||uniqueOrderedList->head==NULL) return NULL;
    uniqueOrderedList->iterator=uniqueOrderedList->head;
    return uniqueOrderedList->head->e;
}
UniqueOrderedListResult uniqueOrderedListRemove(UniqueOrderedList uniqueOrderedList, Element element)
{
    if(uniqueOrderedList== NULL || !element )return UNIQUE_ORDERED_LIST_NULL_ARGUMENT;
    if(uniqueOrderedList->head==NULL||!uniqueOrderedListContains(uniqueOrderedList,element))
    {
        return UNIQUE_ORDERED_LIST_ITEM_DOES_NOT_EXIST;
    }
    uniqueOrderedListGetLowest(uniqueOrderedList);
    if(uniqueOrderedList->Equal(element,uniqueOrderedList->iterator->e))
    {
        uniqueOrderedList->head=uniqueOrderedList->iterator->next_node;
        uniqueOrderedList->free(uniqueOrderedList->iterator->e);
        free(uniqueOrderedList->iterator);
        uniqueOrderedList->iterator=NULL;
        return UNIQUE_ORDERED_LIST_SUCCESS;
    }
    while(uniqueOrderedList->iterator->next_node)
    {
        if(uniqueOrderedList->Equal(uniqueOrderedList->iterator->next_node->e,element)) break;
        uniqueOrderedListGetNext(uniqueOrderedList);

    }
    Node temp=uniqueOrderedList->iterator->next_node->next_node;
    uniqueOrderedList->free(uniqueOrderedList->iterator->next_node->e);
    free(uniqueOrderedList->iterator->next_node);
    uniqueOrderedList->iterator->next_node=temp;
    uniqueOrderedList->iterator=NULL;
    return UNIQUE_ORDERED_LIST_SUCCESS;
}



