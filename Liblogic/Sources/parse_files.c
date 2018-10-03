#include <liblogic.h>
#include <libft.h>

t_file_list* parse_files(int argc, const char** argv)
{
	const char* file_name = ".";
	const char* file_path = "";
	t_file_list* result =
		(t_file_list*)ft_memalloc(sizeof(t_file_list));
	for (int i = 1; i < argc; ++i)
		if (!is_flag_argv(argv[i]))
			append_file_node(result, new_file_node(argv[i], file_path));
	if (result->len == 0)
		append_file_node(result, new_file_node(file_name, file_path));
	return result;
}
