#include "minishell.h"

void	ft_pwd(char *input)
{
	char	pwd[254];
	input = NULL;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd() error!");
	else
		printf("%s\n", pwd);
}
