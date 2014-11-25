/************************************************************************//**
*  @file
*
*  @brief Class interpretation of the Read BMP file from Dr. Weiss's example.
* Contains the header information for the TextureMap class. 
* Ref: based on code from RgbImage.cc (Buss, 3-D Computer Graphics, 2003).
***************************************************************************/

#pragma once

/*!
* @brief Windows overrides based on the ReadBMP file made by Dr. John Weiss
* refrencing RgbImage.cc (Buss, 3-D Computer Graphics, 2003).
*/
// Windoze hacks (JMW 121026)
#if defined(_WIN32)
#  ifndef APIENTRY
#    define APIENTRY
#  endif
#  ifndef WINGDIAPI
#    define WINGDIAPI
#  endif
#endif

#include <GL/freeglut.h>
#include <stdio.h>


/*!
* @brief The TextureMap class takes an image from file and creates a texture map from it.
*/
class TextureMap
{

public:
    /*!
    *  @brief The constructor for the TextureMap class 
    */
    TextureMap(const char* filename, GLUquadricObj* sphere);
    /*!
    *  @brief Default constructor
    */
    TextureMap(); 
    /*!
    *  @brief The destructor
    */
    ~TextureMap();
    /*!
    * @brief the id of the texture drawn 
    */
    unsigned int Texture;

private:
    /*!
    *  @brief Opens and reads a BMP file
    */
    bool LoadBmpFile(const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr);
    /*!
    *  @brief Reads and 16 bit integer from file 
    */
    static short readShort(FILE* infile);
    /*!
    *  @brief Reads a 32 bit integer from file 
    */
    static int readLong(FILE* infile);
    /*!
    *  @brief Skips over a number of charactors in file 
    */
    static void skipChars(FILE* infile, int numChars);        
    /*!
    *  @brief The number of bytes in a row of image 
    */
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

