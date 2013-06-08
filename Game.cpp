using namespace std;
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include "TwentyQuestionsTree.h"

int main(int argc, char *argv[])
{

  TwentyQuestionsTree *tree;
  FILE *fp;

	// if there was a command-line argument,
	// assume it is the filename and pass in a file to initialize
	// tree
	if (argc == 2)
	  {
		fp = fopen(argv[1],"r");
		tree= new TwentyQuestionsTree(fp);
	  } 
	else
	  tree = new TwentyQuestionsTree();

	int play;
	do{
		char buf[256];


		// start the game
		tree->reset();
		char *question = tree->currentQuestion();
		char *lastquestion;
		int answer = 0;
		while(question != NULL)
		{
			// ask the question
			printf("%s (yes=1, no=0): ",question);
			// read the response
			fgets(buf,256,stdin);
			answer = atoi(buf);
			if (answer == 0)
				printf("No\n");
			else
				printf("Yes\n");
			tree->recordAnswer(answer);
			lastquestion = question;
			question = tree->currentQuestion();
		}
		
		// check to see if computer was correct
		if (answer == 1)
			printf("Yippee!  I got it right!\n");
		else
		{
                        printf("What should I have guessed?\n");
                        printf("(i.e. Is it a platypus?)?  ");
			char *r,*o;
			char realanswer[300], otherquestion[256];
			fgets(realanswer,256,stdin);
			// strip last \n
			r = strtok(realanswer,"\n");
			printf("Real question: %s\n",realanswer);
			printf("What question would have distinguished this from %s\n",lastquestion);
			fgets(otherquestion,256,stdin);
			// strip last \n, leading spaces
			r = strtok(otherquestion,"\n");
			printf("Other question: %s\n",r);
			do{
				printf("Would the answer to that question have been yes or no (yes=1,no=0)? ");
				o = fgets(buf,256,stdin);
				answer = atoi(o);
			} while(!isdigit(*o));
			
			if (answer == 0)
				tree->modifyAndInsert(r,
						realanswer,lastquestion);
			else
				tree->modifyAndInsert(r,
						lastquestion,realanswer);

		}

		printf("Would you like to play again (yes=1,no=0)?");
		fgets(buf,256,stdin);
		play = atoi(buf);
	} while(play == 1);
	
	
	// if a filename was given, reopen the file for writing and
	// write out the current state of the tree
	if(argc==2)
	  {
	    	fclose(fp);
	    	fp = fopen(argv[1],"w");
	    	tree->storeTree(fp);
	    	fclose(fp);
	  }
}


