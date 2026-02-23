/*
 * 4_Height.c
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

#define FEET_IN_CM		30.48f
#define CM_IN_INCH		0.393701f

int main(int argc, char **argv)
{
	float heightCm = 0, heightInch = 0;
	int  heightFeet = 0;
	
	printf("Enter the height in centimeters: ");
	scanf("%f", &heightCm);
	
	while (heightCm > 0.)
	{
		heightFeet = heightCm / FEET_IN_CM;
		heightInch = (heightCm - heightFeet * FEET_IN_CM) * CM_IN_INCH;
		printf("%.1f centimeters = %d feet, %.1f inches.\n", heightCm, heightFeet, heightInch);
		printf("Enter the height in centimeters: ");
		scanf("%f", &heightCm);
	}
	
	return 0;
}

