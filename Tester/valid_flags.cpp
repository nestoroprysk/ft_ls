#define CATCH_CONFIG_MAIN
#include "catch.hpp"

extern "C"
{
	#include <liblogic.h>
}

TEST_CASE("Basic tests", "[valid flags]")
{
	{
		constexpr int argc = 1;
		const char* argv[argc] = {"./a.out"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == false);
		REQUIRE(flags->state[flag_R] == false);
		REQUIRE(flags->state[flag_a] == false);
		REQUIRE(flags->state[flag_r] == false);
		REQUIRE(flags->state[flag_t] == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "l"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == false);
		REQUIRE(flags->state[flag_R] == false);
		REQUIRE(flags->state[flag_a] == false);
		REQUIRE(flags->state[flag_r] == false);
		REQUIRE(flags->state[flag_t] == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-l"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == true);
		REQUIRE(flags->state[flag_R] == false);
		REQUIRE(flags->state[flag_a] == false);
		REQUIRE(flags->state[flag_r] == false);
		REQUIRE(flags->state[flag_t] == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == false);
		REQUIRE(flags->state[flag_R] == false);
		REQUIRE(flags->state[flag_a] == false);
		REQUIRE(flags->state[flag_r] == false);
		REQUIRE(flags->state[flag_t] == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-t"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == false);
		REQUIRE(flags->state[flag_R] == false);
		REQUIRE(flags->state[flag_a] == false);
		REQUIRE(flags->state[flag_r] == false);
		REQUIRE(flags->state[flag_t] == true);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-R"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == false);
		REQUIRE(flags->state[flag_R] == true);
		REQUIRE(flags->state[flag_a] == false);
		REQUIRE(flags->state[flag_r] == false);
		REQUIRE(flags->state[flag_t] == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-a"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == false);
		REQUIRE(flags->state[flag_R] == false);
		REQUIRE(flags->state[flag_a] == true);
		REQUIRE(flags->state[flag_r] == false);
		REQUIRE(flags->state[flag_t] == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-r"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == false);
		REQUIRE(flags->state[flag_R] == false);
		REQUIRE(flags->state[flag_a] == false);
		REQUIRE(flags->state[flag_r] == true);
		REQUIRE(flags->state[flag_t] == false);
	}
}

TEST_CASE("Mixed flags in single string", "[valid flags]")
{
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out","-lR"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == true);
		REQUIRE(flags->state[flag_R] == true);
		REQUIRE(flags->state[flag_a] == false);
		REQUIRE(flags->state[flag_r] == false);
		REQUIRE(flags->state[flag_t] == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out","-rt"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == false);
		REQUIRE(flags->state[flag_R] == false);
		REQUIRE(flags->state[flag_a] == false);
		REQUIRE(flags->state[flag_r] == true);
		REQUIRE(flags->state[flag_t] == true);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out","-lRrt"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == true);
		REQUIRE(flags->state[flag_R] == true);
		REQUIRE(flags->state[flag_a] == false);
		REQUIRE(flags->state[flag_r] == true);
		REQUIRE(flags->state[flag_t] == true);
	}
}

TEST_CASE("Single flags in a few strings", "[valid flags]")
{
	{
		constexpr int argc = 3;
		const char* argv[argc] = {"./a.out","-l", "-R"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == true);
		REQUIRE(flags->state[flag_R] == true);
		REQUIRE(flags->state[flag_a] == false);
		REQUIRE(flags->state[flag_r] == false);
		REQUIRE(flags->state[flag_t] == false);
	}
	{
		constexpr int argc = 4;
		const char* argv[argc] = {"./a.out","-l", "-R", "-t"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == true);
		REQUIRE(flags->state[flag_R] == true);
		REQUIRE(flags->state[flag_a] == false);
		REQUIRE(flags->state[flag_r] == false);
		REQUIRE(flags->state[flag_t] == true);
	}
	{
		constexpr int argc = 5;
		const char* argv[argc] = {"./a.out","-l", "-R", "-t", "-a"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == true);
		REQUIRE(flags->state[flag_R] == true);
		REQUIRE(flags->state[flag_a] == true);
		REQUIRE(flags->state[flag_r] == false);
		REQUIRE(flags->state[flag_t] == true);
	}
	{
		constexpr int argc = 6;
		const char* argv[argc] = {"./a.out","-l", "-R", "-t", "-a", "-r"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == true);
		REQUIRE(flags->state[flag_R] == true);
		REQUIRE(flags->state[flag_a] == true);
		REQUIRE(flags->state[flag_r] == true);
		REQUIRE(flags->state[flag_t] == true);
	}
}

TEST_CASE("Mixed flags in a few strings", "[valid flags]")
{
	{
		constexpr int argc = 3;
		const char* argv[argc] = {"./a.out","-la", "-R"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == true);
		REQUIRE(flags->state[flag_R] == true);
		REQUIRE(flags->state[flag_a] == true);
		REQUIRE(flags->state[flag_r] == false);
		REQUIRE(flags->state[flag_t] == false);
	}
	{
		constexpr int argc = 4;
		const char* argv[argc] = {"./a.out","-la", "-rR", "-t"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == true);
		REQUIRE(flags->state[flag_R] == true);
		REQUIRE(flags->state[flag_a] == true);
		REQUIRE(flags->state[flag_r] == true);
		REQUIRE(flags->state[flag_t] == true);
	}
	{
		constexpr int argc = 3;
		const char* argv[argc] = {"./a.out","-lrta", "-R"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == true);
		REQUIRE(flags->state[flag_R] == true);
		REQUIRE(flags->state[flag_a] == true);
		REQUIRE(flags->state[flag_r] == true);
		REQUIRE(flags->state[flag_t] == true);
	}
	{
		constexpr int argc = 3;
		const char* argv[argc] = {"./a.out","-lr", "-Rta"};
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->state[flag_l] == true);
		REQUIRE(flags->state[flag_R] == true);
		REQUIRE(flags->state[flag_a] == true);
		REQUIRE(flags->state[flag_r] == true);
		REQUIRE(flags->state[flag_t] == true);
	}
}
