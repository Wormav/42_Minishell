/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 07:33:28 by jlorette          #+#    #+#             */
/*   Updated: 2025/01/16 08:32:46 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void ft_free_array(char **array)
{
	int i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char **extract_options(char *str)
{
    char **words;
    char **options;
    int i;
    int count;

    words = ft_split(str, ' ');
    if (!words)
        return (NULL);

    // Compter les options
    count = 0;
    i = 0;
    while (words[i])
    {
        if (words[i][0] == '-')
            count++;
        i++;
    }

    // Allouer et copier les options
    options = ft_calloc(count + 1, sizeof(char *));
    if (!options)
    {
        ft_free_array(words);
        return (NULL);
    }

    count = 0;
    i = 0;
    while (words[i])
    {
        if (words[i][0] == '-')
            options[count++] = ft_strdup(words[i]);
        i++;
    }
    ft_free_array(words);
    return (options);
}

static char *extract_params(char *str)
{
    char **words;
    char *params;
    int i;
    int start;

    words = ft_split(str, ' ');
    if (!words)
        return (NULL);

    // Trouver le début des paramètres
    i = 1; // Skip command
    while (words[i] && words[i][0] == '-')
        i++;

    // Joindre les paramètres restants
    if (!words[i])
    {
        ft_free_array(words);
        return (NULL);
    }

    start = i;
    params = ft_strdup(words[i]);
    i++;
    while (words[i])
    {
        char *tmp = ft_strjoin(params, " ");
        free(params);
        params = ft_strjoin(tmp, words[i]);
        free(tmp);
        i++;
    }
    ft_free_array(words);
    return (params);
}

t_cmd *exec_create_cmd(t_ast *ast)
{
    t_cmd *cmd;
    char **words;

    if (ast->token != TOKEN_CMD || !ast->content)
        return (NULL);

    cmd = ft_calloc(1, sizeof(t_cmd));
    if (!cmd)
        return (NULL);

    words = ft_split(ast->content, ' ');
    if (!words)
    {
        free(cmd);
        return (NULL);
    }

    // Premier mot est la commande
    cmd->cmd = ft_strdup(words[0]);
    ft_free_array(words);

    if (!cmd->cmd)
    {
        free(cmd);
        return (NULL);
    }

    // Extraire options et paramètres
    cmd->options = extract_options(ast->content);
    cmd->params = extract_params(ast->content);

    return (cmd);
}
