/*-
 * $Id: rr-debug.h,v 1.6 2002/11/28 21:00:24 jonas Exp $
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

#ifndef __zz_debug_H__
#define __zz_debug_H__

#include <glib/gmessages.h>

//add more dubug info to log
#define zz_log(...)                G_STMT_START{                               \
    zz_debug("[%s:%d]: ", __FILE__, __LINE__); \
    zz_debug(__VA_ARGS__);                     \
}G_STMT_END

#define zz_log1(...)                G_STMT_START{                               \
    zz_debug1("[%s:%d]: ", __FILE__, __LINE__); \
    zz_debug1(__VA_ARGS__);                     \
}G_STMT_END

#define zz_log2(...)                G_STMT_START{                               \
    zz_debug2("[%s:%d]: ", __FILE__, __LINE__); \
    zz_debug2(__VA_ARGS__);                     \
}G_STMT_END

#define zz_log3(...)                G_STMT_START{                               \
    zz_debug3("[%s:%d]: ", __FILE__, __LINE__); \
    zz_debug3(__VA_ARGS__);                     \
}G_STMT_END

#define zz_log4(...)                G_STMT_START{                               \
    zz_debug4("[%s:%d]: ", __FILE__, __LINE__); \
    zz_debug4(__VA_ARGS__);                     \
}G_STMT_END

typedef enum
{
	ZZ_LOG_LEVEL_DEBUG1 = 1 << (G_LOG_LEVEL_USER_SHIFT),
	ZZ_LOG_LEVEL_DEBUG2 = 1 << (G_LOG_LEVEL_USER_SHIFT + 1),
	ZZ_LOG_LEVEL_DEBUG3 = 1 << (G_LOG_LEVEL_USER_SHIFT + 2),
	ZZ_LOG_LEVEL_DEBUG4 = 1 << (G_LOG_LEVEL_USER_SHIFT + 3),
	ZZ_LOG_LEVEL_DEBUG  = (ZZ_LOG_LEVEL_DEBUG1 | ZZ_LOG_LEVEL_DEBUG2 |
			       ZZ_LOG_LEVEL_DEBUG3 | ZZ_LOG_LEVEL_DEBUG4),
	/* These are inappropriate but do the job.  */
	ZZ_LOG_LEVEL_NET_IN  = 1 << (G_LOG_LEVEL_USER_SHIFT + 4),
	ZZ_LOG_LEVEL_NET_OUT = 1 << (G_LOG_LEVEL_USER_SHIFT + 5),
	ZZ_LOG_LEVEL_NET     = (ZZ_LOG_LEVEL_NET_IN | ZZ_LOG_LEVEL_NET_OUT)
} RRLogLevelFlags;


#ifndef ZZ_LOG_DOMAIN
#define ZZ_LOG_DOMAIN "RR"
#endif


#ifdef G_HAVE_ISO_VARARGS

#ifdef ZZ_NO_DEBUG
#define zz_debug(...)
#define zz_debug1(...)
#define zz_debug2(...)
#define zz_debug3(...)
#define zz_debug4(...)
#else
#define zz_debug(...) \
 g_log (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG1, __VA_ARGS__)
#define zz_debug1(...) \
 g_log (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG1, __VA_ARGS__)
#define zz_debug2(...) \
 g_log (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG2, __VA_ARGS__)
#define zz_debug3(...) \
 g_log (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG3, __VA_ARGS__)
#define zz_debug4(...) \
 g_log (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG4, __VA_ARGS__)
#endif


#elif defined(G_HAVE_GNUC_VARARGS)

#ifdef RR_NO_DEBUG
#define zz_debug(fmt...)
#define zz_debug1(fmt...)
#define zz_debug2(fmt...)
#define zz_debug3(fmt...)
#define zz_debug4(fmt...)
#else
#define zz_debug(fmt...) \
 g_log (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG1, fmt)
#define zz_debug1(fmt...) \
 g_log (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG1, fmt)
#define zz_debug2(fmt...) \
 g_log (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG2, fmt)
#define zz_debug3(fmt...) \
 g_log (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG3, fmt)
#define zz_debug4(fmt...) \
 g_log (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG4, fmt)
#endif


#else /* No VARARGS at all */


#ifdef RR_NO_DEBUG
static void zz_debug  (const gchar *format, ...) {};
static void zz_debug1 (const gchar *format, ...) {};
static void zz_debug2 (const gchar *format, ...) {};
static void zz_debug3 (const gchar *format, ...) {};
static void zz_debug4 (const gchar *format, ...) {};
#else

static void
zz_debug (const gchar *format, ...)
{
  va_list args;
  va_start (args, format);
  g_logv (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG1, format, args);
  va_end (args);
}

static void
zz_debug1 (const gchar *format, ...)
{
  va_list args;
  va_start (args, format);
  g_logv (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG1, format, args);
  va_end (args);
}

static void
zz_debug2 (const gchar *format, ...)
{
  va_list args;
  va_start (args, format);
  g_logv (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG2, format, args);
  va_end (args);
}

static void
zz_debug3 (const gchar *format, ...)
{
  va_list args;
  va_start (args, format);
  g_logv (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG3, format, args);
  va_end (args);
}

static void
zz_debug4 (const gchar *format, ...)
{
  va_list args;
  va_start (args, format);
  g_logv (ZZ_LOG_DOMAIN, ZZ_LOG_LEVEL_DEBUG4, format, args);
  va_end (args);
}
#endif


#endif /* VARARGS */


void zz_debug_init (void);

void zz_debug_exit (void);


#ifndef zz_debug_NET_ENABLE
#define zz_debug_net_log_transfer(a,b,c)
#else
void zz_debug_net_log_transfer (const void *data, size_t size, gboolean is_read);
#endif


#endif /* __zz_debug_-H__ */

