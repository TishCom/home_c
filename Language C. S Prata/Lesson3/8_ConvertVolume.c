/*
 * 8_ConvertVolume.c
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
	int volume = 0;
	printf("%s", "Enter the volume in cups: ");
	scanf("%d", &volume);
	printf("%s %f\n", "Entered volume in pints:", volume / 2.);
	printf("%s %f\n", "Entered volume in ounces:", volume * 8.);
	printf("%s %f\n", "Entered volume in tablespoons:", volume * 16.);
	printf("%s %f\n", "Entered volume in teaspoons:", volume * 48.);
	
	return 0;
}

