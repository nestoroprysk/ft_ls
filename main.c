#include <liblogic.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, const char** argv)
{
	assert(valid_flags(argc, argv));
	t_flags flags = parse_flags(argc, argv);
	init_flag_funcs(&flags);
	display_input_files(argc, argv, &flags);
	return 0;
}
