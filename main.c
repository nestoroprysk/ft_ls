#include <liblogic.h>
#include <assert.h>

int main(int argc, const char** argv)
{
	assert(valid_flags(argc, argv));
	t_flags* flags = parse_flags(argc, argv);
	flags = init_flag_funcs(flags);
	assert(flags);
	t_file_list* files = parse_files(argc, argv);
	files = prepare_files(files);
	assert(files && valid_files(files) && files->len > 0);
	display_file_list(files, flags);
	return 0;
}
