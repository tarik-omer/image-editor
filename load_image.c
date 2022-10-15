// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "definition.h"

// read a grayscale image in binary
void read_binary(img *pic_address, FILE *fin)
{
	img pic = *pic_address;

	// through testing, I found that when reading in binary
	// I get a random value of "10" between the max value and the pixel matrix
	unsigned char trash;
	fread(&trash, sizeof(unsigned char), 1, fin);

	unsigned char TGS;

	for (int i = 0; i < pic.height; i++)
		for (int j = 0; j < pic.width; j++) {
			fread(&TGS, sizeof(unsigned char), 1, fin);
			pic.GS[i][j] = (double)TGS;
		}
}

// read a grayscale image in plain text
void read_text(img *pic_address, FILE *fin)
{
	img pic = *pic_address;

	unsigned char TGS;

	for (int i = 0; i < pic.height; i++)
		for (int j = 0; j < pic.width; j++) {
			fscanf(fin, "%hhu", &TGS);
			pic.GS[i][j] = TGS;
		}
}

// read RGB pixel-map written in binary
void read_binary_RGB(img *pic_address, FILE *fin)
{
	img pic = *pic_address;

	// same issue, with the random "10"
	unsigned char trash;
	fread(&trash, sizeof(unsigned char), 1, fin);

	unsigned char TR, TG, TB;

	for (int i = 0; i < pic.height; i++)
		for (int j = 0; j < pic.width; j++) {
			fread(&TR, sizeof(unsigned char), 1, fin);
			fread(&TG, sizeof(unsigned char), 1, fin);
			fread(&TB, sizeof(unsigned char), 1, fin);
			pic.R[i][j] = (double)TR;
			pic.G[i][j] = (double)TG;
			pic.B[i][j] = (double)TB;
		}
}

// read RGB pixel-map written in plain text
void read_text_RGB(img *pic_address, FILE *fin)
{
	img pic = *pic_address;
	unsigned char TR, TG, TB;
	for (int i = 0; i < pic.height; i++)
		for (int j = 0; j < pic.width; j++) {
			fscanf(fin, "%hhu", &TR);
			fscanf(fin, "%hhu", &TG);
			fscanf(fin, "%hhu", &TB);
			pic.R[i][j] = (double)TR;
			pic.G[i][j] = (double)TG;
			pic.B[i][j] = (double)TB;
		}
}

// free memory allocated to a potential previous matrix
void clear_previous_image(img *pic_address)
{
	img pic = *pic_address;
	// check whether the image is loaded and what kind of image it is
		if (pic.is_loaded == 1) {
			if (pic.col == 1)
				free_GS(pic_address);
			else if (pic.col == 2)
				free_RGB(pic_address);
		}
	pic.is_loaded = 0;
	*pic_address = pic;
}

// main load function
void lock_and_load(char path[1000], img *pic_address)
{
	FILE *fin = fopen(path, "rb");
	img pic = *pic_address;
	// check whether the file exists
	if (!fin) {
		printf("Failed to load %s\n", path);
		if (pic.is_loaded == 1)
			clear_previous_image(pic_address);
		pic.is_loaded = 0;
	} else {
		clear_previous_image(pic_address);
		fscanf(fin, "%s", pic.type);
		fscanf(fin, "%d %d", &pic.width, &pic.height);
		fscanf(fin, "%d", &pic.max_val);

		// for easier usage of the image type, I will use pic.col
		// 1 - P2 / P5
		// 2 - P3 / P6

		// and for image format, I will use pic.format
		// 1 - P2 / P3
		// 2 - P5 / P6

		if (!strcmp(pic.type, "P2") || !strcmp(pic.type, "P5")) {
			// grayscale
			pic.col = 1;

			pic.GS = alloc_matrix(pic.height, pic.width);

			if (!strcmp(pic.type, "P2")) {
				// text
				pic.format = 1;
				read_text(&pic, fin);
			} else if (!strcmp(pic.type, "P5")) {
				// binary
				pic.format = 2;
				read_binary(&pic, fin);
			}

		} else if (!strcmp(pic.type, "P3") || !strcmp(pic.type, "P6")) {
			// RGB
			pic.col = 2;
			pic.R = alloc_matrix(pic.height, pic.width);
			pic.G = alloc_matrix(pic.height, pic.width);
			pic.B = alloc_matrix(pic.height, pic.width);

			if (!strcmp(pic.type, "P3")) {
				// text
				pic.format = 1;
				read_text_RGB(&pic, fin);
			} else if (!strcmp(pic.type, "P6")) {
				// binary
				pic.format = 2;
				read_binary_RGB(&pic, fin);
			}
		}
		// after loading, the selection coordinates
		// will always be the whole image
		pic.x1 = 0;
		pic.x2 = pic.width;
		pic.y1 = 0;
		pic.y2 = pic.height;

		pic.is_loaded = 1;
		*pic_address = pic;
		fclose(fin);
		printf("Loaded %s\n", path);
	}
}
