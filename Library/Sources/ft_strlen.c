#include <library.h>

size_t ft_strlen(const char* str)
{
	size_t i = 0;
	if (!str) return 0;
	while (str[i])
		++i;
	return i;
}
