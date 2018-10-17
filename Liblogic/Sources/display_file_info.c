#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <assert.h>

static t_file_node* display(t_file_node* n);

void display_file_info(t_file_node* n)
{
	static map_node_type f[EITHER_OR] =
		{ display, foo };
	assert(n);
	f[n->info.is_hidden](n);
	
}

static t_file_node* display(t_file_node* n)
{
	printf("%s\n", n->display_buff.data);
	return n;
}
