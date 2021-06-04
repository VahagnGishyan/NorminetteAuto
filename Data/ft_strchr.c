/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:43:28 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:43:29 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

char*		ft_strchr(const char* string, int symbol)
{
	return (char*)(ft_memchr(string, symbol, ft_strlen(string) + 1));
}
