/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:45:40 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:45:41 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char* ft_strjoin(char const* string1, char const* string2)
{
	char*	string;
	size_t	s1_length;
	size_t	s2_length;

	if (is_null(string1))
		return NULL;
	if (is_null(string2))
		return NULL;
	s1_length = ft_strlen(string1);
	s2_length = ft_strlen(string2);
	if (get_dynamic_memory(string, (s1_length + s2_length) + 1))
		return NULL;
	ft_memcpy(string, string1, s1_length);
	ft_memcpy(string + s1_length, string2, s2_length);
	string[s1_length + s2_length] = '\0';
	return (string);
}
