#include <liblogic.h>
#include <libft.h>

t_file_list* parse_files(int argc, const char** argv)
{
	const char* file_name = ".";
	const char* file_path = "";
	t_file_list* result =
		(t_file_list*)ft_memalloc(sizeof(t_file_list));
	for (int i = 1; i < argc; ++i)
	{
		if (!is_flag_argv(argv[i]))
		{
			t_file_node* new_node = new_file_node(argv[i], file_path);
			append_file_node(result, new_node);
			if (new_node->info.type == current_prev_dir_file_type ||
				new_node->info.type == dir_file_type)
				new_node->nested_file_list = add_dir_content(new_node);
		}
	}
	if (result->len == 0)
	{
		t_file_node* new_node = new_file_node(file_name, file_path);
		result = add_dir_content(new_node);
	}
	return result;
}
