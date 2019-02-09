


#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cs1713p1.h"

FILE *pFileStu;               // stream Input for Student Registration data

void processCommandSwitches(int argc, char *argv[], char **ppszStudentFileName);
void processRegistrations();

int main(int argc, char *argv[])
{
    char *pszStudentFileName = NULL;
    
    // Process the command switches
    processCommandSwitches(argc, argv,  &pszStudentFileName);
    
    // open the Student Registration stream data file
    if (pszStudentFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-s");
    
    pFileStu = fopen(pszStudentFileName, "r"); // open file for reading
    if (pFileStu == NULL)
        exitError(ERR_STUDENT_RES_FILENAME, pszStudentFileName);
    
    // process the Registrations
    processRegistrations(pFileStu);
    
    fclose(pFileStu);
    printf("\n");    // included so that you can put a breakpoint on this line
    return 0;
}

/****** you need to document and code this function *****/

void processRegistrations(FILE *pFileStu)
{
    Student student;
    CourseRequest courserequest;
    char szInputBuffer[100], *buffer;
    int line1;
    int line2;
    int line3;
    char *pszStudentFileName;
    
    while (fgets(szInputBuffer, 100, pFileStu) != NULL)
    {
        
        printf("******************** Student Registration Request ********************\n");
        
        line1 = sscanf(szInputBuffer,"%7s %c %11s %[^,]",
                       student.szStudentId,
                       &student.cGender,
                       student.szBirthDt,
                       student.szFullName);
        
        
        printf("%6s %c %10s %-11s",
               student.szStudentId,
               student.cGender,
               student.szBirthDt,
               student.szFullName);
        fgets(szInputBuffer, 100, pFileStu);
        
        line2 = sscanf (szInputBuffer,"%[^,],%[^,],%lf,%c",
                        student.szMajor,
                        student.szEmail,
                        &student.dGpa,
                        &student.cInternationalStudent);
        
        printf("%-s %s %.2lf %c\n",
               student.szMajor,
               student.szEmail,
               student.dGpa,
               student.cInternationalStudent);

        while (strcmp(fgets(szInputBuffer, 100, pFileStu),"END\n"))
        {
            
            if (feof(pFileStu)){
                break;
            }
   
            line3 = sscanf (szInputBuffer,"%11s",courserequest.szCourseId);
            
            printf("%s\n", courserequest.szCourseId);

        }
    }
}


/******************** processCommandSwitches *****************************
 void processCommandSwitches(int argc, char *argv[], char **ppszStudentFileName)
 Purpose:
 Checks the syntax of command line arguments and returns the filenames.
 If any switches are unknown, it exits with an error.
 Parameters:
 I   int argc                        count of command line arguments
 I   char *argv[]                    array of command line arguments
 O   char **ppszStudentFileName     student registration file name
 Notes:
 If a -? switch is passed, the usage is printed and the program exits
 with USAGE_ONLY.
 If a syntax error is encountered (e.g., unknown switch), the program
 prints a message to stderr and exits with ERR_COMMAND_LINE_SYNTAX.
 **************************************************************************/
void processCommandSwitches(int argc, char *argv[], char **ppszStudentFileName)
{
    int i;
    
    for (i = 1; i < argc; i++)
    {
        // check for a switch
        if (argv[i][0] != '-')
            exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        // determine which switch it is
        switch (argv[i][1])
        {
            case 's':                   // Student Registration File Name
                if (++i >= argc)
                    exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
                else
                    *ppszStudentFileName = argv[i];
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
    fprintf(stderr, "reserve -s studentRegistrationFile\n");
    if (iArg >= 0)
        exit(-1);
    else
        exit(-2);
}
