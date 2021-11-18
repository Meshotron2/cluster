#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void)
{
	/*
	 * Get from user:
	 * 	- width, depth, height (int)
	 * 	- update freq (48000Hz, 44100Hz, 22050Hz, 16000Hz, 11025Hz, 8000Hz)
	 */
	
	int w, h, d;
	int f = -1;
	int c = 343;

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
		printf("1) 48000\n");
		printf("2) 44100\n");
		printf("3) 22050\n");
		printf("4) 16000\n");
		printf("5) 11025\n");
		printf("6) 8000\n");
		printf("frequency: ");
		scanf("%d", &f);
		printf("\n");
	}
	int freqs[] = {48000, 44100, 22050, 16000, 11025, 8000}

	f = freqs[f - 1];

	int x = getNodes(f, w, c);
	int y = getNodes(f, d, c);
	int z = getNodes(f, h, c);

	/*
	 * Customize room
	 */

	customizeRoom();
}

int getNodes(int f, int dim, int c)
{
	return (f*dim)/(c*sqrt(3));
}

void customizeRoom()
{
	char choice = 0;

	while (
		choice != 'S' && 
		choice != 'C' && 
		choice != 's' && 
		choice != 'r' && 
		choice != 'q'
		)
	{
		printf("Sphere: 'S'\n");
		printf("Cuboid: 'C'\n");
		printf("Source: 's'\n");
		printf("Receiver: 'r'\n");
		printf("QUIT: 'q'\n");
		printf("Select one... ")

		scanf("%c", &choice);
		printf("\n");
	}

	switch (choice)
	{
		case 'q':
			return;
		case 'S':
			buildSphere();
			break;
		case 'C':
			buildCuboid();
			break;
		case 's':
			//TODO: only one source allowed, check for this
			//		maybe store the source's last state and reset it whenever a new source is set. 
			setSource();
			break;
		case 'r':
			setReceiver();
			break;
	}
}

void setReceiver()
{
	int x, y, z;

	printf("receiver x: ");
	scanf("%d", &x);
	printf("\n");

	printf("receiver y: ");
	scanf("%d", &y);
	printf("\n");
	
	printf("receiver z: ");
	scanf("%d", &z);
	printf("\n");

	// set receiver
}

void setSource()
{
	int x, y, z;

	printf("source x: ");
	scanf("%d", &x);
	printf("\n");

	printf("source y: ");
	scanf("%d", &y);
	printf("\n");
	
	printf("source z: ");
	scanf("%d", &z);
	printf("\n");

	// set source
}

void buildSphere()
{
	int x, y, z, r;

	printf("centre x: ");
	scanf("%d", &x);
	printf("\n");

	printf("centre y: ");
	scanf("%d", &y);
	printf("\n");
	
	printf("centre z: ");
	scanf("%d", &z);
	printf("\n");

	printf("radious: ");
	scanf("%d", &r);
	printf("\n");

	char c = showOpts();
	
	// taking the radious, center a cube arround the centre
	// run through each point and aply to those whose distance is <= than the redious
	// populate with c
}

void buildCuboid()
{
	int x1, x2, y1, y2, z1, z2;


	printf("point 1 x: ");
	scanf("%d", &x1);
	printf("\n");

	printf("point 1 y: ");
	scanf("%d", &y1);
	printf("\n");
	
	printf("point 1 z: ");
	scanf("%d", &z1);
	printf("\n");
	
	printf("point 2 x: ");
	scanf("%d", &x2);
	printf("\n");

	printf("point 2 y: ");
	scanf("%d", &y2);
	printf("\n");
	
	printf("point 2 z: ");
	scanf("%d", &z2);
	printf("\n");

	char c = showOpts();
	
	// for from x1 - x2, then y1 - y2, ...
	// populate with c
}

char showOpts()
{
	char opt = '';
	
	while (
		opt != ' ' &&
		opt != 'S' &&
		opt != 'R' &&
		opt != 'Z' &&
		!('A' <= opt && opt <= 'J') &&
		!('1' <= opt && opt <= '9')
		)
	{
		printf("standard: ' '\n");
		printf("source: 'S'\n");
		printf("receiver: 'R'\n");
		printf("p=0: A");
		printf("p=0.1: B");
		printf("p=0.2: C");
		printf("p=0.3: D");
		printf("p=0.4: E");
		printf("p=0.5: F");
		printf("p=0.6: G");
		printf("p=0.7: H");
		printf("p=0.8: I");
		printf("p=0.9: J");
		printf("p=0.91: 1");
		printf("p=0.92: 2");
		printf("p=0.93: 3");
		printf("p=0.94: 4");
		printf("p=0.95: 5");
		printf("p=0.96: 6");
		printf("p=0.97: 7");
		printf("p=0.98: 8");
		printf("p=0.99: 9");

		printf("Configuration: ");
		scanf("%c", &opt);
		printf("\n");
	}
	return opt;
}

