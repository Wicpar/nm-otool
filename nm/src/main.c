/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 15:58:00 by fnieto            #+#    #+#             */
/*   Updated: 2017/02/25 15:29:16 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>
#include <stdlib.h>

int		ft_strlen(const char *str)
{
	int ret;

	ret = 0;
	while (*str++)
		ret++;
	return ret;
}

void	enofile(const char *nm,const char* name)
{
	write(2, nm, ft_strlen(nm));
	write(2, ": ", 2);
	write(2, name, ft_strlen(name));
	write(2, ": The file was not recognized as a valid object file.\n", 54);
}

void	enomagic(const char *nm,const char* name)
{
	write(2, nm, ft_strlen(nm));
	write(2, ": ", 2);
	write(2, name, ft_strlen(name));
	write(2, ": No such file or directory.\n", 29);
}

void	nm64(const char *nm, const char* name, const void* mem)
{
	struct mach_header	*header;

	header = (struct mach_header*)mem;
	printf("magic = %x", header->magic);
}

void	nm32(const char *nm, const char* name, const void* mem)
{
	struct mach_header	*header;

	header = (struct mach_header*)mem;
	printf("magic = %x", header->magic);
}

void	nm(const char *nm, const char* name)
{
	int					fd;
	const void			*mem;
	struct stat			sb;
	struct mach_header	*header;

	if (*name != '-')
	{
		fd = open(name, O_RDONLY);
		if (fd == -1)
			return enofile(nm, name);
		fstat(fd, &sb);
		mem = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
		if (mem == MAP_FAILED)
			return (void)printf("FAILED\n");
		header = (struct mach_header*)mem;
		if (header->magic == MH_MAGIC)
			nm32(nm, name, mem);
		else if (header->magic == MH_MAGIC_64)
			nm64(nm, name, mem);
		else
			enomagic(nm, name);
		munmap((void*)mem, sb.st_size);
		close(fd);
	}
}

int		main(int argc,const char *argv[])
{
	int i;

	i = 0;
	if (argc == 1)
		nm(argv[0], "a.out");
	else
		while (++i < argc)
			nm(argv[0], argv[i]);
	return 0;
}
