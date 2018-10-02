#include <liblogic.h>
#include <assert.h>

int main(int argc, const char** argv)
{
	assert(valid_flags(argc, argv));
	t_flags flags = parse_flags(argc, argv);
	t_file_node* files = parse_files_to_display(argc, argv);
	assert(valid_files(files));
	while (files)
	{
		display_file_info(files, &flags);
		pop_front_file(&files);
	}
	return 0;
}
