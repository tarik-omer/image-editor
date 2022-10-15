// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#ifndef IMG_H
#define IMG_H

#define LEN 3

typedef struct {
	char type[LEN];
	int width, height, max_val, is_loaded;
	double **GS, **R, **G, **B;
	int format, col, x1, x2, y1, y2;
} img;

#endif
