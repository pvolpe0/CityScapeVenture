#ifndef CSE167_Window_h
#define CSE167_Window_h

class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void keyboard(unsigned char key, int x, int y);
	static void onMouseClick(int button, int state, int x, int y);
	static void onMouseMove(int x, int y);
    
};

#endif

