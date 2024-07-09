/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mablatie <mablatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:32:52 by bvaujour          #+#    #+#             */
/*   Updated: 2024/01/23 13:26:08 by mablatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_add_to_tab(char **tab, char *more)
{
	int		i;
	char	**new;

	i = 0;
	while (tab[i])
		i++;
	if (more != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (tab[++i])
		new[i] = tab[i];
	if (more != NULL)
		new[i++] = more;
	new[i] = 0;
	free(tab);
	return (new);
}
