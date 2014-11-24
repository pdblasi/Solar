#include "TextureMap.h"

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Texture Map constructor loads a bmp file from the filename passed in and
* then creates the texture map and the quadric to draw the texture map on. 
*
* @param filename - the filename for the bmp file to use for a texture 
*
*****************************************************************************/
TextureMap::TextureMap(const char* filename)
{
    //load the file and record the filename 
    LoadBmpFile(filename, NumRows, NumCols, ImagePtr);
    FileName = filename; 

    //enable texturing, get a reference to the texture you are making
    glEnable(GL_TEXTURE_2D); 
    glGenTextures(1, (GLuint*)(&Texture));
    glBindTexture(GL_TEXTURE_2D, Texture);

    //create the texture 
    glTexImage2D(GL_TEXTURE_2D, 0, 3, NumCols, NumRows, 0, GL_RGB, GL_UNSIGNED_BYTE, ImagePtr);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //create a quadric to draw the texture on
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluQuadricTexture(sphere, GL_TRUE);
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* An empty constructor for the texture map 
*
*****************************************************************************/
TextureMap::TextureMap()
{

}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* The destructor for the texture map class 
*
*****************************************************************************/
TextureMap::~TextureMap()
{
}

/**************************************************************************//**
* @author John Weiss 
*
* @par Description:Code to read in a BMP image file.
* Ref: based on code from RgbImage.cc (Buss, 3-D Computer Graphics, 2003).
*
*****************************************************************************/
bool TextureMap::LoadBmpFile(const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr)
{
    FILE* infile; 
    #if _WIN32
    fopen_s(&infile, filename, "rb");	// Open for reading binary data
    #else
    infile = fopen(filename, "rb");
    #endif

    if (!infile)
    {
        fprintf(stderr, "LoadBmpFile(): unable to open file: %s\n", filename);
        return false;
    }

    bool fileFormatOK = false;
    int bChar = fgetc(infile);
    int mChar = fgetc(infile);
    if (bChar == 'B' && mChar == 'M')
    {			// If starts with "BM" for "BitMap"
        skipChars(infile, 4 + 2 + 2 + 4 + 4);			// Skip 4 fields we don't care about
        NumCols = readLong(infile);
        NumRows = readLong(infile);
        skipChars(infile, 2);					// Skip one field
        int bitsPerPixel = readShort(infile);
        skipChars(infile, 4 + 4 + 4 + 4 + 4 + 4);		// Skip 6 more fields

        if (NumCols > 0 && NumCols <= 100000 && NumRows > 0 && NumRows <= 100000
            && bitsPerPixel == 24 && !feof(infile))
        {
            fileFormatOK = true;
        }
    }

    if (!fileFormatOK)
    {
        fclose(infile);
        fprintf(stderr, "Not a valid 24-bit bitmap file: %s.\n", filename);
        return false;
    }

    // Allocate memory
    ImagePtr = new unsigned char[NumRows * GetNumBytesPerRow(NumCols)];
    if (!ImagePtr)
    {
        fclose(infile);
        fprintf(stderr, "Unable to allocate memory for %i x %i bitmap: %s.\n",
            NumRows, NumCols, filename);
        return false;
    }

    unsigned char* cPtr = ImagePtr;
    for (int i = 0; i < NumRows; i++)
    {
        int j;
        for (j = 0; j < NumCols; j++)
        {
            *(cPtr + 2) = fgetc(infile);	// Blue color value
            *(cPtr + 1) = fgetc(infile);	// Green color value
            *cPtr = fgetc(infile);		// Red color value
            cPtr += 3;
        }
        int k = 3 * NumCols;					// Num bytes already read
        for (; k < GetNumBytesPerRow(NumCols); k++)
        {
            fgetc(infile);				// Read and ignore padding;
            *(cPtr++) = 0;
        }
    }

    if (feof(infile))
    {
        fclose(infile);
        fprintf(stderr, "Premature end of file: %s.\n", filename);
        return false;
    }

    fclose(infile);	// Close the file

    return true;
}

/**************************************************************************//**
* @author John Weiss
*
* Description: Gets the number of bytes per row in the image based on the number
* of colums in the image
* Ref: based on code from RgbImage.cc (Buss, 3-D Computer Graphics, 2003).
*
*****************************************************************************/
// Rows are word aligned
inline int TextureMap::GetNumBytesPerRow(int NumCols)
{
    return ((3 * NumCols + 3) >> 2) << 2;
}

/**************************************************************************//**
* @author John Weiss
*
* Description: Reads a 16 bit integer from the input file 
* Ref: based on code from RgbImage.cc (Buss, 3-D Computer Graphics, 2003).
*
*****************************************************************************/
short TextureMap::readShort(FILE* infile)
{
    unsigned char lowByte, hiByte;
    lowByte = fgetc(infile);			// Read the low order byte (little endian form)
    hiByte = fgetc(infile);			// Read the high order byte

    // Pack together
    short ret = hiByte;
    ret <<= 8;
    ret |= lowByte;
    return ret;
}

/**************************************************************************//**
* @author John Weiss
*
* Description: Reads a 32 bit integer from the input file 
* Ref: based on code from RgbImage.cc (Buss, 3-D Computer Graphics, 2003).
*
*****************************************************************************/
int TextureMap::readLong(FILE* infile)
{
    unsigned char byte0, byte1, byte2, byte3;
    byte0 = fgetc(infile);			// Read bytes, low order to high order
    byte1 = fgetc(infile);
    byte2 = fgetc(infile);
    byte3 = fgetc(infile);

    // Pack together
    int ret = byte3;
    ret <<= 8;
    ret |= byte2;
    ret <<= 8;
    ret |= byte1;
    ret <<= 8;
    ret |= byte0;
    return ret;
}

/**************************************************************************//**
* @author John Weiss
*
* Description: Skips over a given number of byes in the input file 
* Ref: based on code from RgbImage.cc (Buss, 3-D Computer Graphics, 2003).
*
*****************************************************************************/
void TextureMap::skipChars(FILE* infile, int numChars)
{
    for (int i = 0; i < numChars; i++)
    {
        fgetc(infile);
    }
}
