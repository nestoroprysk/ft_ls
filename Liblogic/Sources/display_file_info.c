#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <assert.h>

static t_file_node* display(t_file_node* n);

void display_file_info(t_file_node* n)
{
	static map_node_type f[EITHER_OR] =
		{ display, foo };
	assert(n);
	f[n->info.is_hidden](n);
}

static t_file_node* display(t_file_node* n)
{
	assert(n);
	t_string_list* list_ptr = &n->display_buff;
	for (size_t i = 0; i < list_ptr->len; ++i)
	{
		printf("%s", list_ptr->elems[i].data);
		if (i != list_ptr->len - 1)
			printf(" ");
	}
	printf("\n");
	return n;
}
