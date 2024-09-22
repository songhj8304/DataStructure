#include "LstElementType.h"

typedef struct _Node {
    LstElement element;
    struct _Node* next;
} ListNode;

typedef struct {
    ListNode* head; // points to the first node
    ListNode* tail; // points to the last node
} List;

typedef void (*PrintFunc)(const LstElement* e);

// returns 1 if e1 and e2 are identical, otherwise returns 0
typedef int (*CompareFunc)(const LstElement* e1, const LstElement* e2);

typedef void (*IterateFunc)(const LstElement* e, void* p);

// Allocates a list structure and returns the pointer. Returns NULL if the allocation fails
List* LstCreate(void);

// Returns 1 if no data exist in the list. Returns 0 if exists
int LstEmpty(const List* list);

// Adds e at the end of the list. Returns 1 if succeeds or returns 0 if fails
int LstPushBack(List* list, const LstElement* e);

// Adds e as the first node of the list
// Returns 1 if succeeds or returns 0 if fails
int LstPushFront(List* list, const LstElement* e);

// Returns an element at pos index through e. Returns 1 if succeeds 0 otherwise
int LstGetEntry(List* list, int pos, LstElement* e);

// Inserts e right before next node if it exists
// Returns 1 if next node exists and the insertion succeeds 
// Otherwise returns 0
int LstInsertBefore(List* list, ListNode* next, const LstElement* e);

// Inserts e right after previous node if it exists
// Returns 1 if previous node exists and the insertion succeeds 
// Otherwise returns 0
int LstInsertAfter(List* list, ListNode* previous, const LstElement* e);

// Inserts e at pos index. Returns 1 if succeeds 0 otherwise
int LstInsert(List* list, int pos, const LstElement* e);

// Prints out all elements using func fucntion
void LstPrint(List* list, PrintFunc print);

// Deletes the given node from the list
// Returns 1 if succeeds, otherwise returns 0
int LstDelete(List* list, ListNode* node);

// Deletes all elements from the list
void LstClear(List* list);

// Returns the first node that has e from the list. func is used to compare an element 
// from the list and the given element e
// If e is not found, returns NULL
ListNode* LstFindNode(List* list, const LstElement* e, CompareFunc compare);

// Applies func function to each node of the list. p is used as an argument to the func function
void LstIterate(List* list, IterateFunc iterate, void* p);

// Deletes all nodes of the list and deallocates the list structure
void LstDestroy(List* list);

