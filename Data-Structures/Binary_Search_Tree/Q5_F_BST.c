//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode
{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode; // You should not change the definition of BSTNode

typedef struct _stackNode
{
	BSTNode *data;
	struct _stackNode *next;
} StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
} Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode *removeNodeFromTree(BSTNode *root, int value);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	// Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root)
{
	if (root == NULL)
		return;

	Stack s1, s2;
	s1.top = NULL;
	s2.top = NULL;

	push(&s1, root);

	while (s1.top != NULL)
	{
		BSTNode *cur = pop(&s1);

		push(&s2, cur);

		if (cur->left != NULL)
			push(&s1, cur->left);
		if (cur->right != NULL)
			push(&s1, cur->right);
	}

	while (s2.top != NULL)
	{
		BSTNode *cur = pop(&s2);
		printf(" %d", cur->item);
	}
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
BSTNode *removeNodeFromTree(BSTNode *root, int value)
{
	// 1) 기저 조건: 빈 서브트리이면 그대로 반환
	if (root == NULL)
		return root;
	// 2) 찾기 단계: 삭제할 값이 현재 노드값보다 작으면 왼쪽, 크면 오른쪽으로 재귀
	if (root->item > value)									// 노드의 값 > 삭제할 값
		root->left = removeNodeFromTree(root->left, value); // 왼쪽 탐색
	else if (root->item < value)							// 노드의 값 < 삭제할 값
		root->right = removeNodeFromTree(root->right, value);
	// 3) 여기서 root가 삭제할 노드인 경우
	else
	{
		// 3-1) 삭제대상 노드가 자식이 없는 경우 (leaf) => 그냥 해제
		if (root->left == NULL && root->right == NULL)
		{
			free(root);
			return NULL;
		}
		// 3-2) 삭제대상 노드가 자식이 1명만 있는 경우 => 삼할 연산자로 한방에 가능하지 않아?
		else if (root->left == NULL || root->right == NULL)
		{
			// left || right 중 NULL이 아닌 값을 temp에 보관
			BSTNode *temp = (root->left != NULL) ? root->left : root->right;
			free(root);
			return temp;
		}
		else
		{
			// 3-3) 삭제 대상의 자손이 2명인 경우
			// 삭제 대상의 가장 작은값을 오른쪽 맨아래 자손에서 찾기
			BSTNode *succ = root->right;
			while (succ->left != NULL)
				succ = succ->left;

			// 가장 작은값을 삭제대상 노드에 복사
			root->item = succ->item;

			// 마지막 succ노드의 자손도 있을 수 있기에 재귀
			root->right = removeNodeFromTree(root->right, succ->item);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value)
{
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL)
		{
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value > (*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode *node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}

BSTNode *pop(Stack *s)
{
	StackNode *temp, *t;
	BSTNode *ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode *peek(Stack *s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
