#include "minishell.h"

int	ft_check_arg_for_pwd(const char *s)
{
	int	i;

	i = 0;
	if (s[i] && !(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= 'A' && s[i] <= 'Z'))
	{
		if (s[i] == '-')
		{
			if (!s[i + 1] || (s[i + 1] == '-' && !s[i + 2]))
				return (0);
			else
			{
				ft_putstr_fd("pwd: -", 2);
				ft_putchar_fd(((char)s[i + 1]), 2);
				ft_putstr_fd(": invalid option\n", 2);
				//printf("pwd: -%c: invalid option\n", s[i + 1]);
			}
		}
		/* if (s[i] == '-' && s[i + 1] == '-' && !s[i + 2])
			return (0);
		else if (s[i] == '-' && s[i + 1] && s[i + 1] != '-')
		{
			ft_putstr_fd("pwd: -", 2);
			ft_putchar_fd((char)s[i + 1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			//printf("unset: -%c: invalid option\n", s[i + 1]);
		} */
		else if (s[i] == '!')
		{
			if (!s[i + 1])
				return (0);
			else
			{
				ft_putstr_fd("pwd: ", 2);
				ft_putstr_fd((char *)s, 2);
				ft_putstr_fd(": event not found\n", 2);
				//printf("unset: %s: event not found\n", s);
			}
		}
		/* else if (s[i] == '!' && s[i + 1])
		{
			ft_putstr_fd("pwd: ", 2);
			ft_putstr_fd((char *)s, 2);
			ft_putstr_fd(": event not found\n", 2);
			//printf("unset: %s: event not found\n", s);
		} */
		return (1);
	}
	return (0);
}

void	ft_pwd(char *input)
{
	char	pwd[255];

	input = NULL;
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		ft_putstr_fd("getcwd() error!", 2);
	else
	{
		ft_putstr_fd(pwd, 2);
		ft_putstr_fd("\n", 2);
	}
}
