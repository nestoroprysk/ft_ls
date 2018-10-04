#include <liblogic.h>
#include <libft.h>
#include <assert.h>

t_file_node* partition(t_file_node** head, t_file_node** last);
void sort(t_file_node** head_ptr, t_file_node** last_ptr);
void swap_nodes(t_file_node** a, t_file_node** b);
void swap(t_file_node** a, t_file_node** b);

void sort_file_list(t_file_list* dir_files)
{
	assert(dir_files);
	sort(&dir_files->head, &dir_files->last);
}

void sort(t_file_node** head_ptr, t_file_node** last_ptr)
{
	t_file_node prev_head;
	t_file_node next_last;
	(*head_ptr)->prev = &prev_head;
	prev_head.next = *head_ptr;
	(*last_ptr)->next = &next_last;
	next_last.prev = *last_ptr;

	t_file_node* mid = partition(head_ptr, last_ptr);
	assert(mid);

	*head_ptr = prev_head.next;
	(*head_ptr)->prev = NULL;
	*last_ptr = next_last.prev;
	(*last_ptr)->next = NULL;
}

t_file_node* partition(t_file_node** head_ptr, t_file_node** last_ptr)
{
	assert(head_ptr && last_ptr && *head_ptr && *last_ptr);
	swap_nodes(head_ptr, last_ptr);
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
