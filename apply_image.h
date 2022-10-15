// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#ifndef APPLY_IMAGE_H
#define APPLY_IMAGE_H

#include "definition.h"

double clamp(double num);
double apply_kernel(int kernel[3][3], int p_x, int p_y,
					int sums[3], double **mat);
// void apply_kernel_d(img *pic_add, int **kernel, int p_x, int p_y, int div,
					// int sums[3]);
void create_edge_kernel(int kernel[3][3]);
void create_sharpen_kernel(int kernel[3][3]);
void create_blur_kernel(int kernel[3][3]);
void create_gaussian_kernel(int kernel[3][3]);
void apply_it(img *pic_address, char parameter[100]);
void reduce_sel(int *tx1, int *tx2, int *ty1, int *ty2, img pic);
void apply_kernel_on_matrix(double **sel_R, double **sel_G,
							double **sel_B, int tx1, int tx2, int ty1,
							int ty2, img *pic_address, int **kernel);
void apply_filter(img *pic_address, int tx1, int tx2, int ty1, int ty2,
				  double **sel_R, double **sel_G,
				  double **sel_B);
void apply_kernel_on_matrix_div(double **sel_R, double **sel_G,
								double **sel_B, int tx1, int tx2,
								int ty1, int ty2, img *pic_address,
								int kernel[3][3], double div);
void box_blur(img *pic_address, int tx1, int tx2, int ty1, int ty2);
void gaussian_blur(img *pic_address, int tx1, int tx2, int ty1, int ty2);
void edge_detection(img *pic_address, int tx1, int tx2, int ty1, int ty2);
void sharpen(img *pic_address, int tx1, int tx2, int ty1, int ty2);

#endif
