#include "catch.hpp"

extern "C"
{
	#include <liblogic.h>
}

TEST_CASE("Basic strange tests", "[valid and invalid flags]")
{
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-llllll"};
		REQUIRE(valid_flags(argc, argv) == true);
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->l == true);
		REQUIRE(flags->R == false);
		REQUIRE(flags->a == false);
		REQUIRE(flags->r == false);
		REQUIRE(flags->t == false);
		free(flags);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-lRartlrRRlR"};
		REQUIRE(valid_flags(argc, argv) == true);
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->l == true);
		REQUIRE(flags->R == true);
		REQUIRE(flags->a == true);
		REQUIRE(flags->r == true);
		REQUIRE(flags->t == true);
		free(flags);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-lRarqtlrRRlR"};
		REQUIRE(valid_flags(argc, argv) == false);
	}
	{
		constexpr int argc = 3;
		const char* argv[argc] = {"./a.out", "-lRartlrRRlR", "-lRartlrRRlR"};
		REQUIRE(valid_flags(argc, argv) == true);
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->l == true);
		REQUIRE(flags->R == true);
		REQUIRE(flags->a == true);
		REQUIRE(flags->r == true);
		REQUIRE(flags->t == true);
		free(flags);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "--lRartlrRRlR"};
		REQUIRE(valid_flags(argc, argv) == false);
	}
}
