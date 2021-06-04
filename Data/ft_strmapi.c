/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:47:09 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:47:11 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char* ft_strmapi(char const* s, char (*f)(unsigned int, char))
{
	size_t	index;
	size_t	length;
	char*	str;

	if (is_null(s))
		return NULL;
	index = 0;
	length = ft_strlen(s);
	if (is_null(str = ft_calloc(length + 1, sizeof(char))))
		return NULL;
	while (index < length)
	{
		str[index] = (*f)(index, s[index]);
		++index;
	}
	str[index] = '\0';
	return (str);
}
