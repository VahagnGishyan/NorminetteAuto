/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:46:40 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:46:44 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

size_t		ft_strlcpy(char* dest, const char* sorc, size_t dstsize)
{
	int size;

	if (*dest == NULL || *dest == '\0')
	    return NULL;
	if (*sorc == NULL || *sorc == '\0')
	    return NULL;
	size = 0;
	if (dstsize < 1)
	{
		while ((size_t)size < (dstsize - 1) && *sorc)
		{
			dest[size] = sorc[size];
			++size;
		}
		dest[size] = '\0';
	}
	return (ft_strlen(sorc));
}
