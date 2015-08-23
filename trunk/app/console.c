#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <glib.h>
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

extern int GuessNum();

/******************************************************************************
 List of all console commands.
 ******************************************************************************/
static cmd_t cmd_list[] = {
    {"help", (executable *) help},
    {"q", (executable *) exit},
    {"exit", (executable *) exit},
    {"quit", (executable *) exit},
    {"$", SystemCall},
    {"cd", cd},
    {"guessnum",(executable *)GuessNum},
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
    for (i = 0; cmd_list[i].name != NULL; i++, p++)
        if (strcmp(name, p->name) == 0)
            return p;
    return 0;
}

static char *command_generator(char *text, int state)
{
    static int list_index, len;
    char *name;

    /* If this is a new word to complete, initialize now.  This includes
       saving the length of TEXT for efficiency, and initializing the index
       variable to 0. */
    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    /* Return the next name which partially matches from the command list. */
    while ((name = cmd_list[list_index].name)) {
        list_index++;

        if (strncmp(name, text, len) == 0)
            return (g_strdup(name));
    }

    /* If no names matched, then return NULL. */
    return ((char *) NULL);
}

static char **command_completion(char *text, int start, int end)
{
    char **matches;

    matches = (char **) NULL;

    /* If this word is at the start of the line, then it is a command
       to complete.  Otherwise it is the name of a file in the current
       directory. */
    if (start == 0)
        matches = (char**)completion_matches(text, command_generator);

    return (matches);
}

static void initialize_readline()
{
    /* Allow conditional parsing of the ~/.inputrc file. */
    rl_readline_name = "FileMan";

    /* Tell the completer that we want a crack first. */
    rl_attempted_completion_function = (CPPFunction *) command_completion;
}

static void execute_line(char *line)
{
    cmd_t *pcmd;
    int argc = 0;
    char *argv[MAX_ARGVS];
    char *q = strtok(line, " ");
    while (1) {
        if (q == 0)
            break;
        argv[argc++] = q;
        q = strtok(0, " ");
    }

    /* Look for the command in the console command list */
    pcmd = GetEntry(line);
    if (pcmd == 0) {
        printf("Bad Command! \n");
        printf("Type \"help\" to get help\n");
    } else {
        pcmd->entry(argc, argv);
    }
}


int main()
{
    printf("***************************************************************\n");
    printf("                         CONSOLE                               \n");
    printf("***************************************************************\n");
    printf("To get help, please type \"help\"\n");

    char *line, *s;
    initialize_readline();

    while (1) {
        line = readline("> ");
        if (!line)
            break;
        s = g_strstrip(line);
        if (*s) {
            add_history(s);
            execute_line(s);
        }

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
        printf("$:\t\tRun system command;for example: $ ls\n");
        printf("guessnum:\ta guess number game\n");
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

static int cd(int argc, char **argv)
{
    if (argc < 2)
        return -1;
    chdir(argv[1]);
    return 0;
}

