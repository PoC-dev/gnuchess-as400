/*
 * Define if you have the `alarm' function.
 */
#undef HAVE_ALARM

/*
 * Define if you have the <errno.h> header file.
 */
#define HAVE_ERRNO_H

/*
 * Define if you have the <fcntl.h> header file.
 */
#define HAVE_FCNTL_H

/*
 * Define if you have the `gettimeofday' function.
 */
#undef HAVE_GETTIMEOFDAY

/*
 * Define if you have the <inttypes.h> header file.
 */
#undef HAVE_INTTYPES_H

/*
 * Define if you have the `m' library (-lm).
 */
#define HAVE_LIBM

/*
 * Define if you have the `ncurses' library (-lncurses).
 */
#undef HAVE_LIBNCURSES

/*
 * Define if you have the `readline' library (-lreadline).
 */
#undef HAVE_LIBREADLINE

/*
 * Define if your system has a working `malloc' function.
 */
#define HAVE_MALLOC

/*
 * Define if you have the <memory.h> header file.
 */
#define HAVE_MEMORY_H

/*
 * Define if you have the `memset' function.
 */
#define HAVE_MEMSET

/*
 * Define if you have the <readline/history.h> header file.
 */
#undef HAVE_READLINE_HISTORY_H

/*
 * Define if you have the <readline/readline.h> header file.
 */
#undef HAVE_READLINE_READLINE_H

/*
 * Define if you have the <stdint.h> header file.
 */
#undef HAVE_STDINT_H

/*
 * Define if you have the <stdlib.h> header file.
 */
#define HAVE_STDLIB_H

/*
 * Define if you have the `strchr' function.
 */
#define HAVE_STRCHR

/*
 * Define if you have the `strcspn' function.
 */
#define HAVE_STRCSPN

/*
 * Define if you have the `strerror' function.
 */
#define HAVE_STRERROR

/*
 * Define if you have the <strings.h> header file.
 */
#undef HAVE_STRINGS_H

/*
 * Define if you have the <string.h> header file.
 */
#define HAVE_STRING_H

/*
 * Define if you have the `strstr' function.
 */
#define HAVE_STRSTR

/*
 * Define if you have the `strtol' function.
 */
#define HAVE_STRTOL

/*
 * Define if you have the `strtoul' function.
 */
#define HAVE_STRTOUL

/*
 * Define if you have the <sys/file.h> header file.
 */
#undef HAVE_SYS_FILE_H

/*
 * Define if you have the <sys/ioctl.h> header file.
 */
#undef HAVE_SYS_IOCTL_H

/*
 * Define if you have the <sys/stat.h> header file.
 */
#undef HAVE_SYS_STAT_H

/*
 * Define if you have the <sys/time.h> header file.
 */
#undef HAVE_SYS_TIME_H

/*
 * Define if you have the <sys/types.h> header file.
 */
#undef HAVE_SYS_TYPES_H

/*
 * Define if you have the <time.h> header file.
 */
#define HAVE_TIME_H

/*
 * Define if you have the <unistd.h> header file.
 */
#define HAVE_UNISTD_H

/*
 * Name of package
 */
#undef PACKAGE

/*
 * Define as the return type of signal handlers (`int' or `void').
 */
#define RETSIGTYPE int

/*
 * The size of a `long', as computed by sizeof.
 */
#define SIZEOF_LONG 32

/*
 * Define if you have the ANSI C header files.
 */
#define STDC_HEADERS

/*
 * Define if you can safely include both <sys/time.h> and <time.h>.
 */
#define TIME_WITH_SYS_TIME

/*
 * Define if your <sys/time.h> declares `struct tm'.
 */
#undef TM_IN_SYS_TIME

/*
 * Version number of package
 */
#define VERSION "5.05-poc"

/*
 * Define if your processor stores words with the most significant byte first
 * (like Motorola and SPARC, unlike Intel and VAX).
 */
#define WORDS_BIGENDIAN

/*
 * Define to empty if `const' does not conform to ANSI C.
 */
#undef const

/*
 * Define as `__inline' if that's what the C compiler calls it, or to nothing
 * if it is not supported.
 */
#undef inline

/*
 * Define to `unsigned' if <sys/types.h> does not define.
 */
#undef size_t

/*
 * Manually verified. A normal long int is 32 bits.
 */
typedef unsigned long long int uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;

/*
 * -----------------------------------------------------------------------------
 * vim: ft=c colorcolumn=81 autoindent shiftwidth=4 tabstop=4 expandtab
 */
