#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>

t_file_list* parse_files(int argc, const char** argv)
{
	t_file_list* result =
		(t_file_list*)ft_memalloc(sizeof(t_file_list));
	for (int i = 1; i < argc; ++i)
		if (!is_flag_argv(argv[i]))
			append_file_node(result, new_file_node(argv[i]));
	if (result->len == 0)
		append_file_node(result, new_file_node("."));
	return result;
}
