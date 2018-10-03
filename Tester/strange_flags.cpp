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
		REQUIRE(flags->flag[flag_l] == true);
		REQUIRE(flags->flag[flag_R] == false);
		REQUIRE(flags->flag[flag_a] == false);
		REQUIRE(flags->flag[flag_r] == false);
		REQUIRE(flags->flag[flag_t] == false);
		free(flags);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-lRartlrRRlR"};
		REQUIRE(valid_flags(argc, argv) == true);
		t_flags* flags = parse_flags(argc, argv);
		REQUIRE(flags->flag[flag_l] == true);
		REQUIRE(flags->flag[flag_R] == true);
		REQUIRE(flags->flag[flag_a] == true);
		REQUIRE(flags->flag[flag_r] == true);
		REQUIRE(flags->flag[flag_t] == true);
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
		REQUIRE(flags->flag[flag_l] == true);
		REQUIRE(flags->flag[flag_R] == true);
		REQUIRE(flags->flag[flag_a] == true);
		REQUIRE(flags->flag[flag_r] == true);
		REQUIRE(flags->flag[flag_t] == true);
		free(flags);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "--lRartlrRRlR"};
		REQUIRE(valid_flags(argc, argv) == false);
	}
}
