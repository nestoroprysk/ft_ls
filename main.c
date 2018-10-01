#include <liblogic.h>

int main(int argc, const char** argv)
{
	if (!valid_flags(argc, argv))
		return -1;
	t_flags flags = parse_flags(argc, argv);
	return 0;
}
