// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#include <stdio.h>
#include <string.h>

#include "definition.h"
#include "utils.h"

double clamp(double num)
{
	if (num > 255)
		num = 255;
	else if (num < 0)
		num = 0;
	return num;
}

// function to apply kernel on a single pixel
double apply_kernel(int kernel[3][3], int p_x, int p_y, double **mat)
{
	double sum = 0;
	// multiply values from the kernel with the coresponding pixels
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			sum += mat[p_y + i - 1][p_x + j - 1] * kernel[i][j];

	return sum;
}

void create_edge_kernel(int kernel[3][3])
{
	kernel[0][0] = -1;
	kernel[0][1] = -1;
	kernel[0][2] = -1;
	kernel[1][0] = -1;
	kernel[1][1] = 8;
	kernel[1][2] = -1;
	kernel[2][0] = -1;
	kernel[2][1] = -1;
	kernel[2][2] = -1;
}

void create_sharpen_kernel(int kernel[3][3])
{
	kernel[0][0] = 0;
	kernel[0][1] = -1;
	kernel[0][2] = 0;
	kernel[1][0] = -1;
	kernel[1][1] = 5;
	kernel[1][2] = -1;
	kernel[2][0] = 0;
	kernel[2][1] = -1;
	kernel[2][2] = 0;
}

void create_blur_kernel(int kernel[3][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			kernel[i][j] = 1;
}

void create_gaussian_kernel(int kernel[3][3])
{
	kernel[0][0] = 1;
	kernel[0][1] = 2;
	kernel[0][2] = 1;
	kernel[1][0] = 2;
	kernel[1][1] = 4;
	kernel[1][2] = 2;
	kernel[2][0] = 1;
	kernel[2][1] = 2;
	kernel[2][2] = 1;
}

// function to reduce selection to modifiable pixels
void reduce_sel(int *tx1, int *tx2, int *ty1, int *ty2, img pic)
{
	if (pic.x1 == 0)
		*tx1 = 1;
	else
		*tx1 = pic.x1;

	if (pic.x2 == pic.width)
		*tx2 = pic.width - 1;
	else
		*tx2 = pic.x2;

	if (pic.y1 == 0)
		*ty1 = 1;
	else
		*ty1 = pic.y1;

	if (pic.y2 == pic.height)
		*ty2 = pic.height - 1;
	else
		*ty2 = pic.y2;
}

// function to apply the kernel on a matrix
void apply_kernel_on_matrix(double **sel_R, double **sel_G,
							double **sel_B, int tx1, int tx2, int ty1,
							int ty2, img *pic_address, int kernel[3][3])
{
	img pic = *pic_address;
	for (int i = ty1; i < ty2; i++)
		for (int j = tx1; j < tx2; j++) {
			sel_R[i - ty1][j - tx1] =
				clamp(apply_kernel(kernel, j, i, pic.R));
			sel_G[i - ty1][j - tx1] =
				clamp(apply_kernel(kernel, j, i, pic.G));
			sel_B[i - ty1][j - tx1] =
				clamp(apply_kernel(kernel, j, i, pic.B));
		}
	*pic_address = pic;
}

// function to apply selection on the main matrix
// copy values from one matrix to another
void apply_filter(img *pic_address, int tx1, int tx2, int ty1, int ty2,
				  double **sel_R, double **sel_G,
				  double **sel_B)
{
	img pic = *pic_address;
	for (int i = ty1; i < ty2; i++)
		for (int j = tx1; j < tx2; j++) {
			pic.R[i][j] = sel_R[i - ty1][j - tx1];
			pic.G[i][j] = sel_G[i - ty1][j - tx1];
			pic.B[i][j] = sel_B[i - ty1][j - tx1];
		}
	*pic_address = pic;
}

// function to shift a string one char to the left
void shift_left(char parameter[100])
{
	parameter[strlen(parameter) - 1] = '\0';
	for (unsigned int i = 0; i < strlen(parameter); i++)
		parameter[i] = parameter[i + 1];
}

// apply kernel on a matrix, but dividing the resulting value by div
void apply_kernel_on_matrix_div(double **sel_R, double **sel_G,
								double **sel_B, int tx1, int tx2,
								int ty1, int ty2, img *pic_address,
								int kernel[3][3], double div)
{
	img pic = *pic_address;
	for (int i = ty1; i < ty2; i++)
		for (int j = tx1; j < tx2; j++) {
			double r = (double)apply_kernel(kernel, j, i, pic.R) / div;
			double g = (double)apply_kernel(kernel, j, i, pic.G) / div;
			double b = (double)apply_kernel(kernel, j, i, pic.B) / div;
			sel_R[i - ty1][j - tx1] = (double)clamp(r);
			sel_G[i - ty1][j - tx1] = (double)clamp(g);
			sel_B[i - ty1][j - tx1] = (double)clamp(b);
		}
	*pic_address = pic;
}

void box_blur(img *pic_address, int tx1, int tx2, int ty1, int ty2)
{
	img pic = *pic_address;
	// create kernel
	int kernel[3][3];
	create_blur_kernel(kernel);
	double **sel_R = alloc_matrix(ty2 - ty1, tx2 - tx1);
	double **sel_G = alloc_matrix(ty2 - ty1, tx2 - tx1);
	double **sel_B = alloc_matrix(ty2 - ty1, tx2 - tx1);

	// apply the kernel on each pixel on the selection
	apply_kernel_on_matrix_div(sel_R, sel_G, sel_B, tx1, tx2,
							   ty1, ty2, pic_address, kernel, 9.0);
	// apply filter to the main image
	apply_filter(pic_address, tx1, tx2, ty1, ty2, sel_R, sel_G, sel_B);

	// free occupied memory
	free_matrix(&sel_R, ty2 - ty1);
	free_matrix(&sel_G, ty2 - ty1);
	free_matrix(&sel_B, ty2 - ty1);

	*pic_address = pic;
}

void gaussian_blur(img *pic_address, int tx1, int tx2, int ty1, int ty2)
{
	img pic = *pic_address;
	// create kernel
	int kernel[3][3];
	create_gaussian_kernel(kernel);
	double **sel_R = alloc_matrix(ty2 - ty1, tx2 - tx1);
	double **sel_G = alloc_matrix(ty2 - ty1, tx2 - tx1);
	double **sel_B = alloc_matrix(ty2 - ty1, tx2 - tx1);

	// apply the kernel on each pixel on the selection
	apply_kernel_on_matrix_div(sel_R, sel_G, sel_B, tx1, tx2,
							   ty1, ty2, pic_address, kernel, 16.0);
	// apply filter to the main image
	apply_filter(pic_address, tx1, tx2, ty1, ty2, sel_R, sel_G, sel_B);

	// free occupied memory
	free_matrix(&sel_R, ty2 - ty1);
	free_matrix(&sel_G, ty2 - ty1);
	free_matrix(&sel_B, ty2 - ty1);

	*pic_address = pic;
}

void edge_detection(img *pic_address, int tx1, int tx2, int ty1, int ty2)
{
	img pic = *pic_address;
	// create kernel
	int kernel[3][3];
	create_edge_kernel(kernel);
	double **sel_R = alloc_matrix(ty2 - ty1, tx2 - tx1);
	double **sel_G = alloc_matrix(ty2 - ty1, tx2 - tx1);
	double **sel_B = alloc_matrix(ty2 - ty1, tx2 - tx1);

	// apply the kernel on each pixel on the selection
	apply_kernel_on_matrix(sel_R, sel_G, sel_B, tx1, tx2, ty1, ty2,
						   pic_address, kernel);
	// apply filter to the main image
	apply_filter(pic_address, tx1, tx2, ty1, ty2, sel_R, sel_G, sel_B);

	// free occupied memory
	free_matrix(&sel_R, ty2 - ty1);
	free_matrix(&sel_G, ty2 - ty1);
	free_matrix(&sel_B, ty2 - ty1);

	*pic_address = pic;
}

void sharpen(img *pic_address, int tx1, int tx2, int ty1, int ty2)
{
	img pic = *pic_address;
	// create kernel
	int kernel[3][3];
	create_sharpen_kernel(kernel);
	double **sel_R = alloc_matrix(ty2 - ty1, tx2 - tx1);
	double **sel_G = alloc_matrix(ty2 - ty1, tx2 - tx1);
	double **sel_B = alloc_matrix(ty2 - ty1, tx2 - tx1);

	// apply the kernel on each pixel on the selection
	apply_kernel_on_matrix(sel_R, sel_G, sel_B, tx1, tx2, ty1, ty2,
						   pic_address, kernel);
	// apply filter to the main image
	apply_filter(pic_address, tx1, tx2, ty1, ty2, sel_R, sel_G, sel_B);

	// free occupied memory
	free_matrix(&sel_R, ty2 - ty1);
	free_matrix(&sel_G, ty2 - ty1);
	free_matrix(&sel_B, ty2 - ty1);

	*pic_address = pic;
}

void apply_it(img *pic_address, char parameter[100])
{
	img pic = *pic_address;
	if (pic.is_loaded == 0) {
		printf("No image loaded\n");
	} else if (parameter[0] == '\n') {
		printf("Invalid command\n");
	} else {
		shift_left(parameter);
		// reduce selection on modifiable pixels
		int tx1, tx2, ty1, ty2;
		reduce_sel(&tx1, &tx2, &ty1, &ty2, pic);

		if (pic.col == 2 && !strcmp(parameter, "SHARPEN")) {
			// sharpen
			sharpen(pic_address, tx1, tx2, ty1, ty2);
			printf("APPLY %s done\n", parameter);

		} else if (pic.col == 2 && !strcmp(parameter, "EDGE")) {
			// edge detection
			edge_detection(pic_address, tx1, tx2, ty1, ty2);
			printf("APPLY %s done\n", parameter);

		} else if (pic.col == 2 && !strcmp(parameter, "BLUR")) {
			// box blur
			box_blur(pic_address, tx1, tx2, ty1, ty2);
			printf("APPLY %s done\n", parameter);

		} else if (pic.col == 2 && !strcmp(parameter, "GAUSSIAN_BLUR")) {
			// gaussian blur
			gaussian_blur(pic_address, tx1, tx2, ty1, ty2);
			printf("APPLY %s done\n", parameter);

		} else if (pic.col == 2) {
			printf("APPLY parameter invalid\n");
		} else if (pic.col == 1) {
			printf("Easy, Charlie Chaplin\n");
		} else {
			printf("Invalid command\n");
		}
	}
	*pic_address = pic;
}
