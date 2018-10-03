#include <liblogic.h>
#include <libft.h>
#include <assert.h>
#include <stdlib.h>

void pop_front_file(t_file_list* files_ptr)
{
	assert(files_ptr && files_ptr->head);
	t_file_node* temp = files_ptr->head;
	files_ptr->head = temp->next;
	free(temp);
	--files_ptr->len;
}

void append_file_node(t_file_list* files_ptr, t_file_node* newNode)
{
	assert(files_ptr && newNode);
	if (files_ptr->len == 0)
	{
		files_ptr->head = newNode;
		files_ptr->last = newNode;
	}
	else
	{
		files_ptr->last->next = newNode;
		files_ptr->last = newNode;
	}
	++files_ptr->len;
}

t_file_node* new_file_node(const char* file_name)
{
	assert(file_name);
	t_file_node* result = (t_file_node*)ft_memalloc(sizeof(t_file_node));
	size_t file_name_len = ft_strlen(file_name);
	assert(file_name_len <= MAX_FILE_NAME_LEN);
	ft_strncpy(result->info.name, file_name, file_name_len + 1);
	result->info.type = define_file_type(file_name);
	result->info.is_valid = true;
	return result;
}

bool valid_files(t_file_list* files_ptr)
{
	for (t_file_node* it = files_ptr->head; it; it = it->next)
		if (!it->info.is_valid)
			return false;
	return true;
}
