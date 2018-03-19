/* Created by Justyna Gorczyca on 12.03.18. */

#include <time.h>
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>
#include "Library.h"

#define BUFF_SIZE 120

int elementsNumber;
int blockSize;
int allocation;
int function1;
int function2;
int function3;

char buffer[BUFF_SIZE];
void* staticTable[1000];
void** dynamicTable;
FILE* in;
FILE* out;
clock_t clk;
struct tms startTime, endTime;

void createStaticTableAndFill();
void findElementAndDeleteStatic();
void addAndDeleteBlocksStatic();
void addAndDeleteAlternatelyBlocksStatic();

void createDynamicTableAndFill();
void findElementAndDeleteDynamic();
void addAndDeleteBlocksDynamic();
void addAndDeleteAlternatelyBlocksDynamic();

char* getContentFromFile();

void saveResults(FILE* out, clock_t clk,struct tms startTime,struct tms endTime, char* operationName)
{
    fprintf(out,"%s\nreal\t%fus\nuser\t%fus\nsys\t%fus\n...................\n", operationName,((double)clk*1000000)/(CLOCKS_PER_SEC),((double)(endTime.tms_utime - startTime.tms_utime)*1000000)/CLOCKS_PER_SEC,((double)(endTime.tms_stime - startTime.tms_stime)*1000000)/CLOCKS_PER_SEC);
}

int processArguments(int argc, char* argv[]){
    //check arguments number
    if(argc != 7)
    {
        printf("Wrong arguments number, should be 7: \n"
                       "   [1] file name \n"
                       "   [2] number of elements in table: [0;1000] \n"
                       "   [3] block size \n"
                       "   [4] allocation: 0 - static, 1 - dynamic \n"
                       "   [5] function 1, should be 1 - create table\n"
                       "   [6] function 2 \n"
                       "   [7] function 3 \n"
                       "\nPossible functions: \n"
                       "   1: create table \n"
                       "   2: find element and delete \n"
                       "   3: add and then delete n blocks \n"
                       "   4: add and delete alternately n blocks\n" );
        return 0;
    }

    printf("\nliczba argumentów: %d ", argc);
    printf("\nnazwa programu: %s",argv[0]);
    printf("\nliczba el w tablicy: %s",argv[1]);
    printf("\nrozmiar bloku: %s",argv[2]);
    printf("\nsposób alokacji: %s",argv[3]);
    printf("\nfunkcja 1: %s",argv[4]);
    printf("\nfunkcja 2: %s",argv[5]);
    printf("\nfunkcja 3: %s",argv[6]);
    

    //check elementsNumber
    int tmp = atoi(argv[1]);
    if(tmp > 0 && tmp < 1000)
        elementsNumber = tmp;
    else
    {
        printf("\nWrong elements number.");
        return 0;
    }

    //check blockSize
    tmp = atoi(argv[2]);
    if(tmp > 0)
        blockSize = tmp;
    else
    {
        printf("\nWrong block size.");
        return 0;
    }

    //check allocation way
    tmp = atoi(argv[3]);
    if(tmp == 0 || tmp == 1)
        allocation = tmp;
    else
    {
        printf("\nWrong allocation number, should be 0 or 1.");
        return 0;
    }

    //check function 1
    tmp = atoi(argv[4]);
    if(tmp == 1)
        function1 = tmp;
    else
    {
        printf("\nWrong function number, should be 1.");
        return 0;
    }

    //check function 2
    tmp = atoi(argv[5]);
    if(tmp == 1 || tmp == 2 || tmp == 3 || tmp == 4)
        function2 = tmp;
    else
    {
        printf("\nWrong function number, shoud be [1;4].");
        return 0;
    }

    //check function 3
    tmp = atoi(argv[6]);
    if(tmp == 1 || tmp == 2 || tmp == 3 || tmp == 4)
        function3 = tmp;
    else
    {
        printf("\nWrong function number, shoud be [1;4].");
        return 0;
    }

    return 1;
}

void callFunction(int functionNumber)
{
    if(allocation == 0) //static
    {
        switch(functionNumber)
        {
            case 1: createStaticTableAndFill();
                break;
            case 2: findElementAndDeleteStatic();
                break;
            case 3: addAndDeleteBlocksStatic();
                break;
            case 4: addAndDeleteAlternatelyBlocksStatic();
                break;
            default:
                break;
        }
    }

    if(allocation == 1) //dynamic
    {
        switch(functionNumber)
        {
            case 1: createDynamicTableAndFill();
                break;
            case 2: findElementAndDeleteDynamic();
                break;
            case 3: addAndDeleteBlocksDynamic();
                break;
            case 4: addAndDeleteAlternatelyBlocksDynamic();
            default:
                break;
        }
    }
}

void createStaticTableAndFill()
{
	times(&startTime);
    clk = clock();

	createStaticTable(elementsNumber);
    printf("\nStatic table is created, size: %d.",elementsNumber);

	int i = 0;
	while(i < elementsNumber)
	{
		char* contentToInsert = getContentFromFile();
		insertBlockToStaticTable(elementsNumber, i, blockSize, contentToInsert);
		i++;			
	}
	//displayStaticTableContent(elementsNumber);
    printf("\nTable filled with blocks, blocks size: %d.",blockSize);

	clk = clock() - clk;
    times(&endTime);
	saveResults(out,clk,startTime,endTime,"create static table and then fill");
}

void findElementAndDeleteStatic()
{   
	times(&startTime);
    clk = clock();

	int index;
	char* contentToFind = "abcd";
	printf("\nAscii sum of 'abcd': %d",getAsciiSum(contentToFind));
	index = findBlockStatic(contentToFind,elementsNumber);
	printf("\nFound index: %d\n",index);
	displayContent(staticTable[index]);
	deleteBlockStatic(index, elementsNumber);
	//displayStaticTableContent(elementsNumber);
	printf("\nElement similar to 'abcd' found and deleted");

	clk = clock() - clk;
    times(&endTime);
	saveResults(out,clk,startTime,endTime,"find element in static table and delete it");
}

void addAndDeleteBlocksStatic()
{
	times(&startTime);
    clk = clock();
	
	int half = elementsNumber / 2;
	for(int i = 1; i <= half; i++)
	{
		deleteBlockStatic(elementsNumber - i, elementsNumber);
	}
	//displayStaticTableContent(elementsNumber);
	printf("\n%d elements deleted from table",half);

	int i = 1;
	while(i <= half)
	{
		char* contentToInsert = getContentFromFile();	
		insertBlockToStaticTable(elementsNumber, elementsNumber - i, blockSize, contentToInsert);
		i++;			
	}
	//displayStaticTableContent(elementsNumber);
    printf("\n%d elements added to table.",half);

	clk = clock() - clk;
    times(&endTime);
	saveResults(out,clk,startTime,endTime,"delete and add blocks to static table");
}

void addAndDeleteAlternatelyBlocksStatic()
{
	times(&startTime);
    clk = clock();

	printf("\nHalf of all blocks is deleted and then added alternately.");
	int i = 0;
	while(i < elementsNumber)
	{
		//printf("\nBlock %d deleted.",i);
		deleteBlockStatic(i, elementsNumber);
		char* contentToInsert = getContentFromFile();	
		//printf(" New content: '%s' inserted.",contentToInsert);
		insertBlockToStaticTable(elementsNumber, i, blockSize, contentToInsert);
		i++;
		i++;
	}

	clk = clock() - clk;
    times(&endTime);
	saveResults(out,clk,startTime,endTime,"delete and then add alternetely blocks to static table");
}

void createDynamicTableAndFill()
{
	times(&startTime);
    clk = clock();

    dynamicTable = createDynamicTable(elementsNumber);
	printf("\nDynamic table is created, size: %d.", elementsNumber);

	int i = 0;
	while(i < elementsNumber)
	{
		char* contentToInsert = getContentFromFile();
		insertBlockToDynamicTable(dynamicTable,elementsNumber,i ,blockSize, contentToInsert);
		i++;			
	}
	//displayDynamicTableContent(elementsNumber,dynamicTable);
    printf("\nTable filled with blocks, blocks size: %d.",blockSize);

	clk = clock() - clk;
    times(&endTime);
	saveResults(out,clk,startTime,endTime,"create dynamic table and then fill");
}

void findElementAndDeleteDynamic()
{  
	times(&startTime);
    clk = clock();

	int index;
	char* contentToFind = "abcd";
	printf("\nAscii sum of 'abcd': %d",getAsciiSum(contentToFind));
	index = findBlockDynamic(contentToFind,dynamicTable, elementsNumber);
	printf("\nFound index: %d\n",index);
	displayContent(dynamicTable[index]);
	deleteBlockDynamic(dynamicTable, index, elementsNumber);
	//displayDynamicTableContent(elementsNumber, dynamicTable);
	printf("\nElement similar to 'abcd' found and deleted");

	clk = clock() - clk;
    times(&endTime);
	saveResults(out,clk,startTime,endTime,"find element in dynamic table and delete it");
}

void addAndDeleteBlocksDynamic()
{
	times(&startTime);
    clk = clock();
	
	int half = elementsNumber/2; 
    for(int i = 1; i <= half; i++)
	{
		deleteBlockDynamic(dynamicTable, elementsNumber - i, elementsNumber);
	}
	//displayDynamicTableContent(elementsNumber,dynamicTable);
	printf("\n%d elements deleted from table",half);

	int i = 1;
	while(i <= half)
	{
		char* contentToInsert = getContentFromFile();	
		insertBlockToDynamicTable(dynamicTable, elementsNumber, elementsNumber - i, blockSize, contentToInsert);
		i++;			
	}
	//displayDynamicTableContent(elementsNumber,dynamicTable);
    printf("\n%d elements added to table.",half);

	clk = clock() - clk;
    times(&endTime);
	saveResults(out,clk,startTime,endTime,"delete and add blocks to dynamic table");
}

void addAndDeleteAlternatelyBlocksDynamic()
{
	times(&startTime);
    clk = clock();

	printf("\nHelf of all blocks is deleted and then added alternately.");
    int i = 0;
	while(i < elementsNumber)
	{
		//printf("\nBlock %d deleted.",i);
		deleteBlockDynamic(dynamicTable, i, elementsNumber);
		char* contentToInsert = getContentFromFile();	
		//printf(" New content: '%s' inserted.",contentToInsert);
		insertBlockToDynamicTable(dynamicTable, elementsNumber, i, blockSize, contentToInsert);
		i++;
		i++;
	}

	clk = clock() - clk;
    times(&endTime);
	saveResults(out,clk,startTime,endTime,"delete and then add alternetely blocks to dynamic table");
}

char* getContentFromFile()
{
	if(feof(in)) 
		return NULL;
	if(fgets(buffer,120,in) == NULL) 
		return NULL;
	else
		return buffer;
}

int main(int argc, char* argv[])
{
    if(processArguments(argc,argv) == 0)
        return 0;

	in = fopen("MOCK_DATA.txt","r");
	out = fopen("result2.txt","w");
	if(in == NULL || out == NULL)
	{
		perror("\nError.");
		return 0;
	}
	else
	{
		/*If you want to update result file uncomment below code*/
		/*
    	fprintf(out,"STATIC TABLE\n");
		allocation = 0;
		callFunction(1);
    	callFunction(2);
    	callFunction(3);
    	callFunction(4);
		deleteStaticTable(elementsNumber);

    	fprintf(out,"\nDYNAMIC TABLE\n");
		allocation = 1;
    	callFunction(1);
    	callFunction(2);
    	callFunction(3);
    	callFunction(4);
		deleteDynamicTable(dynamicTable, elementsNumber);
		*/
		
		printf("\n\n---FUNCTION1---");
    	callFunction(function1);
    	printf("\n\n---FUNCTION2---");
    	callFunction(function2);
    	printf("\n\n---FUNCTION3---");
    	callFunction(function3);

		printf("\n\nTable deleted");
		if(allocation == 0)
			deleteStaticTable(elementsNumber);
		else
			deleteDynamicTable(dynamicTable, elementsNumber);
		
		printf("\n");
	}
   	fclose(in);
	fclose(out);
    return 0;
}
