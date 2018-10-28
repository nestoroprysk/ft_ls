#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void delete_file_list(t_file_list** file_list_ptr)
{
	assert(file_list_ptr && *file_list_ptr);
	t_file_list* file_list = *file_list_ptr;
	t_file_node* it = file_list->head;
	while (it)
	{
		t_file_node* next = it->next;
		delete_file_node(it);
		it = next;
	}
	free(file_list->name);
	free(file_list);
	*file_list_ptr = NULL;
}

static void delete_display_buff(t_string_list* display_buff);
static void delete_file_node_info(t_file_node_info* info);

void delete_file_node(t_file_node* n)
{
	delete_display_buff(&n->display_buff);
	delete_file_node_info(&n->info);
	free(n);
}

static void delete_display_buff(t_string_list* display_buff)
{
	for (size_t i = 0; i < MAX_STRING_LIST_ELEMS; ++i)
		free(display_buff->elems[i].data);
}

static void delete_file_node_info(t_file_node_info* info)
{
	free(info->name.data);
	free(info->path.data);
	free(info->full_name.data);
}
