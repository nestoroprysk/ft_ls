#include <stdio.h>
#include <display_files.h>
#include <library.h>

int main()
{
	display_files();
	char* str = "123";
    printf("Len of '%s' is '%zu'\n", str, ft_strlen(str));
}
