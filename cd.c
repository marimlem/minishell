#include "minishell.h"

int	ft_check_driectory(t_data *d,const char *path)
{
	DIR	*dp;
	struct dirent *dirp;

	dp = opendir(path);
	if (dp == NULL)
	{
		if (errno == EACCES)
		{
			d->exit_code = 1;
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd((char *)path, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		else if (errno == ENOENT)
		{
			d->exit_code = 1;
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

	path = current->args[1];
	if (!current->args[1])
	{
		home = ft_find_key_value(*d->env, "HOME");
		if (home == NULL)
		{
			d->exit_code = 1;
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;
		}
		chdir(home);
	}
	else if (current->args[1] && current->args[2])
	{
		d->exit_code = 1;
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	else if (ft_strcmp(current->args[1], "..") == 0)
		chdir("..");
	else if (ft_strcmp(current->args[1], ".") == 0)
		return ;
	else if (ft_check_driectory(d, path) == 0)
		chdir(path);
	//free_double_array(cd_input);
}
