/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:38:28 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:38:30 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

int			ft_memcmp(const void* string1, const void* string2, size_t size)
{
	unsigned short index;
	unsigned char* s1;
	unsigned char* s2;
	
	index = 0;
	s1 = (unsigned char*)string1;
	s2 = (unsigned char*)string2;
	while (index < size)
	{
		if (s1[index] != s2[index])
			return s1[index] - s2[index];
		++index;
	}
	return 0;
}
