/*
 * 10_Tax.c
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

#define LIM1 			17850.0
#define LIM2 			23900.0
#define LIM3 			29750.0 
#define LIM4 			14875.0
#define TAX1 			0.15
#define TAX2 			0.28 
#define TAX_MONEY1 		LIM1 * TAX1
#define TAX_MONEY2 		LIM2 * TAX1
#define TAX_MONEY3 		LIM3 * TAX1
#define TAX_MONEY4 		LIM4 * TAX1

int main(int argc, char **argv)
{
	int category = 0;
	float sum = 0, tax = 0;
	
	printf("Enter the sum: ");
	scanf("%f", &sum);
	
	printf("Enter category 1 - 5: \n");
	printf("1) %.2f$			2) %.2f$\n", LIM1, LIM2);
	printf("3) %.2f$			4) %.2f$\n", LIM3, LIM4);
	printf("5) Exit\n");
	
	while (scanf("%d", &category) == 1 && category != 5)
	{
		switch (category)
		{
			case 1:
				tax = TAX_MONEY1 + TAX2 * (sum - LIM1);
				break;
			case 2:
				tax = TAX_MONEY2 + TAX2 * (sum - LIM2);
				break;
			case 3:
				tax = TAX_MONEY3 + TAX2 * (sum - LIM3);
				break;
			case 4:
				tax = TAX_MONEY4 + TAX2 * (sum - LIM4);
				break;
			default:
				printf("Enter correct number.\n");
				return 0;
		}
	
		printf("Tax = %.2f\n", tax);
		
		printf("Enter number 1 - 5: \n");
		printf("1) %.2f$			2) %.2f$\n", LIM1, LIM2);
		printf("3) %.2f$			4) %.2f$\n", LIM3, LIM4);
		printf("5) Exit\n");
	}
	
	printf("EXIT.");
	
	return 0;
}
