#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <sys/stat.h>

#define NB_FLAGS 5

#define FLAGS_STR "alrtR"

#define EITHER_OR 2

#define MAX_STRING_LIST_ELEMS 8

enum flag_type { flag_a, flag_l, flag_r, flag_t, flag_R };

enum file_type { current_prev_dir_file_type, dir_file_type, reg_file_file_type, symbolic_link_file_type,
	chr_file_type, blk_file_type, sock_file_type, fifo_file_type, other_file_type };

typedef struct s_file_node t_file_node;

typedef struct s_string
{
	char* data;
	size_t len;
} t_string;

typedef struct s_string_list
{
	t_string elems[MAX_STRING_LIST_ELEMS];
	size_t len;
} t_string_list;

typedef struct s_file_info
{
	t_string name;
	t_string path;
	t_string full_name;
	bool is_valid;
	bool is_hidden;
	enum file_type type;
	size_t total;
} t_file_node_info;

typedef struct s_file_list t_file_list;

typedef struct s_raw_info
{
	struct stat stat;
} t_raw_info;

typedef struct s_file_node
{
	t_string_list display_buff;
	t_file_node_info info;
	t_raw_info raw_info;
	struct s_file_node* prev;
	struct s_file_node* next;
} t_file_node;

typedef struct s_flags t_flags;

typedef struct s_file_list
{
	t_file_node* head;
	t_file_node* last;
	size_t len;
	size_t max_elems_len[MAX_STRING_LIST_ELEMS];
	size_t total;
	char* name;
} t_file_list;

typedef t_file_node* (*map_node_type)(t_file_node*, const t_flags*);

typedef struct s_flags
{
	bool state[NB_FLAGS];
	map_node_type f[NB_FLAGS];
} t_flags;

typedef bool (*comparator_type)(const t_file_node*, const t_file_node*);

bool valid_flags(int argc, const char** argv);
void display_input_files(int argc, const char** argv, const t_flags* flags);
bool valid_files(const t_file_list* files_ptr);
t_flags parse_flags(int argc, const char** argv);
void display_file_info(t_file_node* n, const size_t* max_elems_len);
void display_file_list(t_file_list* file_list, const t_flags* flags);
t_file_list* add_dir_content(const t_file_node* dir_file);
void sort_file_list(t_file_list* dir_files, comparator_type);

void init_flag_funcs(t_flags* flags);
void append_file_node(t_file_list* files_ptr, t_file_node* newNode);
t_file_node* new_file_node(const char* file_name, const char* path);
bool is_flag_argv(const char* str);
char get_file_type_char(t_file_node* n);
enum file_type define_file_type(const t_file_node* n);

t_file_node* partition(t_file_node** head, t_file_node** last, comparator_type f);
t_file_list merge_file_lists(t_file_list* a, t_file_list* b);
t_file_list init_file_list();

void write_str_to_display_buff(t_file_node* n, const char* str, size_t len);
void write_chmod_to_display_buff(t_file_node* n, mode_t chmod);
void write_nb_to_display_buff(t_file_node* n, int chmod);
void write_user_name_to_display_buff(t_file_node* n);
void write_group_name_to_display_buff(t_file_node* n);
void write_time_to_display_buff(t_file_node* n);
void write_linked_file_name_to_buff(t_file_node* n);

void add_string(t_string_list* string_list_ptr, const char* data, size_t len);
void concat_to_last_string(t_string_list* string_list_ptr, const char* data, size_t len);

void delete_file_list(t_file_list** file_list_ptr);
void delete_file_node(t_file_node* n);
