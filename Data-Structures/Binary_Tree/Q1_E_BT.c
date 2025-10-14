//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode; // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode
{
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    StackNode *top;
} Stack;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int identical(BTNode *tree1, BTNode *tree2);

BTNode *createBTNode(int item);

BTNode *createTree();
void push(Stack *stk, BTNode *node);
BTNode *pop(Stack *stk);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c, s;
    char e;
    BTNode *root1, *root2;

    root1 = NULL;
    root2 = NULL;
    c = 1;

    printf("1: Create a binary tree1.\n");
    printf("2: Create a binary tree2.\n");
    printf("3: Check whether two trees are structurally identical.\n");
    printf("0: Quit;\n");

    while (c != 0)
    {
        printf("Please input your choice(1/2/3/0): ");
        if (scanf("%d", &c) > 0)

        {

            switch (c)
            {
            case 1:
                removeAll(&root1);
                printf("Creating tree1:\n");
                root1 = createTree();
                printf("The resulting tree1 is: ");
                printTree(root1);
                printf("\n");
                break;
            case 2:
                removeAll(&root2);
                printf("Creating tree2:\n");
                root2 = createTree();
                printf("The resulting tree2 is: ");
                printTree(root2);
                printf("\n");
                break;
            case 3:
                s = identical(root1, root2);
                if (s)
                {
                    printf("Both trees are structurally identical.\n");
                }
                else
                {
                    printf("Both trees are different.\n");
                }
                removeAll(&root1);
                removeAll(&root2);
                break;
            case 0:
                removeAll(&root1);
                removeAll(&root2);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
        }
        else
        {
            scanf("%c", &e);
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int identical(BTNode *tree1, BTNode *tree2)
{
    // 예외 조건1 : 두 트리 모두 빈트리
    if (tree1 == NULL && tree2 == NULL)
        return 1;
    // 예외 조건2 : 한 쪽만 빈트리 일 시,
    if (tree1 == NULL || tree2 == NULL)
        return 0;
    // 해당 노드 같 && 왼 노드 같 && 오른쪽 노드 같 => return 1
    if ((tree1->item == tree2->item) && (identical(tree1->left, tree2->left)) && (identical(tree1->right, tree2->right)))
        return 1;
    // if에 걸리지 않았을 시, => return 0
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item)
{
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////

BTNode *createTree()
{
    Stack stk;
    BTNode *root, *temp;
    char s;
    int item;

    stk.top = NULL;
    root = NULL;

    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    // 사용자가 정수 입력 → 변환 성공 → 1 반환
    //     (정수 하나 제대로 읽어왔으니까)

    // 사용자가 문자를 입력 (예: a) → 변환 실패 → 0 반환
    //     (%d 변환 불가라 아무것도 못 읽음)

    // 입력 스트림이 끝났거나 에러 발생 → EOF (-1) 반환
    if (scanf("%d", &item) > 0)
    {
        root = createBTNode(item);
        push(&stk, root);
    }
    else
    {
        scanf("%c", &s);
    }

    while ((temp = pop(&stk)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if (scanf("%d", &item) > 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c", &s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if (scanf("%d", &item) > 0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c", &s);
        }

        if (temp->right != NULL)
            push(&stk, temp->right);
        if (temp->left != NULL)
            push(&stk, temp->left);
    }
    return root;
}

void push(Stack *stk, BTNode *node)
{
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if (temp == NULL)
        return;
    temp->btnode = node;
    if (stk->top == NULL)
    {
        stk->top = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = stk->top;
        stk->top = temp;
    }
}

BTNode *pop(Stack *stk)
{
    StackNode *temp, *top;
    BTNode *ptr;
    ptr = NULL;

    top = stk->top;
    if (top != NULL)
    {
        temp = top->next;
        ptr = top->btnode;

        stk->top = temp;
        free(top);
        top = NULL;
    }
    return ptr;
}

// 중위 순회 출력
void printTree(BTNode *node)
{
    if (node == NULL)
        return;

    printTree(node->left);
    printf("%d ", node->item);
    printTree(node->right);
}
// 후위 순회 메모리 해제

void removeAll(BTNode **node)
{
    if (*node != NULL)
    {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
