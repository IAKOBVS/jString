#ifndef JSTR_H_DEF
#define JSTR_H_DEF

#include <stdlib.h>
#include "/home/james/c/vargc.h"

#define JSTR_MIN_SIZE 8
#define MAX(a,b) ((a)>(b)?(a):(b))

#define jstrNew(JSTR, CONST_STRING) \
	do { \
		JSTR.len = strlen(CONST_STRING); \
		JSTR.size = MAX(JSTR.len, JSTR_MIN_SIZE); \
		if (unlikely(!(JSTR.data = malloc(JSTR.size)))) \
			{ perror(""); return EXIT_FAILURE; } \
		memcpy(JSTR.data, CONST_STRING, JSTR.len); \
	} while (0)

#define jstrInit(JSTR) \
	Jstr JSTR = { \
		.size = 0, \
		.len = 0 \
	}

#define jstrDelete(JSTR) \
	do { \
		if (JSTR.size) \
			free(JSTR.data); \
		JSTR.size = 0; \
	} while (0)
#define jstrDeletePtr(JSTR) \
	do { \
		if (JSTR->size) \
			free(JSTR->str); \
		JSTR->size = 0; \
	} while (0)

#define jstrPr(JSTR) printf("string: %s: \nsize is %zu\nlen is %zu", JSTR.data, JSTR.size, JSTR.len)

#define jstrMinimize(JARR) \
	JARR.data = realloc(JARR.data, JARR.len)

#define jstrReserve(JARR, ALLOC_SIZE) \
	do { \
		if (unlikely(!(JARR.data = malloc(ALLOC_SIZE)))) \
			{ perror(""); return EXIT_FAILURE; } \
		JARR.size = ALLOC_SIZE; \
	} while (0)

#define jstrResize(ALLOC_SIZE) \
	do { \
		if (unlikely(!(JARR.data = realloc(ALLOC_SIZE)))) \
			{ perror(""); return EXIT_FAILURE; } \
		JARR.size = ALLOC_SIZE; \
		JARR.len = ALLOC_SIZE; \
	} while (0)

typedef struct Jstr {
	char *data;
	size_t size;
	size_t len;
} Jstr;

int private_jstrCat(struct Jstr *dest, ...);
#define jstrCat(JSTR, ...) \
	private_jstrCat(&JSTR, __VA_ARGS__, NULL)

int private_jstrPushStr(Jstr *dest, char *src, size_t srcLen);
#define jstrPushStr(JSTR_DEST, STR_SRC) \
	private_jstrPush(&JSTR_DEST, STR_SRC)
#define jstrPushJstr(JSTR_DEST, JSTR_SRC) \
	private_jstrPush(&JSTR_DEST, &JSTR_SRC, JSTR->len)

int isJstr(Jstr *structPtr);

#undef MAX

#endif
