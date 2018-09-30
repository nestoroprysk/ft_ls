#pragma once

#include <stdbool.h>

#define MAX_FILE_LEN 256

#define NB_FLAGS 5

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
	char name[MAX_FILE_LEN];
} t_file_info;

typedef struct s_file
{
	t_file_info info;
	struct s_file* next;
} t_file;

t_file* parse_files_to_display(int argc, const char** argv);
t_flags parse_flags(int argc, const char** argv);
