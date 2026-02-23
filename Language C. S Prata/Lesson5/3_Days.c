/*
 * 3_Days.c
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

#define DAYS_IN_WEEK	7

int main(int argc, char **argv)
{
	int dayIN = 0, weekOUT = 0, dayOUT = 0;
	
	printf("Enter the days value: ");
	scanf("%d", &dayIN);
	
	while (dayIN > 0)
	{
		weekOUT = dayIN / DAYS_IN_WEEK;
		dayOUT = dayIN % DAYS_IN_WEEK;
		printf("%d days is %d weeks and %d days.\n", dayIN, weekOUT, dayOUT);
		printf("Enter the days value: ");
		scanf("%d", &dayIN);
	}
	
	return 0;
}

