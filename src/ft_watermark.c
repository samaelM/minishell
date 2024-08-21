/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_watermark.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:34:00 by maemaldo          #+#    #+#             */
/*   Updated: 2024/07/02 19:24:28 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_bird(void)
{
	ft_printf("\t\t\t\t\t\t              ＿＿   \n");
	ft_printf("\t\t\t\t\t\t　　　 ＿＿／　　 ヽ \n");
	ft_printf("\t\t\t\t\t\t　　 ／　 ／　／⌒ヽ| \n");
	ft_printf("\t\t\t\t\t\t　　/ (ﾟ)/　／ /    \n");
	ft_printf("\t\t\t\t\t\t　 /　　 ﾄ､/｡⌒ヽ。   \n");
	ft_printf("\t\t\t\t\t\t　彳　　 ＼＼ﾟ｡∴｡ｏ   \n");
	ft_printf("\t\t\t\t\t\t`／　　　　＼＼｡ﾟ｡ｏ   \n");
	ft_printf("\t\t\t\t\t\t/　　　　 /⌒＼Ｕ∴)   \n");
	ft_printf("\t\t\t\t\t\t　　　　 ｜　　ﾞＵ｜  \n");
	ft_printf("\t\t\t\t\t\t　　　　 ｜　　　||  \n");
	ft_printf("\t\t\t\t\t\t　　　　　　　　 Ｕ   \n");
}

static void	ft_text(void)
{
	ft_printf("      .o.       ooooo      ooo       .o.        .oooooo..o ");
	ft_printf("ooooo   ooooo oooooooooooo ooooo        ooooo        \n");
	ft_printf("     .888.      `888b.     `8'      .888.      d8P'    `Y8 ");
	ft_printf("`888'   `888' `888'     `8 `888'        `888'        \n");
	ft_printf("    .8\"888.      8 `88b.    8      .8\"888.     Y88bo.    ");
	ft_printf("   888     888   888          888          888         \n");
	ft_printf("   .8' `888.     8   `88b.  8     .8' `888.     `\"Y8888o. ");
	ft_printf("  888ooooo888   888oooo8     888          888         \n");
	ft_printf("  .88ooo8888.    8     `88b.8    .88ooo8888.        `\"Y88b");
	ft_printf("  888     888   888    \"     888          888         \n");
	ft_printf(" .8'     `888.   8       `888   .8'     `888.  oo     .d8P ");
	ft_printf(" 888     888   888       o  888       o  888       o \n");
	ft_printf("o88o     o8888o o8o        `8  o88o     o8888o 8\"\"88888P'");
	ft_printf("  o888o   o888o o888ooooood8 o888ooooood8 o888ooooood8 \n");
}

void	ft_watermark(void)
{
	ft_printf("\n\n\n");
	ft_bird();
	ft_text();
	ft_printf("\n\n\t\t\tby Mael Maldonado (maemaldo)");
	ft_printf(" and Anaelle Henault (ahenault)\n\n");
}
