/* Created by Justyna Gorczyca on 12.03.18. */

#ifndef UNTITLED_LIBRARY_H
#define UNTITLED_LIBRARY_H

/* ----------------------block functions---------------------- */
typedef struct
{
    char* content;
    int asciiValue;
} block;

block* createBlock(int blockSize, char* content);
int getAsciiSum(char* word);
void displayContent(block* block);
int properIndex(int elementsNumber, int index);
int getBlockAsciiValue(block* block);
block* getBlock(block* block);

/* ----------------------dynamic table functions---------------------- */
void** createDynamicTable(int elementsNumber);
void** insertBlockToDynamicTable(void** dynamicTable, int elementsNumber, int index, int blockSize, char* content);
void displayDynamicTableContent(int elementsNumber, void** dynamicTable);
int findBlockDynamic(char* contentToFind, void** dynamicTable, int elementsNumber);
void** deleteBlockDynamic(void** dynamicTable, int index, int elementsNumber);
void deleteDynamicTable(void** dynamicTable, int elementsNumber);

/* ----------------------static table functions---------------------- */
/*extern void* staticTable[1000];*/

void createStaticTable(int elementsNumber);
void insertBlockToStaticTable(int elementsNumber, int index, int blockSize, char* content);
void displayStaticTableContent(int elementsNumber);
int findBlockStatic(char* contentToFind, int elementsNumber);
void deleteBlockStatic(int index, int elementsNumber);
void deleteStaticTable(int elementsNumber);

#endif /* UNTITLED_LIBRARY_H */
