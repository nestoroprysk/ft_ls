#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <assert.h>

mode_t define_chmod(const char* full_name)
{
	assert(full_name);
	struct stat file_info;
	assert(stat(full_name, &file_info) == 0);
	return file_info.st_mode;
}
