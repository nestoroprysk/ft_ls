#include <liblogic.h>
#include <libft.h>
#include <assert.h>

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
	if (*head_ptr == *last_ptr) return;
	if ((*head_ptr)->next == *last_ptr)
	{
		if (is_bigger(*head_ptr, *last_ptr))
			swap_nodes(head_ptr, last_ptr);
		return;
	}
	t_file_node* mid = partition(head_ptr, last_ptr);
	assert(mid && head_ptr && last_ptr);
	sort(head_ptr, &mid);
	sort(&mid->next, last_ptr);
}

t_file_node* partition(t_file_node** head_ptr, t_file_node** last_ptr)
{
	assert(head_ptr && last_ptr && *head_ptr && *last_ptr);
	t_file_node* head_prev = (*head_ptr)->prev;
	t_file_node* last_next = (*last_ptr)->next;
	t_file_node* pivot = *head_ptr;
	t_file_list smaller = init_file_list();
	t_file_list bigger = init_file_list();
	t_file_node* it = pivot->next;
	while (it != *last_ptr)
	{
		t_file_node* temp = it;
		it = it->next;
		append_file_node(!is_bigger(temp, pivot) ? &smaller : &bigger, temp);
	}
	append_file_node(!is_bigger(it, pivot) ? &smaller : &bigger, it);
	append_file_node(&smaller, pivot);
	t_file_list result = merge_file_lists(&smaller, &bigger);
	if (head_prev)
	{
		result.head->prev = head_prev;
		head_prev->next = result.head;
	}
	if (last_next)
	{
		result.last->next = last_next;
		last_next->prev = result.last;
	}
	*head_ptr = result.head;
	*last_ptr = result.last;
	return pivot;
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
	if (a->next == b)
	{
		if (a_prev) a_prev->next = b;
		if (b_next) b_next->prev = a;
		b->next = a;
		a->next = b_next;
		a->prev = b;
		b->prev = a_prev;
		*a_ptr = b;
		*b_ptr = a;
		return;
	}
	if (a_prev) a_prev->next = b;
	if (b_prev) b_prev->next = a;
	if (a_next) a_next->prev = b;
	if (b_next) b_next->prev = a;
	swap(&a->next, &b->next);
	swap(&a->prev, &b->prev);
	swap(a_ptr, b_ptr);
}

void swap(t_file_node** a, t_file_node** b)
{
	assert(a && b);
	t_file_node* temp = *a;
	*a = *b;
	*b = temp;
}
