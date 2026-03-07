/*
 * F16_BlackWhite.c
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

void blackOrWhite(void);

int main(int argc, char **argv)
{
	blackOrWhite();
	
	return 0;
}

void blackOrWhite(void)
{
	char cell[3];
	int later = 0, number = 0;
	
	scanf("%s", cell);
	later = cell[0] - 'A';
	number = cell[1] - '0';
	
	if (later % 2 == 0)
		number++;
	
	if ((later * 8 + number) % 2)
		printf("WHITE\n");
	else
		printf("BLACK\n");
}
