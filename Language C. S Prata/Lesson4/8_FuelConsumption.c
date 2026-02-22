/*
 * 8_FuelConsumption.c
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

#define LITERS_PER_GALLON 3.785f
#define KILOMETERS_PER_MILE 1.609f

int main(int argc, char **argv)
{
	float fuel = 0., distance = 0., consumption = 0.;
	
	printf("Tell me how many miles have you traveled: ");
	scanf("%f", &distance);
	
	printf("Tell me how much fuel you used in gallons: ");
	scanf("%f", &fuel);
	
	consumption = distance / fuel;
	
	printf("You drove %.1f miles on one gallon of fuel.\n", consumption);
	
	fuel *= LITERS_PER_GALLON;
	distance *= KILOMETERS_PER_MILE;
	consumption = (fuel / distance) * 100.0;
	
	printf("You spent %.1f liters per 100 kilometers.\n", consumption);
	
	return 0;
}

