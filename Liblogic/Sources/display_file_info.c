#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <assert.h>

#define MAX_PRINT_N_CHARS_BUFF_LEN 128
#define COLUMN_SEPARATOR ' '

typedef void (*mod_display_node_type)(t_file_node* n, const size_t* max_elems_len);

static void display(t_file_node* n, const size_t* max_elems_len);
static void bar(t_file_node* n, const size_t* max_elems_len);
static void print_n_chars(char ch, size_t n);

void display_file_info(t_file_node* n, const size_t* max_elems_len)
{
	static mod_display_node_type f[EITHER_OR] =
		{ display, bar };
	assert(n && max_elems_len);
	f[n->info.is_hidden](n, max_elems_len);
}

static void display(t_file_node* n, const size_t* max_elems_len)
{
	static size_t separators[MAX_STRING_LIST_ELEMS] =
		{ 2, 1, 2, 2, 1, 1, 1, 1 };
	assert(n && max_elems_len);
	t_string_list* list_ptr = &n->display_buff;
	assert(list_ptr->len <= MAX_STRING_LIST_ELEMS);
	for (size_t i = 0; i < list_ptr->len; ++i)
	{
		printf("%s", list_ptr->elems[i].data);
		if (i < list_ptr->len - 1)
			print_n_chars(COLUMN_SEPARATOR, (i == list_ptr->len - 2) 
				? 1 : max_elems_len[i + 1] -
					list_ptr->elems[i + 1].len + separators[i]);
	}
	printf("\n");
}

static void bar(t_file_node* n, const size_t* max_elems_len)
{
	assert(n && max_elems_len);
}

static void print_n_chars(char ch, size_t n)
{
	assert(n < MAX_PRINT_N_CHARS_BUFF_LEN);
	char buff[MAX_PRINT_N_CHARS_BUFF_LEN];
	ft_bzero(buff, MAX_PRINT_N_CHARS_BUFF_LEN);
	for (size_t i = 0; i < n; ++i)
		buff[i] = ch;
	printf("%s", buff);
}
