#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "jstr.h"

#define MIN_SIZE 8

int jstr_cat(Jstr *dest, ...)
{
	va_list ap;
	va_start(ap, dest);
	int argLen=0;
	for (;;) {
		char *argvStr = va_arg(ap, char*);
		if (!argvStr[0])
			break;
		argLen += strlen(argvStr);
	}
	va_end(ap);
	int i = dest->len;
	dest->len += argLen;
	if (dest->size < 2 * dest->len) {
		if (!(dest->str = realloc(dest->str,
			(dest->size *= 2 > 2 * dest->len)
			? dest->size
			: 2 * dest->len)))
			goto ERR;
	}
	/* while (dest->str[i]) */
	/* 	++i; */
	va_start(ap, dest);
	for (;;) {
		char *argvStr = va_arg(ap, char*);
		if (!argvStr[0])
			break;
		do {
			(dest->str)[i++] = *argvStr++;
		} while (*argvStr);
	}
	va_end(ap);
	(dest->str)[dest->len + 1] = '\0';
	return dest->size;

ERR:
	perror("int jstrcat(char *dest->string, ...): ");
	return 0;
}

int jstradd(Jstr *dest, Jstr *src)
{
	if (dest->size < 2 * dest->len) {
		if (!(dest->str = realloc(dest->str,
			(dest->size *= 2 > 2 * dest->len)
			? dest->size
			: 2 * dest->len)))
			goto ERR;
	}
	int i = dest->len;
	int j = 0;
	while (dest->str[i])
		++i;
	do {
		(dest->str)[i++] = (src->str)[j++];
	} while (j < src->len);
	dest->len += src->len;
	(dest->str)[dest->len + 1] = '\0';
	return dest->size;
ERR:
	perror("int jstradd(Jstr *dest, Jstr *src): ");
	return 0;
}

int stradd(Jstr *dest, char *src)
{
	/* *dest->size must be initialized with 0 if empty */
	size_t srcLen;
	if (!(srcLen = strlen(src)))
		goto ERR;
	if (dest->size < 2 * dest->len) {
		if (!(dest->str = realloc(dest->str,
			dest->size
			= (dest->size *= 2 > 2 * dest->len)
			? dest->size
			: 2 * dest->len)))
			goto ERR;
	}
	int i = dest->len;
	int j = 0;
	/* while (dest->str[i]) */
	/* 	++i; */
	do {
		(dest->str)[i++] = (src)[j++];
	} while (j < srcLen);
	dest->len += srcLen;
	(dest->str)[dest->len + 1] = '\0';
	return dest->size;

ERR:
	perror("int stradd(Jstr *dest, char *src): ");
	return 0;
}

int aredigits(char* src)
{
	while (*src)
		switch (*src++){
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			continue;
		default:
			return 0;
		}
	return 1;
}

int isjstr(Jstr *structPtr)
{
	if (!*((unsigned char *)&*structPtr))
		return 0;
	return 1;
}
