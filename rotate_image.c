// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#include <stdio.h>

#include "utils.h"

// rotates anti-cloclwise a matrix (90 degrees)
void rotate_anticlk(double **mat, double **mat2, int h, int w)
{
	for (int i = h - 1; i >= 0; i--)
		for (int j = 0; j < w; j++)
			mat[h - i - 1][j] = mat2[j][i];
}

// rotates clockwise a matrix (90 degrees)
void rotate_clk(double **mat, double **mat2, int h, int w)
{
	for (int i = 0; i < h; i++)
		for (int j = w - 1; j >= 0; j--)
			mat[i][w - j - 1] = mat2[j][i];
}

// rotates 180 degrees the whole image
void flip_img(double **mat, double **mat2, int h, int w)
{
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			mat[i][j] = mat2[h - i - 1][w - j - 1];
}

// check if the selection is the whole image
int is_whole_image(img pic)
{
	if (pic.x1 != 0 || pic.x2 != pic.width)
		return 0;
	else if (pic.y1 != 0 || pic.y2 != pic.height)
		return 0;
	else
		return 1;
}

// check if the selection is square
int is_square(img pic)
{
	int s_w = pic.x2 - pic.x1;
	int s_h = pic.y2 - pic.y1;

	if (s_w == s_h)
		return 1;
	else
		return -1;
}

// check whether the angle is supported
// and return the number of 90 degree turns equivalent to the angle
int check_angle(int angle)
{
	int turns = 0;
	if (angle % 90 == 0) {
		turns = angle / 90;
		turns = turns % 4;
		return turns;
	} else {
		return -1;
	}
}

// rotate selection for grayscale
void rotate_sel_gs(img *pic_address, int s_w, int s_h, double **rot,
				   int turns, int sgn)
{
	img pic = *pic_address;
	if (turns == 2) {
		// // flip the selection
		// clockwise 90 degrees rotation
		for (int i = 0; i < s_h; i++)
			for (int j = s_w - 1; j >= 0; j--)
				rot[i][s_w - j - 1] = pic.GS[j + pic.y1][i + pic.x1];

		// replacing the rotated selection in the main image
		for (int i = pic.y1; i < pic.y2; i++)
			for (int j = pic.x1; j < pic.x2; j++)
				pic.GS[i][j] = rot[i - pic.y1][j - pic.x1];

		// clockwise 90 degrees rotation
		for (int i = 0; i < s_h; i++)
			for (int j = s_w - 1; j >= 0; j--)
				rot[i][s_w - j - 1] = pic.GS[j + pic.y1][i + pic.x1];

	} else if (turns == 0) {
		// selection remains unchanged
		for (int i = 0; i < s_h; i++)
			for (int j = 0; j < s_w; j++)
				rot[i][j] = pic.GS[i + pic.y1][j + pic.x1];

	} else if ((sgn == 1 && turns == 1) || (sgn == -1 && turns == 3)) {
		// clockwise 90 degrees rotation
		for (int i = 0; i < s_h; i++)
			for (int j = s_w - 1; j >= 0; j--)
				rot[i][s_w - j - 1] = pic.GS[j + pic.y1][i + pic.x1];

	} else if ((sgn == -1 && turns == 1) || (sgn == 1 && turns == 3)) {
		// counter-clockwise 90 degrees rotation
		for (int i = s_h - 1; i >= 0; i--)
			for (int j = 0; j < s_w; j++)
				rot[s_w - i - 1][j] = pic.GS[j + pic.y1][i + pic.x1];
	}

	// replacing the rotated selection in the main image
	for (int i = pic.y1; i < pic.y2; i++)
		for (int j = pic.x1; j < pic.x2; j++)
			pic.GS[i][j] = rot[i - pic.y1][j - pic.x1];
	*pic_address = pic;
}

// rotate selection for RGB
void rotate_sel_rgb(img *pic_address, int s_w, int s_h, double **rt1,
					double **rt2, double **rt3, int turns,
					int sgn)
{
	img pic = *pic_address;
	if (turns == 2) {
		// flip the selection
		// clockwise 90 degrees rotation
		for (int i = 0; i < s_h; i++)
			for (int j = s_w - 1; j >= 0; j--) {
				rt1[i][s_w - j - 1] = pic.R[j + pic.y1][i + pic.x1];
				rt2[i][s_w - j - 1] = pic.G[j + pic.y1][i + pic.x1];
				rt3[i][s_w - j - 1] = pic.B[j + pic.y1][i + pic.x1];
			}

		// replacing the rotated selection in the main image
		for (int i = pic.y1; i < pic.y2; i++)
			for (int j = pic.x1; j < pic.x2; j++) {
				pic.R[i][j] = rt1[i - pic.y1][j - pic.x1];
				pic.G[i][j] = rt2[i - pic.y1][j - pic.x1];
				pic.B[i][j] = rt3[i - pic.y1][j - pic.x1];
			}

		// clockwise 90 degrees rotation
		for (int i = 0; i < s_h; i++)
			for (int j = s_w - 1; j >= 0; j--) {
				rt1[i][s_w - j - 1] = pic.R[j + pic.y1][i + pic.x1];
				rt2[i][s_w - j - 1] = pic.G[j + pic.y1][i + pic.x1];
				rt3[i][s_w - j - 1] = pic.B[j + pic.y1][i + pic.x1];
			}

	} else if (turns == 0) {
		// selection remains unchanged
		for (int i = 0; i < s_h; i++)
			for (int j = 0; j < s_w; j++) {
				rt1[i][j] = pic.R[i + pic.y1][j + pic.x1];
				rt2[i][j] = pic.G[i + pic.y1][j + pic.x1];
				rt3[i][j] = pic.B[i + pic.y1][j + pic.x1];
			}

	} else if ((sgn == 1 && turns == 1) || (sgn == -1 && turns == 3)) {
		// clockwise 90 degrees rotation
		for (int i = 0; i < s_h; i++)
			for (int j = s_w - 1; j >= 0; j--) {
				rt1[i][s_w - j - 1] = pic.R[j + pic.y1][i + pic.x1];
				rt2[i][s_w - j - 1] = pic.G[j + pic.y1][i + pic.x1];
				rt3[i][s_w - j - 1] = pic.B[j + pic.y1][i + pic.x1];
			}

	} else if ((sgn == -1 && turns == 1) || (sgn == 1 && turns == 3)) {
		// counter-clockwise 90 degrees rotation
		for (int i = s_h - 1; i >= 0; i--)
			for (int j = 0; j < s_w; j++) {
				rt1[s_w - i - 1][j] = pic.R[j + pic.y1][i + pic.x1];
				rt2[s_w - i - 1][j] = pic.G[j + pic.y1][i + pic.x1];
				rt3[s_w - i - 1][j] = pic.B[j + pic.y1][i + pic.x1];
				}
	}

	// replacing the rotated selection in the main image
	for (int i = pic.y1; i < pic.y2; i++)
		for (int j = pic.x1; j < pic.x2; j++) {
			pic.R[i][j] = rt1[i - pic.y1][j - pic.x1];
			pic.G[i][j] = rt2[i - pic.y1][j - pic.x1];
			pic.B[i][j] = rt3[i - pic.y1][j - pic.x1];
		}
	*pic_address = pic;
}

// rotate the whole image (for both image types)
void rotate_all(img *pic_address, int turns, int sgn, int true_angle)
{
	img pic = *pic_address;
	if (pic.col == 1) {
		// grayscale
		if (turns == 2) {
			// flip image
			double **rot = alloc_matrix(pic.height, pic.width);
			flip_img(rot, pic.GS, pic.height, pic.width);
			// replace old image data
			free_GS(pic_address); pic.GS = rot;
		} else if (turns == 0) {
			// image remains unchanged
		} else if ((sgn == 1 && turns == 1) || (sgn == -1 && turns == 3)) {
			// clockwise 90 degrees rotation
			double **rot = alloc_matrix(pic.width, pic.height);
			rotate_clk(rot, pic.GS, pic.width, pic.height);
			// replace old image data
			free_GS(pic_address);
			int aux = pic.width; pic.width = pic.height; pic.height = aux;
			pic.GS = rot;
		} else if ((sgn == -1 && turns == 1) || (sgn == 1 && turns == 3)) {
			// counter-clockwise 90 degrees rotation
			double **rot = alloc_matrix(pic.width, pic.height);
			rotate_anticlk(rot, pic.GS, pic.width, pic.height);
			// replace old image data
			free_GS(pic_address); pic.GS = rot;
			int aux = pic.width; pic.width = pic.height; pic.height = aux;
		}
		printf("Rotated %d\n", true_angle);
		} else if (pic.col == 2) {
			// RGB
			if (turns == 2) {
				// flip image
				double **rt1 = alloc_matrix(pic.height, pic.width);
				double **rt2 = alloc_matrix(pic.height, pic.width);
				double **rt3 = alloc_matrix(pic.height, pic.width);
				flip_img(rt1, pic.R, pic.height, pic.width);
				flip_img(rt2, pic.G, pic.height, pic.width);
				flip_img(rt3, pic.B, pic.height, pic.width);
				// replace old image data
				free_RGB(pic_address);
				pic.R = rt1; pic.G = rt2; pic.B = rt3;
			} else if (turns == 0) {
				// image remains unchanged
			} else if ((sgn == 1 && turns == 1) ||
				(sgn == -1 && turns == 3)) {
				// clockwise 90 degrees rotation
				double **rt1 = alloc_matrix(pic.width, pic.height);
				double **rt2 = alloc_matrix(pic.width, pic.height);
				double **rt3 = alloc_matrix(pic.width, pic.height);
				rotate_clk(rt1, pic.R, pic.width, pic.height);
				rotate_clk(rt2, pic.G, pic.width, pic.height);
				rotate_clk(rt3, pic.B, pic.width, pic.height);
				// replace old image data
				free_RGB(pic_address);
				int aux = pic.width; pic.width = pic.height; pic.height = aux;
				pic.R = rt1; pic.G = rt2; pic.B = rt3;
			} else if ((sgn == -1 && turns == 1) ||
				(sgn == 1 && turns == 3)) {
				// counter-clockwise 90 degrees rotation
				double **rt1 = alloc_matrix(pic.width, pic.height);
				double **rt2 = alloc_matrix(pic.width, pic.height);
				double **rt3 = alloc_matrix(pic.width, pic.height);
				rotate_anticlk(rt1, pic.R, pic.width, pic.height);
				rotate_anticlk(rt2, pic.G, pic.width, pic.height);
				rotate_anticlk(rt3, pic.B, pic.width, pic.height);
				// replace old image data
				free_RGB(pic_address);
				int aux = pic.width; pic.width = pic.height; pic.height = aux;
				pic.R = rt1; pic.G = rt2; pic.B = rt3;
			}
			printf("Rotated %d\n", true_angle);
		}
	pic.x1 = 0; pic.x2 = pic.width; pic.y1 = 0; pic.y2 = pic.height;
	*pic_address = pic;
}

// main rotate function
void do_a_barrel_roll(img *pic_address)
{
	img pic = *pic_address;
	int true_angle, angle;
	scanf("%d", &true_angle);
	// get the rotation direction (clockwise or counter-clockwise)
	int sgn;
	if (true_angle >= 0) {
		angle = true_angle;
		sgn = 1;
	} else {
		sgn = -1;
		angle = -true_angle;
	}
	// number of 90 degrees turns
	int turns = check_angle(angle);

	if (pic.is_loaded == 0) {
		printf("No image loaded\n");
	} else if (is_whole_image(pic) == 1 && check_angle(angle) != -1) {
		// case ROTATE ALL
		rotate_all(&pic, turns, sgn, true_angle);
	} else if (is_square(pic) == 1 && check_angle(angle) != -1) {
		// case ROTATE SELECTION
		// get the selection size
		int s_w = pic.x2 - pic.x1;
		int s_h = pic.y2 - pic.y1;
		if (pic.col == 1) {
			// grayscale
			double **rot = alloc_matrix(s_h, s_w);
			rotate_sel_gs(pic_address, s_w, s_h, rot, turns, sgn);
			free_matrix(&rot, s_h);
		} else if (pic.col == 2) {
			// RGB
			double **rt1 = alloc_matrix(s_h, s_w);
			double **rt2 = alloc_matrix(s_h, s_w);
			double **rt3 = alloc_matrix(s_h, s_w);
			rotate_sel_rgb(pic_address, s_w, s_h, rt1, rt2, rt3, turns, sgn);
			free_matrix(&rt1, s_h);
			free_matrix(&rt2, s_h);
			free_matrix(&rt3, s_h);
		}
		printf("Rotated %d\n", true_angle);
	} else if (is_square(pic) == 1 && check_angle(angle) != -1) {
		printf("The selection must be square\n");
	} else if (check_angle(true_angle) == -1) {
		printf("Unsupported rotation angle\n");
	}
	*pic_address = pic;
}
