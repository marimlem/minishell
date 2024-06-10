#include "minishell.h"

int	ft_check_driectory(t_data *d, const char *path)
{
	DIR	*dp;
	/* struct dirent *dirp; */

	dp = opendir(path);
	if (dp == NULL)
	{
		d->exit_code = 1;
		if (errno == EACCES)
			ft_putstr_fd("cd: ", 2), ft_putstr_fd((char *)path, 2), ft_putstr_fd(": Permission denied\n", 2);
		else if (errno == ENOENT)
			ft_putstr_fd("cd: ", 2), ft_putstr_fd((char *)path, 2), ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	/* else
		dirp = readdir(dp); */
	closedir(dp);
	return (0);
}

void	change_to_home_directory(t_data *d)
{
	const char	*home;

	home = ft_find_key_value(*d->env, "HOME");
	if (home == NULL)
	{
		d->exit_code = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	else
		chdir(home);
}

void	cd_too_many_args(t_data *d)
{
	d->exit_code = 1;
	ft_putstr_fd("cd: too many arguments\n", 2);
}

void	change_directory(t_data *d, const char *path)
{
	if (ft_strcmp(path, "..") == 0)
		chdir("..");
	else if (ft_strcmp(path, ".") == 0)
		return;
	else if (ft_check_driectory(d, path) == 0)
		chdir(path);
}

void	ft_cd(t_data *d, t_com *current)
{
	d->exit_code = 0;

	if (current->args[1] == NULL)
		change_to_home_directory(d);
	else if (current->args[2])
		cd_too_many_args(d);
	else
		change_directory(d, current->args[1]);
}
