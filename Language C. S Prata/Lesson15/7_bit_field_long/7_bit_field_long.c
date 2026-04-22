#include <inttypes.h>
#include <ctype.h>
#include <stdio.h>

#define GET_UNDERLINE(x)	((x) & 1)
#define SET_UNDERLINE(x)	((x) << 0)
#define RESET_UNDERLINE		(~(1 << 0))
#define INV_UNDERLINE(x)	((x) ^ (1 << 0))

#define GET_ITALIC(x)		(((x) & 2) >> 1)
#define SET_ITALIC(x)		((x) << 1)
#define RESET_ITALIC		(~(1 << 1))
#define INV_ITALIC(x)		((x) ^ (1 << 1))

#define GET_FAT(x) 			(((x) & 4) >> 2)
#define SET_FAT(x)			((x) << 2)
#define RESET_FAT			(~(1 << 2))
#define INV_FAT(x)			((x) ^ (1 << 2))

#define ALIGNMENT 			3
#define GET_ALIG(x)			(((x) & (3 << ALIGNMENT)) >> ALIGNMENT)
#define SET_ALIG(x)			((x) << ALIGNMENT)
#define RESET_ALIG			(~(3 << ALIGNMENT))

#define SIZE 				5
#define GET_SIZE(x)			(((x) & (127 << SIZE)) >> SIZE)
#define SET_SIZE(x)			((x) << SIZE)
#define RESET_SIZE			(~(127 << SIZE))

#define ID	 				12
#define GET_ID(x)			(((x) & (255 << ID)) >> ID)
#define SET_ID(x)			((x) << ID)
#define RESET_ID			(~(255 << ID))

char *alignment[3] = {"left", "center", "right"};

char *onOff[2] = {"OFF", "ON"};

char myGetchar(void);
void skipString(void);
char menu(unsigned long myFont1);
void changeAlignment(unsigned long *myFont1);
void changeSize(unsigned long *myFont1);
void changeFont(unsigned long *myFont1);

int main(int argc, char **argv)
{
	char ch = 0;
	unsigned long myFont = SET_ID(1) | SET_SIZE(12) | SET_ALIG(0) | SET_FAT(0) | SET_ITALIC(0) |  SET_UNDERLINE(0);
	
	while ((ch = menu(myFont)) != 'g')
	{
		switch(ch)
		{
			case 'a':
				changeFont(&myFont);
				break;
			case 'b':
				changeSize(&myFont);
				break;
			case 'c':
				changeAlignment(&myFont);
				break;
			case 'd':
				myFont = INV_FAT(myFont);
				break;
			case 'e':
				myFont = INV_ITALIC(myFont);
				break;
			case 'f':
				myFont = INV_UNDERLINE(myFont);
		};
	}
	
	printf("exit.\n");
	
	return 0;
}

void changeFont(unsigned long *myFont)
{
	int b = 0;
	
	do
	{
		printf("Enter the font id (0-255): ");
		scanf("%d", &b);
		skipString();
	}while (b & ~0b11111111);
	
	*myFont &= RESET_ID;
	*myFont |= SET_ID(b);
}

void changeSize(unsigned long *myFont)
{
	int b = 0;
	
	do
	{
		printf("Enter the font size (0-127): ");
		scanf("%d", &b);
		skipString();
	}while (b & ~0b01111111);
	
	*myFont &= RESET_SIZE;
	*myFont |= SET_SIZE(b);
}

void changeAlignment(unsigned long *myFont)
{
	char ch = 0;
	
	printf("Select the alignment\n");
	
	do
	{
		printf("a)left b)center c)right\n");
		ch = myGetchar();
	}while (ch != 'a' && ch != 'b' && ch != 'c');
	
	*myFont &= RESET_ALIG;
	*myFont |= SET_ALIG((ch - 'a') % 3);
}

char menu(unsigned long myFont)
{
	printf(" ID  Size  Alignment  Fat  Italic  Underline\n");
	printf("%3d %4d %8s %7s %5s %8s\n", GET_ID(myFont), GET_SIZE(myFont), alignment[GET_ALIG(myFont)], onOff[GET_FAT(myFont)],  onOff[GET_ITALIC(myFont)],  onOff[GET_UNDERLINE(myFont)]);
	
	printf("a)change font b)change size c)change alignment\n");
	printf("d)bold        e)italic      f)underline\n");
	printf("g)exit\n");
	
	return myGetchar();
}

void skipString(void)
{
	while (getchar() != '\n')
		continue;
}

char myGetchar(void)
{
	char ch = 0;
	
	while (isspace(ch = getchar()))
		continue;
		
	skipString();
	 
	return ch;
}
