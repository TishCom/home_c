/*
 * 8_%.c
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
	int operand2 = 0, operand1 = 0;
	
	printf("This program calculates the result of a modulo division.\n");
	
	printf("Enter a whole number that will serve as the second operand: ");
	scanf("%d", &operand2);
	
	printf("Now enter the first operand: ");
	scanf("%d", &operand1);
	
	while (operand1 > 0)
	{
		printf("%d %% %d = %d\n", operand1, operand2, operand1 % operand2);
		printf("Enter the following number of the first operand: ");
		scanf("%d", &operand1);
	}
	
	printf("Done!");
	
	return 0;
}

