#include <liblogic.h>
#include <libft.h>
#include <assert.h>

t_file_node* partition(t_file_node** head, t_file_node** last);
void sort(t_file_node** head_ptr, t_file_node** last_ptr);
void swap(t_file_node** a, t_file_node** b);

void sort_file_list(t_file_list* dir_files)
{
	assert(dir_files && dir_files->len > 1);
	sort(&dir_files->head, &dir_files->last);
}

void sort(t_file_node** head_ptr, t_file_node** last_ptr)
{
	assert(head_ptr && last_ptr && *head_ptr && *last_ptr);
	t_file_node* mid = partition(head_ptr, last_ptr);
	assert(mid);	
}

t_file_node* partition(t_file_node** head_ptr, t_file_node** last_ptr)
{
	assert(head_ptr && last_ptr && *head_ptr && *last_ptr);
	t_file_node* pivot = *head_ptr;
	t_file_node* it = pivot->next;
	t_file_node* first_open = it;
	while (it != *last_ptr)
	{
		if (ft_strcmp(it->info.name, pivot->info.name) < 0)
			swap_nodes(&it, &first_open);
		it = it->next;
	}
	swap_nodes(&pivot, &first_open);
	return *head_ptr;
}

void swap_nodes(t_file_node** a_ptr, t_file_node** b_ptr)
{
	assert(a_ptr && b_ptr && *a_ptr && *b_ptr);
	t_file_node* a = *a_ptr;
	t_file_node* b = *b_ptr;
	t_file_node* a_prev = a->prev;
	t_file_node* b_prev = b->prev;
	t_file_node* a_next = a->next;
	t_file_node* b_next = b->next;

	if (a_prev) a_prev->next = b;
	if (b_prev) b_prev->next = a;
	if (a_next) a_next->prev = b;
	if (b_next) b_next->prev = a;

	a->prev = b_prev;
	a->next = b_next;
	b->prev = a_prev;
	b->next = a_next;

	swap(a_ptr, b_ptr);
}

void swap(t_file_node** a, t_file_node** b)
{
	assert(a && b && *a && *b);
	t_file_node* temp = *a;
	*a = *b;
	*b = temp;
}
