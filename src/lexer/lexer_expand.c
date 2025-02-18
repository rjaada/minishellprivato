/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:28:41 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/14 14:09:05 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*get_var_name(char *str, int *i)
{
	int	start;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*get_shell_var_value(char **env, char *var_name)
{
	int		i;
	int		len;
	char	*value;

	if (!var_name)
		return (ft_strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(g_exit_status));
	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
		{
			value = ft_strchr(env[i], '=');
			if (value)
				return (ft_strdup(value + 1));
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*expand_shell_vars(char *str, char **env)
{
	int		i;
	char	*result;
	char	*var_name;
	char	*var_value;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = get_var_name(str, &i);
			if (!var_name)
				return (NULL);
			var_value = get_shell_var_value(env, var_name);
			free(var_name);
			result = join_var_value(result, var_value);
			free(var_value);
			if (!result)
				return (NULL);
		}
		else
		{
			result = join_chars(result, str[i]);
			if (!result)
				return (NULL);
			i++;
		}
	}
	return (result);
}

char	*expand_env_vars(char *str)
{
	int		i;
	char	*result;
	char	*var_name;
	char	*var_value;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = get_var_name(str, &i);
			if (!var_name)
				return (NULL);
			var_value = getenv(var_name);
			free(var_name);
			result = join_var_value(result, var_value);
			if (!result)
				return (NULL);
		}
		else
		{
			result = join_chars(result, str[i]);
			if (!result)
				return (NULL);
			i++;
		}
	}
	return (result);
}
