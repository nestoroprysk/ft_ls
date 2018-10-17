#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <sys/stat.h>
#include <pwd.h>

#define MAX_FILE_NAME_LEN 255

#define MAX_PATH_LEN 255

#define MAX_L_LEN 127

#define MAX_INFO_BUFF_LEN (MAX_FILE_NAME_LEN + MAX_PATH_LEN + MAX_L_LEN)

#define NB_FLAGS 5

#define FLAGS_STR "alRrt"

#define NB_FILE_TYPES 4

#define EITHER_OR 2

enum flag_type { flag_a, flag_l, flag_R, flag_r, flag_t };

enum file_type { root_dir_file_type, dir_file_type, reg_file_file_type, other_file_type };

typedef struct s_file_info
{
	char name[MAX_FILE_NAME_LEN + 1];
	size_t name_len;
	char path[MAX_PATH_LEN + 1];
	size_t path_len;
	char full_name[MAX_PATH_LEN + MAX_FILE_NAME_LEN + 1];
	size_t full_name_len;
	bool is_valid;
	bool is_hidden;
	enum file_type type;
} t_file_node_info;

typedef struct s_file_list t_file_list;

typedef struct s_display_buff
{
	size_t len;
	char data[MAX_INFO_BUFF_LEN + 1];
} t_display_buff;

typedef struct s_raw_info
{
	struct stat stat;
	struct passwd* getpwuid; // leak
} t_raw_info;

typedef struct s_file_node
{
	t_display_buff display_buff;
	t_file_node_info info;
	t_raw_info raw_info;
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
char get_file_type_char(t_file_node* n);
enum file_type define_file_type(const t_file_node* n);

t_file_node* partition(t_file_node** head, t_file_node** last);
t_file_list merge_file_lists(t_file_list* a, t_file_list* b);
t_file_list init_file_list();
bool is_bigger(t_file_node const* a, t_file_node const* b);
t_file_node* foo(t_file_node* n);

void write_char_to_display_buff(t_file_node* n, char ch);
void write_str_to_display_buff(t_file_node* n, const char* str, size_t len);
void write_chmod_to_display_buff(t_file_node* n, mode_t chmod);
void write_nb_to_display_buff(t_file_node* n, int chmod);
void write_user_name_to_display_buff(t_file_node* n);
