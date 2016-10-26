/* A trivally simple 2D sprite library, for
a graphical user interface access.

Orion Sky Lawlor, olawlor@acm.org, 2010-11-11 (Public Domain)
*/
#ifndef __OSL_SPRITELIB_H
#define __OSL_SPRITELIB_H

#define kb_f1           0x0001
#define kb_f2           0x0002
#define kb_f3           0x0003
#define kb_f4           0x0004
#define kb_f5           0x0005
#define kb_f6           0x0006
#define kb_f7           0x0007
#define kb_f8           0x0008
#define kb_f9           0x0009
#define kb_f10          0x000A
#define kb_f11          0x000B
#define kb_f12          0x000C

#define kb_enter        0x100D
#define kb_escape       0x101B
#define kb_space        0x1020

#define kb_0            0x1030
#define kb_1            0x1031
#define kb_2            0x1032
#define kb_3            0x1033
#define kb_4            0x1034
#define kb_5            0x1035
#define kb_6            0x1036
#define kb_7            0x1037
#define kb_8            0x1038
#define kb_9            0x1039

#define kb_a            0x1061
#define kb_b            0x1062
#define kb_c            0x1063
#define kb_d            0x1064
#define kb_e            0x1065
#define kb_f            0x1066
#define kb_g            0x1067
#define kb_h            0x1068
#define kb_i            0x1069
#define kb_j            0x106A
#define kb_k            0x106B
#define kb_l            0x106C
#define kb_m            0x106D
#define kb_n            0x106E
#define kb_o            0x106F
#define kb_p            0x1070
#define kb_q            0x1071
#define kb_r            0x1072
#define kb_s            0x1073
#define kb_t            0x1074
#define kb_u            0x1075
#define kb_v            0x1076
#define kb_w            0x1077
#define kb_x            0x1078
#define kb_y            0x1079
#define kb_z            0x107A

#define kb_left         0x0064
#define kb_up           0x0065
#define kb_right        0x0066
#define kb_down         0x0067
#define kb_pageup       0x0068
#define kb_pagedown     0x0069
#define kb_home         0x006A
#define kb_end          0x006B
#define kb_insert       0x006C

/* Spritelib is built on top of OpenGL.  So you can call OpenGL, if you want.
  Unfortunately, you also need GLUT installed; the distro comes with Freeglut.
*/
#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <GLUT/glut.h>
#else
# include "GL/glut.h" /* OpenGL Utilities Toolkit, for GUI tools */
#endif
#include <string>

#include <stdexcept>
    using std::runtime_error;

#include <fstream>
    using std::ofstream;

bool keyboard_check(int);
bool keyboard_check_pressed(int);

/* This represents a 2D texture image, loaded on the graphics card.
   See spritelib.read_tex for how to get one.
*/
typedef unsigned int spritelib_tex;

/** This is the main class inside spritelib.  It's packed with handy data,
and has functions to draw stuff on the screen. */
class spritelib {
public:
/* Drawing functions */
	/* Load up a texture image from this filename.
	   You should probably only call this once, and stash the spritelib_tex
	   in a static variable or class member.
	*/
	spritelib_tex read_tex(const char *filename) const;

	/* Draw a square sprite with this texture,
	   centered at pixel (x,y),
	   of size w by h pixels,
	   rotated counterclockwise by angle "angle" (in degrees)
	*/
	void draw(spritelib_tex tex, float x,float y,
		float w,float h,float angle=0.0,bool glow=false) const;

    /* Draw Animation!!! */
    void draw_anim(spritelib_tex tex,float img,int imgNum,float x,float y,
		float w,float h,float angle=0.0,bool glow=false) const;

	/* Draw this string, at this X,Y, in this RGBA color */
	void text(const std::string &s,float x,float y,const float *rgba_color) const;

/* Info about the current window ("screen") */
	float background[4]; /* RGBA background color (read/write) */
	float screenw,screenh; /* size of our window, in pixels (read only) */
	float screenscale;

/* Time */
	float time; /* time since application started, in seconds */
	float dt; /* time between frames, in seconds (for physics) */

/* Keyboard */
	bool key[256]; /* if true, the corresponding key is currently pressed */
	bool key_typed[256]; /* oneshot: the corresponding key was *just* typed */
	bool shift,ctrl,alt; /* this modifier key is currently pressed (note: only updated when another key or mouse is pressed!) */

/* Mouse */
	int mousex,mousey; /* location of the mouse */
	bool mouseleft; /* the left mouse button is currently pressed */
	bool mouseleft_clicked; /* oneshot: the left mouse button was *just* clicked */
	bool mouseright; /* ... ditto for right button... */
	bool mouseright_clicked;
	int mousewheel; /* current position of scroll wheel on mouse */

/* Special */
    bool kb_check[256];
    bool kb_pressed[256];

private:
	spritelib(void):screenscale(2.0){}/* Don't make your own spritelib objects... */
	friend spritelib &spritelib_get(bool check); /*...he will. */
	spritelib(const spritelib &o); /* Don't copy spritelib objects... */
	void operator=(const spritelib &o); /* ...don't assign them either. */
};

spritelib &spritelib_get(bool check=true);

/** You must call this function once, from your main function.
  Spritelib will open a window with the given title and size,
  and then handle events to that window until you exit.
  This function never returns. */
void spritelib_run(const char *window_title,int screenw,int screenh);


/**
  You must write this function.  Spritelib will call it repeatedly
  to draw stuff on the screen, and handle mouse and keyboard events.
*/
void spritelib_draw_screen(spritelib &lib);



#endif
