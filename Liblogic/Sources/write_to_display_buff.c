#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>

#define NB_PERMISSION_TYPES 3
#define NB_CHMOD_FIELDS 9

void write_char_to_display_buff(t_file_node* n, char ch)
{
	assert(n->display_buff.len != MAX_INFO_BUFF_LEN);
	n->display_buff.data[n->display_buff.len] = ch;
	++n->display_buff.len;
}

void write_str_to_display_buff(t_file_node* n, const char* str, size_t len)
{
	assert(n->display_buff.len + len <= MAX_INFO_BUFF_LEN);
	ft_strncpy(&n->display_buff.data[n->display_buff.len], str, len);
	n->display_buff.len += len;
}

void write_chmod_to_display_buff(t_file_node* n, mode_t chmod)
{
	static char permission[EITHER_OR][NB_PERMISSION_TYPES] =
		{{ '-', '-', '-' }, { 'r', 'w', 'x' }}; 
	assert(n);
	for (int i = 0; i < NB_CHMOD_FIELDS; ++i)
		write_char_to_display_buff(n,
			permission[(chmod >> (NB_CHMOD_FIELDS - i - 1)) & 1]
				[i % NB_PERMISSION_TYPES]);
}
