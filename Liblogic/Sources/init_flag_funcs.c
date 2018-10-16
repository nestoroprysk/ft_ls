#include <liblogic.h>
#include <libft.h>
#include <assert.h>

static t_file_node* a(t_file_node* n);
static t_file_node* l(t_file_node* n);
static t_file_node* R(t_file_node* n);
static t_file_node* name(t_file_node* n);

t_flags* init_flag_funcs(t_flags* flags)
{
	static map_node_type f[EITHER_OR][NB_FLAGS] =
		{{ foo, name, foo, foo, foo },
		{ a, l, R, foo, foo }};
	for (size_t i = 0; i < NB_FLAGS; ++i)
		flags->f[i] = f[flags->state[i]][i];
	return flags;
}

static t_file_node* a(t_file_node* n)
{
	assert(n);
	n->info.is_hidden = false;
	return n;
}

static t_file_node* l(t_file_node* n)
{
	assert(n);
	const char file_type = get_file_type(n);
	const char nb_chars_to_add = 2;
	assert(ft_strlen(n->display_buff) + nb_chars_to_add < MAX_INFO_LEN);
	ft_strncat(n->display_buff, &file_type, 1);
	ft_strcat(n->display_buff, " ");
	n = name(n);
	return n;
}

static t_file_node* final_R(t_file_node* n);

static t_file_node* R(t_file_node* n)
{
	static map_node_type f[EITHER_OR][NB_FILE_TYPES] =
		{{ foo, final_R, foo, foo },
		{ foo, foo, foo, foo }};
	assert(n);
	n = f[n->info.is_hidden][n->info.type](n);
	return n;
}

static t_file_node* name(t_file_node* n)
{
	assert(n);
	ft_strcat(n->display_buff, n->info.name);
	return n;
}

static t_file_node* final_R(t_file_node* n)
{
	assert(n);
	n->nested_file_list = add_dir_content(n);
	return n;
}
