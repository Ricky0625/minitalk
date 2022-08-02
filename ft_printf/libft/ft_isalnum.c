/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:12:09 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 16:12:41 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// check whether ch is alphabets or digits, either one will return 1 (true)
// short circuit OR: if the 1st case is true, no need to evaluate the 2nd case
int	ft_isalnum(int ch)
{
	return (ft_isalpha(ch) || ft_isdigit(ch));
}
