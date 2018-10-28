#include <liblogic.h>
#include <libft.h>
#include <assert.h>

#define NB_L_CHARS 2

static t_file_node* a(t_file_node* n);
static t_file_node* l(t_file_node* n);
static t_file_node* R(t_file_node* n);
static t_file_node* name(t_file_node* n);

void init_flag_funcs(t_flags* flags)
{
	static map_node_type f[EITHER_OR][NB_FLAGS] =
		{{ foo, name, foo, foo, foo },
		{ a, l, R, foo, foo }};
	for (size_t i = 0; i < NB_FLAGS; ++i)
		flags->f[i] = f[flags->state[i]][i];
}

static t_file_node* a(t_file_node* n)
{
	assert(n);
	n->info.is_hidden = false;
	return n;
}

static t_file_node* l(t_file_node* n)
{
	assert(n && n->info.is_valid);
	write_chmod_to_display_buff(n, n->raw_info.stat.st_mode);
	write_nb_to_display_buff(n, n->raw_info.stat.st_nlink);
	write_user_name_to_display_buff(n);
	write_group_name_to_display_buff(n);
	write_nb_to_display_buff(n, n->raw_info.stat.st_size);
	write_time_to_display_buff(n);
	n = name(n);
	return n;
}

static t_file_node* final_R(t_file_node* n);

static t_file_node* R(t_file_node* n)
{
	static map_node_type f[EITHER_OR][NB_FILE_TYPES] =
		{{ foo, final_R, foo, foo },
		{ foo, foo, foo, foo }};
	assert(n && n->info.is_valid);
	n = f[n->info.is_hidden || n->nested_file_list][n->info.type](n);
	return n;
}

static t_file_node* name(t_file_node* n)
{
	assert(n && n->info.is_valid);
	write_str_to_display_buff(n, n->info.name.data, n->info.name.len);
	return n;
}

static t_file_node* final_R(t_file_node* n)
{
	assert(n && n->info.is_valid);
	n->nested_file_list = add_dir_content(n);
	return n;
}
