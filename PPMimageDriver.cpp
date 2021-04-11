/*
* Project 4
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
#include <direct.h>
#include <cstdlib>
#include <unistd.h>
#include <tchar.h>
#include <Windows.h>
#include "PPMimage.h"

using namespace std;
using namespace egre246;

int *sort(int num, int *color){
	for(int i = 0;i < num; i++){for(int j = i+1;j<num;j++){if(color[i]>color[j]){int Temp = color[i];color[i] = color[j];color[j] = Temp;}}}return color;}
int median(int num,int *color){
		int w = 0;
		if(num%2==0){w=(color[(num/2)-1]+color[num/2])/2;}else{w = color[num/2];}return w;}
int main(int argc, char* argv[]){ 
   int z = 0;int num = atoi(argv[2]);string files[num];
   cout<<"ERGE246 Project #4 - L. Morro, C. O'Leary\n"<<"File prefix: "<<argv[1]<<"\n"<<"Number of images: "<<argv[2]<<"\nImages:\n";
   int i = 1;string file = "";string i_ = "";int *pixx = new int[1];
   while(i<=num){file = argv[1];
   if(i<=9){i_ = to_string(i);file+="00";file+=i_;file+=".ppm";
   }else if(i<=99&&i>9){i_ = to_string(i);file+="0";file+=i_;file+=".ppm";
	   }else if(i<=999&&i>99){i_ = to_string(i);file+=i_;file+=".ppm";
	   }cout<<i<<": "<<file<<"; "<<"valid? ";files[i-1]=file;PPMimage image(file);
	   if(image.isValid()){cout<<"yes\n";
	   }else{cout<<"no\n";
	   }i++;
}
	PPMimage image(files[0]);
	int *red = new int[image.getWidth()*image.getHeight()*num];
	int *green = new int[image.getWidth()*image.getHeight()*num];
	int *blue = new int[image.getWidth()*image.getHeight()*num];
	int *red_ = new int[num];int *green_ = new int[num];int *blue_ = new int[num];
	int *final_ = new int[image.getWidth()*image.getHeight()*3];
	int *finalgrey= new int[image.getWidth()*image.getHeight()*3];
	int *pixl = new int[3];int x = 0;
	for(int h = 0; h<num;h++){
		PPMimage image(files[h]);
		for(int i = 0;i<image.getHeight();i++){
			for(int j = 0;j<image.getWidth();j++){
				red[x]=image.getRed(i,j);
				green[x]=image.getGreen(i,j);
				blue[x]=image.getBlue(i,j);
				x++;}}}x=0;
	for(int i = 0;i<image.getWidth()*image.getHeight();i++){
		for(int j = 0; j<num;j++){
			red_[j]=red[image.getWidth()*image.getHeight()*j+i];
			green_[j]=green[image.getWidth()*image.getHeight()*j+i];
			blue_[j]=blue[image.getWidth()*image.getHeight()*j+i];
		}
		red_=sort(num,red_);blue_=sort(num,blue_);green_=sort(num,green_);
		final_[x]=median(num,red_);
		final_[x+1]=median(num,green_);
		final_[x+2]=median(num,blue_);
		finalgrey[x]=(final_[x]*0.299)+(final_[x+1]*0.587)+(final_[x+2]*0.114);
		finalgrey[x+1]=(final_[x]*0.299)+(final_[x+1]*0.587)+(final_[x+2]*0.114);
		finalgrey[x+2]=(final_[x]*0.299)+(final_[x+1]*0.587)+(final_[x+2]*0.114);
		x+=3;	
	}		
	image.setPixels(final_,image.getWidth(),image.getHeight());
	string finale = argv[1];
	finale+=".ppm";
	image.writeImage(finale);
	
	image.setPixels(finalgrey,image.getWidth(),image.getHeight());
	string grey = argv[1];
	grey+="GREY.ppm";
	image.writeImage(grey);
	cout<<"filtered output file: "<< finale<<"\ngreyscale filtered output file: "<< grey;
}
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
  