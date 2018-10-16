#include <liblogic.h>
#include <libft.h>
#include <assert.h>

static void display_name(t_file_node* n);
static void l(t_file_node* n);
static void R(t_file_node* n);
static void a(t_file_node* n);
static void r(t_file_node* n);
static void t(t_file_node* n);
static void foo(t_file_node* n);

void apply_flags(t_file_list* files, t_flags* flags)
{
	assert(files && flags);
	static flag_func_type flag_functions[NB_FLAGS] =
		{ l, R, a, r, t };
	files->f[flag_l] = (flags->flag[flag_l]) ? l : display_name;
	for (size_t i = flag_R; i < NB_FLAGS; ++i)
		files->f[i] = (flags->flag[i]) ? flag_functions[i] : foo;
}

static void display_name(t_file_node* n)
{
	assert(n);
	ft_strcat(n->display_buff, n->info.name);
}

static void l(t_file_node* n)
{
	assert(n);
	const char file_type = get_file_type(n);
	const char nb_chars_to_add = 2;
	assert(ft_strlen(n->display_buff) + nb_chars_to_add < MAX_INFO_LEN);
	ft_strncat(n->display_buff, &file_type, 1);
	ft_strcat(n->display_buff, " ");
	display_name(n);
}

static void R(t_file_node* n)
{
	assert(n);
	if (n->info.type == dir_file_type)
		n->nested_file_list = add_dir_content(n);
}

static void a(t_file_node* n)
{
	assert(n);
}

static void r(t_file_node* n)
{
	assert(n);
}

static void t(t_file_node* n)
{
	assert(n);
}

static void foo(t_file_node* n)
{
	assert(n);
}
