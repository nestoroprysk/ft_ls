#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>

t_file_list* parse_files(int argc, const char** argv)
{
	t_file_node* head = NULL;
	for (int i = 1; i < argc; ++i)
		if (!is_flag_argv(argv[i]))
			append_file_node(&head, argv[i]);
	if (!head) append_file_node(&head, ".");
	t_file_list* result = (t_file_list*)ft_memalloc(sizeof(t_file_list));
	result->head = head;
	result->last = get_last_file_node(head);
	return result;
}
