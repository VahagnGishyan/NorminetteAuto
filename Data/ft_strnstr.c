/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:47:46 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:47:48 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char*		ft_strnstr(const char* haystack, const char* needle, size_t len)
{
	//Chem kara bacatrem bard em grel, gnaceq Hovsepin harcreq
	if(len == 0)
		return ((char*)haystack);
	while (haystack = ft_strchr(haystack, needle[0]))
	{
		if(!ft_strncmp(haystack, needle, len))
			return ((char*)haystack);
		++haystack;
	}
	return 0;
}
