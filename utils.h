// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#ifndef UTILS_H
#define UTILS_H

#include "definition.h"

void free_GS(img * pic_address);
void free_RGB(img *pic_address);
double **alloc_matrix(int m, int n);
void free_matrix(double ***mat_ad, int h);

#endif
