#include <liblogic.h>
#include <libft.h>
#include <assert.h>

void sort(t_file_node** head_ptr, t_file_node** last_ptr);
void swap_neighbours(t_file_node** left_ptr, t_file_node** right_ptr);

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
			swap_neighbours(head_ptr, last_ptr);
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

void swap_neighbours(t_file_node** left_ptr, t_file_node** right_ptr)
{
	assert(left_ptr && right_ptr && *left_ptr && *right_ptr &&
		(*left_ptr)->next == *right_ptr);
	t_file_node* a = *left_ptr;
	t_file_node* b = *right_ptr;
	t_file_node* a_prev = a->prev;
	t_file_node* b_next = b->next;
	if (a_prev) a_prev->next = b;
	if (b_next) b_next->prev = a;
	b->next = a;
	a->next = b_next;
	a->prev = b;
	b->prev = a_prev;
	*left_ptr = b;
	*right_ptr = a;
}
