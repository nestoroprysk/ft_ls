#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <assert.h>

void add_string(t_string_list* string_list_ptr, const char* data, size_t len)
{
	assert(string_list_ptr->len != MAX_STRING_LIST_ELEMS);
	assert(string_list_ptr);
	string_list_ptr->elems[string_list_ptr->len].len = len;
	string_list_ptr->elems[string_list_ptr->len].data = ft_strdup(data);
	++string_list_ptr->len;
}
