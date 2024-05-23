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
			//printf("cd: %s: Permission denied\n", path);
		else if (errno == ENOENT)
			printf("cd: %s: No such file or directory\n", path);
		return (1);
	}
	else
		dirp = readdir(dp);
	closedir(dp);
	return (0);
}

	void	ft_cd(t_data *d)
{
	const char	*home;
	const char	*path;
	char	**cd_input;

	home = ft_find_key_value(*d->env, "HOME");
	cd_input = ft_split2(d->input, ' ');
	path = cd_input[1];
	if (ft_strcmp(d->input, "cd") == 0)
		chdir(home);
	else if (ft_strcmp(d->input, "cd ..") == 0)
		chdir("..");
	else if (ft_check_driectory(path) == 0)
		chdir(path);
	free_double_array(cd_input);
}
