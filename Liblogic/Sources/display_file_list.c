#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <assert.h>

void display_file_list(t_file_list* file_list)
{
	static size_t i = 0;
	assert(file_list);
	printf("[%zu]  ", i++);
	for (t_file_node* it = file_list->head; it; it = it->next)
	{
		display_file_info(it);
		if (it->nested_file_list)
			display_file_list(it->nested_file_list);
	}
}
