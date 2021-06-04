/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:46:53 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:46:55 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

size_t		ft_strlen(const char* string)
{
	unsigned short size;

	size = 0;
	while (string[size])
		++size;
	return (size);
}
