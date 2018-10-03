#include <liblogic.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

bool is_valid_flag(const char* str);

bool valid_flags(int argc, const char** argv)
{
	for (int i = 1; i < argc; i++)
		if (is_flag_argv(argv[i]))
			if (!is_valid_flag(argv[i]))
				return false;
	return true;
}

t_flags* parse_flags(int argc, const char** argv)
{
	t_flags* result = (t_flags*)ft_memalloc(sizeof(t_flags));
	for (int i = 1; i < argc; i++)
		if (is_flag_argv(argv[i]))
			for (size_t j = 0; j < NB_FLAGS; ++j)
				if (ft_strchr(argv[i], FLAGS_STR[j]))
					result->flag[j] = true;
	return result;
}

bool is_flag_argv(const char* str)
{
	assert(str);
	return ft_strlen(str) > 1 && str[0] == '-';
}

bool is_valid_flag(const char* str)
{
	assert(str);
	size_t len = ft_strlen(str);
	for (size_t i = 1; i < len; ++i)
		if (!ft_strchr(FLAGS_STR, str[i]))
			return false;
	return true;
}

