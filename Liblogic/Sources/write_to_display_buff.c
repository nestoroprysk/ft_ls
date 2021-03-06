#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

#define NB_FILE_TYPE_FIELDS 1
#define NB_PERMISSION_TYPES 3
#define NB_CHMOD_FIELDS 9
#define CHMOD_BUFF_LEN (NB_FILE_TYPE_FIELDS + NB_CHMOD_FIELDS + 1)
#define NB_MONTHS 12
#define FILE_TYPE_FIELD 0
#define TIME_BUFF_LEN 24
#define POSITION_AFTER_MONTH 3
#define MONTH_BUFF_LEN 3
#define BUFF_LEN 128
#define ERROR_VALUE -1

void write_str_to_display_buff(t_file_node* n, const char* str, size_t len)
{
	assert(n && str);
	add_string(&n->display_buff, str, len);
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
	add_string(&n->display_buff, result_buff, ft_strlen(result_buff));
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

	assert(n);
	struct passwd* a = getpwuid(n->raw_info.stat.st_uid);
	assert(a);
	write_str_to_display_buff(n, a->pw_name, ft_strlen(a->pw_name));
}

void write_group_name_to_display_buff(t_file_node* n)
{
	assert(n);
	struct group* g = getgrgid(n->raw_info.stat.st_gid);
	assert(g);
	write_str_to_display_buff(n, g->gr_name, ft_strlen(g->gr_name));
}

void write_time_to_display_buff(t_file_node* n)
{
	assert(n);
	char* time = ctime(&n->raw_info.stat.st_mtime);
	assert(time);
	const size_t len = ft_strlen(time);
	const size_t tail = 9;
	assert(len > tail);
	time[len - tail] = '\0';
	const size_t head = 4;
	add_string(&n->display_buff, &time[head], len - tail);
}

void write_linked_file_name_to_buff(t_file_node* n)
{
	char buff[BUFF_LEN]; ft_bzero(buff, BUFF_LEN);
	assert(readlink(n->info.full_name.data, buff, BUFF_LEN) != ERROR_VALUE);
	concat_to_last_string(&n->display_buff, buff, ft_strlen(buff));
}
