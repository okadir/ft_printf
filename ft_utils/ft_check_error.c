/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 22:44:27 by haitkadi          #+#    #+#             */
/*   Updated: 2021/12/12 22:44:29 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../ft_printf.h"

static int is_compatible(t_args args)
{
    if(args.flags.ziro && !ft_strchr("csp", args.type))
        return (1);
    if(args.is_precision && !ft_strchr("sdiuxX", args.type))
        return (1);
    if(args.flags.hash && !ft_strchr("xX", args.type))
        return (1);
    if(args.flags.space && !ft_strchr("sdi", args.type))
        return (1);
    if(args.flags.plus && !ft_strchr("di", args.type))
        return (1);
    return (0);
}
static int check_incompatible_flags(const char *frmt)
{
    t_args args;
    int i;

    ft_bzero(&args.flags, sizeof(args.flags));
    ft_bzero(&args, sizeof(args));
    i = 0;
    manage_flags(frmt, 0, &args);
    if(is_compatible(args))
        return (1);
    return (0);
}

int check_error(const char *frmt)
{
    int i;
    int j;
    int check_doubel_pre;
    const char    *copy;

    i = 0;
    j = 0;
    check_doubel_pre = 0;
    copy = NULL;
    while(frmt[i])
        
        if(frmt[i++] == '%')
        {
            copy = &frmt[i];

            while(ft_strchr(" -+#.0123456789", copy[j]))
                if(copy[j++] == '.')
                    check_doubel_pre++;
            if(!ft_strchr("cspdiuxX", copy[j]) || check_doubel_pre > 1)
                return (1);
        }
    if(check_incompatible_flags(copy))
        return (1);
    return (0);
}