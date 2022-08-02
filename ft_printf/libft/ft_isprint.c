/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:07:12 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 16:18:17 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// check if ch is a printing character
int	ft_isprint(int ch)
{
	return (ch >= 32 && ch <= 126);
}
