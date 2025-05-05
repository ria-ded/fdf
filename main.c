/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 07:59:45 by mdziadko          #+#    #+#             */
/*   Updated: 2025/05/04 15:52:41 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	main(int argc, char **argv)
{
	t_data	*fdf;
	
	if (argc == 2)
	{
		fdf = fdf_init(argv[1]);
		if (!fdf)
			return (perror("Fdf init failed"), 1);
		render(fdf);
		handle_events(fdf);
		free_fdf(fdf);
	}
	return (0);
}