#ifndef JSTR_H_DEF
#define JSTR_H_DEF

#include <stddef.h>
#include "/home/james/c/vargc.h"

#if defined(__PRETTY_FUNCTION__)
	#define CURR_FUNC __PRETTY_FUNCTION__
#elif defined(__FUNCTION__)
	#define CURR_FUNC __FUNCTION__
#elif defined(__func__)
	#define CURR_FUNC __func__
#else
	#define CURR_FUNC ""
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define ALWAYS_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
    #define ALWAYS_INLINE __forceinline inline
#else
    #define ALWAYS_INLINE inline
#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
# define RESTRICT restrict
#elif defined(__GNUC__) || defined(__clang__)
# define RESTRICT __restrict__
#elif defined(_MSC_VER)
# define RESTRICT __restrict
#else
# define RESTRICT
#endif

#if (defined(__GNUC__) && (__GNUC__ >= 3)) || (defined(__clang__) && __has_builtin(__builtin_expect))
  #define likely(x) __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else
  #define likely(x) (x)
  #define unlikely(x) (x)
#endif

#define JSTR_MIN_SIZE 8
#define MAX(a,b) ((a)>(b)?(a):(b))

typedef struct Jstring {
	char *data;
	size_t capacity;
	size_t size; 
} Jstring;

int private_jstrCat(Jstring *RESTRICT dest, ...);
#define jstrCat(JSTR, ...) private_jstrCat(JSTR, __VA_ARGS__, NULL)

void jstrInit(Jstring *RESTRICT dest);
void jstrDeleteFast(Jstring *RESTRICT dest);
void jstrDelete(Jstring *RESTRICT dest);
int jstrNew(Jstring *RESTRICT dest, const char *RESTRICT src, const size_t srcLen);
#define jstrNewAuto(dest, src) jstrNew(dest, src, strlen(src))
int jstrPushback(Jstring *dest, const char c);
void jstrPopback(Jstring *RESTRICT dest);
int jstrAppend(Jstring *dest, const char *RESTRICT src, const size_t srcLen);
#define jstrAppendAuto(dest, src) jstrAppend(dest, src, strlen(src))
/* swaps dest with src and updates the Jstring struct members */
void jstrSwap(Jstring *RESTRICT dest, Jstring *RESTRICT src);
void jstrSwapStr(Jstring *RESTRICT dest, char **RESTRICT src, size_t *srcLen, size_t *srcSize);
int jstrShrink(Jstring *RESTRICT dest);
int jstrReserve(Jstring *RESTRICT dest, size_t size);
/* replaces dest->data with dest and reallocs if needed */
int jstrReplace(Jstring *RESTRICT dest, char *RESTRICT src, const size_t srcLen);
/* compares two Jstr, and if equal, returns 0 */
int jstrCmp(Jstring *RESTRICT dest, Jstring *RESTRICT src);

#undef ALWAYS_INLINE
#undef RESTRICT

#endif
