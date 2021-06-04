/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:46:10 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:46:26 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

size_t		ft_strlcat(char* destination, const char* source, size_t destsize)
{
	char*			dest;
	char*			sorc;
	unsigned short		dest_length;

	dest = destination;
	sorc = (char*)source;
	dest_length = 0;
	while (dest_length < destsize && *dest)
	{
		++dest;
		++dest_length;
	}
	if (dest_length == destsize)
		return (dest_length + ft_strlen(sorc));		
	while (*sorc)
	{
		if (dest_length < destsize)
		{
			*dest++ = *sorc;
			++dest_length;
		}
		++sorc;
	}
	*dest = '\0';
	return (dest_length + ft_strlen(sorc));
}
