/*
 * C6_HowManyGrains.c
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
#include <stdint.h>
#include <inttypes.h>

uint64_t howManyGrains(uint64_t square);

int main(int argc, char **argv)
{
	uint64_t number = 0;
	
	scanf("%"SCNu64, &number);
	
	number = howManyGrains(number);
	
	if(number != 0)
		printf("%" PRIu64 "\n", number);
	
	return 0;
}

uint64_t howManyGrains(uint64_t square)
{
	uint64_t result = 1;
	
	if (square < 1 || square > 64)
	{
		printf("printing 1 - 64");
		return 0;
	}
	
	for (int i = 1; i < square; i++)
		result *= (uint64_t)2;
		
	return result;
}
