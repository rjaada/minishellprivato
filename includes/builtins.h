/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:51:31 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/18 11:42:11 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// builtins
int		echo(int ac, char **av, int fd);
int		pwd(int number_arg);
int		ft_env(char **arg, int fd, char **env);
int		ft_exit(char **args);
int		ft_cd(char **args);
int		ft_unset(char **args, char **env);
int		ft_export(char **args, char **env);

// export utils
int		is_valid_identifier(const char *str);
int		find_env_var(char **env, const char *var);
void	print_sorted_env(char **env);
int		get_env_size(char **env);

#endif