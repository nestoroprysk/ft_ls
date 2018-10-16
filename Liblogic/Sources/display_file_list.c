#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <assert.h>

static void call_flag_funcs(t_file_node* n, t_flags* flags);

void display_file_list(t_file_list* file_list, t_flags* flags)
{
	assert(file_list && flags);
	for (t_file_node* it = file_list->head; it; it = it->next){
		call_flag_funcs(it, flags);
		display_file_info(it);
	}
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
