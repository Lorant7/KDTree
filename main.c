#include <stdio.h>
#include <stdlib.h>

#define K 2

// Data strucutre for a node in a 2D Tree
typedef struct KDNode
{
    // Array to hold all the dimensions of the data points
    int point[K];

    // Pointers to the left and right nodes of the node in the tree
    struct KDNode *left;
    struct KDNode *right;
} Node;

// Node initializer (this does not add it to the tree, it simply creates the new node)
Node *newNode(int *data)
{
    Node *nNode = (Node *)malloc(sizeof(Node));

    for (int i = 0; i < K; i++)
    {
        (nNode->point[i]) = data[i];
    }

    nNode->left = NULL;
    nNode->right = NULL;

    return nNode;
}

// Data strucutre for the kd tree
// for now it just holds the root of the tree (might want to add other vairables such as
// the cound of nodes on each side to check if it balanced, etc)
typedef struct kdTree
{
    Node *root;
    int nodeCount;

} Tree;

Tree *newTree(void)
{
    Tree *nTree = (Tree *)malloc(sizeof(Tree));
    nTree->root = NULL;

    nTree->nodeCount = 0;

    return nTree;
}

// Remove a node from the tree
// TODO: need to find a heuristic that when a node is removed the tree continues to be balanced
void removeNode(Node *node)
{
    node->right = NULL;
    node->left = NULL;
    free(node->point);
}

// Function that adds the given node to the tree
// TODO: figure out if you can add nodes in a way such that the tree stays balanced
// (I don't think so but, there might be a better way to do it instead of doing it like a simple binar tree.)
Node *addNode(Node *newNode, Tree *tree)
{

    int i = 0;
    int found = 0;
    int left = 1;
    Node *current = tree->root;
    Node *prev = NULL;

    // You can probably generalize these if statments with the array you use
    while (!found)
    {
        // TODO: there is no root (OR WE FOUND WHERE TO PLACE IT), make the given node the root
        if (current == NULL)
        {
            found = 1;
            if (prev == NULL)
            {
                tree->root = newNode;
            }
            else
            {

                if (left)
                {
                    prev->left = newNode;
                }
                else
                {
                    prev->right = newNode;
                }
            }
        }
        else
        {
            // if the number is even check x, if the number is odd check y
            prev = current;
            if (i % 2 == 0)
            {
                if (newNode->point[0] < current->point[0])
                {
                    current = current->left;
                    left = 1;
                }
                else
                {
                    current = current->right;
                    left = 0;
                }
            }
            else
            {
                if (newNode->point[1] < current->point[1])
                {
                    current = current->left;
                    left = 1;
                }
                else
                {
                    current = current->right;
                    left = 0;
                }
            }
            i = i + 1;
        }
    }

    tree->nodeCount = tree->nodeCount + 1;
}

int main()
{

    printf("Hello, World!\n");

    Tree *tree = newTree();
    printf("Node count: %d\n", tree->nodeCount);
    int arr[2];
    arr[0] = 1;
    arr[1] = 2;
    Node *node1 = newNode(arr);
    printf("node 1 values:  x: %d y: %d \n", node1->point[0], node1->point[1]);

    addNode(node1, tree);
    printf("Node count: %d\n", tree->nodeCount);

    arr[0] = 3;
    arr[1] = 4;

    Node *node2 = newNode(arr);
    printf("node 2 values:  x: %d y: %d \n", node2->point[0], node2->point[1]);

    addNode(node2, tree);
    printf("Node count: %d\n", tree->nodeCount);

    // removeNode(node1);
    // removeNode(node2);
};