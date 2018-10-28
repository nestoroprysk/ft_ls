#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void free_file_node(t_file_node** n_ptr)
{
	t_file_node* n = *n_ptr;
	free(n->raw_info.getpwuid);
	free(n->raw_info.getgrgid);
	free(n);
	*n_ptr = NULL;
}
