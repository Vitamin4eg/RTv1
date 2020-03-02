/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:32:35 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/02 17:35:35 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		valid1(t_rtv *rtv)
{
	char *line;

	rtv->fd = open(rtv->name, O_RDONLY);
	if (rtv->fd < 0)
	{
		close(rtv->fd);
		return (-1);
	}
	if ((get_next_line(rtv->fd, &line) <= 0))
	{
		close(rtv->fd);
		return (-1);
	}
	else
	{
		ft_strdel(&line);
		close(rtv->fd);
		return (0);
	}
}

int		help_valid2(char k, t_rtv *rtv)
{
	if (((k >= 48) && (k <= 57)) || (k == ' ') || (k == '\n') ||
		(k == '-') || (k == '\t') || ((k >= 97) && (k <= 122)) ||
		(k == ')') || (k == '(') || (k == '{') || (k == '}') || (k == '_'))
	{
		rtv->i++;
		return (0);
	}
	else
		return (-1);
}

int		valid2(t_rtv *rtv)
{
	char *line;

	rtv->fd = open(rtv->name, O_RDONLY);
	while (get_next_line(rtv->fd, &line) > 0)
	{
		rtv->i = 0;
		while (line[rtv->i])
		{
			if (help_valid2(line[rtv->i], rtv) != 0)
			{
				ft_strdel(&line);
				return (-1);
			}
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(rtv->fd);
	return (0);
}

int		init_k(t_rtv *rtv)
{
	int i;

	i = 0;
	while (rtv->scene[i] != NULL)
		i++;
	return (i);
}

int		valid_objects(t_rtv *rtv)
{
	int		k;

	k = init_k(rtv);
	rtv->i = 0;
	while (rtv->i < k)
	{
		if ((ft_strcmp(rtv->scene[rtv->i], "camera\0") == 0 &&
			valid_camera(rtv, rtv->i, k) == 0) ||
			(ft_strcmp(rtv->scene[rtv->i], "light\0") == 0 &&
			valid_light(rtv, rtv->i, k) == 0))
			rtv->i = rtv->i + 6;
		else if ((ft_strcmp(rtv->scene[rtv->i], "plane\0") == 0 &&
			valid_plane(rtv, rtv->i, k) == 0) ||
			(ft_strcmp(rtv->scene[rtv->i], "sphere\0") == 0 &&
			valid_sphere(rtv, rtv->i, k) == 0))
			rtv->i = rtv->i + 8;
		else if ((ft_strcmp(rtv->scene[rtv->i], "cylinder\0") == 0 &&
			valid_cylinder(rtv, rtv->i, k) == 0) ||
			(ft_strcmp(rtv->scene[rtv->i], "cone\0") == 0 &&
			valid_cone(rtv, rtv->i, k) == 0))
			rtv->i = rtv->i + 9;
		else
			return (-1);
	}
	return (0);
}

char		*ft_strjoin_2(char *s1, char *s2)
{
	char	*snew;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	snew = (char *)malloc(sizeof(*snew) * (len + 1));
	if (!snew)
		return (NULL);
	ft_strcpy(snew, s1);
	ft_strcat(snew, s2);
	ft_strdel(&s1);
	return (snew);
}

void	render2(t_rtv *rtv)
{
	char	*line;
	char	*str;

	line = NULL;
	str = NULL;
	rtv->buf = ft_strnew(1);
	rtv->fd = open(rtv->name, O_RDONLY);
	while (get_next_line(rtv->fd, &line) > 0)
	{
		str = ft_strjoin(line, "\n");
		rtv->buf = ft_strjoin_2(rtv->buf, str);
		ft_strdel(&str);
		ft_strdel(&line);
	}
	rtv->scene = ft_strsplit(rtv->buf, '\n');
	ft_strdel(&line);
	ft_strdel(&str);
	ft_strdel(&rtv->buf);
}

void	init_array(t_rtv *rtv)
{
	rtv->nbr[CAM] = 0;
	rtv->nbr[LIGHT] = 0;
	rtv->nbr[SPHERE] = 0;
	rtv->nbr[PLANE] = 0;
	rtv->nbr[CYLINDER] = 0;
	rtv->nbr[CONE] = 0;
	rtv->index[CAM] = 0;
	rtv->index[LIGHT] = 0;
	rtv->index[SPHERE] = 0;
	rtv->index[PLANE] = 0;
	rtv->index[CYLINDER] = 0;
	rtv->index[CONE] = 0;
}

int		count_items(t_rtv *rtv)
{
	int i;

	i = 0;
	init_array(rtv);
	while (rtv->scene[i])
	{
		if (ft_strcmp(rtv->scene[i], "camera\0") == 0)
			rtv->nbr[CAM]++;
		else if (ft_strcmp(rtv->scene[i], "light\0") == 0)
			rtv->nbr[LIGHT]++;
		else if (ft_strcmp(rtv->scene[i], "sphere\0") == 0)
			rtv->nbr[SPHERE]++;
		else if (ft_strcmp(rtv->scene[i], "plane\0") == 0)
			rtv->nbr[PLANE]++;
		else if (ft_strcmp(rtv->scene[i], "cylinder\0") == 0)
			rtv->nbr[CYLINDER]++;
		else if (ft_strcmp(rtv->scene[i], "cone\0") == 0)
			rtv->nbr[CONE]++;
		i++;
	}
	if ((rtv->nbr[CAM] != 1) || (rtv->nbr[LIGHT] == 0))
		return (-1);
	return (0);
}

void	malloc_structures(t_rtv *rtv)
{
	if (!(rtv->cam = (t_cam*)malloc(rtv->nbr[CAM] * sizeof(t_cam))) ||
	!(rtv->light = (t_light*)malloc(rtv->nbr[LIGHT] * sizeof(t_light))) ||
	!(rtv->sphere = (t_sphere*)malloc(rtv->nbr[SPHERE] * sizeof(t_sphere))) ||
	!(rtv->plane = (t_plane*)malloc(rtv->nbr[PLANE] * sizeof(t_plane))) ||
	!(rtv->cylinder = (t_cylinder*)malloc(rtv->nbr[CYLINDER] *
		sizeof(t_cylinder)))
	|| !(rtv->cone = (t_cone*)malloc(rtv->nbr[CONE] * sizeof(t_cone))))
	{
		free(rtv);
		ft_error(MEM_ALLOC_ERR);
	}
}

void		valid(t_rtv *rtv)
{
	if ((valid1(rtv) != 0))
	{
		free(rtv);
		ft_error(OPEN_FILE_ERR);
	}
	else if ((valid2(rtv) != 0))
	{
		free(rtv);
		ft_error(INVALID_SYMBOLS);
	}
	render2(rtv);
	if (count_items(rtv) != 0)
	{
		free(rtv);
		ft_strdel(rtv->scene);
		ft_error(CAM_OR_LIGHT_ERR);
	}
	malloc_structures(rtv);
	if (valid_objects(rtv) != 0)
	{
		free(rtv);
		ft_error(INVALID_OBJ);
	}
}


static	int		close_app(t_rtv *rtv)
{
	free(rtv);
	exit(0);
}

void	ft_error(int code)
{
	if (code == TOO_MANY_PARAMS)
		ft_putstr("Too many parameters\n");
	else if (code == USE_SCENE)
		ft_putstr("Use scene from scenes folder\n");
	else if (code == RTV_ERR)
		ft_putstr("Can't allocate enough memory for the structure\n");
	else if (code == MEM_ALLOC_ERR)
		ft_putstr("Memory allocation error!\n");
	else if (code == OPEN_FILE_ERR)
		ft_putstr("Can't open specified file\n");
	else if (code == INVALID_SYMBOLS)
		ft_putstr("Invalid symbols were found in the file\n");
	else if (code == CAM_OR_LIGHT_ERR)
		ft_putstr("No light or not one camera in the file\n");
	else if (code == INVALID_OBJ)
		ft_putstr("Invalid scene or content description\n");
	else
		ft_putstr("Something went wrong\n");
	exit(0);
}

static	void	init(t_rtv *rtv)
{
	t_image *image;

	image = &rtv->image;
	rtv->mlx = mlx_init();
	rtv->window = mlx_new_window(rtv->mlx, WIDTH, HEIGHT, "RTv1");
	image->image = mlx_new_image(rtv->mlx, WIDTH, HEIGHT);
	image->ptr = mlx_get_data_addr(image->image, &image->bpp,
		&image->line_s, &image->endian);
	image->bpp /= 8;
}

void	img_pixel_put_one(t_rtv *rtv, int x, int y, t_color color)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		rtv->image.ptr[(WIDTH * y + x) * rtv->image.bpp + 2] =
		(char)fmin(color.r * 255.0f, 255.0f);
		rtv->image.ptr[(WIDTH * y + x) * rtv->image.bpp + 1] =
		(char)fmin(color.g * 255.0f, 255.0f);
		rtv->image.ptr[(WIDTH * y + x) * rtv->image.bpp] =
		(char)fmin(color.b * 255.0f, 255.0f);
	}
}

void	find_basis(t_cam *cam)
{
	t_vector3 tmp;

	if (cam->dir.x == 0 && fabs(cam->dir.y) == 1 && cam->dir.z == 0)
		tmp = new_vector3(0, 0, -cam->dir.y);
	else
		tmp = new_vector3(0, 1, 0);

	cam->i = cross_vector3(tmp, cam->dir);
	cam->i = normalize(cam->i);
	cam->j = cross_vector3(cam->dir, cam->i);
	cam->j = normalize(cam->j);
}

int		draw(t_rtv *rtv)
{
	int				x;
	int				y;
	t_color		color;

	x = 0;
	find_basis(rtv->cam);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			color = calculate_color((t_rtv*)rtv, x, y);
			img_pixel_put_one((t_rtv*)rtv, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(rtv->mlx, rtv->window, rtv->image.image, 0, 0);
	return (0);
}

int				main(int argc, char **argv)
{
	t_rtv *rtv;

	if (argc > 2)
		ft_error(TOO_MANY_PARAMS);
	else if (argc == 1)
		ft_error(USE_SCENE);
	if (!(rtv = (t_rtv *)malloc(sizeof(t_rtv))))
		ft_error(RTV_ERR);
	rtv->name = argv[1];
	valid(rtv);
	init(rtv);
	mlx_expose_hook(rtv->window, draw, rtv);
	mlx_hook(rtv->window, 3, 1L << 1, key_release, rtv);
	mlx_hook(rtv->window, 17, 1L << 17, close_app, rtv);
	mlx_loop(rtv->mlx);
	return (0);
}
