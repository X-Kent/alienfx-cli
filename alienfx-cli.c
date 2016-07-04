#include <stdio.h>
#include <stdlib.h>

#include "alienfx-cli.h"
#include "alienfx-usb.h"
#include "string.h"

char* regions[] = 
{
	"All&0x4BEF",
	"Numpad&0x0008",
	"Keyboard Right&0x0004",
	"Keyboard Center&0x0002",
	"Keyboard Left&0x0001",
	"Bottom Pipes&0x0060",
	"Logo&0x0100",
	"Trackpad&0x0200",
	"Status&0x4800",
	NULL
};

char* colors[] =
{
	"Off&0x0000",
	"Royal&0x00F0",
	"Corn flower&0x06F0",
	"Turquise&0x0AF0",
	"Aqua&0x0F90",
	"Chive&0x3F40",
	"Grass&0x1D10",
	"Emerald&0x1F00",
	"Green&0x2F00",
	"Lime&0x4F00",
	"Lemon&0x7F00",
	"Marigold&0xCE00",
	"Burnt Orange&0xF800",
	"Pumpkin&0xF500",
	"Cherry&0xF000",
	"Hot Pink&0xF010",
	"Fuchsia&0xF0F0",
	"Grape&0x60F0",
	"Indigo&0x30F0",
	NULL
};	

void printUsage(char* execname) 
{
	printf("Usage:\n\n%s <region number> <color number>\n\nRegions:\n",execname);
	int i;
	for(i=0; regions[i]; i++) 
	{
		int len = strchr(regions[i],'&') - regions[i];
		printf(" %d -> %.*s\n",i,len,regions[i]);
	}
	
	printf("\nColors:\n");
	
	for(i=0; colors[i]; i++) 
	{
		int len = strchr(colors[i],'&') - colors[i];
		printf(" %d -> %.*s\n",i,len,colors[i]);
	}

	printf("\nYou can use:\n%s --regions to print all possible regions, --colors to print all possible colors\n",execname);
	printf("\n");
}

int getHex(char* strHex, char* arr[]) {
	int i;
	int index = strtol(strHex,NULL,10);

	for (i=0;arr[i];i++) { // So we don't overflow
		if (index == i) {
			char* start = strchr(arr[i],'&');
			start++;
			
			return (int)strtol(start, NULL, 16);;
		}
	}
	
	return -1;
}

void printArray(char* arr[]) {
	int i;
	for (i=0;arr[i];i++) {
		int len = strchr(arr[i],'&') - arr[i];
		printf("%.*s\n",len,arr[i]);
	}
}

int main(int argc, char** argv) {
	
	if (argc == 2) {
		if (strcmp(argv[1],"--regions") == 0) {
			printArray(regions);
			return 0;
		}
		if (strcmp(argv[1],"--colors") == 0) {
			printArray(colors);
			return 0;
		}
	}
	
	if (argc != 3) {
		printUsage(argv[0]);
		return -1;
	}
	
	int reg = getHex(argv[1],regions);
	if (reg == -1) {
		printf("Invalid region provided: %s \n",argv[1]);
		printUsage(argv[0]);
		return -1;
	}
	int color = getHex(argv[2],colors);	
	if (color == -1) {
		printf("Invalid color provided: %s \n",argv[2]);
		printUsage(argv[0]);
		return -1;
	}
	
	usbTestCode(reg,color);
	
	return 0;
}
