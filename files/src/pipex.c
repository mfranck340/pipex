
#include "../include/pipex.h"


char *search_path(char *command, char **envp)
{
	int		i;
	char	**path;
	char	*path_env;
	char	*path_command;

	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	path = ft_split(path_env, ':');
	if (path == 0)
	{
		perror("Error splitting path");
		return (0);
	}
	i = 0;
	while (path[i] != 0)
	{
		path_command = ft_strjoin(path[i], "/");
		if (path_command == 0)
		{
			perror("Error joining path");
			return (0);
		}
		path_command = ft_strjoin(path_command, command);
		if (path_command == 0)
		{
			perror("Error joining path");
			return (0);
		}
		if (access(path_command, F_OK) == 0)
		{
			return (path_command);
		}
		i++;
	}
	return (0);
}

int execute_command(char *command, char **envp)
{
	char	**args;
	char	*path;
	int		i;

	args = ft_split(command, ' ');
	if (args == NULL)
	{
		perror("Error splitting command");
		return (1);
	}
	path = search_path(args[0], envp);
	if (path == NULL)
	{
		perror("Error joining path");
		return (1);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		execve(path, args, envp);
		i++;
	}
	perror("Error executing command");
	return (1);
}


int main(int argc, char **argv, char **envp)
{
	int	count;
	int	fd[2];
	int	pipefd[2];
	int	i;
	int	j;
	int	pid;

	/*if (argc != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}*/

	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
	{
		perror("Error opening file 1");
		return (1);
	}
	fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		perror("Error opening file 2");
		return (1);
	}
	
	count = argc - 3;
	i = 0;
	while (i < count - 1)
	{
		if (pipe(pipefd + 2 * i) == -1)
		{
			perror("Error creating pipe");
			return (1);
		}
		i++;
	}

	i = 0;
	while (i < count)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error creating child process");
			return (1);
		}
		if (pid == 0)
		{
			if (i == 0)
			{
				dup2(fd[0], STDIN_FILENO);
				dup2(pipefd[1], STDOUT_FILENO);
			}
			else
			{
				dup2(pipefd[0], STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
			}
			j = 0;
			while (j < 2 * (count - 1))
			{
				close(pipefd[j]);
				j++;
			}

			execute_command(argv[i + 2], envp);
			
			return (1);
		}
		i++;
	}

	i = 0;
	while (i < 2 * (count - 1))
	{
		close(pipefd[i]);
		i++;
	}

	close(fd[0]);
	close(fd[1]);

	i = 0;
	while (i < count)
	{
		wait(0);
		i++;
	}
	
	return (0);
}
