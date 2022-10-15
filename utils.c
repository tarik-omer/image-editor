// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#include <stdio.h>
#include <stdlib.h>

#include "definition.h"

// free the grayscale image currently loaded
void free_GS(img *pic_address)
{
	img pic = *pic_address;
	for (int i = 0; i < pic.height; i++)
		free(pic.GS[i]);
	free(pic.GS);
}

// free the RGB image currently loaded
void free_RGB(img *pic_address)
{
	img pic = *pic_address;
	for (int i = 0; i < pic.height; i++) {
		free(pic.R[i]);
		free(pic.G[i]);
		free(pic.B[i]);
	}
	free(pic.R);
	free(pic.G);
	free(pic.B);
}

// function to return a pointer to a freshly allocated matrix
double **alloc_matrix(int m, int n)
{
	double **matrix = malloc(m * sizeof(double *));
	if (!matrix) {
		free(matrix);
		printf("Failed to malloc");
		return NULL;
	}
	for (int i = 0; i < m; i++) {
		matrix[i] = malloc(n * sizeof(double));
		if (!matrix[i]) {
			free(matrix[i]);
			printf("Failed to malloc");
			return NULL;
		}
	}
	return matrix;
}

// free memory allocated to a matrix
void free_matrix(double ***mat_ad, int h)
{
	double **mat = *mat_ad;
	for (int i = 0; i < h; i++)
		free(mat[i]);
	free(mat);
}
