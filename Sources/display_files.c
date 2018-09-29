#include <display_files.h>
#include <display_file_type.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

static void display_full_file_info(const char* file_name)
{
	struct stat file_info;
	stat(file_name, &file_info);
	display_file_type(file_info.st_mode);
	printf(" %s\n", file_name);
}

void display_files(const char* file_name)
{
	DIR* dir_ptr = opendir(file_name);
	if (!dir_ptr)
	{
		perror("Error on opening the directory");
		return ;
	}
	struct dirent* dir_info;
	while ((dir_info = readdir(dir_ptr)) != NULL)
		display_full_file_info(dir_info->d_name);
	closedir(dir_ptr);
}
