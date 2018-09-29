#include <library.h>
#include <stdlib.h>

char* ft_strnew(size_t size)
{
	char* result = (char*)malloc(sizeof(char) * (size + 1));
	if (!result) return NULL;
	size_t i = 0;
	while (i <= size)
		result[i] = '\0';
	return result;
}
