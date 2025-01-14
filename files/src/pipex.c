

#include "../include/pipex.h"



void	child_process(char **argv, int *fd, int i)
{
	int		file;

	if (i == 0)
	{
		file = open(argv[1], O_RDONLY);
		if (file == -1)
			exit_error("open");
		dup2(file, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	else
	{
		file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1)
			exit_error("open");
		dup2(fd[0], STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
	}
	close(fd[0]);
	close(fd[1]);
	close(file);
}

void	parent_wait(void)
{
	int	status;

	wait(&status);
	wait(&status);
}

void	create_childs(char **argv, char **envp, int *fd)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < 2)
	{
		pid = fork();
		if (pid == -1)
			exit_error("fork");
		if (pid == 0)
		{
			child_process(argv, fd, i);
			execute(argv[i + 2], envp);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit_error("pipe");
		create_childs(argv, envp, fd);
		close(fd[0]);
		close(fd[1]);
		parent_wait();
	}
	else
		ft_printf("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
	return (0);
}
