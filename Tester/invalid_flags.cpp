#include "catch.hpp"

extern "C"
{
	#include <liblogic.h>
}

TEST_CASE("Basic invalid tests", "[invalid flags]")
{
	{
		constexpr int argc = 1;
		const char* argv[argc] = {"./a.out"};
		REQUIRE(valid_flags(argc, argv) == true);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-lq"};
		REQUIRE(valid_flags(argc, argv) == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "--"};
		REQUIRE(valid_flags(argc, argv) == false);
	}
	{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "-l-"};
		REQUIRE(valid_flags(argc, argv) == false);
	}
		{
		constexpr int argc = 2;
		const char* argv[argc] = {"./a.out", "--l"};
		REQUIRE(valid_flags(argc, argv) == false);
	}
}
