/**********************************************************************
p1awd141.c  by Doan, Danny
(change the previous line for your abc123 ID and your name)
Purpose:
    This program reads team data to show current rankings.
Command Line Arguments:
    p1  -t  teamFileName  
Input:  
    Stream input file which contains many teams. There are two different 
    kinds of lines of data for each team:
    - Team Identification Information:
        o One line per team (separated by spaces)
            szTeamId  iWins  iLosses  dFeeAmount  dPaidAmount  
             6s       d      d        lf          lf
    - Team Contact Information:
        o One line per team (separated by commas)
            szTeamNm  szEmail szPhone szContactName
            12s       30s     13s     20s
        o Although szTeamNm is a maximum of 12 characters, it may 
          contain spaces; therefore, you cannot simply use %13s.  
          For szFullName, you will have to use a bracket format 
          code using %[^,].  The next two values are also terminated by 
          commas.
        o For szContactName, it contains spaces and is terminated by
          a new line character.  You will have to use a bracket format code 
          using %[^\n]

Results:
    Print the list of teams as shown below.
    Examples:
        Id     Team Name    Wins Loss  Fee Amt   Paid Amt
                        Contact Name         Phone         Email
        UTSA01 Armadillos      8    0    150.00     80.00
                        Jean E Us            (210)555-1111 utsa@xyz.com
        COM001 Comm Eagles     7    1    150.00     75.00
                        Mae King             (210)555-2222 maeking@xyz.com
        SOUTH1 Slam Dunk       5    3    120.00     75.00
                        Jerry Tall           (210)555-3333 slamdunk@gmail.com
        ALHGHT Cake Eaters     4    4    175.00    100.00
                        E Z Street           (210)555-6666 sliverspoon@xyz.com
        UNKN01 Org New Blk     1    7    150.00     50.00
                        Bob Wire             (210)555-1234 bobwire@xyz.com
        NEWB01 River Rats      0    8    120.00     75.00
                        Rock D Boat          (210)555-4444 riverrat@xyz.com
        UNKN02 Hackers         3    5    150.00     75.00
                        Tom E Gunn           (210)555-5555 cyber@gmail.com


Returns:
    0  normal
    -1 invalid command line syntax
    -2 show usage only
    -3 error during processing, see stderr for more information
Notes:
    p1 -?  will provide the usage information.  In some shells,
                you will have to type reserve -\?
  
**********************************************************************/
// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cs1713p2.h"
FILE *pFileTeam;               // stream Input for Team data
FILE *pFileGame;			   // steam Input for games

void processCommandSwitches(int argc, char *argv[], char **ppszTeamFileName, char **ppszGameFileName);
int getTeams(Team teamM[]);
void printTeams(char szHeading[], Team teamM[], int iTeamCnt);
void processGameFile(Team teamM[], int iTeamCnt);
void processGame(Game game, Team teamM[], int iTeamCnt);
int findTeam(Team teamM[], int iTeamCnt, char szTeamId[]);

//something wrong with commandswitches or pfileteam
int main(int argc, char *argv[])
{
	Team teamM[MAX_TEAMS];
	char *pszGameFileName = NULL;
    char *pszTeamFileName = NULL;
 	int iTeamACnt;
    // Process the command switches
    processCommandSwitches(argc, argv,  &pszTeamFileName, &pszGameFileName);
    // open the Team stream data file
    if (pszTeamFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-t");
    
    pFileTeam = fopen(pszTeamFileName, "r");
    if (pFileTeam == NULL)
        exitError(ERR_TEAM_FILENAME, pszTeamFileName);
   
   if(pszGameFileName == NULL)
		exitError(ERR_MISSING_SWITCH, "-g");
		
	pFileGame = fopen(pszGameFileName, "r");

	if (pFileGame == NULL)
		exitError(ERR_GAME_FILENAME, pszGameFileName);
		
    // get the Teams Data
    iTeamACnt = getTeams(teamM);
    printTeams("heading",teamM,iTeamACnt);
	processGameFile(teamM,iTeamACnt);
	
	fclose(pFileGame);
    fclose(pFileTeam);
    printf("\n");    // included so that you can put a breakpoint on this line
    return 0;
}

/*********************** getTeams *****************************************
void getTeams() 
Purpose:
    Takes data and stores it inside the struct in cs1713p1.h to then 
	reformat and print.
Parameters:

Notes:
	This function uses the global variable 'pFileTeam' to open and read
	"p1Team.txt".
**************************************************************************/
int getTeams(Team teamM[])
{
    char szInputBuffer[100];                            //for inputs
    int iscanfCnt;										//created variable to check for input errors
    Team team;              							//renaming struct 'Team' for ease of use
    int i = 0;
    
    //fscanf(pFileTeam,"%s", szInputBuffer);
	//printf("%s", szInputBuffer);
    //while loop so code runs until there is no more input data
    
    //for some reason it wont read this information
    while(fgets(szInputBuffer, 100, pFileTeam) != NULL) {
    	
        //populates variables inside struct "Team"
        iscanfCnt=sscanf(szInputBuffer, "%6s %d %d %lf %lf", team.szTeamId, &team.iWins, &team.iLosses, &team.dFeeAmount, &team.dPaidAmount);
        //checks if given data has the correct amount of inputs
        if(iscanfCnt < 5) {
            printf("Invalid Input Data");
		}
        fgets(szInputBuffer, 100, pFileTeam);
        //populates variables inside struct "Team"
        iscanfCnt=sscanf(szInputBuffer, "%[^,],%[^,],%[^,],%[^\n]", team.szTeamName, team.szEmailAddr, team.szPhone, team.szContactname);
        //checks if given data has the correct amount of inputs
        if(iscanfCnt < 4) {
            printf("Invalid Input Data");
		}
        teamM[i] = team;
        i++;

    }    
    return i;
}

//how to access parts of 'Team'
//why won't teamM(.) pop anything up
int findTeam(Team teamM[], int iTeamCnt, char szTeamId[]) {
	int i;
	for(i=0; i<iTeamCnt; i++) {
		if(strcmp(teamM[i].szTeamId,szTeamId)==0) {
			return i;
		}
	}
		return -1;
}

//figure out what to do with teamM[]
//processgamefile does it until EOF, but processgame is part of it
//processgamefile(processgame)
//while(fgets(szINputbuffer etc...
void processGame(Game game, Team teamM[], int iTeamCnt) {
	int i;
	int j;
	
	char szInputBuffer[100];
	printf("\n%s %s %-2d %-2d", game.szTeamId1, game.szTeamId2, game.iScore1, game.iScore2);

	i = findTeam(teamM, iTeamCnt, game.szTeamId1);
	j = findTeam(teamM, iTeamCnt, game.szTeamId2);
	if(i < 0) {
		printf(" team %s not found", game.szTeamId1);
	}
	if(j < 0) {
		printf("team %s not found", game.szTeamId2);
	}
}

//how do i update the scores based on this
//
void processGameFile(Team teamM[], int iTeamCnt) {
	char szInputBuffer[100];
	int i;
	int iscanfCnt;
	Game game;
	while(fgets(szInputBuffer,100, pFileGame) != NULL) {
		iscanfCnt = sscanf(szInputBuffer, "%s %s %d %d", game.szTeamId1, game.szTeamId2, &game.iScore1, &game.iScore2);
		if(iscanfCnt < 4){
			printf("invalid inputs for game");
		}
		processGame(game, teamM, iTeamCnt);
	}
}

/******************** printTeams *****************************
   void printTeams(char szHeading[], Team teamM[], int iTeamCnt)
Purpose:
    Prints team information. 
Parameters:
    i char szHeading[]  string describing why the teams are printed
                        (e.g., "Original Team Information")
    i Team teamM[]      array of teams
    i int iTeamCnt      number of teams
Notes:
    Prints two lines of text per team.
**************************************************************************/
void printTeams(char szHeading[], Team teamM[], int iTeamCnt)
{
    int i;          // local counter
    // Print the heading
    printf("%s\n", szHeading);
    printf("  %-6s %-12s %4s %4s  %-8s  %-8s\n"
        , "Id", "Team Name", "Wins", "Loss", "Fee Amt", "Paid Amt");
    printf("\t\t  %-20s %-13s %s\n"
        , "Contact Name", "Phone", "Email");
    // iterate through the teamM array
    
    for (i = 0; i < iTeamCnt; i++)
    {
    	
        printf("  %-6s %-12s %4d %4d  %8.2lf  %8.2lf\n"
            , teamM[i].szTeamId
            , teamM[i].szTeamName
            , teamM[i].iWins
            , teamM[i].iLosses
            , teamM[i].dFeeAmount
            , teamM[i].dPaidAmount);
        printf("\t\t  %-20s %-13s %s\n"
            , teamM[i].szContactname
            , teamM[i].szPhone
            , teamM[i].szEmailAddr);
    }
}

/******************** processCommandSwitches *****************************
void processCommandSwitches(int argc, char *argv[], char **ppszTeamFileName, char **ppszGameFileName)
Purpose:
    Checks the syntax of command line arguments and returns the filenames.
    If any switches are unknown, it exits with an error.
Parameters:
    I   int argc                    Count of command line arguments
    I   char *argv[]                Array of command line arguments
    O   char **ppszTeamFileName     Team file name
Notes:
    If a -? switch is passed, the usage is printed and the program exits
    with USAGE_ONLY.
    If a syntax error is encountered (e.g., unknown switch), the program
    prints a message to stderr and exits with ERR_COMMAND_LINE_SYNTAX.
**************************************************************************/
void processCommandSwitches(int argc, char *argv[], char **ppszTeamFileName, char **ppszGameFileName)
{
    int i;
    int j;
    // Examine each command argument (except argument 0 which is the executable name)
    for (i = 1; i < argc; i++)
    {
        // check for a switch
        
        if (argv[i][0] != '-')
            exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        // determine which switch it is
        switch (argv[i][1])
        {
            case 't':                   // Team File Name
                if (++i >= argc)
                    exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
                else
                    *ppszTeamFileName = argv[i];
                break;
            case '?':
                exitUsage(USAGE_ONLY, "", "");
                break;
            default:
                exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        }
        i++;
        
        // check for a switch
        if (argv[i][0] != '-')
            exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
         
        // determine which switch it is
        
        switch (argv[i][1])
        {
        	
            case 'g':                   // Team File Name
                if (++i >= argc){
				
                 
                    exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);}
                else
                
                    *ppszGameFileName = argv[i];
                    printf("%s", *ppszGameFileName);
                break;
            case '?':
                exitUsage(USAGE_ONLY, "", "");
                break;
            default:
                exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
                
        }
    }
}

/******************** exitError *****************************
    void exitError(char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    Prints an error message and diagnostic to stderr.  Exits with
    ERROR_PROCESSING.
Parameters:
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitError(char *pszMessage, char *pszDiagnosticInfo)
{
    fprintf(stderr, "Error: %s %s\n"
        , pszMessage
        , pszDiagnosticInfo);
    exit(ERROR_PROCESSING);
}
/******************** exitUsage *****************************
    void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    If this is an argument error (iArg >= 0), it prints a formatted message
    showing which argument was in error, the specified message, and
    supplemental diagnostic information.  It also shows the usage. It exits
    with ERR_COMMAND_LINE_SYNTAX.

    If this is just asking for usage (iArg will be -1), the usage is shown.
    It exits with USAGE_ONLY.
Parameters:
    I int iArg                      command argument subscript
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
    if (iArg >= 0)
        fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
            , iArg
            , pszMessage
            , pszDiagnosticInfo);
    fprintf(stderr, "p1 -t TeamFileName\n");
    if (iArg >= 0)
        exit(-1);
    else
        exit(-2);
}
