#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <assert.h>

void append_file_node(t_file_node** head_ptr, const char* file_name);
t_file_node* new_file_node(const char* file_name);
void copy_file_name(char* dst, const char* src);
t_file_node* get_last_file_node(t_file_node* head);

t_file_node* parse_files_to_display(int argc, const char** argv)
{
	t_file_node* head = NULL;
	for (int i = 1; i < argc; ++i)
		if (!is_flag_argv(argv[i]))
			append_file_node(&head, argv[i]);
	if (!head) append_file_node(&head, ".");
	return head;
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
	copy_file_name(result->info.name, file_name);
	result->next = NULL;
	result->info.is_valid = true;
	result->info.type = other_file_type;
	return result;
}

void copy_file_name(char* dst, const char* src)
{
	assert(dst && src);
	ft_bzero(dst, MAX_FILE_NAME_LEN + 1);
	size_t file_name_len = ft_strlen(src);
	ft_strncpy(dst, src, (file_name_len > MAX_FILE_NAME_LEN) ?
		MAX_FILE_NAME_LEN : file_name_len);
}

t_file_node* get_last_file_node(t_file_node* head)
{
	assert(head);
	t_file_node* it = head;
	while (it && it->next)
		it = it->next;
	return it;
}
