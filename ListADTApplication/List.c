#include <stdlib.h>
#include "List.h"

static ListNode* createListNode(const LstElement* e)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (node) {
        node->element = *e; // memcpy(&node->element, e, sizeof(Element))
        node->next = NULL;
    }
    return node;
}

// Assume that list->head is not next node
static ListNode* findPreviousNode(List* list, ListNode* next)
{
    ListNode* prev = NULL;
    ListNode* temp = list->head;
    while (temp != NULL && temp != next) {
        prev = temp;
        temp = temp->next;
    }
    return prev;
}

// V2 Works even if list->head and next are the same
//static ListNode* FindPreviousNode(List* list, ListNode* next, int* noNext)
//{
//    *noNext = 0;
//    ListNode* prev = NULL;
//    ListNode* temp = list->head;
//    while (temp != NULL && temp != next) {
//        prev = temp;
//        temp = temp->next;
//    }
//    if (temp == NULL) { // next가 없음
//        *noNext = 1;
//    }
//    return prev;
//}

List* LstCreate(void)
{
    List* list = (List*)malloc(sizeof(List));
    if (list) {
        list->head = NULL;
        list->tail = NULL;
    }
    return list;
}

int LstEmpty(const List* list)
{
    return list->head == NULL && list->tail == NULL;
}

int LstPushBack(List* list, const LstElement* e)
{
    if (list) {
        ListNode* newnode = createListNode(e);
        if (newnode) {
            if (LstEmpty(list)) {
                list->head = newnode;
                list->tail = newnode;
            }
            else {
                list->tail->next = newnode;
                list->tail = newnode;
            }
            return 1;
        }
    }
    return 0;
}

int LstPushFront(List* list, const LstElement* e)
{
    if (list) {
        ListNode* newnode = createListNode(e);
        if (newnode) {
            if (LstEmpty(list)) {
                list->head = newnode;
                list->tail = newnode;
            }
            else {
                newnode->next = list->head;
                list->head = newnode;
            }
            return 1;
        }
    }
    return 0;
}

int LstGetEntry(List* list, int pos, LstElement* e)
{
    if (list) {
        int i = 0;
        ListNode* node = list->head;
        while (i < pos && node != NULL) {
            node = node->next;
            i++;
        }
        if (node) {
            *e = node->element;
        }
        return 1;
    }
    return 0;
}

int LstInsertBefore(List* list, ListNode* next, const LstElement* e)
{
    if (list && next && list->head) {
        if (list->head == next) {
            LstPushFront(list, e);
        }
        else {
            ListNode* prev = findPreviousNode(list, next);
            if (prev != NULL) {
                LstInsertAfter(list, prev, e);
            }
        }
        return 1;
    }
    return 0;
}

// v2
//int LstInsertBefore(List* list, ListNode* next, Element e)
//{
//    if (list && next && list->head) {
//        int noNext = 0;
//        ListNode* prev = FindPreviousNode(list, next, &noNext);
//        if (noNext == 0) return 0;
//        if (prev == NULL) { // next가 head인 경우
//            LstAddToFront(list, e);
//        }
//        else {
//            LstInsertAfter(list, prev, e);
//        }
//        return 1;
//    }
//    return 0;
//}

int LstInsertAfter(List* list, ListNode* previous, const LstElement* e)
{
    if (list && previous) {
        ListNode* temp = list->head;
        while (temp != NULL && temp != previous) {
            temp = temp->next;
        }
        if (temp != NULL) {
            ListNode* newnode = createListNode(e);
            if (newnode) {
                newnode->next = previous->next;
                previous->next = newnode;
            }
            return 1;
        }
    }
    return 0;
}

int LstInsert(List* list, int pos, const LstElement* e)
{
    if (list) {
        ListNode* node = createListNode(e);
        if (node) {
            if (list->head) {
                int i = 0;
                ListNode* prevNode = list->head;
                while (i < pos - 1 && node != NULL) {
                    prevNode = prevNode->next;
                    i++;
                }
                if (prevNode) {
                    if (prevNode == list->tail) {                        
                        prevNode->next = node;
                        list->tail = node;
                    }
                    else {
                        node->next = prevNode->next;
                        prevNode->next = node;
                    }
                }
            }
            else {
                list->head = list->tail = node;
            }
        }
    }
    return 0;
}

void LstPrint(List* list, PrintFunc print)
{
    if (list) {
        ListNode* temp = list->head;
        while (temp != NULL) {
            print(&(temp->element));
            temp = temp->next;
        }
    }
}

int LstDelete(List* list, ListNode* node)
{
    if (list && node && LstEmpty(list) == 0) {
        ListNode* temp = list->head;
        while (temp != NULL && temp != node) {
            temp = temp->next;
        }
        if (temp) {
            // if there is only one node in the list
            if (list->head == node && list->tail == node) {
                list->head = NULL;
                list->tail = NULL;
                free(node);
            }
            else if (list->head == node) {
                list->head = node->next;
                free(node);
            }
            else if (list->tail == node) {
                ListNode* prev = findPreviousNode(list, node);
                if (prev != NULL) {
                    list->tail = prev;
                    prev->next = NULL;
                    free(node);
                }
            }
            else {
                ListNode* prev = findPreviousNode(list, node);
                if (prev != NULL) {
                    prev->next = node->next;
                    free(node);
                }
            }
        }
    }
    return 0;
}


int LstDeleteFront(List* list)
{
    if (list && LstEmpty(list) == 0) {
        ListNode* temp = list->head;
        if (temp) {
            list->head = temp->next;
            free(temp);
            return 1;
        }
    }
    return 0;
}

void LstClear(List* list)
{
    if (list) {
        if (list->head) {
            ListNode* temp = NULL;
            while (list->head) {
                temp = list->head->next;
                free(list->head);
                list->head = temp;
            }
        }
    }
}

ListNode* LstFindNode(List* list, const LstElement* e, CompareFunc compare)
{
    if (list) {
        ListNode* temp = list->head;
        while (temp != NULL && compare(&(temp->element), e) != 1) {
            temp = temp->next;
        }
        return temp;
    }
    return NULL;
}

void LstIterate(List* list, IterateFunc iterate, void* p)
{
    if (list) {
        ListNode* temp = list->head;
        while (temp != NULL) {
            iterate(&(temp->element), p);
            temp = temp->next;
        }
    }
}

void LstDestroy(List* list)
{
    LstClear(list);
    if (list) {
        free(list);
    }
}

