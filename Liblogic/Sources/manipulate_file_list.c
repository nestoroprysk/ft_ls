#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>

#define HIDDEN_FILE_PREFIX '.'

void append_file_node(t_file_list* files_ptr, t_file_node* new_node)
{
	assert(files_ptr && new_node);
	if (files_ptr->len == 0)
	{
		new_node->prev = NULL;
		new_node->next = NULL;
		files_ptr->head = new_node;
		files_ptr->last = new_node;
	}
	else
	{
		new_node->prev = files_ptr->last;
		new_node->next = NULL;
		files_ptr->last->next = new_node;
		files_ptr->last = new_node;
	}
	++files_ptr->len;
}

t_file_node* new_file_node(const char* file_name, const char* path)
{
	assert(file_name);
	t_file_node* result =
		(t_file_node*)ft_memalloc(sizeof(t_file_node));
	assert(result);
	result->info.name.len = ft_strlen(file_name);
	assert(result->info.name.data = ft_strdup(file_name));
	result->info.path.len = ft_strlen(path);
	assert(result->info.path.data = ft_strdup(path));
	result->info.full_name.len = result->info.path.len + result->info.name.len;
	assert(result->info.full_name.data = ft_strjoin(path, file_name));
	result->info.is_valid = stat(result->info.full_name.data, &result->raw_info.stat) == 0;
	if (!result->info.is_valid) return result;
	result->info.type = define_file_type(result);
	result->info.is_hidden = file_name[0] == HIDDEN_FILE_PREFIX;
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

t_file_list* add_dir_content(t_file_node* dir_file)
{
	assert(dir_file);
	char* temp = create_path(dir_file->info.path.data, dir_file->info.name.data);
	DIR* dir_ptr = opendir(temp);
	free(temp);
	if (!dir_ptr) return NULL;
	struct dirent* dir_info;
	t_file_list* result =
		(t_file_list*)ft_memalloc(sizeof(t_file_list));
	result->name = ft_strdup(dir_file->info.full_name.data);
	while ((dir_info = readdir(dir_ptr)) != NULL)
	{
		char* path = create_path(dir_file->info.path.data,
			dir_file->info.name.data);
		assert(path);
		t_file_node* new_node = new_file_node(dir_info->d_name, path);
		append_file_node(result, new_node);
		result->total += new_node->raw_info.stat.st_blocks;
		free(path);
	}
	closedir(dir_ptr);
	return result;
}

static char* create_path(const char* a, const char* b)
{
	char* temp = ft_strjoin(a, b);
	assert(temp);
	char* result = ft_strjoin(temp, "/");
	assert(result);
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
