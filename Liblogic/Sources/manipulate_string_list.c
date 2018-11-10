#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <assert.h>

void add_string(t_string_list* string_list_ptr, const char* data, size_t len)
{
	assert(string_list_ptr);
	assert(string_list_ptr->len != MAX_STRING_LIST_ELEMS);
	string_list_ptr->elems[string_list_ptr->len].len = len;
	string_list_ptr->elems[string_list_ptr->len].data = ft_strdup(data);
	++string_list_ptr->len;
}

void concat_to_last_string(t_string_list* string_list_ptr, const char* data, size_t len)
{
	assert(string_list_ptr);
	assert(string_list_ptr->len != 0);
	char* old = string_list_ptr->elems[string_list_ptr->len - 1].data;
	string_list_ptr->elems[string_list_ptr->len - 1].data = ft_strjoin(old, data);
	ft_strdel(&old);
	string_list_ptr->elems[string_list_ptr->len - 1].len += len;
}
