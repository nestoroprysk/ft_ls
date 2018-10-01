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
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == false);
		REQUIRE(flags.R == false);
		REQUIRE(flags.a == false);
		REQUIRE(flags.r == false);
		REQUIRE(flags.t == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "l"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == false);
		REQUIRE(flags.R == false);
		REQUIRE(flags.a == false);
		REQUIRE(flags.r == false);
		REQUIRE(flags.t == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-l"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == true);
		REQUIRE(flags.R == false);
		REQUIRE(flags.a == false);
		REQUIRE(flags.r == false);
		REQUIRE(flags.t == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == false);
		REQUIRE(flags.R == false);
		REQUIRE(flags.a == false);
		REQUIRE(flags.r == false);
		REQUIRE(flags.t == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-t"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == false);
		REQUIRE(flags.R == false);
		REQUIRE(flags.a == false);
		REQUIRE(flags.r == false);
		REQUIRE(flags.t == true);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-R"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == false);
		REQUIRE(flags.R == true);
		REQUIRE(flags.a == false);
		REQUIRE(flags.r == false);
		REQUIRE(flags.t == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-a"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == false);
		REQUIRE(flags.R == false);
		REQUIRE(flags.a == true);
		REQUIRE(flags.r == false);
		REQUIRE(flags.t == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-r"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == false);
		REQUIRE(flags.R == false);
		REQUIRE(flags.a == false);
		REQUIRE(flags.r == true);
		REQUIRE(flags.t == false);
	}
}

TEST_CASE("Mixed flags in single string", "[valid flags]")
{
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out","-lR"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == true);
		REQUIRE(flags.R == true);
		REQUIRE(flags.a == false);
		REQUIRE(flags.r == false);
		REQUIRE(flags.t == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out","-rt"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == false);
		REQUIRE(flags.R == false);
		REQUIRE(flags.a == false);
		REQUIRE(flags.r == true);
		REQUIRE(flags.t == true);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out","-lRrt"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == true);
		REQUIRE(flags.R == true);
		REQUIRE(flags.a == false);
		REQUIRE(flags.r == true);
		REQUIRE(flags.t == true);
	}
}

TEST_CASE("Single flags in a few strings", "[valid flags]")
{
	{
		constexpr int argc = 3;
		const char* argv[argc] = {"./a.out","-l", "-R"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == true);
		REQUIRE(flags.R == true);
		REQUIRE(flags.a == false);
		REQUIRE(flags.r == false);
		REQUIRE(flags.t == false);
	}
	{
		constexpr int argc = 4;
		const char* argv[argc] = {"./a.out","-l", "-R", "-t"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == true);
		REQUIRE(flags.R == true);
		REQUIRE(flags.a == false);
		REQUIRE(flags.r == false);
		REQUIRE(flags.t == true);
	}
	{
		constexpr int argc = 5;
		const char* argv[argc] = {"./a.out","-l", "-R", "-t", "-a"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == true);
		REQUIRE(flags.R == true);
		REQUIRE(flags.a == true);
		REQUIRE(flags.r == false);
		REQUIRE(flags.t == true);
	}
	{
		constexpr int argc = 6;
		const char* argv[argc] = {"./a.out","-l", "-R", "-t", "-a", "-r"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == true);
		REQUIRE(flags.R == true);
		REQUIRE(flags.a == true);
		REQUIRE(flags.r == true);
		REQUIRE(flags.t == true);
	}
}

TEST_CASE("Mixed flags in a few strings", "[valid flags]")
{
	{
		constexpr int argc = 3;
		const char* argv[argc] = {"./a.out","-la", "-R"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == true);
		REQUIRE(flags.R == true);
		REQUIRE(flags.a == true);
		REQUIRE(flags.r == false);
		REQUIRE(flags.t == false);
	}
	{
		constexpr int argc = 4;
		const char* argv[argc] = {"./a.out","-la", "-rR", "-t"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == true);
		REQUIRE(flags.R == true);
		REQUIRE(flags.a == true);
		REQUIRE(flags.r == true);
		REQUIRE(flags.t == true);
	}
	{
		constexpr int argc = 3;
		const char* argv[argc] = {"./a.out","-lrta", "-R"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == true);
		REQUIRE(flags.R == true);
		REQUIRE(flags.a == true);
		REQUIRE(flags.r == true);
		REQUIRE(flags.t == true);
	}
	{
		constexpr int argc = 3;
		const char* argv[argc] = {"./a.out","-lr", "-Rta"};
		t_flags flags = parse_flags(argc, argv);
		REQUIRE(flags.l == true);
		REQUIRE(flags.R == true);
		REQUIRE(flags.a == true);
		REQUIRE(flags.r == true);
		REQUIRE(flags.t == true);
	}
}
