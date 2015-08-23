#include <glib.h>
#include "zz-log.h"
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

int main()
{

    //g_setenv("ZZ_DEBUG","FILE=out.dat:2",TRUE);
    g_setenv("ZZ_DEBUG",":3",TRUE);
    zz_debug_init();

    zz_log("akljflakdjf");
    zz_log1("1hello,%d",100);
    zz_log2("2hi,%s","nifei");
    zz_log3("3noting");
    zz_log4("4log4");


    DBG("hello,world");
    TRACE("hello,world");
    zz_debug_exit();

    return 0;
}
