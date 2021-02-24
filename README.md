# BinarySearchTree
In this repository, We create a binary search tree and level ordered binary tree.  
*Materials*: Text files which include words and the frequencies of the words, Source code.  

### What we do?  

* **For Binary Search Tree:** We allocate memories for each word while reading the text file and we put the words and the frequencies of the words into nodes. Meanwhile we are creating a binary search tree based on the frequencies of the words. Most searched word is in the right deepest level.   

* **For Level Ordered Binary Tree:** We are doing the same things with BST except creating a search tree, We create a balanced binary tree in this part.  

We are asked to calculate the total access time for each trees, compare their differences and determine what the main reason is for the differences. How do we calculate total access time for each trees?  
**sum of all nodes with the formula -> [frequency x (depth level + 1)]** 
