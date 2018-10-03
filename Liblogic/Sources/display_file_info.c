#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <assert.h>

void display_file_info(t_file_node* file)
{
	assert(file);
	printf("{%s} (%s) <%i>\n", file->info.path, file->info.name, file->info.type);
}
