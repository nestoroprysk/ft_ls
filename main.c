#include <liblogic.h>

int main(int argc, const char** argv)
{
	t_file* files_to_display =
		parse_files_to_display(argc, argv);
	t_flags flags = parse_flags(argc, argv);
	(void)files_to_display;
	(void)flags;
	return 0;
}
