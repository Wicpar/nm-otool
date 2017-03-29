/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 15:58:32 by fnieto            #+#    #+#             */
/*   Updated: 2017/03/29 19:52:12 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <mach-o/loader.h>
# include <mach-o/swap.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>

typedef union		u_mem
{
	void					*mem;
	struct mach_header		*header;
}					t_mem;

typedef struct		s_context
{
		int						fd;
		struct stat				stat;
		t_mem					mem;
		const char				*name;
		const char				*nm;
}					t_context;

#endif