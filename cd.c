#include "minishell.h"

int	ft_check_driectory(const char *path)
{
	DIR	*dp;
	struct dirent *dirp;

	dp = opendir(path);
	if (dp == NULL)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd((char *)path, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		else if (errno == ENOENT)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd((char *)path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			//printf("cd: %s: No such file or directory\n", path);
		}
		return (1);
	}
	else
		dirp = readdir(dp);
	closedir(dp);
	return (0);
}

	void	ft_cd(t_data *d, t_com *current)
{
	const char	*home;
	const char	*path;
	char	**cd_input;

	home = ft_find_key_value(*d->env, "HOME");
	cd_input = current->args;
	path = cd_input[1];
	if (!current->args[1])
	{
		if (ft_strcmp(current->args[0], "cd") == 0)
			chdir(home);
	}
	else if (current->args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	else if (ft_strcmp(current->args[1], "..") == 0)
		chdir("..");
	else if (ft_check_driectory(path) == 0)
		chdir(path);
	//free_double_array(cd_input);
}
