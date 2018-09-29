#include <display_files.h>
#include <stdio.h>
#include <dirent.h>

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
		printf("%s\n", dir_info->d_name);
	closedir(dir_ptr);
}
