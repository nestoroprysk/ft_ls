#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
static bool is_directory(const t_file_node* n);
static void display_current_directory(const t_flags* flags);
static void display_directory(const t_file_node* file_node, const t_flags* flags);
static void display_file(const t_file_node* new_node, const t_flags* flags);

void display_input_files(int argc, const char** argv, const t_flags* flags)
{
	const char* file_path = "";
	bool file_found = false;
	for (int i = 1; i < argc; ++i)
	{
		if (!is_flag_argv(argv[i]))
		{
			file_found = true;
			t_file_node* new_node = new_file_node(argv[i], file_path);
			if (is_directory(new_node))
				display_directory(new_node, flags);
			else
				display_file(new_node, flags);
			delete_file_node(new_node);
		}
	}
	if (!file_found) display_current_directory(flags);
}

static bool is_directory(const t_file_node* n)
{
	return n->info.type == current_prev_dir_file_type ||
		n->info.type == dir_file_type;
}

static void display_current_directory(const t_flags* flags)
{
	const char* file_name = ".";
	const char* file_path = "";
	assert(flags);
	t_file_node* new_node = new_file_node(file_name, file_path);
	display_directory(new_node, flags);
	delete_file_node(new_node);
}

static void display_directory(const t_file_node* file_node, const t_flags* flags)
{
	assert(file_node && flags);
	t_file_list* directory = add_dir_content(file_node);
	display_file_list(directory, flags);
	delete_file_list(&directory);
}

static void display_file(const t_file_node* new_node, const t_flags* flags)
{
	assert(new_node && flags);
	printf("%s\n", new_node->info.name.data);
}
