#include <liblogic.h>
#include <libft.h>
#include <assert.h>

#define NB_COMP_STATES 3

enum comparison_type { comp_smaller, comp_equal, comp_bigger };

static void sort(t_file_node** head_ptr, t_file_node** last_ptr, comparator_type f);
static void swap_neighbours(t_file_node** left_ptr, t_file_node** right_ptr);
static enum comparison_type compare(const t_file_node* a,
	const t_file_node* b, comparator_type f);

void sort_file_list(t_file_list* dir_files, comparator_type f)
{
	assert(dir_files && dir_files->len > 1 && f);
	sort(&dir_files->head, &dir_files->last, f);
}

static void sort(t_file_node** head_ptr, t_file_node** last_ptr, comparator_type f)
{
	if (!(head_ptr && last_ptr && *head_ptr && *last_ptr && f)) return;
	if (*head_ptr == *last_ptr) return;
	if ((*head_ptr)->next == *last_ptr)
	{
		if (f(*last_ptr, *head_ptr))
			swap_neighbours(head_ptr, last_ptr);
		return;
	}
	t_file_node* mid = partition(head_ptr, last_ptr, f);
	assert(mid && head_ptr && last_ptr);
	sort(head_ptr, &mid, f);
	sort(&mid->next, last_ptr, f);
}

t_file_node* partition(t_file_node** head_ptr, t_file_node** last_ptr, comparator_type f)
{
	assert(head_ptr && last_ptr && *head_ptr && *last_ptr && f);
	t_file_node* head_prev = (*head_ptr)->prev;
	t_file_node* last_next = (*last_ptr)->next;
	t_file_node* pivot = *head_ptr;
	t_file_list smaller = init_file_list();
	t_file_list equal = init_file_list();
	t_file_list bigger = init_file_list();
	t_file_list* data_lists[NB_COMP_STATES] = { &smaller, &equal, &bigger };
	t_file_node* it = pivot->next;
	while (it != *last_ptr)
	{
		t_file_node* temp = it;
		it = it->next;
		append_file_node(data_lists[compare(temp, pivot, f)], temp);
	}
	append_file_node(data_lists[compare(it, pivot, f)], it);
	append_file_node(&smaller, pivot);
	t_file_list result = merge_file_lists(&smaller, &equal);
	result = merge_file_lists(&result, &bigger);
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

static enum comparison_type compare(const t_file_node* a,
	const t_file_node* b, comparator_type f)
{
	const bool a_is_smaller = f(a, b);
	const bool b_is_smaller = f(b, a);
	if (a_is_smaller) return comp_smaller;
	else if (b_is_smaller) return comp_bigger;
	else return comp_equal;
}

static void swap_neighbours(t_file_node** left_ptr, t_file_node** right_ptr)
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
