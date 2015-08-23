#ifndef _DEBUG_H__
#define _DEBUG_H__

#include <stdio.h>

#include <glib.h>

#if defined(ZZ_NO_DEBUG)
#define DBG(...)   G_STMT_START{ (void)0; }G_STMT_END
#define TRACE(...) G_STMT_START{ (void)0; }G_STMT_END
#else

#if (defined(G_HAVE_ISO_VARARGS) || defined(G_HAVE_GNUC_VARARGS))

#if defined(__NetBSD__) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
#define __DBG_FUNC__    __func__
#elif defined(__GNUC__) && __GNUC__ >= 3
#define __DBG_FUNC__	__FUNCTION__
#else
#define __DBG_FUNC__    "??"
#endif

#if defined(G_HAVE_ISO_VARARGS)

#define DBG(...)                G_STMT_START{                               \
    fprintf(stderr, "DBG[%s:%d] %s(): ", __FILE__, __LINE__, __DBG_FUNC__); \
    fprintf(stderr, __VA_ARGS__);                                           \
    fprintf(stderr, "\n");                                                  \
}G_STMT_END

#elif defined(G_HAVE_GNUC_VARARGS)

#define DBG(fmt, args...)       G_STMT_START{                               \
{                                                                           \
    fprintf(stderr, "DBG[%s:%d] %s(): ", __FILE__, __LINE__, __DBG_FUNC__); \
    fprintf(stderr, fmt, ##args);                                           \
    fprintf(stderr, "\n");                                                  \
}G_STMT_END

#endif

#if defined(DEBUG_TRACE) && (DEBUG_TRACE > 0)

#if defined(G_HAVE_ISO_VARARGS)

#define TRACE(...)              G_STMT_START{                               \
    fprintf(stderr, "TRACE[%s:%d] %s(): ",__FILE__,__LINE__,__DBG_FUNC__);  \
    fprintf(stderr, __VA_ARGS__);                                           \
    fprintf(stderr, "\n");                                                  \
}G_STMT_END

#elif defined (G_HAVE_GNUC_VARARGS)

#define TRACE(fmt, args...)     G_STMT_START{                               \
{                                                                           \
    fprintf(stderr, "TRACE[%s:%d] %s(): ",__FILE__,__LINE__,__DBG_FUNC__);  \
    fprintf(stderr, fmt, ##args);                                           \
    fprintf(stderr, "\n");                                                  \
}G_STMT_END

#endif

#else /* !defined(DEBUG_TRACE) || DEBUG_TRACE <= 0 */

#define TRACE(...) G_STMT_START{ (void)0; }G_STMT_END

#endif

#else /*defined(G_HAVE_ISO_VARARGS) || defined(G_HAVE_GNUC_VARARGS)*/

#define DBG(...)   G_STMT_START{ (void)0; }G_STMT_END
#define TRACE(...) G_STMT_START{ (void)0; }G_STMT_END

#endif /*defined(G_HAVE_ISO_VARARGS) || defined(G_HAVE_GNUC_VARARGS)*/

#endif/* !defined(ZZ_NO_DEBUG) */
#endif	/* !_DEBUG_H__ */
