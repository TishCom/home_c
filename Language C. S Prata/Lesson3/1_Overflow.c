/*
 * 1_Overflow.c
 * 
 * Copyright 2026 tisha <tisha@DESKTOP-H2QK95F>
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


#include <stdio.h>

int main(int argc, char **argv)
{
	int max = 2147483647;
	float maxf = 3.402823466e38;
	
	printf("%d\n", max);
	printf("%d\n", max + 1);
	printf("%f\n", maxf);
	printf("%f\n", maxf + 10000000000000000000000000.);
	printf("%f\n", maxf + 1000000000000000000.);
	printf("%f\n", maxf * 10);
	
	return 0;
}

