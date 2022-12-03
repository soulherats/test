/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.in by autoheader.  */

/* Define if .gnu.warning accepts long strings. */
/* #undef HAS_GNU_WARNING_LONG */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 0

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 0

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 0

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 0

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 0

/* Define to 1 if your system has a GNU libc compatible `malloc' function, and
   to 0 otherwise. */
#define HAVE_MALLOC 0

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 0

/* Define to 1 if you have the `open' function. */
#define HAVE_OPEN 0

/* Define to 1 if your system has a GNU libc compatible `realloc' function,
   and to 0 otherwise. */
#define HAVE_REALLOC 0

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 0

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 0

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 0

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 0

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 0

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 0

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 0

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 0

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 0

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 0

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 0

/* Define to 1 if you have the `strndup' function. */
#define HAVE_STRNDUP 0

/* Define to 1 if you have the <syslog.h> header file. */
#define HAVE_SYSLOG_H 0

/* Define to 1 if you have the <sys/cdefs.h> header file. */
#define HAVE_SYS_CDEFS_H 0

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 0

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 0

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 0

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 0

/* Define to 1 if you have the `vasprintf' function. */
#define HAVE_VASPRINTF 0

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 0

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 0

/* Define to 1 if you have the `vsyslog' function. */
#define HAVE_VSYSLOG 0

/* Public define for json_inttypes.h */
#define JSON_C_HAVE_INTTYPES_H 0

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "json-c"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "json-c@googlegroups.com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "json-c"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "json-c 0.11"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "json-c"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.11"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "0.11"

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to rpl_malloc if the replacement function should be used. */
/* #undef malloc */

/* Define to rpl_realloc if the replacement function should be used. */
/* #undef realloc */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */


#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/ctype.h>

extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *realloc(void *ptr, size_t size);
extern void *calloc(size_t n, size_t size);
extern char * strdup(const char *str);
extern char * strdup_reverse(const char *str);

#define INT32_MAX		((int)(~0U>>1))
#define INT32_MIN		(-INT32_MAX - 1)
#define INT64_MAX		((long long)(~0ULL>>1))
#define INT64_MIN		(-INT64_MAX - 1)
#define PRId64			"lld"
#define	SCNd64			"lld"


