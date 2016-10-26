#ifndef SPRITELIB_NUM_H
#define SPRITELIB_NUM_H

//Spritelib Headers
#include "spritelib.h"

//String Headers
#include <string>
    using std::string;

//Math Headers
#include <cmath>
    using std::cos;
    using std::sin;

//spritelib_text Declaration
class spritelib_text
{
    public:
        spritelib_text(spritelib_tex &tex,const double,const double,const int);

        void draw(spritelib &,const string &,const double,const double,const double,const double,const double);
        void draw(spritelib &,const char &,const double,const double,const double,const double,const double);

    private:
        spritelib_tex *_texture;
        double _width;
        double _height;
        int _numFrames;
};

#endif
