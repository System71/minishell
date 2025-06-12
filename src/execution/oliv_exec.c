#include "minishell.h"

int	is_path_absolute_or_relative(char *cmd)
{
	int	len;

	len = 0;
	if (!cmd)
		return (0);
	if (cmd[0] == '/')
		return (1);
	if (cmd[0] == '.' && cmd[1] == '/')
		return (1);
	if (cmd[0] == '.')
	{
		if (cmd[1] == '.' && cmd[2] == '/')
			return (1);
	}
	return (0);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*find_executable(char **allpath, char **cmd)
{
	int		i;
	char	*path_part;
	char	*exec;

	i = 0;
	while (allpath[i])
	{
        path_part = ft_strjoin(allpath[i], "/");
		if (!path_part)
			ft_free_double_tab(allpath, cmd);
		exec = ft_strjoin(path_part, cmd[0]);
		free(path_part);
		if (!exec)
			ft_free_double_tab(allpath, cmd);
		if (access(exec, F_OK) == 0)
		{
			ft_free_tab(allpath, 0);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_free_tab(allpath, 0);
    return (NULL);
}

char	*get_path(char **cmd, char **env)
{
	char	*env_path;
	char	**allpath;
	char	*exec;

	env_path = my_getenv("PATH", env);

	if (!env_path)
		return (NULL);
	allpath = ft_split(env_path, ':');
	if (!allpath)
		exit(-1);
	exec = find_executable(allpath, cmd);
	return (exec);
}

char	*get_cmd_path(char **s_cmd, char **env)
{
	int		abs_path;
	char	*tmp;
	char	*path;

	abs_path = is_path_absolute_or_relative(s_cmd[0]);
	tmp = NULL;
	path = NULL;
	if (abs_path)
	{
        if (access(s_cmd[0], F_OK) == 0)
        tmp = ft_strdup(s_cmd[0]);
		return (tmp);
	}
	path = get_path(s_cmd, env);
	return (path);
}

void	check_permission(char **s_cmd, char *path)
{
	struct stat st;

    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
    {
        ft_putstr_fd(s_cmd[0], 2);
        ft_putstr_fd(": Is a directory\n", 2);
        free(path);
        ft_free_tab(s_cmd, 0);
        exit(126);
    }
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd(s_cmd[0], 2);
		ft_putstr_fd(": permission denied\n", 2);
		free(path);
		ft_free_tab(s_cmd, 0);
		exit(126);
	}
}

void	execute_command(char **s_cmd, char **env)
{
	char	*path;
	int		err;

	path = get_cmd_path(s_cmd, env);
	if (!path)
	{
		ft_putstr_fd(s_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_tab(s_cmd, 0);
		exit(127);
	}
	check_permission(s_cmd, path);
	if (execve(path, s_cmd, env) == -1)
	{
		err = errno;
		perror(s_cmd[0]);
		free(path);
		ft_free_tab(s_cmd, 0);
		if (err == EISDIR || err == EACCES || err == ENOEXEC)
			exit(126);
		else if (err == ENOENT)
			exit(127);
		else
			exit(1);
	}
}