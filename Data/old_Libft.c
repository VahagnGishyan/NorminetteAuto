/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:50:31 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:50:45 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

bool			is_null(const char *ptr)
{
	return (ptr == NULL);
}

bool			get_dynamic_memory(char *ptr, int size)
{
	ptr =(char *) malloc(size);
	return (ptr == NULL);
}