#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <assert.h>

void append_string_node(t_string_list* string_list_ptr, t_string* new_node)
{
	assert(string_list_ptr->len != MAX_STRING_LIST_ELEMS);
	assert(string_list_ptr && new_node);
	string_list_ptr->elems[string_list_ptr->len].len = new_node->len;
	string_list_ptr->elems[string_list_ptr->len].data = new_node->data;
	++string_list_ptr->len;
	free(new_node);
}

t_string* new_string_node(const char* data, size_t len)
{
	t_string* result =
		(t_string*)ft_memalloc(sizeof(t_string));
	assert(result);
	assert(result->data = ft_strdup(data));
	result->len = len;
	return result;
}
