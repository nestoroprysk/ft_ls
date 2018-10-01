#include <liblogic.h>
#include <libft.h>
#include <assert.h>
#include <stdio.h>

void display_file_info(t_file_node* file, t_flags* flags)
{
	assert(file);
	assert(flags);
	printf("%s %i\n", file->info.name, file->info.type);
}
