#pragma once

#include <stdbool.h>

#define MAX_FILE_NAME_LEN 255

#define NB_FLAGS 5

#define FLAGS_STR "lRart"

#define NB_FLAG_TYPES 5

#define NB_FILE_TYPES 2

enum flag_type { flag_l, flag_R, flag_a, flag_r, flag_t };

enum file_type { dir_file_type, reg_file_file_type, other_file_type };

typedef struct s_flags
{
	bool flag[NB_FLAG_TYPES];
} t_flags;

typedef struct s_file_info
{
	char name[MAX_FILE_NAME_LEN + 1];
	bool is_valid;
	enum file_type type;
} t_file_node_info;

typedef struct s_file_node
{
	t_file_node_info info;
	struct s_file_node* next;
} t_file_node;

typedef struct s_file_list
{
	t_file_node* head;
	t_file_node* last;
} t_file_list;

bool valid_flags(int argc, const char** argv);
t_file_list* parse_files(int argc, const char** argv);
bool valid_files(t_file_list* files_ptr);
t_flags* parse_flags(int argc, const char** argv);
void display_file_info(t_file_node* file, t_flags* flags);

void pop_front_file(t_file_list* files_ptr);
void append_file_node(t_file_node** head_ptr, const char* file_name);
t_file_node* new_file_node(const char* file_name);
t_file_node* get_last_file_node(t_file_node* head);
bool files_left(t_file_list* files_ptr);

bool is_flag_argv(const char* str);
enum file_type define_file_type(const char* file_name);
