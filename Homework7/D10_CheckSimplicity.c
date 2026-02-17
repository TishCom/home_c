/*
 * D10_CheckSimplicity.c
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
#include <inttypes.h>

uint32_t isPrime(uint32_t number);
uint32_t isPrimeNumber(uint32_t i, uint32_t n) ;

int main(int argc, char **argv)
{
	int32_t number = 0;
	
	scanf("%d", &number);
	
	if (isPrime(number))
		printf("YES");
	else
		printf("NO");
	
	return 0;
}

uint32_t isPrime(uint32_t number)
{
	if (number <= 1)
		return 0;
	
	return isPrimeNumber(2, number);
}

uint32_t isPrimeNumber(uint32_t i, uint32_t n) 
{
	if(i == n)
		return 1;
	else if (n % i == 0)
		return 0;
	
	return isPrimeNumber(i + 1, n);
}
