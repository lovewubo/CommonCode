#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <time.h>


using namespace std;

struct shortArray
{
	int *pData;
	int nLength;

	shortArray()
	{
		pData = NULL;
		nLength = 0;
	}

	shortArray(int nSize)
	{
		nLength = nSize;
		pData = new int[nLength];
	}

	~shortArray()
	{
		if(NULL != pData)
		{
			delete []pData;
		}
		nLength = 0;
	}
};

bool fillRandomNum(shortArray *pArr);
bool mergeSort(shortArray *pShortArr[], int nSize, int nAllCount, int *pOutArr);
void printArray(int *pArr, int nSize);
void printArray(vector<int> &vec);
void bubbleSort(shortArray *pArr);
int testRoutine1();

int main(int argc, char *argv[])
{
  for(int i=0; i<3; i++)
  {
    testRoutine1();
  }
  return 0;
}

int testRoutine1()
{
	const int baseArraySize = 20000;
	const int arrCnt = 16;
	int allArrElementCnt = 0;

	shortArray *allArr[arrCnt];

	for(int i=0; i<arrCnt; i++)
	{
		int elementCount = baseArraySize + i;
		allArr[i] = new shortArray(elementCount);

		fillRandomNum(allArr[i]);
		//printArray(allArr[i]->pData, allArr[i]->nLength);

		bubbleSort(allArr[i]);//pre-sorting
		//printArray(allArr[i]->pData, allArr[i]->nLength);

		allArrElementCnt += elementCount;

		Sleep(100);//make different seed for srand()
	}

	//merge into one big array for sorting by stl
	vector<int> allArr_stl;
	for(int i=0; i<arrCnt; i++)
	{
		for(int j=0; j<allArr[i]->nLength; j++)
		{
			allArr_stl.push_back(allArr[i]->pData[j]);
		}
	}

	//printArray(allArr_stl);

	//alloc one big array for merge sort
	int *pAllArr_merge = new int[allArrElementCnt];

	//test begin
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;
	int durationMsec_stl = 0;
	int durationMsec_mine = 0;
	QueryPerformanceFrequency(&nFreq);

	//stl (quick sort)
	QueryPerformanceCounter(&nLast);

	sort(allArr_stl.begin(), allArr_stl.end());

	QueryPerformanceCounter(&nNow);

	durationMsec_stl = (int)((nNow.QuadPart - nLast.QuadPart) * 1000 / nFreq.QuadPart);
	printf("stl: %d(ms) ", durationMsec_stl);

	//printArray(allArr_stl);

	//merge sort
	QueryPerformanceCounter(&nLast);

	mergeSort(allArr, arrCnt, allArrElementCnt, pAllArr_merge);

	QueryPerformanceCounter(&nNow);

	durationMsec_mine = (int)((nNow.QuadPart - nLast.QuadPart) * 1000 / nFreq.QuadPart);
	printf("Mine: %d(ms)\n", durationMsec_mine);
	//test end

	//printArray(pAllArr_merge, allArrElementCnt);

	//get stl sort result and compare it to merge sort result
	int *pStlResult = new int[allArrElementCnt];
	for(int i=0; i<allArrElementCnt; i++)
	{
		pStlResult[i] = allArr_stl[i];
	}
	
	//just for confirmation
	if(0 != memcmp(pStlResult, pAllArr_merge, allArrElementCnt))
	{
		printf("error\n");
	}

	delete []pAllArr_merge;
	for(int i=0; i<arrCnt; i++)
	{
		delete allArr[i];
	}

	return 0;
}

bool fillRandomNum(shortArray *pArr)
{
	if(NULL == pArr)
	{
		return false;
	}

	//srand((unsigned)time(NULL));
	srand(GetTickCount());
	for(int i=0; i<pArr->nLength; i++)
	{
		pArr->pData[i] = rand();
	}
	return true;
}

bool mergeSort(shortArray *pShortArr[], int nSize, int nAllCount, int *pOutArr)
{
	if(NULL == pOutArr || 0 == nAllCount)
	{
		return false;
	}

	int *pIndex = new int[nSize];
	for(int i=0; i<nSize; i++)
	{
		pIndex[i] = 0;
	}

	int nStartIndex = 0;
	for(int i=0; i<nAllCount; i++)
	{
		int minArrIndex = -1;
		for(int j=0; j<nSize; j++)
		{
			if(pIndex[j] < pShortArr[j]->nLength)
			{
				if(minArrIndex == -1 || pShortArr[minArrIndex]->pData[pIndex[minArrIndex]] > pShortArr[j]->pData[pIndex[j]])
				{
					minArrIndex = j;
				}
			}
		}
		pOutArr[i] = pShortArr[minArrIndex]->pData[pIndex[minArrIndex]];
		pIndex[minArrIndex]++;
	}

	delete []pIndex;
	return true;
}


void bubbleSort(shortArray *pArr)
{
	int i,j;
	bool bok=false;//sentry

	for(i=0; i<pArr->nLength-1, bok!=true; i++)
	{
		bok = true;
		for(j=pArr->nLength-1; j>i; j--)
		{
			if(pArr->pData[j] < pArr->pData[j-1])
			{
				int temp = pArr->pData[j];
				pArr->pData[j] = pArr->pData[j-1];
				pArr->pData[j-1] = temp;
				bok = false;
			}
		}
	}
}

void printArray(int *pArr, int nSize)
{
	if(NULL == pArr || 0 == nSize)
	{
		return;
	}

	printf("info:\n");
	for(int i=0; i<nSize; i++)
	{
		printf("%d ", pArr[i]);
	}
	printf("\n");
}

void printArray(vector<int> &vec)
{
	if(vec.empty())
	{
		return;
	}

	vector<int>::iterator ite;
	printf("info:\n");
	for(ite = vec.begin(); ite != vec.end(); ++ite)
	{
		printf("%d ", *ite);
	}
	printf("\n");
}
