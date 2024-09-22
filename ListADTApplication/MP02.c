#include <string.h>
#include "ReadPopulationData.h"
#include "List.h"

typedef struct {
    int men;
    int women;
} SUM_DATA;

const char* DATA_FILE_NAME = "SeoulPopulation2020.txt";

PopulationData PDs[3] = {
    { "Jongnogu", 76876, 82120 }, { "Eunpyeonggu", 231998, 252045 }, { "Gangdong", 228044, 235954 }
};

void GetTotalPopulation(const PopulationData* pd, void* p)
{
    SUM_DATA* sumData = (SUM_DATA*)p;
    sumData->men += pd->men;
    sumData->women += pd->women;
}

void PrintPopulationData(const PopulationData* pd)
{
    if (pd) {
        printf("Name: %s, Men: %d, Women: %d\n", pd->name, pd->men, pd->women);
    }
}

void PrintPopulationData2(const PopulationData* pd, void* p)
{
    if (pd) {
        printf("Name: %s, Men: %d, Women: %d\n", pd->name, pd->men, pd->women);
    }
}

int CompareName(const PopulationData* pd1, const PopulationData* pd2)
{
    return strcmp(pd1->name, pd2->name) == 0;
}

List* CreateList(const char* fileName)
{
    FILE* f = OpenPopulationDataFile(DATA_FILE_NAME);
    if (f) {
        PopulationData pd;
        List* list = LstCreate();
        if (list) {
            int n = ReadPopulationData(f, &pd);
            while (n) {
                if (LstPushBack(list, &pd) == 0) {
                    printf("Adding data to the list failed\n");
                    LstDestroy(list);
                    break;
                }
                n = ReadPopulationData(f, &pd);
            }
            ClosePopulationDataFile(f);
            return list;
        }
    }
    return NULL;
}

void TestDeleteNodes(List* list)
{
    PopulationData pd;

    // deletes the head node
    strcpy(pd.name, "Jongnogu");
    ListNode* node = LstFindNode(list, &pd, CompareName);
    if (node) {
        LstDelete(list, node);
        printf("\n\nList after deleting Jongnogu\n");
        LstPrint(list, PrintPopulationData);
    }

    // deletes the tail node
    strcpy(pd.name, "Gangdonggu");
    node = LstFindNode(list, &pd, CompareName);
    if (node) {
        LstDelete(list, node);
        printf("\n\nList after deleting Gandonggu\n");
        LstPrint(list, PrintPopulationData);
    }

    // deletes a node in the middle
    strcpy(pd.name, "Eunpyeonggu");
    node = LstFindNode(list, &pd, CompareName);
    if (node) {
        LstDelete(list, node);
        printf("\n\nList after deleting Eunpyeonggu\n");
        LstPrint(list, PrintPopulationData);
    }
}

void TestInsertNodes(List* list)
{
    PopulationData pd;

    // Inserts in front of the head node
    LstInsertBefore(list, list->head, &PDs[0]);
    printf("\n\nList after inserting Jongnogu\n");
    LstPrint(list, PrintPopulationData);

    // Inserts after the tail node 
    LstInsertAfter(list, list->tail, &PDs[2]);
    printf("\n\nList after inserting Gangdonggu\n");
    LstPrint(list, PrintPopulationData);

    // Inserts in the middle
    strcpy(pd.name, "Nowongu");
    ListNode* node = LstFindNode(list, &pd, CompareName);
    if (node) {
        LstInsertAfter(list, node, &PDs[1]);
        printf("\n\nList after inserting Eunpyeonggu\n");
        LstPrint(list, PrintPopulationData);
    }
}

int main(void)
{
    // Constructs a list by reading data from a given file
    List* list = CreateList(DATA_FILE_NAME);
    if (list && LstEmpty(list) == 0) {
        // Output all elements of the list
        LstPrint(list, PrintPopulationData);
        // Deletes three nodes from the list and output the elements
        TestDeleteNodes(list);
        // Adds three deleted nodes back in to the list and output
        TestInsertNodes(list);     

        // Calculates men and women population in Seoul
        SUM_DATA sum = { 0, 0 };
        LstIterate(list, GetTotalPopulation, &sum);
        printf("Number of Men in Seoul: %d, Number of Women in Seoul: %d\n", sum.men, sum.women);

        // Output elements using ListIterate function
        printf("\nOutput elements using ListIterate function\n");
        LstIterate(list, PrintPopulationData2, NULL);

        // Test LstGetEntry()
        printf("\nOutput using LstGetEntry function\n");
        LstElement e;
        for (int i = 0; i < 25; i++) {
            LstGetEntry(list, i, &e);
            PrintPopulationData(&e);
        }

        // Test LstInsert()
        printf("\nOutput testing LstInsert function\n");
        List* list2 = LstCreate();
        if (list2) {
            for (int i = 0; i < 25; i++) {
                LstGetEntry(list, i, &e);
                LstInsert(list2, i, &e);
            }
        }
        for (int i = 0; i < 25; i++) {
            LstGetEntry(list2, i, &e);
            PrintPopulationData(&e);
        }

        printf("\nOutput testing LstInsert function 2\n");
        int entryNum[] = { 0, 1, 2, 1, 2, 4, 6, 1, 3, 7, 5, 0, 12, 1, 10, 3, 17, 15, 14, 13, 10, 12, 8, 14, 15 };
        List* list3 = LstCreate();
        if (list3) {
            for (int i = 0; i < 25; i++) {
                LstGetEntry(list, i, &e);
                LstInsert(list3, entryNum[i], &e);
            }
        }
        for (int i = 0; i < 25; i++) {
            LstGetEntry(list3, i, &e);
            PrintPopulationData(&e);
        }


        // Destroy the list
        LstDestroy(list);
        LstDestroy(list2);
        LstDestroy(list3);
    }
    else {
        printf("List is NULL or no data exists in the list\n");
    }
    return 0;
}

