#ifndef _WINDOW_H_
#define _WINDOW_H_


class Window	  // OpenGL output window related routines
{
  public:
    static int width, height; 	            // window size

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void displayCube(void);
	static void displaySphere(void);
	static void displayHouse(void);
	static void displayBunny(void);
	static void displayDragon(void);
};

#endif

