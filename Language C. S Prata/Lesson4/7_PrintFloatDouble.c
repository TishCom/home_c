/*
 * 7_PrintFloatDouble.c
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
#include <float.h>

int main(int argc, char **argv)
{
	float a = 1.0/3.0;
	double b = 1.0/3.0;
	
	printf("%.4f %.4f\n", a, b);
	printf("%.12f %.12f\n", a, b);
	printf("%.16f %.16f\n", a, b);
	printf("%d %d\n", FLT_DIG, DBL_DIG);
	
	return 0;
}

