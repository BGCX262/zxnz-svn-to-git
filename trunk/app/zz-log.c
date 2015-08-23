/*-
 * $Id: rr-debug.c,v 1.8 2002/10/10 19:39:55 jonas Exp $
 *
 * See the file LICENSE for redistribution information.
 * If you have not received a copy of the license, please contact CodeFactory
 * by email at info@codefactory.se, or on the web at http://www.codefactory.se/
 * You may also write to: CodeFactory AB, SE-903 47, Ume?, Sweden.
 *
 * Copyright (c) 2002 Jonas Borgstr?m <jonas@codefactory.se>
 * Copyright (c) 2002 Daniel Lundin   <daniel@codefactory.se>
 * Copyright (c) 2002 CodeFactory AB.  All rights reserved.
 */


#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <glib.h>
#include <glib-object.h>
#include "zz-log.h"

static void zz_debug_log_handler (const gchar *log_domain,
				  GLogLevelFlags log_level,
				  const gchar *message,
				  gpointer user_data);

static RRLogLevelFlags debug_flags = 0;
static FILE *debug_file = NULL;

static const GDebugKey debug_keys[] = {
	{"1",          ZZ_LOG_LEVEL_DEBUG1},
	{"2",          (ZZ_LOG_LEVEL_DEBUG1 | ZZ_LOG_LEVEL_DEBUG2)},
	{"3",          (ZZ_LOG_LEVEL_DEBUG1 | ZZ_LOG_LEVEL_DEBUG2
	                | ZZ_LOG_LEVEL_DEBUG3)},
	{"4",          ZZ_LOG_LEVEL_DEBUG},
	{"NET",        ZZ_LOG_LEVEL_NET},
	{"ALL",        ZZ_LOG_LEVEL_NET | ZZ_LOG_LEVEL_DEBUG},
	{"TCP",        ZZ_LOG_LEVEL_NET},
	{"TCP_IN",     ZZ_LOG_LEVEL_NET_IN},
	{"NET_IN",     ZZ_LOG_LEVEL_NET_IN},
	{"TCP_OUT",    ZZ_LOG_LEVEL_NET_OUT},
	{"NET_OUT",    ZZ_LOG_LEVEL_NET_OUT}
};


#define NUM_DEBUG_KEYS (sizeof (debug_keys) / sizeof (GDebugKey))

static void
init_debug_output_files (const gchar *zz_debug)
{
	const gchar *str;

	if ((str = strstr (zz_debug, "FILE="))) {
		gchar *filename = g_strdup (str + 5);

		if (strchr (filename, ':'))
			*strchr (filename, ':') = 0;
		debug_file = fopen (filename, "w");
		g_free (filename);
	}
	if (debug_file == NULL)
		debug_file = stderr;
}

void
zz_debug_init (void)
{
	const gchar *env_zz_debug;

	env_zz_debug = g_getenv ("ZZ_DEBUG");

	if (env_zz_debug) {
		debug_flags = g_parse_debug_string (env_zz_debug, debug_keys,
						    NUM_DEBUG_KEYS);
		init_debug_output_files (env_zz_debug);
	}

	if (debug_flags)
		g_type_init_with_debug_flags (G_TYPE_DEBUG_OBJECTS);
	else
		g_type_init ();

	g_log_set_handler ("RR", ZZ_LOG_LEVEL_DEBUG, zz_debug_log_handler,
			   NULL);
}


void
zz_debug_exit (void)
{
	if (debug_file && debug_file != stderr)
		fclose (debug_file);
}


static void
zz_debug_log_handler (const gchar *log_domain,
		      GLogLevelFlags log_level,
		      const gchar *message,
		      gpointer user_data)
{
	//printf("message = %s\n",message);
    //printf("log_level=%d\n",log_level);
    //printf("debug_flags=%d\n",debug_flags);
    if (debug_flags & log_level) {
		//printf("message = %s\n",message);
        fprintf (debug_file, message);
		fprintf (debug_file, "\n");
		fflush (debug_file);
		log_domain = log_domain;//erase warning
		user_data = user_data;//erase warning
	}
}

