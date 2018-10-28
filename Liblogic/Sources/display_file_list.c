#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <assert.h>

static void display_dir_total(const t_file_list* file_list);
static void call_flag_funcs(t_file_node* n, const t_flags* flags);
static void calculate_max_elems_len(t_file_list* file_list);

void display_file_list(t_file_list* file_list, const t_flags* flags)
{
	static bool first_entry = true;
	assert(file_list && flags);
	if (first_entry)
		first_entry = false;
	else
		printf("\n%s:\n", file_list->name);
	display_dir_total(file_list);
	for (t_file_node* it = file_list->head; it; it = it->next)
		call_flag_funcs(it, flags);
	calculate_max_elems_len(file_list);
	for (t_file_node* it = file_list->head; it; it = it->next)
		display_file_info(it, file_list->max_elems_len);
}

static void call_flag_funcs(t_file_node* n, const t_flags* flags)
{
	assert(n && flags);
	if (!n->info.is_valid) return;
	for (size_t i = 0; i < NB_FLAGS; ++i)
		assert(flags->f[i]);
	for (size_t i = 0; i < NB_FLAGS; ++i)
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
