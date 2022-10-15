// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#include <stdio.h>

#include "utils.h"

void crop_crop_crop(img *pic_address)
{
	img pic = *pic_address;

	// cropped width and height
	int new_width = pic.x2 - pic.x1;
	int new_height = pic.y2 - pic.y1;
	// check if the image is loaded
	if (pic.is_loaded == 0) {
		printf("No image loaded\n");
	} else if (pic.col == 1) {
	// check image color format
		// grayscale
		double **cropped_image = alloc_matrix(new_height, new_width);
		// copy the selection into a new image matrix
		for (int i = pic.y1; i < pic.y2; i++)
			for (int j = pic.x1; j < pic.x2; j++)
				cropped_image[i - pic.y1][j - pic.x1] = pic.GS[i][j];
		// switch old image with the new one
		free_GS(pic_address);
		pic.GS = cropped_image;
		// save image details
		pic.height = new_height;
		pic.width = new_width;
		pic.x1 = 0;
		pic.x2 = new_width;
		pic.y1 = 0;
		pic.y2 = new_height;
		*pic_address = pic;
		printf("Image cropped\n");
	} else if (pic.col == 2) {
		// RGB
		double **cropped_R = alloc_matrix(new_height, new_width);
		double **cropped_G = alloc_matrix(new_height, new_width);
		double **cropped_B = alloc_matrix(new_height, new_width);
		// copy the selection into a new image matrix
		for (int i = pic.y1; i < pic.y2; i++)
			for (int j = pic.x1; j < pic.x2; j++) {
				cropped_R[i - pic.y1][j - pic.x1] = pic.R[i][j];
				cropped_G[i - pic.y1][j - pic.x1] = pic.G[i][j];
				cropped_B[i - pic.y1][j - pic.x1] = pic.B[i][j];
			}
		// switch the old image with the new one
		free_RGB(pic_address);
		pic.R = cropped_R;
		pic.G = cropped_G;
		pic.B = cropped_B;
		// save image details
		pic.height = new_height;
		pic.width = new_width;
		pic.x1 = 0;
		pic.x2 = new_width;
		pic.y1 = 0;
		pic.y2 = new_height;
		*pic_address = pic;
		printf("Image cropped\n");
	}
}
