/** 
 *\file console.c 
 *\brief not commented 
 *\author nifei 
 *\date 2007-11-16 
 * 
 *$Id$ 
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "guessnum.h"

/* The maximum number of command's args */
#define MAX_ARGVS 16
/* The maximum size of command */
#define MAX_CMD_SIZE 50
/******************************************************************************
 An entry in the console command list consists of a command name and its
 entry point.
 ******************************************************************************/

typedef int executable(int argc, char **argv);
typedef struct {
    char *name;
    executable *entry;
} cmd_t;


/******************************************************************************
 Command prototypes
 ******************************************************************************/
static int help(int argc, char **argv);
static int SystemCall(int argc, char **argv);
static int cd(int argc, char **argv);
static int guessNum();
/******************************************************************************
 List of all console commands.
 ******************************************************************************/
static cmd_t cmd_list[] = {
    {"help", (executable *) help},
    {"q", (executable *) exit},
    {"exit", (executable *) exit},
    {"quit", (executable *) exit},
    {"guessnum", (executable *) guessNum},
    {"$", SystemCall},
    {"cd", cd},
    {NULL, NULL}
};

 /******************************************************************************
 Search for a console command with matching name in the console command list.
 Return 0 if not found.
 ******************************************************************************/
static cmd_t *GetEntry(char *name)
{
    cmd_t *p = cmd_list;
    int i;
    for (i = 0; cmd_list[i].name != NULL; i++, p++) {
        if (strcmp(name, p->name) == 0) {
            return p;
        }
    }
    return 0;
}

/** 
 *\brief not commented 
 *\author nifei 
 
 *\date 2007-11-16 
 *\return 
 */
int main()
{
    printf("***************************************************************\n");
    printf("                         CONSOLE                               \n");
    printf("***************************************************************\n");
    printf("To get help, please type \"help\"\n");
    char cmd[MAX_CMD_SIZE];
    cmd_t *pcmd;
    while (1) {
        char *p;
        printf(">");
        fgets(cmd, sizeof(cmd), stdin);
        p = cmd;
        if (*p == '\n') {
            continue;
        }
        while (*p != '\n')
            p++;
        *p = '\0';

        int argc = 0;
        char *argv[MAX_ARGVS];
        char *q = strtok(cmd, " ");
        while (1) {
            if (q == 0)
                break;
            argv[argc++] = q;
            q = strtok(0, " ");
        }

        /* Look for the command in the console command list */
        pcmd = GetEntry(cmd);
        if (pcmd == 0) {
            printf("Bad Command! \n");
            printf("Type \"help\" to get help\n");
        } else
            pcmd->entry(argc, argv);
    }
    return 0;
}

/*****************************************************************************
 *command help
 *The "help" command do nothing but just print the command and it's argvs
 *****************************************************************************/
static int help(int argc, char **argv)
{
    if (argc < 2) {
        printf("The commands already implemented are:\n");
        printf("help:\t\tShow all command and relate info\n");
        printf("q:\t\tExit\n");
        printf("quit:\t\tExit\n");
        printf("exit:\t\tExit\n");
        printf("cd:\t\tEnter specified directory\n");
        printf("guessnum:\ta guess number game\n");
        printf("$:\t\tRun system command;for example: $ ls\n");
    } else {
        int i;
        for (i = 0; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    }

    return 0;
}

/******************************************************************************
 *command syscall
 *The "syscall" command allow you to use system commands
 *Example:
 *>syscall ls /home  
 *****************************************************************************/

/** 
 *\brief not commented 
 *\author nifei 
 *\param argc
 *\param argv 
 *\date 2007-11-16 
 *\return 
 */
static int SystemCall(int argc, char **argv)
{
    char cmd[MAX_CMD_SIZE];
    int i;
    if (argc < 2) {
        return -1;
    }
    strcpy(cmd, argv[1]);
    for (i = 2; i < argc; i++) {
        strcat(cmd, " ");
        strcat(cmd, argv[i]);
    }
    system(cmd);
    return 0;
}

/** 
 *\brief not commented 
 *\author nifei 
 *\param argc
 *\param argv 
 *\date 2007-11-16 
 *\return 
 */
static int cd(int argc, char **argv)
{
    if (argc < 2)
        return -1;
    chdir(argv[1]);
    return 0;
}
static int guessNum()
{
    GuessNum();
    return 0;
}
