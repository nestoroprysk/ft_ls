#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <assert.h>

static void call_flag_funcs(t_file_list* file_list, t_file_node* n);

void display_file_list(t_file_list* file_list, t_flags* flags)
{
	apply_flags(file_list, flags);
	static size_t i = 0;
	printf("======%zu======\n", i++);
	assert(file_list);
	for (t_file_node* it = file_list->head; it; it = it->next){
		call_flag_funcs(file_list, it);
		display_file_info(it);
	}
	for (t_file_node* it = file_list->head; it; it = it->next)
		if (it->nested_file_list)
			display_file_list(it->nested_file_list, flags);
}

static void call_flag_funcs(t_file_list* file_list, t_file_node* n)
{
	assert(file_list && n);
	for (size_t i = 0; i < NB_FLAGS; ++i)
		assert(file_list->f[i]);
	for (size_t i = 0; i < NB_FLAGS; ++i)
		file_list->f[i](n);
}
