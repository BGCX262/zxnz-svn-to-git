#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <assert.h>
#include "guessnum.h"
static char g_pcComparedStr[5];
static char g_pcResultStr[5];


static char *Compare(char *pcStr1, char *pcStr2);
static char* GetFourRandNums();
static int _CompareNotBySeq(char *pcompareStr, char *pg_pcComparedStr);
static int _CompareBySeq(char *pcompareStr, char *pg_pcComparedStr);
static int _ProcessInputData(char *pc);


static char* GetFourRandNums(){
    unsigned int seed;
    char num_src[11];
    char buffer[11];
    char* ret = g_pcComparedStr;
    int tryidx;
    strcpy(num_src,"0123456789");
    for(tryidx=0;tryidx<4;++tryidx){              
        int ridx;
        unsigned int i,j;
        char r;
        seed = (unsigned int) time(NULL);
        srand(seed);
        ridx = rand() % strlen(num_src);
        r = num_src[ridx];     
        for(i=0,j=0;i<strlen(num_src);++i){
            if(num_src[i]!=r){
                buffer[j++]=num_src[i];
            }
        }   
        buffer[j]='\0';
        strcpy(num_src,buffer);
        ret[tryidx]=r;
    }
    ret[tryidx]='\0';

    return ret;
}

static char *Compare(char *pcStr1, char *pcStr2)
{
    assert(strlen(pcStr1) == 4);
    assert(strlen(pcStr2) == 4);
    int a = _CompareBySeq(pcStr1, pcStr2);
    int b = _CompareNotBySeq(pcStr1, pcStr2);
    sprintf(g_pcResultStr, "%dA%dB", a, b);
    return g_pcResultStr;
}

static int _CompareBySeq(char *pcStr1, char *pcStr2)
{             
    assert(strlen(pcStr1) == 4);
    assert(strlen(pcStr2) == 4);
    int i;
    int n = 0;
    for (i = 0; i < 4; i++) {
        if (pcStr1[i] == pcStr2[i]) {
            ++n;
        }
    }
    return n;

}

static int _CompareNotBySeq(char *pcStr1, char *pcStr2)
{       
    assert(strlen(pcStr1) == 4);
    assert(strlen(pcStr2) == 4);
    int i, j;
    int n = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (pcStr1[i] == pcStr2[j]) {
                ++n;
            }
        }
    }

    n -= _CompareBySeq(pcStr1, pcStr2);
    return n;

}

static int _ProcessInputData(char *pc)
{                               //输入字符必须是数字,且不能重复
    int i, j;
    for (i = 0; i < 4; i++) {
        if (!isdigit(pc[i])) {
            return -1;
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 4; j++) {
            if (pc[i] == pc[j]) {
                return -1;
            }
        }
    }
    return 0;
}

int GuessNum()
{
    char pcInput[5];
    int counter = 1;
    int i;
    char *pc;
    pc = GetFourRandNums();
    printf("the answer is %s\n",pc);
    for(i=0;i<50;++i){
        puts("");
    }
    
    printf("**********NEW GAME*******************\n");
    printf("PLEASE INPUT A FOUR-BIT NUMBER TO GUESS\n");
    while (counter <= 10) {

        scanf("%s", pcInput);
        if (strlen(pcInput) != 4 || _ProcessInputData(pcInput) != 0) {
            if (strcmp(pcInput,"quit")==0){
                return -1;
            }else{
                printf("NOTICE! YOU SHOULD ENTER JUST 4 DIFFRENT NUM CHAR\n");
            }
            continue;
        }

        if (strcmp(pcInput, pc) == 0) {
            printf("***********************************\n");
            printf("VERY GOOD ,YOU ARE THE WINNER\n");
            return 0;
        }
        //printf("pcInput=%s,pc=%s\n",pcInput,pc);
        char *pr = Compare(pcInput, pc);
        //printf("%s\n",pc);
        printf("%d:  %s\n", counter, pr);
        ++counter;
    }

    
        printf("************************************\n");
        printf("Sorry,You lost this game\n");
        printf("The Right answer is %s", pc);
        return -1;
    
    
}
