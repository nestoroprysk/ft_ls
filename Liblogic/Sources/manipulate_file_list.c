#include <liblogic.h>
#include <libft.h>
#include <assert.h>
#include <stdlib.h>

void pop_front_file(t_file_node** head)
{
	assert(head && *head);
	t_file_node* temp = *head;
	*head = temp->next;
	free(temp);
}

void append_file_node(t_file_node** head_ptr, const char* file_name)
{
	assert(head_ptr && file_name);
	t_file_node* new_node = new_file_node(file_name);
	if (!(*head_ptr))
		*head_ptr = new_node;
	else
		get_last_file_node(*head_ptr)->next = new_node;
}

t_file_node* new_file_node(const char* file_name)
{
	assert(file_name);
	t_file_node* result = (t_file_node*)malloc(sizeof(t_file_node));
	result->next = NULL;
	size_t file_name_len = ft_strlen(file_name);
	assert(file_name_len <= MAX_FILE_NAME_LEN);
	ft_strncpy(result->info.name, file_name, file_name_len + 1);
	result->info.type = define_file_type(file_name);
	result->info.is_valid = true;
	return result;
}

t_file_node* get_last_file_node(t_file_node* head)
{
	assert(head);
	t_file_node* it = head;
	while (it && it->next)
		it = it->next;
	return it;
}
