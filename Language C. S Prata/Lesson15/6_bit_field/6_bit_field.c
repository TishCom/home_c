/*
 * 6_bit_field.c
 * 
 * Copyright 2026 Tisha <Tisha@DESKTOP-TSPB5RM>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <inttypes.h>
#include <ctype.h>
#include <stdio.h>

struct font
{
	unsigned int id 		: 8;
	unsigned int size 		: 7;
	unsigned int alignment 	: 2;
	unsigned int fat 		: 1;
	unsigned int italics 	: 1;
	unsigned int underline 	: 1;
};

char *alignment[3] = {"left", "center", "right"};

char *onOff[2] = {"OFF", "ON"};

char func(struct font a);
void changeSize(struct font *a);
void changeFont(struct font *a);
void changeAlignment(struct font *a);
char myGetchar(void);
void skipString(void);

int main(int argc, char **argv)
{
	struct font myFont = {.id = 1, .size = 12, .alignment = 0, .fat = 0, .italics = 0, .underline = 0};
	char ch = 0;
	
	while ((ch = func(myFont)) != 'g')
	{
		switch(ch)
		{
			case 'a':
				changeFont(&myFont);
				break;
			case 'b':
				changeSize(&myFont);
				break;
			case 'c':
				changeAlignment(&myFont);
				break;
			case 'd':
				myFont.fat = (myFont.fat + 1) % 2;
				break;
			case 'e':
				myFont.italics = (myFont.italics + 1) % 2;
				break;
			case 'f':
				myFont.underline = (myFont.underline + 1) % 2;
		};
	}
	
	printf("exit.\n");
	
	return 0;
}

char func(struct font a)
{
	printf(" ID  Size  Alignment  Fat  Italic  Underline\n");
	printf("%3d %4d %8s %7s %5s %8s\n", a.id, a.size, alignment[a.alignment], onOff[a.fat],  onOff[a.italics],  onOff[a.underline]);
	
	printf("a)change font b)change size c)change alignment\n");
	printf("d)bold        e)italic      f)underline\n");
	printf("g)exit\n");
	
	return myGetchar();
}

void changeSize(struct font *a)
{
	int b = 0;
	
	do
	{
		printf("Enter the font size (0-127): ");
		scanf("%d", &b);
		skipString();
	}while (b & ~0b01111111);
	
	a->size = (uint8_t)b;
}

void changeFont(struct font *a)
{
	int b = 0;
	
	do
	{
		printf("Enter the font id (0-255): ");
		scanf("%d", &b);
		skipString();
	}while (b & ~0b11111111);
	
	a->id = (uint8_t)b;
}

void changeAlignment(struct font *a)
{
	char ch = 0;
	
	printf("Select the alignment\n");
	
	do
	{
		printf("a)left b)center c)right\n");
		ch = myGetchar();
	}while (ch != 'a' && ch != 'b' && ch != 'c');
	
	a->alignment = (ch - 'a') % 3;
}

void skipString(void)
{
	while (getchar() != '\n')
		continue;
}

char myGetchar(void)
{
	char ch = 0;
	
	while (isspace(ch = getchar()))
		continue;
		
	skipString();
	 
	return ch;
}
