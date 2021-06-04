/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:47:25 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:47:29 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strncmp(const char* string1, const char* string2, size_t size)
{
	while (size > 0 && *string1 && *string2)
	{
		if (*string1 != *string2)
			break;
		string1++;
		string2++;
		--size;
	}
	if (size == 0)
		return (0);
	return (*(unsigned char*)string1 - *(unsigned char*)string2);
}
