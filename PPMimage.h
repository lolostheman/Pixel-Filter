#include <string>

#ifndef PPMIMAGE_H
#define PPMIMAGE_H

namespace egre246 {
  
class PPMimage{
 public:
  PPMimage(); // default object does not store an image; leaves pixel array equal to NULL
  PPMimage(const std::string filename); // loads P3 PPM image from file
  PPMimage(const PPMimage &); // copy constructor
  ~PPMimage(); // destructor

  std::string getFileName() const; // returns fileName if image has been loaded from file
                                   // or an empty string if no file has been loaded
  void readImage(const std::string name);  // reads image from file; asserts that the magic number
                                           // string is P3, width>0, height>0, and max color is
                                           // between 0 and 255 inclusive
  void writeImage(const std::string name); // writes image to file if image is valid, does nothing
                                           // if it is invalid
  
  // setters make no judgments about the validity of the data
  std::string getMagicNumber() const;
  void setMagicNumber(const std::string="P3");
  int  getWidth() const;
  void setWidth(const int);
  int  getHeight() const;
  void setHeight(const int);
  int  getMaxColor() const;
  void setMaxColor(const int=255);
  int  *getPixels() const; // returns a copy of the pixel array
  void setPixels(const int *, const int w, const int h); // copies pixel array to object; assumes
                                                         // w,h are the width, height of image; sets
                                                         // object width to w, height to h
  bool isValid() const; // true if magic is P3, width and height are greater than 0,
                        // 0 <= maxColor <= 255, and the pixels array is not NULL
  
  int getRed(const int row, const int col) const;
  int getGreen(const int row, const int col) const;
  int getBlue(const int row, const int col) const;

  int *getPixel(const int row, const int col) const; // returns pixel as an array of 3 values
                                                     // with order RGB
  void setPixel(const int *pixel, const int row, const int col);
      // assumes pixel is stored as an array of 3 values with order RGB

 private:
  std::string fileName;
  std::string magic;
  int width, height, maxColor;
  int *pixels;
};
 
}
#endif