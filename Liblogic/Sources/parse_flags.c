#include <liblogic.h>
#include <libft.h>
#include <stdio.h>

typedef void (*t_turn_on_func)(t_flags* flags);
void turn_on_l(t_flags* flags);
void turn_on_R(t_flags* flags);
void turn_on_a(t_flags* flags);
void turn_on_r(t_flags* flags);
void turn_on_t(t_flags* flags);

t_flags parse_flags(int argc, const char** argv)
{
	t_turn_on_func turn_on_flag_func_array[NB_FLAGS] =
		{turn_on_l,turn_on_R,turn_on_a,turn_on_r,turn_on_t};
	t_flags result = {false,false,false,false,false};
	char* flags = "lRart";
	size_t nb_flags = 5;
	for (int i = 1; i < argc; i++)
		if (ft_strlen(argv[i]) > 1 && argv[i][0] == '-')
			for (size_t j = 0; j < nb_flags; ++j)
				if (ft_strchr(argv[i], flags[j]))
					turn_on_flag_func_array[j](&result);
	return result;
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
