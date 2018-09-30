#define CATCH_CONFIG_MAIN
#include "catch.hpp"

extern "C"
{
	#include <liblogic.h>
}

TEST_CASE("Basic tests", "[flags]")
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

TEST_CASE("Mixed flags in single string", "[flags]")
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
