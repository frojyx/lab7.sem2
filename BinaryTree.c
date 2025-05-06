#include "functions.h"

BinaryTree* CreateBinaryTree(int num)
{
	BinaryTree* t = malloc(sizeof(BinaryTree));
	t->right = t->left=NULL;
	t->value = num;
	return t;
}

BinaryTree* AddNode(BinaryTree* t,int num)
{
	if (t == NULL)
	{
		t = CreateBinaryTree(num);
		return t;
	}
	if (num >= t->value)
		t->right =AddNode(t->right, num);
	else
		t->left =AddNode(t->left, num);
	return t;
}

BinaryTree* findNodeByValue(BinaryTree* root, int value) {
	if (root == NULL || root->value == value) return root;
	
	BinaryTree* tmp;
	if (tmp = findNodeByValue(root->left, value) != NULL) return tmp;
	if (tmp = findNodeByValue(root->right, value) != NULL) return tmp;
	return NULL;
}

BinaryTree* replaceNode(BinaryTree* t, int num)
{
	BinaryTree* Del, * Prev_Del, * R, * Prev_R;
	Del = t; 
	Prev_Del = NULL;
	while (Del != NULL && Del->value != num) {
		Prev_Del = Del;
		if (num < Del->value)  Del = Del->left;
		else Del = Del->right;
	}
	if (Del == NULL) {        
		puts("\n Такого элемента нету.\n");
		return t;
	}
	if (Del->right == NULL) R = Del->left;
	else
		if (Del->left == NULL) R = Del->right;
		else {
			Prev_R = Del;
			R = Del->left;
			while (R->right != NULL) {
				Prev_R = R;
				R = R->right;
			}
			if (Prev_R == Del)
				R->right = Del->right;
			else {
				R->right = Del->right;
				Prev_R->right = R->left;
				R->left = Prev_R;
			}
		}
	if (Del == t) t = R;
	
	else
		if (Del->value < Prev_Del->value)
			Prev_Del->left = R;	 
		else
			Prev_Del->right = R;  
	free(Del);
	return t;
}

Queue enqueueObject(Queue queue, BinaryTree* node) {
	QueueObject* tmp = (QueueObject*)malloc(sizeof(QueueObject));
	tmp->node = node;
	tmp->next = NULL;
	if (queue.begin == NULL) {
		queue.begin = queue.end = tmp;
	}
	else {
		queue.end->next = tmp;
		queue.end = tmp;
	}
	return queue;
}

Queue popObject(Queue queue) {
	if (queue.begin == queue.end) {
		free(queue.begin);
	}
	QueueObject* tmp = queue.begin;
	queue.begin = queue.begin->next;
	free(tmp);
	return queue;
}

Queue initQueue() {
	Queue queue;
	queue.begin = NULL;
	queue.end = NULL;
	return queue;
}

int findGeneralElements(BinaryTree* root) {
	Queue queue, tmp_queue;
	
	queue = initQueue();
	queue = fillQueueWithTreeNodes(queue, root);
	while (queue.begin != queue.end) {
		tmp_queue = queue;
		while (tmp_queue.begin != tmp_queue.end) {
			if (queue.begin->node != tmp_queue.begin->node &&
				queue.begin->node->value == tmp_queue.begin->node->value) return 1;
			tmp_queue.begin = tmp_queue.begin->next;
		}
		queue = popObject(queue);
	}
	return 0;
}

Queue fillQueueWithTreeNodes(Queue queue, BinaryTree* node) {
	if (node == NULL) return queue;

	if (node->left != NULL) {
		queue = fillQueueWithTreeNodes(queue, node->left);
	}
	if (node->right != NULL) {
		queue = fillQueueWithTreeNodes(queue, node->right);
	}
	queue = enqueueObject(queue, node);
	return queue;
}

void FreeTree(BinaryTree* t) {
	if (t == NULL) return;
	FreeTree(t->left);
	FreeTree(t->right);
	free(t);
}

void MenuForTree()
{
	int num=0;
	int value = 0;
	BinaryTree* t = NULL;
	int answer;

	printf("Выберите действие.");
	printf("\n+================================+\n1.Ввод элемент дерева.\n2.Удаление элемента из дерева.\n3.Визуализация дерева.\n4.Проверка на равенство элементов.\n5.Очистка консоли.\n6.Конец задания.\n+================================+\n");
	do {
		answer = 0;
		printf("\nВыберите пункт из меню.\n\n");
		while (answer < '1' || answer > '6') answer = _getch();
		if (answer == '1') {
			printf("Введите элемент:\n");
			num = InputNum();
			t=AddNode(t, num);
		}
		else if (answer == '2') {
			printf("Введите элемент:\n");
			num = InputNum();
			t = replaceNode(t, num);
		}
		else if (answer == '3') {
			showBinaryTree(t, 0);
		}
		else if (answer == '4') {
			if(findGeneralElements(t) == 1) printf("В вашей дереве есть совпадающие элементы.\n");
			else printf("В вашей дереве нету совпадающих элементов.\n");
		}
		else if (answer == '5')
		{
			system("cls");
			printf("\n+================================+\n1.Ввод элемент дерева.\n2.Удаление элемента из дерева.\n3.Визуализация дерева.\n4.Проверка на равенство элементов.\n5.Очистка консоли.\n6.Конец задания.\n+================================+\n");
		}
	} while (answer != '6');
	FreeTree(t);
}

void showBinaryTree(BinaryTree* node, int level) {
	if (node != NULL) {
		showBinaryTree(node->right, level + 1);
		for (int ind = 0; ind < level; ind++) printf("	");
		printf("%d\n", node->value);
		showBinaryTree(node->left, level + 1);
	}
}
