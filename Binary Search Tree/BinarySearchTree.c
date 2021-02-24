#include <stdio.h>
#include <stdlib.h>		// initializing libraries which are necessary
#include <string.h>

struct n {			// initializing the struct
	int id;
	char word[25];
	int freq;
	struct n *left;
	struct n *right;
};

typedef struct n node;	//initializing typedef


node *insert(node *tree, int id, char word[], int freq ){		//a recursive function to insert new node to BINARY TREE
	if(tree == NULL){
		node *root = (node*)malloc(sizeof(node));		
		root->left =NULL;
		root->right =NULL;
		root->id = id;
		strcpy(root->word, word);				//this function insert new nodes depends on the node's freq
		root->freq = freq;
		return root;	
	}
	if(tree->freq > freq){
		tree->left = insert(tree->left, id, word, freq);	// adding new node to left side of binary tree
	}else {
		tree->right = insert(tree->right, id, word, freq);	// adding new node to right side of binary tree
	}
	
	return tree;
}

node *insertAlpha(node *tree, int id, char word[], int freq){	// a recursive function to insert new node to BINARY SEARCH TREE
	if(tree == NULL){
		tree = (node*)malloc(sizeof(node));
		tree->left =NULL;
		tree->right =NULL;
		tree->id = id;
		strcpy(tree->word, word);
		tree->freq = freq;						// this function insert new nodes depends on the node's word
		return tree;	
	}
	
	if(strcasecmp(tree->word, word) > 0){
		tree->left = insertAlpha(tree->left, id, word, freq);	// adding new node to left side of binary search tree
	}else {
		tree->right = insertAlpha(tree->right, id, word, freq);	// adding new node to right side of binary search tree
	}
	
	
	return tree;
}

node *nodeBT(int freq, char word[]) { // to create a new node for binary tree

    node *root = (node*)malloc(sizeof(node));
    root->freq = freq; 
    strcpy(root->word, word);
    root->left =NULL;
	root->right =NULL; 
	
    return (root); 
} 

node *insertBinaryTree(node array[], node *root, int i, int k) { // a recursive function insert nodes to binary tree from array
    if (i < k) { 
    	node *temp = nodeBT(array[i].freq, array[i].word);
        root = temp; 
        root->left = insertBinaryTree(array, root->left, 2*i + 1, k); 
        root->right = insertBinaryTree(array, root->right, 2*i + 2, k); 
    } 
    return root; 
} 

void traverse(node *tree){			// a recursive function to traverse whole tree LNR (infix order)
	if(tree == NULL){
		return;
	}
	traverse(tree->left);
	printf("	%s %d\n", tree->word, tree->freq);
	traverse(tree->right);
}

int findDepth(node *tree, char word[25], int depth) 
{ 
	if (tree ==NULL) 
		return 0; 

	if (strcmp(tree->word, word) ==0) 
		return depth; 

	int downdepth = findDepth(tree->left, word, depth+1); 
	if (downdepth != 0) 
		return downdepth; 

	downdepth = findDepth(tree->right, word, depth+1); 
	return downdepth; 
} 
int getDepth(node *node, char word[25]) 
{ 
	return findDepth(node,word,1); 
} 

int time = 0;	// a global variable to calculate access time
int accessTime(node *tree, node *root){	// a recursive function to calculate access time
	if(tree == NULL){
		return ;
	}
	accessTime(tree->left, root);
	time = time + (getDepth(root, tree->word) * tree->freq); 
	accessTime(tree->right, root);
}

int arrayI = 0;		// a global variable to initialize index of array to convert to binary tree
void toArray(node *tree, node array[50]){	// a recursive function to add nodes to the array
	if(tree == NULL){
		return;
	}
	toArray(tree->right, array);
	array[arrayI].id = tree->id;
	strcpy(array[arrayI].word, tree->word);
	array[arrayI++].freq = tree->freq;
	toArray(tree->left, array);
}

void readInputFile(node *tree, node *tree2){		// a function to read txt file 
	char wholeLine[100], id[25], word[25], freq[25];	// initializing  the variables for tree to insert
	int i = 0, k = 0, j = 0;
	int lengthOfArray;
	
	FILE *fileptr = fopen("input.txt","r");
	
	if(fileptr == NULL){	// a control statement to check whether if file exists or able to be opened
		printf("File couldn't be opened or such file does not exist...");
		return ;
	}
	
	while(fgets(wholeLine, 100, fileptr) !=NULL){	
		i = 0;
		k = 0;
		j = 0;
		
		if (wholeLine[0] != '\n'){ 
		
			for(i; i<25; i++){
				id[i] = '\0';
				word[i] = '\0';
				freq[i] = '\0';
			}
			
			for(i = 0; wholeLine[i] != ',' ;i++){
				id[i] = wholeLine[i];
			}
			i++;	
			for(i; wholeLine[i] != ',' ;i++){
				word[k] = wholeLine[i];
				k++;
			}
			i++;	
			for(i; wholeLine[i] != '\n' ;i++){
				freq[j] = wholeLine[i];
				j++;
			}
			int idI = atoi(id);
			int freqI = atoi(freq);
			
			tree = insertAlpha(tree, idI, word, freqI);
			tree2 = insert(tree2, idI, word, freqI);
			lengthOfArray++;
		}
	}
	
	node array[lengthOfArray];
	printf("\n	LNR traversal of Word BST\n\n");
	traverse(tree);
	accessTime(tree, tree);
	printf("\n	Access time of BINARY SEARCH TREE: %d\n", time);
	
	
	printf("\n\n*************************************************************\n\n");
	
	toArray(tree2, array);
	time = 0;
	tree2 = insertBinaryTree(array, tree2, 0, lengthOfArray);
	printf("	LNR traversal of frequency BINARY TREE\n\n");
	traverse(tree2);
	accessTime(tree2, tree2);
	printf("\n\n	Access time of BINARY TREE: %d\n", time);
}

int main(){	// main funtion to run whole code
	node *Word = NULL;
	node *freq = NULL;
	readInputFile(Word, freq);
}


