#include <liblogic.h>

int main(int argc, const char** argv)
{
	if (!valid_flags(argc, argv)) return -1;
	t_flags flags = parse_flags(argc, argv);
	t_file_node* files = parse_files_to_display(argc, argv);
	while (files)
	{
		fill_file_info(files, &flags);
		if (!files->info.is_valid) return -2;
		display_file_info(files, &flags);
		pop_front_file(&files);
	}
	return 0;
}
