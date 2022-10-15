// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#include <stdio.h>

#include "utils.h"
#include "definition.h"

void exit_all(img *pic_address)
{
	img pic = *pic_address;
	// check what type of image is loaded and free corresponding memory
	if (pic.is_loaded == 1) {
		if (pic.col == 1)
			free_GS(pic_address);
		else if (pic.col == 2)
			free_RGB(pic_address);
	} else {
		printf("No image loaded\n");
	}
}
