/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouahidi <nouahidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:53:09 by nouahidi          #+#    #+#             */
/*   Updated: 2022/11/18 23:19:00 by nouahidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *sv)
{
	char	*ln;
	int		i;

	i = 0;
	if (!sv[i])
		return (NULL);
	while (sv[i] != '\n' && sv[i])
		i++;
	if (sv[i] == '\n')
		ln = malloc(i + 2);
	else
		ln = malloc(i + 1);
	if (!ln)
		return (NULL);
	i = 0;
	while (sv[i] != '\n' && sv[i])
	{
		ln[i] = sv[i];
		i++;
	}
	if (sv[i] == '\n')
		ln[i++] = '\n';
	ln[i] = '\0';
	return (ln);
}

char	*ft_next(char *sv)
{
	size_t		k;
	int			i;
	char		*str;

	k = 0;
	i = 0;
	while (sv[k] != '\n' && sv[k])
		k++;
	if (sv[k] == '\n')
		k++;
	if (ft_strlen(sv) == k)
		return (free(sv), NULL);
	str = malloc(ft_strlen(sv) - k + 1);
	if (!str)
		return (NULL);
	while (sv[k])
		str[i++] = sv[k++];
	str[i] = '\0';
	return (free(sv), sv = NULL, str);
}

char	*get_next_line(int fd)
{
	t_var		var;
	static char	*sv[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!sv[fd])
		sv[fd] = ft_strdup("");
	var.i = 1;
	var.str = malloc(BUFFER_SIZE + 1);
	if (!var.str)
		return (NULL);
	while (!ft_strchr(sv[fd], '\n') && var.i)
	{
		var.i = read(fd, var.str, BUFFER_SIZE);
		if (var.i < 0)
			return (free(var.str), free(sv[fd]), sv[fd] = NULL, NULL);
		var.str[var.i] = '\0';
		sv[fd] = ft_strjoin(sv[fd], var.str);
	}
	free (var.str);
	var.ln = ft_get_line(sv[fd]);
	sv[fd] = ft_next(sv[fd]);
	return (var.ln);
}
