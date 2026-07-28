#include <stdio.h>
#include <iostream>
#include <crtdbg.h> 

using namespace std;

struct SNode {
	int nData;
	SNode* pNext;
};

SNode* CreateNode(SNode* pNode, int data);
SNode* FindNodeData(SNode* pStart, int data); 
void DeleteNodeData(SNode* pStart, int del); 
void PrintLinkedList(SNode* pStart); 
void DeleteLinkedList(SNode* pStart); 


void main()
{
	SNode* pFront = NULL;
	SNode* pFirst = NULL;
	SNode* pEnd = NULL;

	CreateNode(pFront, 10);
}

SNode* CreateNode(SNode* pNode, int data)
{
	SNode* pTemp = NULL;

	pTemp = new SNode();
	pTemp->nData = data;

	pTemp->pNext = NULL;

	if (pNode != NULL)
		pNode->pNext = pTemp;

	return  pTemp;
}

SNode* FindNodeData(SNode* pStart, int data)
{
	SNode* pNode = pStart;

	while (pNode)
	{
		if (pNode->nData == data)
			break;
		else
			pNode = pNode->pNext;

		if (pNode == NULL)
			break;
	}

	return pNode;
}

void DeleteNodeData(SNode* pStart, int del)
{
	SNode* pPre = NULL;
	SNode* pNode = pStart;

	pPre = FindNodeData(pNode, del);

	while (pNode)
	{
		if (pNode->pNext == pPre)
		{
			pNode->pNext = pPre->pNext;
			delete pPre;
			break;
		}
		else
			pNode = pNode->pNext;
	}
}

void PrintLinkedList(SNode* pStart)
{
	SNode* pNode = pStart;
	printf("data:");
	while (pNode)
	{
		printf("%d", pNode->nData);
		pNode = pNode->pNext;

		if (pNode != NULL)
			printf(",");

		/*if (pNode == pStart)
			break;*/

	}
	printf("\n");
}

void DeleteLinkedList(SNode* pStart)
{
	SNode* pNode = pStart;
	SNode* pDel = NULL;

	while (pNode)
	{
		pDel = pNode;
		pNode = pNode->pNext;
		delete pDel;
	}
}

