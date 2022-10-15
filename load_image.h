// Copyright 2021-2022 Omer Tarik Ilhan 314CA
#ifndef LOAD_IMAGE_H
#define LOAD_IMAGE_H

#include "definition.h"

void read_binary(img * pic_address, FILE * fin);
void read_text(img *pic_address, FILE *fin);
void read_binary_RGB(img *pic_address, FILE *fin);
void read_text_RGB(img *pic_address, FILE *fin);
void clear_previous_image(img *pic_address);
void lock_and_load(char path[1000], img *pic_address);

#endif
