#include <liblogic.h>
#include <libft.h>
#include <assert.h>

t_file_node* partition(t_file_node** head, t_file_node** last);
void sort(t_file_node** head_ptr, t_file_node** last_ptr);
void swap_nodes(t_file_node** a, t_file_node** b);
void swap(t_file_node** a, t_file_node** b);

void sort_file_list(t_file_list* dir_files)
{
	assert(dir_files && dir_files->len > 1);
	t_file_node prev_head;
	t_file_node next_last;
	dir_files->head->prev = &prev_head;
	prev_head.next = dir_files->head;
	dir_files->last->next = &next_last;
	next_last.prev = dir_files->last;
	sort(&dir_files->head, &dir_files->last);
	dir_files->head = prev_head.next;
	dir_files->head->prev = NULL;
	dir_files->last = next_last.prev;
	dir_files->last->next = NULL;
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

t_file_node** take_next(t_file_node** a);
t_file_node** take_prev(t_file_node** a);

void swap_nodes(t_file_node** a, t_file_node** b)
{
	assert(a && b && *a && *b);
	swap(take_next(a), take_next(b));
	swap(take_next(&(*a)->prev), take_next(&(*b)->prev));
	swap(take_prev(a), take_prev(b));
	swap(take_prev(&(*a)->next), take_prev(&(*b)->next));
}

t_file_node** take_next(t_file_node** a)
{
	assert(a);
	return &(*a)->next;
}

t_file_node** take_prev(t_file_node** a)
{
	assert(a);
	return &(*a)->prev;
}

void swap(t_file_node** a, t_file_node** b)
{
	assert(a && b && *a && *b);
	t_file_node* temp = *a;
	*a = *b;
	*b = temp;
}
