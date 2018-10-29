#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <assert.h>

#define NB_COMPARATORS 2

static void display_dir_total(const t_file_list* file_list);
static void call_flag_funcs(t_file_node* n, const t_flags* flags);
static void calculate_max_elems_len(t_file_list* file_list);
static void sort(t_file_list* n, const t_flags* flags);

void display_file_list(t_file_list* file_list, const t_flags* flags)
{
	static bool first_entry = true;
	assert(file_list && flags);
	if (first_entry)
		first_entry = false;
	else if (file_list->len)
		printf("\n%s:\n", file_list->name);
	if (flags->state[flag_l])
		display_dir_total(file_list);
	sort(file_list, flags);
	for (t_file_node* it = file_list->head; it; it = it->next)
		call_flag_funcs(it, flags);
	calculate_max_elems_len(file_list);
	for (t_file_node* it = file_list->head; it; it = it->next)
		display_file_info(it, file_list->max_elems_len);
	assert(flags->f[flag_R]);
	for (t_file_node* it = file_list->head; it; it = it->next)
		flags->f[flag_R](it, flags);
}

static void call_flag_funcs(t_file_node* n, const t_flags* flags)
{
	assert(n && flags);
	if (!n->info.is_valid) return;
	for (size_t i = 0; i < NB_FLAGS - 1; ++i)
		assert(flags->f[i]);
	for (size_t i = 0; i < NB_FLAGS - 1; ++i)
		flags->f[i](n, flags);
}

static void calculate_max_elems_len(t_file_list* file_list)
{
	for (t_file_node* it = file_list->head; it; it = it->next)
		for (size_t i = 0; i < it->display_buff.len; ++i)
			if (it->info.is_valid && it->display_buff.elems[i].len > file_list->max_elems_len[i] &&
				!it->info.is_hidden)
					file_list->max_elems_len[i] = it->display_buff.elems[i].len;
}

static void display_dir_total(const t_file_list* file_list)
{
	printf("total %zu\n", file_list->total);
}

static bool ascending(const t_file_node* a, const t_file_node* b);
static bool descending(const t_file_node* a, const t_file_node* b);

static void sort(t_file_list* n, const t_flags* flags)
{
	static comparator_type f[NB_COMPARATORS] =
		{ ascending, descending };
	assert(n && flags && f[0]);
	sort_file_list(n, f[flags->state[flag_r]]);
}

static bool ascending(const t_file_node* a, const t_file_node* b)
{
	return ft_strcmp(a->info.name.data, b->info.name.data) < 0;
}

static bool descending(const t_file_node* a, const t_file_node* b)
{
	return !ascending(a, b);
}
