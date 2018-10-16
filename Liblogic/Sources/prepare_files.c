#include <liblogic.h>
#include <libft.h>
#include <assert.h>

void prepare_files(t_file_list* files)
{
	for (t_file_node* it = files->head; it; it = it->next)
		if (it->info.type == dir_file_type)
			it->nested_file_list = add_dir_content(it);
}
