/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:15:02 by rjaada            #+#    #+#             */
/*   Updated: 2025/01/29 15:15:08 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/* Error handling */
void	*error_malloc(void);
void	print_error(char *msg);

/* String utils */
char	*str_join_char(char *str, char c);
char	*str_join_free(char *s1, char *s2);

#endif