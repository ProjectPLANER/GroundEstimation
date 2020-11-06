To compile, navigate to the project folder in terminal and type the command "make".
The program is compiled used CMake and C++ compiler GCC.

USAGE:
./interpolation_main <-a0/1> <DEM_Path> <NoValue> <Mask_Path> [-i0/1] 

- "-a" tag:	 Can take value 1 (Aerobotics data) or 0.
- DEM_Path:	 Path to full dem .tif image.
- NoValue:	 Special value used to represent missing information, -1 if none.
- Mask_Path: Path to tree mask dem .tif image.
- "-i" tag:	 Can take value 0 (do not invert mask) or 1 (invert mask).

NOTE: You should have OpenCV and libtiff installed to compile the programme. 
Programme tested and compiled using 
- OpenCV version 4.2.0	
https://opencv.org/
https://www.learnopencv.com/install-opencv-4-on-ubuntu-18-04/
- libtiff version 4.1.0
http://www.libtiff.org/
