/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:35:02 by mprofett          #+#    #+#             */
/*   Updated: 2022/10/04 12:35:05 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(char *s, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
	{
		*(s) = '\0';
		++s;
	}
}