/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:18:01 by frapp             #+#    #+#             */
/*   Updated: 2023/12/31 00:51:27 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void handle_key_presses(mlx_key_data_t keydata, void *arg) {
	t_window *window = (t_window *)arg;
	keys_t key = keydata.key;

	if (keydata.action != MLX_PRESS)
		return;
	switch (key) {
		case MLX_KEY_UP: window->elevation_angle += ROTATION_INCREMENT; break;
		case MLX_KEY_LEFT: window->rotation_angle -= ROTATION_INCREMENT; break;
		case MLX_KEY_RIGHT: window->rotation_angle += ROTATION_INCREMENT; break;
		case MLX_KEY_DOWN: window->elevation_angle -= ROTATION_INCREMENT; break;
		case MLX_KEY_KP_ADD: (window->input.zoom) *= ZOOM_IN_FACTOR; break;
		case MLX_KEY_KP_SUBTRACT: (window->input.zoom) *= ZOOM_OUT_FACTOR; break;
		case MLX_KEY_ESCAPE: clean_exit(arg); break;
		case MLX_KEY_W: window->input.trans_vec[0] += TRANSLATION_INCREMENT; break;
		case MLX_KEY_Q: window->input.trans_vec[0] -= TRANSLATION_INCREMENT; break;
		case MLX_KEY_A: window->input.trans_vec[1] += TRANSLATION_INCREMENT; break;
		case MLX_KEY_S: window->input.trans_vec[1] -= TRANSLATION_INCREMENT; break;
		case MLX_KEY_Z: window->input.trans_vec[2] += TRANSLATION_INCREMENT; break;
		case MLX_KEY_X: window->input.trans_vec[2] -= TRANSLATION_INCREMENT; break;
		default: return;
	}
	update_image(window);
}
