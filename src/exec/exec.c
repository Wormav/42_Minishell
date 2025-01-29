/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:18:29 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/29 07:34:56 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// !retirer les prints

static size_t	cmd_size(t_cmd *cmd)
{
	size_t	size;
	int		i;

	i = 0;
	size = 0;
	if (cmd->params)
		size++;
	if (!cmd->options)
		return (size + 1);
	while (cmd->options[i])
	{
		size++;
		i++;
	}
	return (size + 1);
}

static char	**join_params(t_cmd *cmd)
{
	char	**str;
	int		i;
	int		j;

	str = lp_alloc(sizeof(char *) * cmd_size(cmd) + 1);
	i = 0;
	j = -1;
	str[i] = lp_alloc(ft_strlen(cmd->cmd) + 1);
	ft_strlcpy(str[i], cmd->cmd, ft_strlen(cmd->cmd) + 1);
	i++;
	if (cmd->options)
	{
		while (cmd->options[++j])
		{
			str[i] = lp_alloc(ft_strlen(cmd->options[j]) + 1);
			ft_strlcpy(str[i], cmd->options[j], ft_strlen(cmd->options[j]) + 1);
			i++;
		}
	}
	if (*(cmd->params))
	{
		str[i] = lp_alloc(ft_strlen(cmd->params) + 1);
		ft_strlcpy(str[i], cmd->params, ft_strlen(cmd->params) + 1);
	}
	return (str);
}

static void	trim_cmd_and_options(t_cmd *cmd)
{
	char	*tmp;
	int		i;

	if (!cmd)
		return ;
	if (cmd->cmd)
	{
		tmp = ft_strtrim(cmd->cmd, " '\"\t");
		lp_free(cmd->cmd);
		cmd->cmd = tmp;
	}
	if (cmd->options)
	{
		i = 0;
		while (cmd->options[i])
		{
			tmp = ft_strtrim(cmd->options[i], " '\"\t");
			lp_free(cmd->options[i]);
			cmd->options[i] = tmp;
			i++;
		}
	}
}

static void	process_others_cmd(t_cmd *cmd, t_env *env_lst, int *error)
{
	char	**test_env;
	char	*test;
	char	**argv_cmd;
	pid_t	pid;

	test_env = env_tab(env_lst);
	test = find_cmd(cmd, env_lst, error);
	argv_cmd = join_params(cmd);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (!test)
			if (execve(cmd->cmd, argv_cmd, test_env) == -1)
				exit(1);
		if (execve(test, argv_cmd, test_env) == -1)
			exit(1);
	}
	waitpid(pid, NULL, 0);
}

static char	*exec_cmd(t_cmd *cmd, int *error, t_env *env_lst)
{
	char	*result;

	result = NULL;
	if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd, error, env_lst);
	if (cmd->params)
		cmd->params = parser_filter_quote(cmd->params);
	if (!ft_strcmp(cmd->cmd, "pwd"))
		result = execute_pwd(cmd, error);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		result = execute_unset(cmd, error, env_lst);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		ft_cd(env_lst, cmd, error);
	else if (!ft_strcmp(cmd->cmd, "export"))
		ft_export(&env_lst, cmd, error);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		result = execute_exit(cmd);
	else if (!ft_strcmp(cmd->cmd, "env"))
		result = execute_env(env_lst, cmd, error);
	else if (ft_strcmp(cmd->cmd, "echo"))
		process_others_cmd(cmd, env_lst, error);
	return (result);
}

void	exec(t_ast *ast, t_env *env_lst)
{
	t_cmd	*cmd;
	t_fds	*fds;
	char	*fd;
	char	*result;
	int		error;

	error = 0;
	cmd = NULL;
	fds = NULL;
	fd = exec_identify_fd(ast);
	exec_store_other_fds(ast, &fds, fd);
	print_fds(fds);
	printf("FD =======> [%s]\n", fd);
	cmd = exec_create_cmd(ast->content);
	trim_cmd_and_options(cmd);
	print_cmd(cmd);
	result = exec_cmd(cmd, &error, env_lst);
	if (error)
	{
		ft_putendl_fd("Error !!!!", 2);
		ft_putendl_fd(result, 2);
	}
	else
		printf("%s\n\n", result);
	lp_free(result);
	cleanup_cmd(cmd);
	exec_free_fds(fds);
}
