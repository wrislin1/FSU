#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

//definitions
#define CMDLGTH 81
#define ARGLGTH 71
#define ARGS 11
#define JOBS 100
#define BUFFER_SIZE 512
#define MAXCWDSIZE 71
#define USERDEFAULT "user"
#define SHELLNAME "myshell"
#define true 0
#define false -1

typedef int bool;

//structs
typedef struct commands
{
        char args[ARGS][ARGLGTH];
		bool redirectOut;
        bool redirectIn;
        char inputFile[ARGLGTH];
        char outputFile[ARGLGTH];
        int argCount;
} command;

typedef struct jobs
{
	command cmnd;
	int jid;
	pid_t pid;
} job;

//functions
void InitializePrompt(char*);
void MakeToken(char*, char**);
void ParseTokens(char**, command*);
void Run(char*, bool*, job*, int*);
void EraseArray(command*);

bool Exit(command*);
void Ls(command*);
void Cd(command*);     
void Echo(command*);
void Jobs(command*, job*, int*);
void OtherCmnd(command*, job*, int*);

// main function              
int main()
{
        char* user = getenv("USER");

	InitializePrompt(user);

	return 0;
}

void InitializePrompt(char* user)
{
        char cwd[MAXCWDSIZE];		//current working directory
        int numJobs = 0;
        job jobs[JOBS];
		bool exit = false;
		char input[CMDLGTH];	// input
	//prompt loop
        while (exit == false) {
                getcwd(cwd, MAXCWDSIZE);

                printf("%s@%s:%s> ", user, SHELLNAME, cwd);

                fgets(input, CMDLGTH, stdin);

                Run(input, &exit, jobs, &numJobs);
        }
}

void Run(char* input, bool* exit, job* jobs, int* numJobs)
{
 command cmnd;

	cmnd.argCount = -1;
	cmnd.redirectOut = false;
	cmnd.redirectIn = false;
        char* tokens[ARGS];

        //takes a command imput and turns it into something useable
        MakeToken(input, tokens);

        //takes those tokens and turns them into commands
        ParseTokens(tokens, &cmnd);

        // If command is exit
        if(strcmp(cmnd.args[0], "exit") == 0) {
                *exit = Exit(&cmnd);
        }
        // If command is cd
        else if(strcmp(cmnd.args[0], "cd") == 0) {
                Cd(&cmnd);
        }
        // If command is echo
        else if(strcmp(cmnd.args[0], "echo") == 0) {
                Echo(&cmnd);
        }
        // If command is jobs
        else if(strcmp(cmnd.args[0], "jobs") == 0) {
                Jobs(&cmnd, jobs, numJobs);
        }
        // If command is not built in and user did not simply press enter
        else if(cmnd.args[0][0] != '\0') {
                OtherCmnd(&cmnd, jobs, numJobs);
        }
}

void MakeToken(char* input, char** tokens)
{
        const char* delimiters = " \n\r\f\t\v";
		int i = 0;

	//tokenizes the imput stream
        tokens[i] = strtok(input, delimiters);
        while (tokens[i] != NULL && i < ARGS) {
                ++i;
                tokens[i] = strtok(NULL, delimiters);
        }

	//checking for too many arguments
        if (i == ARGS) 
                printf("too many arguments used, some may be left out\n");
}

void ParseTokens(char** tokens, command* cmnd)        
{
        int i = 0;                   
        int offset = 0;

        // error checks for null string in token array
        // (allows user to press enter on an empty prompt)
        // otherwise parses and populate the arguments as appropriate
        while(tokens[i] != '\0' && i != ARGS) {

                // check for redirection operators
                if (strcmp(tokens[i], ">") == 0) {
                        if (tokens[i+1] == NULL) {
                                printf("must supply output file\n");
                                EraseArray(cmnd);
                                return;
                        }                
                        else {
                                strcpy(cmnd->outputFile, tokens[i+1]);
                                cmnd->redirectOut = true;
                                ++offset;
                                i+=2;
                        }
        	}
                else {
                        strcpy(cmnd->args[i-offset], tokens[i]);
                        cmnd->argCount++;
                        ++i;
                }
        }
}

bool Exit(command* cmnd)
{
        if(cmnd->argCount > 0) {
                printf("there are no paramaters in exit\n");
                return false;
        }
        else return true;
}

void Ls(command* cmnd)
{

}

void Cd(command* cmnd)
{

}

void Echo(command* cmnd)
{
	int i;
	//normal output
	if (cmnd->redirectOut == false) {
		for (i = 1; i <= cmnd->argCount; ++i) {
			printf("%s ", cmnd->args[i]);
		}
		printf("\n");
	}

	//output redirect
	else if (cmnd->redirectOut == true) {
		FILE* outFile = fopen(cmnd->outputFile, "w");
		for (i = 1; i <= cmnd->argCount; ++i) {
			fprintf(outFile, "%s ", cmnd->args[i]);
		}
		fclose(outFile);
	}
}

void Jobs(command* cmnd, job* jobs, int* numJobs)
{

}

void OtherCmnd(command * cmnd, job* jobs, int* numJobs)
{

}

void EraseArray(command* cmnd)
{
	int i;
	for (i = 0; i <= cmnd->argCount; ++i) {
		strcpy(cmnd->args[i], "/0");
	}
	cmnd->argCount = 0;
}
