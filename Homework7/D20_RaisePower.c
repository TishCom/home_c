/*
 * D20_RaisePower.c
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
#include <inttypes.h>

int32_t isPrimeNumber(int32_t i, uint32_t n);

int main(int argc, char **argv)
{
	uint32_t numberB = 0;
	int32_t numberA = 0;
	
	scanf("%d%d", &numberA, &numberB);
	
	printf("%d", isPrimeNumber(numberA, numberB));
	
	return 0;
}

int32_t isPrimeNumber(int32_t i, uint32_t n) 
{
	if(n == 0)
		return 1;
	else 
		return i *= isPrimeNumber(i, n - 1);
}
