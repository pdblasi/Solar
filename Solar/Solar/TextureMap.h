#pragma once

// Windoze hacks (JMW 121026)
#if defined(_WIN32)
#  ifndef APIENTRY
#    define APIENTRY
#  endif
#  ifndef WINGDIAPI
#    define WINGDIAPI
#  endif
#endif

#include <gl/freeglut.h>
#include <stdio.h>

class TextureMap
{

public:
    TextureMap(const char* filename);
    TextureMap(); 
    ~TextureMap();
    GLUquadricObj* sphere; //the object to draw the texture on
    unsigned int Texture; //id of the texture 

private:
    bool LoadBmpFile(const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr);
    static short readShort(FILE* infile);
    static int readLong(FILE* infile);
    static void skipChars(FILE* infile, int numChars);
    static inline int GetNumBytesPerRow(int NumCols);

    unsigned char* ImagePtr; //the image 
    const char* FileName; //the filename of the image 
    int NumCols;    //number of columns in the image 
    int NumRows;    //number of rows in the image 
};

