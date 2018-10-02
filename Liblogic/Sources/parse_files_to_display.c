#include <liblogic.h>
#include <libft.h>
#include <assert.h>

t_file_node* parse_files_to_display(int argc, const char** argv)
{
	t_file_node* head = NULL;
	for (int i = 1; i < argc; ++i)
		if (!is_flag_argv(argv[i]))
			append_file_node(&head, argv[i]);
	if (!head) append_file_node(&head, ".");
	return head;
}

bool valid_files(t_file_node* files)
{
	assert(files);
	for (t_file_node* it = files; it; it = it->next)
		if (!it->info.is_valid)
			return false;
	return true;
}
