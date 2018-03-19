/* Created by Justyna Gorczyca on 13.03.18. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Library.h"

void* staticTable[1000];

/* ----------------------block functions---------------------- */
block* createBlock(int blockSize, char* content) {
    block *newBlock = (block *) malloc(sizeof(block));
    newBlock->content = (char *) malloc(blockSize * sizeof(char)+1);
    memcpy(newBlock -> content, content, (size_t )blockSize);
    newBlock->asciiValue = -1;
    return newBlock;
}

int getAsciiSum(char* word)
{
    int sum = 0;
    int len = (int)strlen(word);
    int i;
	for(i = 0; i < len; i++)
    {
        int x = (int)word[i];
        sum += x;
    }
    return sum;
}

int properIndex(int elementsNumber, int index)
{
    if(index >= elementsNumber) {
        printf("\nIndex is to high, block cannot be added.");
        return 0;
    }
    if(index < 0) {
        printf("\nIndex is to low, block cannot be added.");
        return 0;
    }
    return 1;
}

void displayContent(block* block)
{
    if (block == NULL)
        return;
    printf("content: %s", block->content);
    printf("  ascii value: %d", block->asciiValue);
}


int getBlockAsciiValue(block* block)
{
    if(block -> asciiValue == -1)
        block -> asciiValue = getAsciiSum(block -> content);
    return block -> asciiValue;
}


block* getBlock(block* block)
{
    return block;
}

/* ----------------------dynamic table functions---------------------- */
void** createDynamicTable(int elementsNumber)
{
    void** dynamicTable = calloc((size_t )elementsNumber, sizeof(char*));
	int i;    
	for(i = 0; i < elementsNumber; i++)
        dynamicTable[i] = NULL;
    return dynamicTable;
}


void** insertBlockToDynamicTable(void** dynamicTable, int elementsNumber, int index,
                                 int blockSize, char* content)
{
    if(properIndex(elementsNumber,index) == 0)
        return dynamicTable;

    block* blockToInsert = createBlock(blockSize,content);
    if(dynamicTable[index] == NULL)
        dynamicTable[index] = blockToInsert;
    else {
        printf("\nContent of block %d will be overwritten.",index);
        dynamicTable[index] = blockToInsert;
    }
    return dynamicTable;
}


void displayDynamicTableContent(int elementsNumber, void** dynamicTable)
{
    printf("\n \nDYNAMIC TABLE");
	int i;    
	for(i = 0; i < elementsNumber; i++)
    {
        printf("\ntab[%d] -->  ",i);
        if(dynamicTable[i] != NULL)
            displayContent(dynamicTable[i]);
        else
            printf("NULL");
    }
}

int findBlockDynamic(char* contentToFind, void** dynamicTable, int elementsNumber)
{
    int asciiSum = getAsciiSum(contentToFind);
    int currentAsciiSum;
    int difference = 100000;
    int currentDifference;
    int indexToReturn = -1; 
	int i; 
	for(i = 0; i < elementsNumber; i++)
    {
        if(dynamicTable[i] == NULL)
            continue;

        currentAsciiSum = getBlockAsciiValue(dynamicTable[i]);
        currentDifference = abs(currentAsciiSum - asciiSum);
        if(currentDifference < difference) {
            difference = currentDifference;
            indexToReturn = i;
        }
    }
    return indexToReturn;
}

void** deleteBlockDynamic(void** dynamicTable, int index, int elementsNumber)
{
    if(properIndex(elementsNumber,index) == 0)
        return dynamicTable;

    if(dynamicTable[index] == NULL)
        return dynamicTable;

    block* block = getBlock(dynamicTable[index]);
    free(block -> content);
    block -> content = NULL;
    free(block);
    dynamicTable[index] = NULL;
    return dynamicTable;
}


void deleteDynamicTable(void** dynamicTable, int elementsNumber)
{
	int i;
    for(i = 0; i < elementsNumber; i++)
        deleteBlockDynamic(dynamicTable, i, elementsNumber);
    free(dynamicTable);
    /* dynamicTable = NULL; */
}

/* ----------------------static table functions---------------------- */

void createStaticTable(int elementsNumber)
{
    if(elementsNumber > 1000)
    {
        printf("Max number of elements is 1000");
    }
	int i;
    for(i = 0; i < elementsNumber; i++)
        staticTable[i] = NULL;
}


void insertBlockToStaticTable(int elementsNumber, int index, int blockSize, char* content)
{
    if(properIndex(elementsNumber,index) == 0)
        return;

    block* blockToInsert = createBlock(blockSize,content);
    if(staticTable[index] == NULL)
        staticTable[index] = blockToInsert;
    else {
        printf("\nContent of block %d will be overwritten.",index);
        deleteBlockStatic(index, elementsNumber);
		staticTable[index] = blockToInsert;
    }
}


void displayStaticTableContent(int elementsNumber)
{
    printf("\n \nSTATIC TABLE");
	int i;    
	for(i = 0; i < elementsNumber; i++)
    {
        printf("\ntab[%d] -->  ",i);
        if(staticTable[i] != NULL)
            displayContent(staticTable[i]);
        else
            printf("NULL");
    }
}


int findBlockStatic(char* contentToFind, int elementsNumber)
{
    int asciiSum = getAsciiSum(contentToFind);
    int currentAsciiSum;
    int difference = 100000;
    int currentDifference;
    int indexToReturn = -1; 
	int i; 
	for(i = 0; i < elementsNumber; i++)
    {
        if(staticTable[i] == NULL)
            continue;

        currentAsciiSum = getBlockAsciiValue(staticTable[i]);
        currentDifference = abs(currentAsciiSum - asciiSum);
        if(currentDifference < difference) {
            difference = currentDifference;
            indexToReturn = i;
        }
    }
    return indexToReturn;
}

void deleteBlockStatic(int index, int elementsNumber)
{
    if(properIndex(elementsNumber,index) == 0)
        return;

    if(staticTable[index] == NULL)
        return;

    block* block = getBlock(staticTable[index]);
    free(block -> content);
    block -> content = NULL;
    free(block);staticTable[index] = NULL;
    
}

void deleteStaticTable(int elementsNumber)
{
	int i;
    for(i = 0; i < elementsNumber; i++)
        deleteBlockStatic(i,elementsNumber);
}
