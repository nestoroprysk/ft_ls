#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <assert.h>

static void display_dir_blocks(const t_file_node* n);
static void call_flag_funcs(t_file_node* n, t_flags* flags);
static void calculate_max_elems_len(t_file_list* file_list);

void display_file_list(t_file_list* file_list, t_flags* flags)
{
	assert(file_list && flags);
	display_dir_blocks(file_list->head);
	for (t_file_node* it = file_list->head; it; it = it->next)
		call_flag_funcs(it, flags);
	calculate_max_elems_len(file_list);
	for (t_file_node* it = file_list->head; it; it = it->next)
		display_file_info(it, file_list->max_elems_len);
	for (t_file_node* it = file_list->head; it; it = it->next)
		if (it->nested_file_list)
			display_file_list(it->nested_file_list, flags);
}

static void call_flag_funcs(t_file_node* n, t_flags* flags)
{
	assert(n && flags);
	for (size_t i = 0; i < NB_FLAGS; ++i)
		assert(flags->f[i]);
	for (size_t i = 0; i < NB_FLAGS; ++i)
		flags->f[i](n);
}

static void calculate_max_elems_len(t_file_list* file_list)
{
	for (t_file_node* it = file_list->head; it; it = it->next)
		for (size_t i = 0; i < it->display_buff.len; ++i)
			if (it->display_buff.elems[i].len > file_list->max_elems_len[i])
				file_list->max_elems_len[i] = it->display_buff.elems[i].len;
}

static void display_dir_blocks(const t_file_node* n)
{
	assert(n && (n->info.type == current_prev_dir_file_type ||
		n->info.type == dir_file_type));
	printf("total %zu\n", n->info.st_blocks);
}
