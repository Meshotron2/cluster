#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	/*
	 * Get from user:
	 * 	- width, depth, height (int)
	 * 	- update freq (48000Hz, 44100Hz, 22050Hz, 16000Hz, 11025Hz, 8000Hz)
	 */
	
	int w, h, d;
	int f = -1;

	printf("width: ");
	scanf("%d", &w);
	printf("\n");

	printf("height: ");
	scanf("%d", &h);
	printf("\n");
	
	printf("depth: ");
	scanf("%d", &d);
	printf("\n");

	
	while (f >= 6 || f < 0)
	{
		printf("Possible frequency values:\n");
		printf("0) 48000\n");
		printf("1) 44100\n");
		printf("2) 22050\n");
		printf("3) 16000\n");
		printf("4) 11025\n");
		printf("5) 8000\n");
		printf("frequency: ");
		scanf("%d", &f);
		printf("\n");
	}
	int freqs[] = {48000, 44100, 22050, 16000, 11025, 8000}

	f = freqs[f];
}
