#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>
#include <time.h>

#define NB_FILE_TYPE_FIELDS 1
#define NB_PERMISSION_TYPES 3
#define NB_CHMOD_FIELDS 9
#define CHMOD_BUFF_LEN (NB_FILE_TYPE_FIELDS + NB_CHMOD_FIELDS + 1)
#define NB_MONTHS 12
#define FILE_TYPE_FIELD 0
#define TIME_BUFF_LEN 24
#define POSITION_AFTER_MONTH 3
#define MONTH_BUFF_LEN 3

void write_str_to_display_buff(t_file_node* n, const char* str, size_t len)
{
	assert(n && str);
	append_string_node(&n->display_buff, new_string_node(str, len));
}

void write_chmod_to_display_buff(t_file_node* n, mode_t chmod)
{
	static char permission[EITHER_OR][NB_PERMISSION_TYPES] =
		{{ '-', '-', '-' }, { 'r', 'w', 'x' }}; 
	assert(n);
	char result_buff[CHMOD_BUFF_LEN]; ft_bzero(result_buff, CHMOD_BUFF_LEN);
	result_buff[FILE_TYPE_FIELD] = get_file_type_char(n);
	for (int i = 0; i < NB_CHMOD_FIELDS; ++i)
		result_buff[i + 1] = 
			permission[(chmod >> (NB_CHMOD_FIELDS - i - 1)) & 1]
				[i % NB_PERMISSION_TYPES];
	append_string_node(&n->display_buff, new_string_node(result_buff, ft_strlen(result_buff)));
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

static void write_month_to_result_buff(const t_file_node* n, char* buff);

void write_time_to_display_buff(t_file_node* n)
{
	assert(n);
	char result_buff[TIME_BUFF_LEN]; ft_bzero(result_buff, TIME_BUFF_LEN);
	write_month_to_result_buff(n, result_buff);
	result_buff[POSITION_AFTER_MONTH] = ' ';
	strftime(&result_buff[POSITION_AFTER_MONTH], TIME_BUFF_LEN - POSITION_AFTER_MONTH - 1,
		"%d %H:%M", localtime(&n->raw_info.stat.st_mtime));
	append_string_node(&n->display_buff, new_string_node(result_buff, ft_strlen(result_buff)));
}

static void write_month_to_result_buff(const t_file_node* n, char* buff)
{
	static char* months[NB_MONTHS] = { "Jan", "Fab", "Mar", "Apr", "May",
		"Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	assert(buff);
	char temp[MONTH_BUFF_LEN]; ft_bzero(temp, MONTH_BUFF_LEN);
	strftime(temp, MONTH_BUFF_LEN - 1, "%m", localtime(&n->raw_info.stat.st_mtime));
	const int month_nb = ft_atoi(temp) - 1;
	ft_strcpy(buff, months[month_nb]);
}
