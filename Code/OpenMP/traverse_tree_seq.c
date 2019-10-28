#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct node_s
{
	int id;
	int payload;
	struct node_s *left;
	struct node_s *right;
} node_t;

void doYourWork(node_t *n)
{
	n->payload += 100;
}

static int nesting = 0;
void printNode(node_t *n)
{
	for(int i=0; i<nesting; i++)
		printf(" ");
	printf("[Thread %d/%d] Processing %d. Payload is %d\n",
	       omp_get_thread_num(), omp_get_num_threads(), n->id, n->payload);
}

/* Traverse elements in the tree */
void traverse_tree(node_t *n, void (*fn)(node_t *))
{
  fn(n); // Do work
  nesting++;
  
  if(n->left)
    traverse_tree(n->left, fn);
  if(n->right)
    traverse_tree(n->right, fn);

  nesting --;
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
  
  // Need one thrad only so that prints are in order
  omp_set_num_threads(1);
  traverse_tree(root, printNode);
  
  omp_set_num_threads(4); // 4 thrd on my machine
  traverse_tree(root, doYourWork);
  printf("---------------------------------------\n");
  
  // Need one thrad only so that prints are in order
  omp_set_num_threads(1);
  traverse_tree(root, printNode);
  
  
  return 0;
}