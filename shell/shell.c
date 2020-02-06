#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

//definitions
#define SHELLNAME "myshell"
#define CMDLGTH 81
#define ARGLGTH 71
#define ARGS 11
#define JOBS 100
#define BUFFERSIZE 512
#define MAXCWDSIZE 71
#define USERDEFAULT "user"
#define true 0
#define false -1

typedef int bool;
bool apipe;

//structs
typedef struct commands
{
        char args[ARGS][ARGLGTH];
	char argp[ARGS][ARGLGTH];
	bool redirectOut;
        bool redirectIn;
        char inputFile[ARGLGTH];
        char outputFile[ARGLGTH];
        int argCount;
	int argCountp;
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
void Time(command*);
void ViewProc(command*);
void Cd(command*);     
void Echo(command*);
void OtherCmnd(command*);
void Pipe(command*);

// main function              
int main()
{
        char* user = getenv("USER");

	InitializePrompt(user);

	return 0;
}

void InitializePrompt(char* user)
{ 
	int numJobs = 0;
	job jobs[JOBS];
	char cwd[MAXCWDSIZE];		//current working directory
	bool exit = false;
	char input[CMDLGTH];		// input
	//prompt loop
        while (exit == false) {

		wait(NULL);
		apipe=false;

                getcwd(cwd, MAXCWDSIZE);

                printf("%s@%s:%s> ", user, SHELLNAME, cwd);

                fgets(input, CMDLGTH, stdin);
		
                Run(input, &exit, jobs, &numJobs);
        }
}

void Run(char* input, bool* exit, job* jobs, int* numJobs)
{
 	command cmnd;
	pid_t pid1, pid2;
	int i;

	cmnd.argCount = -1;
	cmnd.redirectOut = false;
	cmnd.redirectIn = false;
        char* tokens[ARGS];
	char* pipe_tok[ARGS];
	char* pipe_cmnd;

        //takes a command imput and turns it into something useable
        MakeToken(input, tokens);

        //takes those tokens and turns them into commands
        ParseTokens(tokens, &cmnd);

	if(apipe == false) {

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
		// If command is viewproc
		else if(strcmp(cmnd.args[0], "viewproc") == 0) {
			ViewProc(&cmnd);
		}	
		// If command is time
        	else if(strcmp(cmnd.args[0], "time") == 0) {
        	        Time(&cmnd);
        	}	
        	// If command is not built in and user did not simply press enter
        	else if(cmnd.args[0][0] != '\0') {
        	        OtherCmnd(&cmnd);
        	}
	}
	
	else
		Pipe(&cmnd);
}

void MakeToken(char* input, char** tokens)
{
        const char* delimiters = " \n\r\f\t\v";
	int i = 0;
	int j = 0;

	//tokenizes the imput stream
        tokens[i] = strtok(input, delimiters);
        while (tokens[i] != NULL && i < ARGS) {
                ++i;
                tokens[i] = strtok(NULL, delimiters);
        }

	//checking for too many arguments
        if (i == ARGS) 
                printf("too many arguments used, some may be left out\n");

	while(j!=i)
	{
		if(strcmp(tokens[j], "|") == 0)
		{
			apipe = true;
		}
		j++;
	}
}

void ParseTokens(char** tokens, command* cmnd)        
{
        int i = 0;
	int j = 0;
        int offset = 0;

	if(apipe == true)
	{
		while(strcmp(tokens[i], "|") != 0)
		{
			strcpy(cmnd->argp[i], tokens[i]);
			cmnd->argCountp++;
			i++;
		}
		i++;
	}
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

void Cd(command* cmnd)
{
	//error checking for # of paramaters
	if(cmnd->argCount > 1) {
		printf("error! cd may not have more than one paramater!\n");
		return;
	}
	
	//changes to the users home directory
	//if no destination is entered
	if(cmnd->argCount == 0 && getenv("HOME") != NULL) {
		chdir(getenv("HOME"));
		return;
	}
	else if (cmnd->args[0] == "~" && getenv("HOME") != NULL){
		chdir(getenv("HOME"));
		return;
	}

	else if (cmnd->argCount ==0) {
		printf("error! You must enter a working directory!\n");
	}

	//changes the directory if all imput is entered correctly
	bool success = chdir(cmnd->args[1]);
	if(success == false)
		printf("error! %s: That directory doesn't exist!\n", cmnd->args[1]);

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

void ViewProc(command* cmnd)
{
	char file[100];
	char ch;
	FILE * fp;
	
	if(cmnd->argCount < 1) {
		printf("you must enter another argument for time!\n");
		return;
	}
	strcpy(file, "/proc/");
	strcat(file, cmnd->args[1]);
	fp = fopen(file, "r");
	if (fp == NULL) {
		printf("Can't open %s \n", cmnd->args[1]);
		return;
	}
	while ((ch = getc(fp)) != EOF) {
		putc(ch, stdout); //print content
	}
	fclose(fp);
}

void Time(command* cmnd)
{
	double t1, t2, timeElapsed;
	struct timeval tim;
	int i;

	if(cmnd->argCount < 1){
		printf("you must enter another argument for time!\n");
		return;	
	}

	for(i = 0; i < cmnd->argCount; i++) {
		strcpy(cmnd->args[i], cmnd->args[i+1]);
	}
	cmnd->argCount = cmnd->argCount - 1;

	gettimeofday(&tim, NULL);
	t1=tim.tv_sec+(tim.tv_usec/1000000.0);

        // If command is cd
        if(strcmp(cmnd->args[0], "cd") == 0) {
                Cd(cmnd);
        }
        // If command is echo
        else if(strcmp(cmnd->args[0], "echo") == 0) {
                Echo(cmnd);
        }
	// If command is viewproc
	else if(strcmp(cmnd->args[0], "viewproc") == 0) {
		ViewProc(cmnd);	
	}
	// If command is time
        else if(strcmp(cmnd->args[0], "time") == 0) {
                Time(cmnd);
        }	
        // If command is not built in and user did not simply press enter
        else if(cmnd->args[0][0] != '\0') {
                OtherCmnd(cmnd);
        }
	
	gettimeofday(&tim, NULL);
	t2=tim.tv_sec+(tim.tv_usec/1000000.0);

	timeElapsed = t2-t1;
	printf("The elapsed time for the function is: %f\n", cmnd->args[0], timeElapsed);
}

void OtherCmnd(command * cmnd)
{
	int argCount = cmnd ->argCount;
	int argCountp = cmnd->argCountp;
	char* path;
	char* args[argCount+2];
	char* token;
	char* tokenp;
	char buffer[BUFFERSIZE];
	char tester[BUFFERSIZE];
	bool exeExists = false;
	struct stat temp;
	int i;
	const char* delim = ":";
	//copies cmnd's args to another array
	for ( i = 0; i <= argCount; ++i) {
		args[i] = cmnd->args[i];
	}
	args[argCount+1] == '\0';

	//get the path
	strcpy(buffer, getenv("PATH"));

	//make tokensssss
	token = strtok(buffer, delim);
	while (token != NULL & exeExists == false) {
		strcpy(tester, token);
		strcat(tester, "/");
		strcat(tester, args[0]);
		exeExists = stat(tester, &temp);

		token = strtok(NULL, delim);
	}
	if (exeExists == true) {
		path = tester;
	}
	else {
		printf("%s: cannot find this command. \n", args[0]);
		return;
	}

	pid_t pid = fork();
	if (pid == -1) {
		printf("forking failed!\n");
		exit(1);
	}
	else if (pid == 0) {
		execv(path, args);
		//printf("%s:execv failed to run!\n", args[0]);
		exit(0);
	}
}

void EraseArray(command* cmnd)
{
	int i;
	for (i = 0; i <= cmnd->argCount; ++i) {
		strcpy(cmnd->args[i], "/0");
	}
	cmnd->argCount = 0;
}

void Pipe(command* cmnd)
{
	int argCount = cmnd->argCount;
	int argCountp = cmnd->argCountp;
	pid_t pid1, pid2;
	int fd[2];
	char* path;
	char* pathp;
	char* args[argCount+2];
	char* argp[argCountp+2];
	char* token;
	char buffer[BUFFERSIZE];
	char tester[BUFFERSIZE];
	char testerp[BUFFERSIZE];
	bool exeExists = false;
	bool exeExistsp = false;
	struct stat temp;
	int i;
	const char* delim = ":";

	for (i = 0; i <= argCount; ++i) {
		args[i] = cmnd->args[i];
	}

	for(i = 0; i <= argCountp; ++i) {
		argp[i] = cmnd->argp[i];
	}

	args[argCount+1] == '\0';
	argp[argCountp+1] == '\0';

	//get the path
	strcpy(buffer, getenv("PATH"));
	token = strtok(buffer, delim);

	while (token != NULL && exeExists == false) {
		strcpy(tester, token);
		strcat(tester, "/");
		strcat(tester, argp[0]);
		exeExists = stat(tester, &temp);
		token = strtok(NULL, delim);
	}

	strcpy(buffer, getenv("PATH"));
	token = strtok(buffer, delim);
	while (token != NULL && exeExistsp == false) {
		strcpy(testerp, token);
		strcat(testerp, "/");
		strcat(testerp, args[0]);
		exeExistsp = stat(testerp, &temp);
		token = strtok(NULL, delim);
	}

	if (exeExists == true && exeExistsp == true) {
		path = tester;
		pathp = testerp;
	}

	else {
		printf("%s: cannot find this command. \n", argp[0]);
		exit(0);
	}

	pipe(fd);

	if ((pid1 = fork()) == 0) {
		printf("%s\n", pathp);
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[1]);
		execv(pathp, args);
	}

	else if ((pid2 = fork()) == 0) {
		printf("%s\n", path);
		dup2(fd[1], 1);
		close(fd[0]);
		execv(path, argp);
		waitpid(pid1, NULL, 0);
	}

	else {
		waitpid(pid2, NULL, 0);
		close(fd[0]);
		close(fd[1]);
	}
	apipe = false;
}
