/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:04:02 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 16:16:23 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// check if the ch is lowercase alphabets
// short circuit AND: if the 1st case is false, no need to evaluate 2nd case
static int	ft_islower(int ch)
{
	return (ch >= 'a' && ch <= 'z');
}

// check if the ch is uppercase alphabets
static int	ft_isupper(int ch)
{
	return (ch >= 'A' && ch <= 'Z');
}

// short circuit OR: if is lower than no need to consider if it's upper or not
int	ft_isalpha(int ch)
{
	return (ft_islower(ch) || ft_isupper(ch));
}
