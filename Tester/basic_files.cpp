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
		t_file_list* result = parse_files(argc, argv);
		REQUIRE(result);
		REQUIRE(strcmp(result->head->info.name, ".") == 0);
		REQUIRE(result->head->info.is_valid);
		REQUIRE(!result->head->next);
	}
	{
		constexpr int argc = 2;
		const char* file_name = "..";
		const char* argv[argc] = {"./a.out", file_name};
		t_file_list* result = parse_files(argc, argv);
		REQUIRE(result);
		REQUIRE(strcmp(result->head->info.name, file_name) == 0);
		REQUIRE(result->head->info.is_valid);
		REQUIRE(!result->head->next);
	}
	{
		constexpr int argc = 2;
		const char* file_name = "-l";
		const char* argv[argc] = {"./a.out", file_name};
		t_file_list* result = parse_files(argc, argv);
		REQUIRE(result);
		REQUIRE(strcmp(result->head->info.name, ".") == 0);
		REQUIRE(result->head->info.is_valid);
		REQUIRE(!result->head->next);
	}
}

TEST_CASE("Multiple file tests", "[file parsing]")
{
	{
		constexpr int argc = 3;
		const char* file_name1 = ".";
		const char* file_name2 = "..";
		const char* argv[argc] = {"./a.out", file_name1, file_name2};
		t_file_list* result = parse_files(argc, argv);
		REQUIRE(result);
		REQUIRE(strcmp(result->head->info.name, file_name1) == 0);
		REQUIRE(result->head->info.is_valid);
		REQUIRE(result->head->next);
		REQUIRE(strcmp(result->head->next->info.name, file_name2) == 0);
		REQUIRE(result->head->next->info.is_valid);
		REQUIRE(!result->head->next->next);
	}
	{
		constexpr int argc = 2;
		const char* file_name = "-la";
		const char* argv[argc] = {"./a.out", file_name};
		t_file_list* result = parse_files(argc, argv);
		REQUIRE(result);
		REQUIRE(strcmp(result->head->info.name, ".") == 0);
		REQUIRE(result->head->info.is_valid);
		REQUIRE(!result->head->next);
	}
}
