#include <liblogic.h>
#include <assert.h>

int main(int argc, const char** argv)
{
	assert(valid_flags(argc, argv));
	t_flags* flags = parse_flags(argc, argv);
	assert(flags);
	t_file_list* files = parse_files(argc, argv);
	assert(files && valid_files(files) && files->len > 0);
	for (t_file_node* it = files->head; it; it = it->next)
		if (it->info.type == dir_file_type)
			it->nested_file_list = add_dir_content(it);
	display_file_list(files);
	return 0;
}
