/*
 * 1_Time.c
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

#define MIN_IN_HOUR	60

int main(int argc, char **argv)
{
	int minIN = 0, hourOUT = 0, minOUT = 0;
	
	printf("Enter the minutes value:");
	scanf("%d", &minIN);
	
	while (minIN > 0)
	{
		hourOUT = minIN / MIN_IN_HOUR;
		minOUT = minIN % MIN_IN_HOUR;
		printf("%d minutes is %d hours and %d minutes.\n", minIN, hourOUT, minOUT);
		printf("Enter the minutes value:");
		scanf("%d", &minIN);
	}
	
	return 0;
}

