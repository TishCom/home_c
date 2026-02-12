/*
 * 1_CoffeeVendingMachine.c
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

typedef enum 
{
	READY,
	PREPFRE,
	WAIT,
	CHANGE,
	RETURN,
	STATE_MAX
} STATE_t;

typedef enum 
{
	RUBL_1,
	RUBL_2,
	CANCEL,
	EVENT_MAX
} EVENT_t;

typedef STATE_t (*STATE_FUNC_PTR_t)(void);

STATE_t ready(void);
STATE_t prepfre(void);
STATE_t wait(void);
STATE_t change(void);
STATE_t myReturn(void);
EVENT_t getEvent(void);


STATE_t (*transition_table[STATE_MAX][EVENT_MAX]) (void) = 
{
	[READY] 	[RUBL_1] 	= ready,
	[READY] 	[RUBL_2] 	= prepfre,
	[READY] 	[CANCEL] 	= wait,
	[PREPFRE]	[RUBL_1] 	= wait,
	[PREPFRE]	[RUBL_2] 	= change,
	[PREPFRE]	[CANCEL] 	= ready,
	[WAIT] 		[RUBL_1] 	= myReturn,
	[WAIT] 		[RUBL_2] 	= change,
	[WAIT] 		[CANCEL] 	= wait,
	[CHANGE] 	[RUBL_1] 	= myReturn,
	[CHANGE]	[RUBL_2] 	= prepfre,
	[CHANGE]	[CANCEL] 	= myReturn,
	[RETURN] 	[RUBL_1] 	= change,
	[RETURN] 	[RUBL_2] 	= myReturn,
	[RETURN] 	[CANCEL] 	= prepfre
};

int main(int argc, char **argv)
{
	STATE_t state = PREPFRE;
	EVENT_t event = CANCEL;
	
	while(1) 
	{
		event = getEvent();
		state = transition_table[state][event]();
	}

	return 0;
}

EVENT_t getEvent(void)
{
    char choice;
    while(1)
    {
        printf("1.Put 1 rubl\n2.Put 2 rubl\n0.Cancel\n");
        scanf("%c", &choice);
        getchar();
        switch(choice)
        {
        case '1':
            return RUBL_1;
        case '2':
            return RUBL_2;
        case '0':
            return CANCEL;
        }
    }
}

STATE_t ready(void)
{
	printf("ready\n");
	
	return READY;
}

STATE_t prepfre(void)
{
	printf("prepfe\n");
	
	return READY;
}

STATE_t wait(void)
{
	printf("wait\n");
	
	return READY;
}

STATE_t change(void)
{
	printf("change\n");
	
	return READY;
}

STATE_t myReturn(void)
{
	printf("myReturn\n");
	
	return READY;
}
