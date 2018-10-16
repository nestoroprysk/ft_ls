#include <liblogic.h>
#include <assert.h>

int main(int argc, const char** argv)
{
	assert(valid_flags(argc, argv));
	t_flags* flags = parse_flags(argc, argv);
	assert(flags);
	t_file_list* files = parse_files(argc, argv);
	assert(files && valid_files(files) && files->len > 0);
	prepare_files(files);
	display_file_list(files, flags);
	return 0;
}
