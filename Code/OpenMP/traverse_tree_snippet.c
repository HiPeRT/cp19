#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
	int id;					// Unique ID
	int payload;			// Some information carried with the node
	struct node_s *left;	// Left child
	struct node_s *right;	// Right child
} node_t;

void traverse_tree(node_t *n)
{
  if(!n)
	  return;
  /* Perform some work here...*/
  
  
  /* Now, traverse elements in the tree */
  if(n->left)
    traverse_tree(n->left);
  if(n->right)
    traverse_tree(n->right);
}
node_t * createNodeT(int id, node_t *left, node_t* right)
{
	node_t *newNode = (node_t *) malloc(sizeof(node_t));
	newNode->id = id;
	newNode->payload = id;
	newNode->left = left;
	newNode->right = right;
	
	return newNode;
}

int main()
{
  node_t *root =
	  createNodeT(	0,
					createNodeT(1,
								createNodeT(3, 0, 0),
								createNodeT(4, 0, 0)
								),
					createNodeT(2,
								createNodeT(5, 0, 0),
								createNodeT(6, 0, 0)
								)
	  );
    
  traverse_tree(root); 
  
  /* No need to destroy the nodes!
   * - Why? (Do you remember 'Programmazione I'?)
   */
  
  return 0;
}