#pragma once

#include <stdbool.h>
#include <stddef.h>

#define MAX_FILE_NAME_LEN 255

#define MAX_PATH_LEN 255

#define MAX_L_LEN 127

#define MAX_INFO_LEN (MAX_FILE_NAME_LEN + MAX_PATH_LEN + MAX_L_LEN)

#define NB_FLAGS 5

#define FLAGS_STR "alRrt"

#define NB_FILE_TYPES 4

#define EITHER_OR 2

enum flag_type { flag_a, flag_l, flag_R, flag_r, flag_t };

enum file_type { root_dir_file_type, dir_file_type, reg_file_file_type, other_file_type };

typedef struct s_file_info
{
	char name[MAX_FILE_NAME_LEN + 1];
	char path[MAX_PATH_LEN + 1];
	bool is_valid;
	bool is_hidden;
	enum file_type type;
} t_file_node_info;

typedef struct s_file_list t_file_list;

typedef struct s_file_node
{
	char display_buff[MAX_INFO_LEN + 1];
	t_file_node_info info;
	struct s_file_node* prev;
	struct s_file_node* next;
	t_file_list* nested_file_list;
} t_file_node;

typedef struct s_flags t_flags;

typedef struct s_file_list
{
	t_file_node* head;
	t_file_node* last;
	size_t len;
} t_file_list;

typedef t_file_node* (*map_node_type)(t_file_node*);

typedef struct s_flags
{
	bool state[NB_FLAGS];
	map_node_type f[NB_FLAGS];
} t_flags;

bool valid_flags(int argc, const char** argv);
t_file_list* parse_files(int argc, const char** argv);
bool valid_files(t_file_list* files_ptr);
t_flags* parse_flags(int argc, const char** argv);
void display_file_info(t_file_node* file);
void display_file_list(t_file_list* file_list, t_flags* flags);
t_file_list* add_dir_content(const t_file_node* dir_file);
void sort_file_list(t_file_list* dir_files);
t_file_list* prepare_files(t_file_list* files);

t_flags* init_flag_funcs(t_flags* flags);
void append_file_node(t_file_list* files_ptr, t_file_node* newNode);
t_file_node* new_file_node(const char* file_name, const char* path);

bool is_flag_argv(const char* str);
char get_file_type(t_file_node* n);
enum file_type define_file_type(const char* path, const char* file_name);
t_file_node* partition(t_file_node** head, t_file_node** last);
t_file_list merge_file_lists(t_file_list* a, t_file_list* b);
t_file_list init_file_list();
bool is_bigger(t_file_node const* a, t_file_node const* b);
t_file_node* foo(t_file_node* n);
