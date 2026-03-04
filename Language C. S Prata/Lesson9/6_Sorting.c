/*
 * Swap.c
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


#include <stdio.h>

void sorting(double *x, double *y, double *z);
void swap(double *x, double *y);

int main(int argc, char **argv)
{
	double x = 3.45, y = 5.04, z = 0.23;
	
	printf("%.2f %.2f %.2f", x, y, z);
	
	sorting(&x, &y, &z);
	
	printf("%.2f %.2f %.2f", x, y, z);
	
	return 0;
}

void sorting(double *x, double *y, double *z)
{
	if(*x > *y)
		swap(x, y);
	if(*x > *z)
		swap(x, z);
	if(*y > *z)
		swap(y, z);
}

void swap(double *x, double *y)
{
	double temp = *x;
	*x = *y;
	*y = temp;
}
