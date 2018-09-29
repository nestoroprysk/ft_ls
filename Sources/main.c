#include <stdio.h>
#include <display_files.h>
#include <library.h>
#include <stdlib.h>

int main(int argc, const char** argv)
{
	const char* dir_name = (argc > 1) ? argv[1] : ".";
	display_files(dir_name);
}
