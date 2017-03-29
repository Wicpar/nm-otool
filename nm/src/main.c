/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 15:58:00 by fnieto            #+#    #+#             */
/*   Updated: 2017/03/29 23:02:47 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char*)s1;
	b = (unsigned char*)s2;
	while (n--)
	{
		if (*a != *b)
			return ((int)*a - (int)*b);
		a++;
		b++;
	}
	return (0);
}

int		ft_strlen(const char *str)
{
	int ret;

	ret = 0;
	while (*str++)
		ret++;
	return (ret);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	return (ft_memcmp(s1, s2, ft_strlen(s1) + 1));
}

void	enofile(const t_context *ctx)
{
	write(2, ctx->nm, ft_strlen(ctx->nm));
	write(2, ": ", 2);
	write(2, ctx->name, ft_strlen(ctx->name));
	write(2, ": No such file or directory.\n", 29);
}

void	enomagic(const t_context *ctx)
{
	write(2, ctx->nm, ft_strlen(ctx->nm));
	write(2, ": ", 2);
	write(2, ctx->name, ft_strlen(ctx->name));
	write(2, ": The file was not recognized as a valid object file.\n", 54);
}

void	enomem(const t_context *ctx)
{
	write(2, ctx->nm, ft_strlen(ctx->nm));
	write(2, ": ", 2);
	write(2, ctx->name, ft_strlen(ctx->name));
	write(2, ": Out of memory.\n", 17);
}

int		get_fd(t_context *ctx)
{
	int		fd;

	if (!ft_strcmp(ctx->name, "-"))
		fd = 0;
	else
		fd = open(ctx->name, O_RDONLY);
	if (fd == -1)
	{
		enofile(ctx);
		return (1);
	}
	ctx->stat.st_size = 0;
	fstat(fd, &(ctx->stat));
	printf("%lli\n", ctx->stat.st_size);
	if (ctx->stat.st_size < sizeof(struct mach_header))
	{
		enomagic(ctx);
		return (1);
	}
	ctx->fd = fd;
	return (0);
}

void	ret_fd(t_context *ctx)
{
	int		fd;

	fd = ctx->fd;
	if (fd > 2)
		close(fd);
	ctx->fd = -1;
}

int		get_mem(t_context *ctx)
{
	void	*mem;

	mem = mmap(NULL, ctx->stat.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE, ctx->fd, 0);
	if (mem == MAP_FAILED)
	{
		printf("%s\n", strerror(errno));
		enomem(ctx);
		return (1);
	}
	ctx->mem.mem = mem;
	return (0);
}

void	ret_mem(t_context *ctx)
{
	munmap(ctx->mem.mem, ctx->stat.st_size);
	ctx->mem.mem = 0;
}

void	nm64(t_context *ctx)
{
	void	*ptr;
	
	ptr = ctx->mem.mem + sizeof(struct mach_header_64);
	printf("magic = %x\n", ctx->mem.header->magic);
	printf("cpuType = %i\n", ctx->mem.header->cputype);
	printf("ncmds = %i\n", ctx->mem.header->ncmds);
	printf("sizeof cmds = %i\n", ctx->mem.header->sizeofcmds);
	int ncmds = ctx->mem.header->ncmds;
	for (int i = 0; i < ncmds; i++) {
		struct segment_command *cmd = ptr;
		if (cmd->cmd == LC_SEGMENT_64) {
			struct segment_command_64 *command = ptr;
			printf("%i\n", command->cmd);
			printf("%i\n", command->cmdsize);
			printf("%s\n", command->segname);
			printf("%llu\n", command->vmaddr);
			printf("%llu\n", command->vmsize);
			printf("%llu\n", command->fileoff);
			printf("%llu\n", command->filesize);
			printf("%i\n", command->nsects);
			printf("%i\n", command->flags);
			printf("\n------\n");
		} else if (cmd->cmd == LC_SEGMENT) {
			struct segment_command *command = ptr;
			printf("%i\n", command->cmd);
			printf("%i\n", command->cmdsize);
			printf("%s\n", command->segname);
			printf("%i\n", command->vmaddr);
			printf("%i\n", command->vmsize);
			printf("%i\n", command->fileoff);
			printf("%i\n", command->filesize);
			printf("%i\n", command->nsects);
			printf("%i\n", command->flags);
			printf("\n------\n");
		}
		ptr += cmd->cmdsize;
	}
}

void	nm32(t_context *ctx)
{
	printf("magic = %x", ctx->mem.header->magic);
}

void	nm(t_context *ctx)
{
	if (*(ctx->name) != '-' || !ft_strcmp(ctx->name, "-"))
	{
		if (get_fd(ctx) || get_mem(ctx))
			return ;
		ret_fd(ctx);
		if (ctx->mem.header->magic == MH_MAGIC)
			nm32(ctx);
		else if (ctx->mem.header->magic == MH_MAGIC_64)
			nm64(ctx);
		else
			enomagic(ctx);
		ret_mem(ctx);
	}
}

int		main(int argc, const char *argv[])
{
	int			i;
	t_context	ctx;

	i = 0;
	ctx.nm = argv[0];
	if (argc == 1)
	{
		ctx.name = "a.out";
		nm(&ctx);
	}
	else
		while (++i < argc)
		{
			ctx.name = argv[i];
			if (!ft_strcmp(ctx.name, "--"))
				ctx.name = "a.out";
			nm(&ctx);
		}
	return (0);
}
