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
		files_ptr->head = newNode;
		files_ptr->last = newNode;
	}
	else
	{
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
	assert(ft_strlen(file_name) <= MAX_FILE_NAME_LEN);
	ft_strcpy(result->info.name, file_name);
	assert(ft_strlen(path) < MAX_PATH_LEN);
	ft_strcpy(result->info.path, path);
	result->info.type = define_file_type(path, file_name);
	result->info.is_valid = true;
	return result;
}

bool valid_files(t_file_list* files_ptr)
{
	assert(files_ptr);
	for (t_file_node* it = files_ptr->head; it; it = it->next)
		if (!it->info.is_valid)
			return false;
	return true;
}

char* create_path(const char* a, const char* b);

t_file_list* add_dir_content(const t_file_node* dir_file)
{
	assert(dir_file);
	DIR* dir_ptr = opendir(dir_file->info.name);
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

char* create_path(const char* a, const char* b)
{
	char* temp = ft_strjoin(a, b);
	char* result = ft_strjoin(temp, "/");
	free(temp);
	return result;
}
