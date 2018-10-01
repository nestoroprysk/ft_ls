#include <liblogic.h>
#include <libft.h>
#include <stdio.h>

typedef void (*t_turn_on_func)(t_flags* flags);
bool is_flag_argv(const char* str);
bool is_valid_flag(const char* str);
void turn_on_l(t_flags* flags);
void turn_on_R(t_flags* flags);
void turn_on_a(t_flags* flags);
void turn_on_r(t_flags* flags);
void turn_on_t(t_flags* flags);

bool valid_flags(int argc, const char** argv)
{
	for (int i = 1; i < argc; i++)
		if (is_flag_argv(argv[i]))
			if (!is_valid_flag(argv[i]))
				return false;
	return true;
}

t_flags parse_flags(int argc, const char** argv)
{
	t_turn_on_func turn_on_flag_func_array[NB_FLAGS] =
		{turn_on_l,turn_on_R,turn_on_a,turn_on_r,turn_on_t};
	t_flags result = {false,false,false,false,false};
	for (int i = 1; i < argc; i++)
		if (is_flag_argv(argv[i]))
			for (size_t j = 0; j < NB_FLAGS; ++j)
				if (ft_strchr(argv[i], FLAGS_STR[j]))
					turn_on_flag_func_array[j](&result);
	return result;
}

bool is_flag_argv(const char* str)
{
	return ft_strlen(str) > 1 && str[0] == '-';
}

bool is_valid_flag(const char* str)
{
	size_t len = ft_strlen(str);
	for (size_t i = 1; i < len; ++i)
		if (!ft_strchr(FLAGS_STR, str[i]))
			return false;
	return true;
}

void turn_on_l(t_flags* flags)
{
	flags->l = true;
}

void turn_on_R(t_flags* flags)
{
	flags->R = true;
}

void turn_on_a(t_flags* flags)
{
	flags->a = true;
}

void turn_on_r(t_flags* flags)
{
	flags->r = true;
}

void turn_on_t(t_flags* flags)
{
	flags->t = true;
}
