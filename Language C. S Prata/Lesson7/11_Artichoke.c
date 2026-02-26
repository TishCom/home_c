/*
 * 11_Artichoke.c
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

#define ARTICHOKE 		2.05
#define BEET 			1.15 
#define CARROT 			1.09

#define LIM 			100
#define DISCOUNT 		0.05
#define LIM_DISCOUNT 	LIM * DISCOUNT

#define DELIVERY1 		6.5
#define WEIGHT1 		5
#define DELIVERY2 		14.0
#define WEIGHT2 		20
#define ADDITIONALLY 	0.5

int main(int argc, char **argv)
{
	char ch = 0;
	int countBeet = 0, countArtichoke = 0, countCarrot = 0, pound = 0;
	int sumPound = 0;
	float sum = 0, discount = 0, delivery = 0, totalAmount = 0;
	
	printf("Enter name:");
	
	while (scanf("%c", &ch) == 1 && ch != 'q')
	{
		printf("Enter weight:");
		scanf("%d", &pound);
		
		switch (ch)
		{
			case 'a':
				countArtichoke += pound;
				break;
			case 'b':
				countBeet += pound;
				break;
			case 'c':
				countCarrot += pound;
				break;
			default:
				printf("Enter correct number.\n");
				continue;
		}
		
		printf("Enter name:");
		
		while(getchar() != '\n')
			continue;
	}
	
	sumPound = countArtichoke + countBeet + countCarrot;
	
	totalAmount = 	countArtichoke * ARTICHOKE + countBeet * BEET +
			countCarrot * CARROT;
			
	if (totalAmount <= LIM)
		discount = totalAmount * DISCOUNT;
	else
		discount = LIM_DISCOUNT;
		
	sum = totalAmount - discount; 
		
	if (sumPound <= WEIGHT1)
		delivery = DELIVERY1;
	else if (sumPound <= WEIGHT2)
		delivery = DELIVERY2;
	else if (sumPound > WEIGHT2)
		delivery = DELIVERY2 + (sumPound - WEIGHT2) * ADDITIONALLY;
		
	sum += delivery; 
	
	printf("sumPound = %d, countArtichoke = %d, countBeet = %d, countCarrot = %d\n"
			"totalAmount = %.2f, discount = %.2f, delivery = %.2f, sum = %.2f,",
			sumPound, countArtichoke, countBeet, countCarrot,
			 totalAmount, discount, delivery, sum);
	
	return 0;
}

