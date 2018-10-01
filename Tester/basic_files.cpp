#include "catch.hpp"
#include <string.h>
#include <string>

extern "C"
{
	#include <liblogic.h>
}

TEST_CASE("Basic file tests", "[file parsing]")
{
	{
		constexpr int argc = 1;
		const char* argv[argc] = {"./a.out"};
		t_file_node* result = parse_files_to_display(argc, argv);
		REQUIRE(result);
		REQUIRE(strcmp(result->info.name, ".") == 0);
		REQUIRE(!result->next);
	}
	{
		constexpr int argc = 2;
		const char* file_name = "file";
		const char* argv[argc] = {"./a.out", file_name};
		t_file_node* result = parse_files_to_display(argc, argv);
		REQUIRE(result);
		REQUIRE(strcmp(result->info.name, file_name) == 0);
		REQUIRE(!result->next);
	}
	{
		constexpr int argc = 2;
		const auto c = 'a';
		std::string file_name(MAX_FILE_NAME_LEN * 2, c);
		const char* argv[argc] = {"./a.out", file_name.c_str()};
		t_file_node* result = parse_files_to_display(argc, argv);
		REQUIRE(result);
		REQUIRE(strncmp(result->info.name,
			file_name.c_str(), MAX_FILE_NAME_LEN) == 0);
		REQUIRE(result->info.name[MAX_FILE_NAME_LEN - 1] == c);
		REQUIRE(result->info.name[MAX_FILE_NAME_LEN] == '\0');
		REQUIRE(!result->next);
	}
	{
		constexpr int argc = 2;
		const char* file_name = "-l";
		const char* argv[argc] = {"./a.out", file_name};
		t_file_node* result = parse_files_to_display(argc, argv);
		REQUIRE(result);
		REQUIRE(strcmp(result->info.name, ".") == 0);
		REQUIRE(!result->next);
	}
}

TEST_CASE("Multiple file tests", "[file parsing]")
{
	{
		constexpr int argc = 3;
		const char* file_name1 = "file";
		const char* file_name2 = "second";
		const char* argv[argc] = {"./a.out", file_name1, file_name2};
		t_file_node* result = parse_files_to_display(argc, argv);
		REQUIRE(result);
		REQUIRE(strcmp(result->info.name, file_name1) == 0);
		REQUIRE(result->next);
		REQUIRE(strcmp(result->next->info.name, file_name2) == 0);
		REQUIRE(!result->next->next);
	}
	{
		constexpr int argc = 4;
		const char* file_name1 = "-";
		const char* file_name2 = "second";
		const char* argv[argc] = {"./a.out", file_name1, "-l", file_name2};
		t_file_node* result = parse_files_to_display(argc, argv);
		REQUIRE(result);
		REQUIRE(strcmp(result->info.name, file_name1) == 0);
		REQUIRE(result->next);
		REQUIRE(strcmp(result->next->info.name, file_name2) == 0);
		REQUIRE(!result->next->next);
	}
	{
		constexpr int argc = 2;
		const char* file_name = "-la";
		const char* argv[argc] = {"./a.out", file_name};
		t_file_node* result = parse_files_to_display(argc, argv);
		REQUIRE(result);
		REQUIRE(strcmp(result->info.name, ".") == 0);
		REQUIRE(!result->next);
	}
	{
		constexpr int argc = 2;
		const char* file_name = "";
		const char* argv[argc] = {"./a.out", file_name};
		t_file_node* result = parse_files_to_display(argc, argv);
		REQUIRE(result);
		REQUIRE(strcmp(result->info.name, "") == 0);
		REQUIRE(!result->next);
	}
}
