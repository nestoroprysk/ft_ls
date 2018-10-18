#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>
#include <time.h>

#define NB_PERMISSION_TYPES 3
#define NB_CHMOD_FIELDS 9
#define MAX_TIME_LEN 20
#define NB_MONTHS 12

void write_char_to_display_buff(t_file_node* n, char ch)
{
	assert(n);
	assert(n->display_buff.len != MAX_INFO_BUFF_LEN);
	n->display_buff.data[n->display_buff.len] = ch;
	++n->display_buff.len;
}

void write_str_to_display_buff(t_file_node* n, const char* str, size_t len)
{
	assert(n && str);
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

void write_nb_to_display_buff(t_file_node* n, int nb)
{
	assert(n);
	char* temp = ft_itoa(nb);
	assert(temp);
	write_str_to_display_buff(n, temp, ft_strlen(temp));
	free(temp);
}

void write_user_name_to_display_buff(t_file_node* n)
{
	assert(n && n->raw_info.getpwuid);
	const char* user_name = n->raw_info.getpwuid->pw_name;
	assert(user_name);
	write_str_to_display_buff(n, user_name, ft_strlen(user_name));
}

void write_group_name_to_display_buff(t_file_node* n)
{
	assert(n &&  n->raw_info.getgrgid);
	const char* group_name = n->raw_info.getgrgid->gr_name;
	assert(group_name);
	write_str_to_display_buff(n, group_name, ft_strlen(group_name));
}

static void write_month_to_display_buff(t_file_node* n);

void write_time_to_display_buff(t_file_node* n)
{
	assert(n);
	write_month_to_display_buff(n);
	write_char_to_display_buff(n, ' ');
	char temp[MAX_TIME_LEN + 1]; ft_bzero(temp, MAX_TIME_LEN + 1);
	strftime(temp, MAX_TIME_LEN, "%d %H:%M", localtime(&n->raw_info.stat.st_mtime));
	write_str_to_display_buff(n, temp, ft_strlen(temp));
}

static void write_month_to_display_buff(t_file_node* n)
{
	static char* months[NB_MONTHS] = { "Jan", "Fab", "Mar", "Apr", "May",
		"Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	char temp[MAX_TIME_LEN + 1]; ft_bzero(temp, MAX_TIME_LEN + 1);
	strftime(temp, MAX_TIME_LEN, "%m", localtime(&n->raw_info.stat.st_mtime));
	const int month_nb = ft_atoi(temp) - 1;
	write_str_to_display_buff(n, months[month_nb], ft_strlen(months[month_nb]));
}
