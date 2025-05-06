#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <limits.h>	

#define ENTER 13        
#define INT_LIMIT 13   

typedef struct BinaryTree{
	int value;
	struct BinaryTree* right;
	struct BinaryTree* left;
}BinaryTree;

typedef struct QueueObject {
	BinaryTree* node;
	struct QueueObject* next;
}QueueObject;

typedef struct {
	QueueObject* begin;
	QueueObject* end;
}Queue;

BinaryTree* CreateBinaryTree(int num);
BinaryTree* AddNode(BinaryTree* t, int num);
void MenuForTree();
void FreeTree(BinaryTree* t);
int myIsDigit(char symbol);
int InputNum();
void showBinaryTree(BinaryTree* node, int level);
BinaryTree* findNodeByValue(BinaryTree* root, int value);
BinaryTree* replaceNode(BinaryTree* t, int num);
Queue enqueueObject(Queue queue, BinaryTree* node);
Queue popObject(Queue queue);
Queue fillQueueWithTreeNodes(Queue queue, BinaryTree* node);
int findGeneralElements(BinaryTree* root);
