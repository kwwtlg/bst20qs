using namespace std;
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "TwentyQuestionsTree.h"

TwentyQuestionsTree::TwentyQuestionsTree(FILE *fp)
{
  char *p,*l,*r;
  char buff[500];
if(root==NULL)
	 {
	   if(fgets(buff,500,fp)!=NULL){
	     p=strtok(buff,",\n");
	     root = new BinaryNode(p);
	     l=strtok(NULL,",\n");
	     root->left=new BinaryNode(l);
	     r=strtok(NULL,"\n");
	     root->right=new BinaryNode(r);}
	 }
 else
   TwentyQuestionsTree();
   
  while((fgets(buff,500,fp)!=NULL))
    {  
        p = strtok(buff,",\n");  
        l = strtok(NULL,",\n");
	r = strtok(NULL, "\n");
	insert(root,p,l,r);
      }
}

TwentyQuestionsTree::TwentyQuestionsTree()
{
	root = new BinaryNode("Is it a platypus?");
}

/* insert
 * This inserts two questions into the tree - the children of the parent.
 * This is used when building the tree from scratch.
 * The assumption is that the parent is already in the tree, and we are 
 * merely adding the left and right children.
*/
bool TwentyQuestionsTree::insert(BinaryNode *r,char *parent, char *left, char *right)
{
  if(r==NULL)
    return false;
 if(r->left == NULL || r->right == NULL)
   {
     if(strcmp(r->question,parent)==0)
       {
	 r->left = new BinaryNode(left);
	 r->right= new BinaryNode(right);
	 return true;
       }
   }
 else
   {
      insert(r->left,parent,left,right);
      insert(r->right,parent,left,right);
      return false;
   }
}

/* modifyAndInsert
 *
 * This modifies the tree as a result of the game being incorrect.  Either 
 * the left child or right child is already in the tree.  This method replaces
 * that existing one with the new parent and creates new left and right 
 * children.
 */
bool TwentyQuestionsTree::modifyAndInsert(BinaryNode *n,char *parent, char *left, char *right)
{
  if(n->left==NULL && n->right==NULL)
    { 
      if(strcmp(n->question,left)==0)
	{
	  char* mod =new char[strlen(n->question)+1];
	  strcpy(mod,n->question);

	  delete n->question;

	  n->question=new char[strlen(parent)+1];
	  n->left=new BinaryNode(mod);
	  n->right=new BinaryNode(right);

	  delete mod;
	  return true;
	}
      else if(strcmp(n->question,right)==0)
	{
	  char* mod =new char[strlen(n->question)+1];
	  strcpy(mod,n->question);
	  delete n->question;

	  n->question=new char[strlen(parent)+1];
	  n->left=new BinaryNode(left);
	  n->right=new BinaryNode(mod);

	  delete mod;
	  return true;
	}
      
    }
  else
    {
      if(n->left!=NULL){
	if(modifyAndInsert(n->left,parent,left,right))
	  return true;}
      else  if(n->right!=NULL)
	{if(modifyAndInsert(n->right,parent,left,right))
	    return true;}
      else
	return false;
    }
}

void TwentyQuestionsTree::modifyAndInsert(char *parent, char *left, char *right)
{
  modifyAndInsert(root,parent,left,right);
}

/* reset
 *
 * This resets the iterator to the beginning of the game
 */
void TwentyQuestionsTree::reset()
{ 
  iterator=root;
}

/* currentQuestions
 *
 * This has been provided for you.  This looks at the current position of 
 * the iterator and returns the question stored in that BinaryNode.
 */
char *TwentyQuestionsTree::currentQuestion()
{
	if (iterator == NULL)
		return NULL;
	else
		return iterator->question;
}
	
			
/* recordAnswer
 *
 * This advances the iterator.  If the answer was yes (1), go right.  If
 * no (0), go left.
 */
void TwentyQuestionsTree::recordAnswer(int answer)
{
  if(answer==0)
    iterator=iterator->left;
  else if(answer==1)
     iterator=iterator->right;
  else
    return;
}

/* storeTree
 *
 * This writes the tree out to the file in the same format as the 
 * sample input file was.
 */
void TwentyQuestionsTree::storeTree(BinaryNode *n,FILE *fp)
{
  if(n==NULL)
    return;
  else
    {
      fputs(n->question,fp);
      storeTree(n->left, fp);
      storeTree(n->right,fp);

    }
}
void TwentyQuestionsTree::storeTree(FILE *fp)
{
  storeTree(root,fp);
}

