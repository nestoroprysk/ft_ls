#pragma once

#include <stdbool.h>

#define MAX_FILE_NAME_LEN 255

#define NB_FLAGS 5

#define FLAGS_STR "lRart"

#define NB_FILE_TYPES 3

enum file_type { dir_file_type, reg_file_file_type, other_file_type };

typedef struct s_flags
{
	bool l;
	bool R;
	bool a;
	bool r;
	bool t;
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

struct stat;

bool valid_flags(int argc, const char** argv);
t_file_node* parse_files_to_display(int argc, const char** argv);
t_flags parse_flags(int argc, const char** argv);
void fill_file_info(t_file_node* file, t_flags* flags);
void display_file_info(t_file_node* file, t_flags* flags);
void pop_front_file(t_file_node** head);

bool is_flag_argv(const char* str);
void fill_file_type(t_file_node* file, struct stat* s);
