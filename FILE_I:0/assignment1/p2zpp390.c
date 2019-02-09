/**********************************************************************
 
 p2abc123.c  by LastName, FirstName
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
FILE *pFileTeam; // stream Input for Team data
FILE *pFileGame; // stream input for Game data

void processCommandSwitches(int argc, char *argv[], char **ppszTeamFileName, char **ppszGameFileName);
int getTeams(Team teamM[]);
void printTeams(char szHeading[], Team teamM[], int iTeamCnt);
void processGameFile(Team teamM[], int iTeamCnt);
void processGame(Game game, Team teamM[], int iTeamCnt);
int findTeam(Team teamM[], int iTeamCnt, char szTeamId[]);


int main(int argc, char *argv[])
{
    Team teamM[MAX_TEAMS];
    
    
 	int iTeamCnt;
 	getTeams(teamM);
 	int i;
 	
    char *pszGameFileName = NULL;
    
    char *pszTeamFileName = NULL;
    
    // Process the command switches
    processCommandSwitches(argc,argv,&pszTeamFileName, &pszGameFileName);
    
    // open the Team stream data file and Game File
    if (pszTeamFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-t");
    if (pszGameFileName == NULL)
        exitError (ERR_MISSING_SWITCH, "-g");
    
    //printf("***%s\n",pszTeamFileName);
    pFileTeam = fopen(pszTeamFileName, "r");
    if (pFileTeam == NULL)
        exitError(ERR_TEAM_FILENAME, pszTeamFileName);
    
    pFileGame = fopen (pszGameFileName,"r");
    //if (pFileGame == NULL)
    // exitError (ERR_GAME_FILENAME, pszGameFileName);
    
    
    
    iTeamCnt = getTeams(teamM); 
    printTeams("heading",teamM,iTeamCnt);
	processGameFile(teamM,iTeamCnt);
	printTeams("\nteegfed",teamM,iTeamCnt);
    // get the Teams Data and Games Date
    //getTeams(teamM);
    fclose(pFileTeam);
    fclose(pFileGame);
    printf("\n");
	return 0;    // included so that you can put a breakpoint on this line
}
 
 
 /****** you need to document and code this function *****/
int  getTeams(Team teamM[] )
{
    Team team;
    
    
    char szInputBuffer[100];// set size of the BUffer to 100
    
    int iScanfcount;
    int i =0;
    
    
    while (fgets(szInputBuffer, 100 , pFileTeam) != NULL)  // Use while loop tu red input from p1Team.txt. fgets return NULL at
    {
        
        // use sscanf to read each line and store as requied in the function
        
        iScanfcount = sscanf(szInputBuffer,"%6s %d %d %lf %lf"
                             ,team.szTeamId
                             ,&team.iWins
                             ,&team.iLosses
                             ,&team.dFeeAmount
                             ,&team.dPaidAmount);
        
        // Using fgets to scan each line store it in the second line and separate with comas.
        fgets(szInputBuffer,100,pFileTeam);
        iScanfcount = sscanf(szInputBuffer,"%[^,],%[^,],%[^,],%[^\n]"     // Use sscanf to get chacracaters, special characters, and numbers.
                             ,team.szTeamName
                             ,team.szEmailAddr
                             ,team.szPhone
                             ,team.szContactname);
                         
                         
        
        
        // use while loop to read the input date of the text from the p1Team.txt
        
        
        teamM[i] = team;
        i++;
    }
    return i;
}
        //This printout the output from the p2Team.txt
        
        //printf ( "%-7s %-14s %d    %d  %-.2lf    %-.2lf\n",szTeamID,szTeamNm, iWins,  iLosses, dFeeAmount, dPaidAmount);  // set spaces and right heading on the first line
        
        //printf( "%25s \t      %-13s %-30s\n",szContactName,szPhone,szEmail) ;   // set spaces and right heading on the second line.
        
        
        
	int findTeam( Team teamM[],int iTeamCnt, char szTeamId[]){
		
		int i;
		for (i=0;i<iTeamCnt;i++){
			
			if (strcmp(teamM[i].szTeamId,szTeamId)==0){
				return i;
			}
			}
			return -1;
		}





	void processGame( Game game, Team teamM[], int iTeamCnt){
	
		int teamNumber1;
		int teamNumber2;
		
		printf("\n%s %s %d %d"
		 ,game.szTeamId1
		 ,game.szTeamId2
		 ,game.iScore1
		 ,game.iScore2);
		 
		 
		teamNumber1= findTeam(teamM, iTeamCnt, game.szTeamId1);
	 	teamNumber2= findTeam(teamM, iTeamCnt, game.szTeamId2);
		
		if ( teamNumber1<0){
			
			printf(" team %s not found", game.szTeamId1);
			
		}
		
		if (teamNumber2<0){
			
			printf(" team %s not found", game.szTeamId2);
		}
	 
	if(game.iScore1 > game.iScore2) {
		teamM[teamNumber1].iWins = (teamM[teamNumber1].iWins + 1);
		teamM[teamNumber2].iLosses = (teamM[teamNumber2].iLosses + 1);
	}
	if(game.iScore2 > game.iScore1) {
		teamM[teamNumber2].iWins = (teamM[teamNumber2].iWins + 1);
		teamM[teamNumber1].iLosses = (teamM[teamNumber1].iLosses + 1);

}
}

void processGameFile(Team teamM[], int iTeamCnt) {
	
	
	char szInputBuffer[100];
	int iScanfcnt;
	Game game;
	printf(" \nProcessing Game\n");
	
		while(fgets(szInputBuffer,100,pFileGame)!=NULL){
		iScanfcnt= sscanf (szInputBuffer,"%7s %7s %d %d"
		,game.szTeamId1
		,game.szTeamId2
		,&game.iScore1
		,&game.iScore2);
		processGame(game, teamM, iTeamCnt);
		
	}
	
	}

		

/******************** processCommandSwitches *****************************
 void processCommandSwitches(int argc, char *argv[], char **ppszTeamFileName)
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
    	
        printf("%-6s %-12s %4d %4d  %8.2lf  %8.2lf\n"
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
 

void processCommandSwitches(int argc, char *argv[], char **ppszTeamFileName , char **ppszGameFileName)
{
    int i;
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
                //adding switch -g
            case'g':                // Game File
                if (++i >= argc)
                    exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
                else
                    *ppszGameFileName = argv[i];
                break;
            case '?':
                exitUsage(USAGE_ONLY, "", "");
                break;
            default:
                exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        }
    }
}




/*  typedef char teamM[20];

int findTeams(char szMatch)
{
    
    Team teamM[] = {" UTSA01","NEWB01","COMM01", "SOUTH1","ALHGHT","UNKN01" };
    int i;
    char ch;
    for ( i = 0; i < 6; i++)
        if (strcmp(szMatch, teamM[i].szTeamId==0) {
            printf("fucking work");
            return 1;
        } else {
            printf("didnt fucking work");
            return -1;
        }
            }
            */
            
            
            
            
            
        /*int findTeams(Team teamM[], int iTeamCnt, char szTeamId[]) {
         int i;
         for(i=0; i<iTeamCnt; i++) {
         if(strcmp(teamM[i].szTeamId,szTeamId)) {
         printf("this works\n");
         return 1;
         } else {
         printf("does not work \n");
         return -1;
         }
         
         }
         }/*
         
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
            fprintf(stderr, "p2 -t TeamFileName\n");
            
            if (iArg >= 0)
                exit(-1);
            else
                exit(-2);
        }

