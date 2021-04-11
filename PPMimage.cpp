/*
* Project 3
* EGRE 206 Fall 2018
* Cameron O'Leary
* Logan Morro
*/

#include <iostream>
#include <string>
#include <string.h>
#include <cassert>
#include <stdbool.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include "PPMimage.h"

using namespace std;
using namespace egre246;
 
  PPMimage::PPMimage(){

  width=-1;
  height=-1;
  maxColor=255;
  pixels = new int[1];
  magic = "P3"; fileName = "";
  }  // default object does not store an image; leaves pixel array equal to NULL
  PPMimage::PPMimage(const std::string filename_){
  PPMimage::readImage(filename_);
  }	  // loads P3 PPM image from file
  
  PPMimage::PPMimage(const PPMimage& a){
	  fileName = a.fileName;
	  maxColor = a.maxColor;
	  width = a.width;
	  magic = a.magic;
	  height = a.height;
	  pixels = new int[width*height*3];
	  for(int i = 0; i< (width*height*3); i++){
		  pixels[i] = a.pixels[i];
	  }
  } // copy constructor
  PPMimage::~PPMimage(){delete[] pixels;} // destructor

  //slide 122 
  
  std::string PPMimage::getFileName() const{
	  return fileName;
	  /*char cstr[fileName.size() +1];
	  strcpy(cstr,fileName.c_str());
	  int n = fileName.length();
	  fstream file;
	  file.open(fileName);
	  if(file.is_open()&&(cstr[n-1]=='m')){
		  return fileName;
		  file.close();
	  }else{
		  return "";
		  */  
	  
  }// returns fileName if image has been loaded from file
                                   // or an empty string if no file has been loaded
  void PPMimage::readImage(const std::string name){ // call filename function
	string filename;
	string word;
	fileName = name;
	fstream file;    
    ifstream fp(name);
	string width_, height_, max_;
	int i = 0;
	string x,y;
	int x_,y_;
	int j = 0;
	while(fp >> word){
		if(i==3){
		}
		if(i==0){
			magic = word;
		}else if(i==1){
			width_ = word;
			width = atoi(width_.c_str());
		}else if(i==2){
			height_ = word;
			height = atoi(height_.c_str());
		}else if(i==3){
			max_ = word;
			maxColor = atoi(max_.c_str());
			break;
		}
		i++;
	}
	pixels = new int[width*height*3];
	
	while(fp>>word){		
			x = word;
			x_ = atoi(x.c_str());
			pixels[j]=x_;
			
		if(j==width*height*3){
			fp.close();
		}
		j++;
		
	}
	assert(magic=="P3");
	assert(width>0);
	assert(height>0);
	assert((maxColor>=0)&&(maxColor<=255));	
  } // reads image from file; asserts that the magic number
                                           // string is P3, width>0, height>0, and max color is
                                           // between 0 and 255 inclusive
										   
										   
										   
										   
										   
  void PPMimage::writeImage(const std::string name){
	  if(isValid()==1){
	  ofstream write;
	  write.open(name,ofstream::out);
	  write << magic << endl << width<< " " << height << endl << maxColor << endl;
	 for(int i =0; i < (width*height*3);){
		 for(int j=1; j<=3;j++){
			 write << pixels[i++] << ((j==3)?"":" ");
			 write << endl;
		 }
	 }
	 write.close();
	  //dont work
	  
  }
  }// writes image to file if image is valid, does nothing
                                           // if it is invalid
  
  // setters make no judgments about the validity of the data
  std::string PPMimage::getMagicNumber() const{
	  return magic;
  }
  void PPMimage::setMagicNumber(const std::string a ){
	  magic = a;
  }//a = p3
  int  PPMimage::getWidth() const{
	  return width;
  }
  void PPMimage::setWidth(const int a){
	  width = a;
  }
  int  PPMimage::getHeight() const{
	  return height;
	  }
  void PPMimage::setHeight(const int a){
	  height = a;
  }
  int  PPMimage::getMaxColor() const{
	  return maxColor;
  }
  void PPMimage::setMaxColor(const int a){
	  maxColor = a;
  }//a =255
  
  int  *PPMimage::getPixels() const{//dont work
	  int *pixx = new int[width*height*3];
	  for(int i = 0; i<(width*height*3);i++){
		  pixx[i] = pixels[i];
	  }
	  return pixx;
  }	  			  // returns a copy of the pixel array
  void PPMimage::setPixels(const int *array, const int w, const int h){//dont work	
		
		int arr = w*h*3;
		pixels = new int[arr];
		for(int j = 0; j<arr;j++){
				pixels[j] = array[j];
			}
		
		width = w;
		height = h;  
  } // copies pixel array to object; assumes
	bool PPMimage::isValid() const{
	  if ((magic=="P3")&&(width>0)&&(height>0)&&(maxColor>=0)&&(maxColor<=255)&&(pixels!=NULL)){
		return true;
	  }
	  else{
		return false;
	  }		
	}
    
	int PPMimage::getRed(const int row, const int col) const{
		int red=0;
		red = width*row*3 + col*3;
		return pixels[red];
  }
  int PPMimage::getGreen(const int row, const int col) const{
		int red=0;
		red = (width*row*3) + (col*3) +1;
		return pixels[red];
  }
  int PPMimage::getBlue(const int row, const int col) const{
	  int red=0;
		red = (width*row*3) + (col*3)+2;
		return pixels[red];}

  int *PPMimage::getPixel(const int row, const int col) const{

	  int* pix = new int[2];
	  pix[0]=pixels[(width*row*3) + (col*3)];
	 // cout<<pix[0] << "\n";
	  
	  pix[1]=pixels[(width*row*3) + (col*3) +1];
	 // cout<<pix[1]<< "\n";
	  pix[2] =pixels[(width*row*3) + (col*3)+2]; 
	  //cout<<pix[2] << "\n";
	  return pix;
	 
  }
                                                     // with order RGB
  void PPMimage::setPixel(const int *pixel, const int row, const int col){
	  int red = width*row*3 + col*3;
	  int green = (width*row*3) + (col*3) +1;
	  int blue = (width*row*3) + (col*3)+2;
	  
	  pixels[red] = *(pixel);
	  pixels[green] = *(pixel+1);
	  pixels[blue] = *(pixel+2);
	  
  }
  


		
		 
      // assumes pixel is stored as an array of 3 values with order RGB
                                                    // w,h are the width, height of image; sets
                                                         // object width to w, height to h
 
  
  
  
  
