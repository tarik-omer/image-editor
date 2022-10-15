// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#ifndef ROTATE_IMAGE_H
#define ROTATE_IMAGE_H

#include "definition.h"

void rotate_anticlk(double **mat, double **mat2, int h, int w);
void rotate_clk(double **mat, double **mat2, int h, int w);
void flip_img(double **mat, double **mat2, int h, int w);
int is_whole_image(img pic);
int is_square(img pic);
void do_a_barrel_roll(img *pic_address);
int check_angle(int angle);
void rotate_sel_gs(img *pic_address, int s_w, int s_h, double **rot,
				   int turns, int sgn);
void rotate_sel_rgb(img *pic_address, int s_w, int s_h, double **rt1,
					double **rt2, double **rt3, int turns,
					int sgn);
void rotate_all(img *pic_address, int turns, int sgn, int true_angle);

#endif
