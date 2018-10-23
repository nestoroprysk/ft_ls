#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>

void append_file_node(t_file_list* files_ptr, t_file_node* newNode)
{
	assert(files_ptr && newNode);
	if (files_ptr->len == 0)
	{
		newNode->prev = NULL;
		newNode->next = NULL;
		files_ptr->head = newNode;
		files_ptr->last = newNode;
	}
	else
	{
		newNode->prev = files_ptr->last;
		newNode->next = NULL;
		files_ptr->last->next = newNode;
		files_ptr->last = newNode;
	}
	++files_ptr->len;
}

t_file_node* new_file_node(const char* file_name, const char* path)
{
	assert(file_name);
	t_file_node* result =
		(t_file_node*)ft_memalloc(sizeof(t_file_node));
	result->info.name_len = ft_strlen(file_name);
	assert(result->info.name_len <= MAX_FILE_NAME_LEN);
	ft_strcpy(result->info.name, file_name);
	result->info.path_len = ft_strlen(path);
	assert(result->info.path_len < MAX_PATH_LEN);
	ft_strcpy(result->info.path, path);
	result->info.full_name_len = result->info.path_len + result->info.name_len;
	assert(result->info.full_name_len <= MAX_FILE_NAME_LEN + MAX_PATH_LEN);
	ft_strcpy(result->info.full_name, path);
	ft_strcpy(&result->info.full_name[result->info.path_len], file_name);
	assert(stat(result->info.full_name, &result->raw_info.stat) == 0);
	result->raw_info.getpwuid = getpwuid(result->raw_info.stat.st_uid);
	assert(result->raw_info.getpwuid);
	result->raw_info.getgrgid = getgrgid(result->raw_info.stat.st_gid);
	assert(result->raw_info.getgrgid);
	result->info.type = define_file_type(result);
	result->info.is_hidden = file_name[0] == '.';
	result->info.is_valid = true;
	return result;
}

bool valid_files(const t_file_list* files_ptr)
{
	assert(files_ptr);
	for (t_file_node* it = files_ptr->head; it; it = it->next)
		if (!it->info.is_valid)
			return false;
	return true;
}

static char* create_path(const char* a, const char* b);

t_file_list* add_dir_content(const t_file_node* dir_file)
{
	assert(dir_file);
	DIR* dir_ptr = opendir(
		create_path(dir_file->info.path, dir_file->info.name));
	assert(dir_ptr);
	struct dirent* dir_info;
	t_file_list* dir_files =
		(t_file_list*)ft_memalloc(sizeof(t_file_list));
	while ((dir_info = readdir(dir_ptr)) != NULL)
	{
		char* path = create_path(dir_file->info.path,
			dir_file->info.name);
		append_file_node(dir_files,
			new_file_node(dir_info->d_name, path));
		free(path);
	}
	closedir(dir_ptr);
	return dir_files;
}

static char* create_path(const char* a, const char* b)
{
	char* temp = ft_strjoin(a, b);
	char* result = ft_strjoin(temp, "/");
	free(temp);
	return result;
}

t_file_list merge_file_lists(t_file_list* a, t_file_list* b)
{
	assert(a && b && !(a->len == 0 && b->len == 0));
	if (a->len == 0) return *b;
	if (b->len == 0) return *a;
	t_file_list result;
	result.head = a->head;
	result.last = b->last;
	result.len = a->len + b->len;
	a->last->next = b->head;
	b->head->prev = a->last;
	a->head = NULL;
	a->last = NULL;
	a->len = 0;
	b->head = NULL;
	a->last = NULL;
	b->len = 0;
	return result;
}

t_file_list init_file_list()
{
	t_file_list result;
	result.head = NULL;
	result.last = NULL;
	result.len = 0;
	return result;
}

t_file_node* foo(t_file_node* n)
{
	assert(n);
	return n;
}
