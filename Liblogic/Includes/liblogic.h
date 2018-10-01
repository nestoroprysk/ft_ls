#pragma once

#include <stdbool.h>

#define MAX_FILE_NAME_LEN 255

#define NB_FLAGS 5

#define FLAGS_STR "lRart"

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
} t_file_node_info;

typedef struct s_file_node
{
	t_file_node_info info;
	struct s_file_node* next;
} t_file_node;

bool valid_flags(int argc, const char** argv);
t_file_node* parse_files_to_display(int argc, const char** argv);
t_flags parse_flags(int argc, const char** argv);

bool is_flag_argv(const char* str);
