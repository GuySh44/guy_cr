#include <stdio.h>

#include "tnode.h"

void BtMirror(bin_node_t *root)
{
	bin_node_t *temp = NULL;
	if(NULL == root)
	{
		return;
	}
	
	BtMirror(TreeNodeGetLeftChild(root));
	BtMirror(TreeNodeGetRightChild(root));
	
	temp = TreeNodeGetRightChild(root);
	TreeNodeSetRightChild(root, TreeNodeGetLeftChild(root));
	TreeNodeSetLeftChild(root, temp);
}

int PrintInt(void *data)
{
	
	printf("%d ", *(int*)data);
	return 0;
}

void printPostorder(bin_node_t *node)
{
    if (node == NULL)
    {
        return;
    }
 
    printPostorder(TreeNodeGetLeftChild(node));
 
    printPostorder(TreeNodeGetRightChild(node));
 
	PrintInt(TreeNodeGetData(node));
}


void printInorder(bin_node_t *node)
{
    if (node == NULL)
    {
        return;
    }
 
    printInorder(TreeNodeGetLeftChild(node));
 
	PrintInt(TreeNodeGetData(node));
 
    printInorder(TreeNodeGetRightChild(node));
}

void printPreorder(bin_node_t *node)
{
    if (node == NULL)
    {
       return;
	}
 
	PrintInt(TreeNodeGetData(node));
 
    printPreorder(TreeNodeGetLeftChild(node));
 
    printPreorder(TreeNodeGetRightChild(node));
}
 

int main()
{
	int one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9;
	
	bin_node_t *one_node, *two_node, *three_node, *four_node, *five_node, *six_node, *seven_node, *eight_node, *nine_node;
	
	one_node = TreeNodeCreate(NULL, NULL, &one);
	three_node = TreeNodeCreate(NULL, NULL, &three);
	nine_node = TreeNodeCreate(NULL, NULL, &nine);
	two_node = TreeNodeCreate(one_node, three_node, &two);
	four_node = TreeNodeCreate(two_node, NULL, &four);
	eight_node = TreeNodeCreate(NULL, nine_node, &eight);
	six_node = TreeNodeCreate(NULL, NULL, &six);
	seven_node = TreeNodeCreate(six_node, eight_node, &seven);
	five_node = TreeNodeCreate(four_node, seven_node, &five);
	
	printf("Inorder:\n");
	printInorder(five_node);
	
	printf("\n");
	
	printf("Preorder:\n");
	printPreorder(five_node);
	
	printf("\n");
	
	printf("Postorder:\n");
	printPostorder(five_node);
	
	printf("\n");
	
	printf("Mirror\n");
	BtMirror(five_node);
	
	printf("Inorder:\n");
	printInorder(five_node);
	
	printf("\n");
	
	printf("Preorder:\n");
	printPreorder(five_node);
	
	printf("\n");
	
	printf("Postorder:\n");
	printPostorder(five_node);
	
	printf("\n");
	
	TreeNodeDestroy(one_node);
	TreeNodeDestroy(two_node);
	TreeNodeDestroy(three_node);
	TreeNodeDestroy(four_node);
	TreeNodeDestroy(five_node);
	TreeNodeDestroy(six_node);
	TreeNodeDestroy(seven_node);
	TreeNodeDestroy(eight_node);
	TreeNodeDestroy(nine_node);
	
	return 0;
}
