#include <liblogic.h>
#include <libft.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void fill_file_info(t_file_node* file, t_flags* flags)
{
	assert(file);
	assert(flags);
	struct stat s;
	file->info.is_valid = stat(file->info.name, &s) == 0;
	if (!file->info.is_valid) return;
	fill_file_type(file, &s);
}

void pop_front_file(t_file_node** head)
{
	assert(head && *head);
	t_file_node* temp = *head;
	*head = temp->next;
	free(temp);
}
