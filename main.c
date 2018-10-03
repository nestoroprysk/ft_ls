#include <liblogic.h>
#include <assert.h>

int main(int argc, const char** argv)
{
	assert(valid_flags(argc, argv));
	t_flags* flags = parse_flags(argc, argv);
	t_file_list* files = parse_files(argc, argv);
	assert(files && valid_files(files) && files->len > 0);
	while (files->len > 0)
	{
		display_file_info(files->head, flags);
		pop_front_file(files);
	}
	return 0;
}
