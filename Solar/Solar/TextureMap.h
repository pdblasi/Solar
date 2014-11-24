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
    TextureMap(const char* filename, GLUquadricObj* sphere);
    TextureMap(); 
    ~TextureMap();
    /*!
    * @brief the id of the texture drawn 
    */
    unsigned int Texture;

private:
    bool LoadBmpFile(const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr);
    static short readShort(FILE* infile);
    static int readLong(FILE* infile);
    static void skipChars(FILE* infile, int numChars);
    static inline int GetNumBytesPerRow(int NumCols);

    /*!
    * @brief A pointer to the image
    */
    unsigned char* ImagePtr;
    /*!
    * @brief the filename of the image 
    */
    const char* FileName; 
    /*!
    * @brief the number of columns in the image 
    */
    int NumCols;  
    /*!
    * @brief the number of rowns in the image 
    */
    int NumRows;   
    /*!
    * @brief the object to draw the texture on 
    */
    GLUquadricObj* sphere; //the object to draw the texture on
};

