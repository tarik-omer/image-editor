// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "definition.h"

// save the image type, size and max value
// which are always in text format
void save_details(img pic, FILE *saved)
{
	fprintf(saved, "%d %d\n%d\n", pic.width, pic.height, pic.max_val);
}

// save a grayscale image to binary
void save_binary(img pic, char save_as[1000])
{
	FILE *saved = fopen(save_as, "wb");
	if (!saved) {
		printf("Cannot open file\n");
	} else {
		fprintf(saved, "P5\n");
		save_details(pic, saved);

		for (int i = 0; i < pic.height; i++)
			for (int j = 0; j < pic.width; j++) {
				// auxiliary variable for a more comprehensible type cast
				unsigned char TGS = (unsigned char)pic.GS[i][j];
				fwrite(&TGS, sizeof(unsigned char), 1, saved);
			}

		fclose(saved);
		printf("Saved %s\n", save_as);
	}
}

// save a grayscale image in plain text
void save_text(img pic, char save_as[1000])
{
	FILE *saved = fopen(save_as, "w");

	if (!saved) {
		printf("Cannot open file\n");
	} else {
		fprintf(saved, "P2\n");
		save_details(pic, saved);

		for (int i = 0; i < pic.height; i++) {
			for (int j = 0; j < pic.width; j++) {
				// auxiliary variable for a more comprehensible type cast
				unsigned char TGS = (unsigned char)pic.GS[i][j];
				fprintf(saved, "%hhu ", TGS);
			}
			fprintf(saved, "\n");
		}
		fclose(saved);
		printf("Saved %s\n", save_as);
	}
}

// save an RGB image in binary
void save_binary_RGB(img pic, char save_as[1000])
{
	FILE *saved = fopen(save_as, "wb");

	if (!saved) {
		printf("Cannot open file\n");
	} else {
		fprintf(saved, "P6\n");
		save_details(pic, saved);

		for (int i = 0; i < pic.height; i++) {
			for (int j = 0; j < pic.width; j++) {
				// auxiliary variables for a more comprehensible type cast
				// but also to round the value to an integer
				unsigned char TR = (unsigned char)round(pic.R[i][j]);
				unsigned char TG = (unsigned char)round(pic.G[i][j]);
				unsigned char TB = (unsigned char)round(pic.B[i][j]);
				fwrite(&TR, sizeof(unsigned char), 1, saved);
				fwrite(&TG, sizeof(unsigned char), 1, saved);
				fwrite(&TB, sizeof(unsigned char), 1, saved);
			}
		}
		fclose(saved);
		printf("Saved %s\n", save_as);
	}
}

// save an RGB image in plain text
void save_text_RGB(img pic, char save_as[1000])
{
	FILE *saved = fopen(save_as, "w");

	if (!saved) {
		printf("Cannot open file\n");
	} else {
		fprintf(saved, "P3\n");
		save_details(pic, saved);

		for (int i = 0; i < pic.height; i++) {
			for (int j = 0; j < pic.width; j++) {
				// auxiliary variables for a more comprehensible type cast
				// but also to round the value to an integer
				unsigned char TR = (unsigned char)round(pic.R[i][j]);
				unsigned char TG = (unsigned char)round(pic.G[i][j]);
				unsigned char TB = (unsigned char)round(pic.B[i][j]);
				fprintf(saved, "%hhu ", TR);
				fprintf(saved, "%hhu ", TG);
				fprintf(saved, "%hhu ", TB);
			}
			fprintf(saved, "\n");
		}
		fclose(saved);
		printf("Saved %s\n", save_as);
	}
}

// main save function
void save_the_world(img *pic_address)
{
	char param[1006], save_as[1000];
	int is_ascii = 0;
	fgets(param, 1000, stdin);
	img pic = *pic_address;

	// check whether the image needs to be saved in ascii or binary
	if (strstr(param, "ascii"))
		is_ascii = 1;

	// get the saving path
	strcpy(save_as, strtok(param, " "));

	// // removing the '\n' at the end of the save_as string
	int ln = strlen(save_as);
	if (is_ascii == 0 && save_as[ln - 1] != 'm')
		save_as[ln - 1] = '\0';

	if (pic.is_loaded == 0) {
		printf("No image loaded\n");
	} else if (pic.col == 1) {
		// grayscale
		if (is_ascii == 1) {
			// save the image in text
			save_text(pic, save_as);
		} else {
			// save the image in binary
			save_binary(pic, save_as);
		}
	} else if (pic.col == 2) {
		// RGB
		if (is_ascii == 1) {
			// save the image in text
			save_text_RGB(pic, save_as);
		} else {
			// save the image in binary
			save_binary_RGB(pic, save_as);
		}
	}
}
