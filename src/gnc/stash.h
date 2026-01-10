/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/10 19:29:18 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STASH_H
# define STASH_H

# include "libft.h"

typedef struct s_stash
{
	int			fd;
	t_buff		buffer;
}	t_stash;

t_buff	*get_buffer(int fd);
void	stash_find_and_free(int fd);
void	stashs_free_all(void);

#endif
