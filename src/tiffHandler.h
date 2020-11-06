
/**
 * @author emrchi001@myuct.ac.za <br>
 * @date July 2020 <br>
 * 
 * tiff file handler
**/

#ifndef __CE_TIFF__
#define __CE_TIFF__

#include "tiffio.h"
#include <opencv2/opencv.hpp>
#include <string>

#define TIFFTAG_33550 33550
#define TIFFTAG_33922 33922
#define TIFFTAG_34735 34735
#define TIFFTAG_34736 34736
#define TIFFTAG_34737 34737
#define TIFFTAG_42113 42113


/**
 * 	<!--
 *	Class name: -->@class tiffHandler
 * 	<!--
 *	Written by:	-->@author emrchi001@myuct.ac.za 
 * 	<!--
 *	Purpose: -->@brief
 *		Objects of this class type will store the grid data of a single-band tiff image. The program
 *      which uses this class can declare and initialise tiffHandler objects, have read-only access to 
 *		the following attribute data: image height, image width, grid data, filename --- read a tiff 
 *		file, write a tiff file, mask the contents of the tiff data, replace the value of tiff tags with 
 *		values from any tiffHandler object.
 * 
 * 	@internal
 *	Member functions:
 *      tiffHandler(cv::Mat && grid, const std::string fileName)
 *          This constructor accepts from the calling program, initial values for grid and fileName.
 *      tiffHandler(cv::Mat & grid, const std::string fileName)
 *          <b>See</b> {@link tiffHandler::tiffHandler(cv::Mat&&grid, const std::string fileName) tiffHandler}.
 *      tiffHandler(const std::string fileName)
 *          This constructor accepts from the calling program, an initial string for fileName. <b>See</b> 
 *			{@link tiffHandler::tiffHandler(cv::Mat&&grid, const std::string filename) tiffHandler}.
 *      tiffHandler()
 *          This constructor does not accept any arguments.
 *      tiffHandler(tiffHandler && rhs)
 *          This is a move constructor.
 *      tiffHandler(const tiffHandler & rhs)
 *          This is a copy constructor.
 *      operator=(const tiffHandler & rhs)
 *          This assignment function deep copies the contents of rhs into the calling object.
 *      operator=(tiffHandler && rhs)
 *          This is a move assignment operator.
 *      getWidth()
 *          This function returns a constant value equal to the image width.
 *      getHeight()
 *          This function returns a constant value equal to the image height.
 *      data()
 *          This function returns a constant reference to the image data.
 *      name()
 *          This function returns a constant reference to fileName.
 *      mask(const tiffHandler & tH, const double v)
 *          This function replaces all values in TIFFgrid with v using tH as a mask.
 *      copyTags(const tiffHandler & tH, bool aer=false)
 *          This function replaces the tag values of the calling object's tiff image with tH's tiff tag values.
 *      saveTiff(TIFF* tempTiff, const tiffHandler & tH)
 *          This function writes the contents of tH.TIFFgrid to an already opened tiff file.
 *
 * 	Member data:
 *      TIFFgrid
 *          cv::Mat variable containing tiff image data.
 *      fileName
 *          Path to tiff image.
 */
class tiffHandler{
	private:
		cv::Mat TIFFgrid;
		std::string fileName;
	public:
		//constructors
        tiffHandler(cv::Mat && grid, const std::string fileName);   //non-default constructor,[x]
        tiffHandler(cv::Mat & grid, const std::string fileName);    //non-default constructor,[x]
        tiffHandler(const std::string fileName);					//non-default constructor[x]
        ~tiffHandler();                                 			//a destructor,[x]
        tiffHandler(tiffHandler && rhs);                			//a move constructor,[x]
        tiffHandler(const tiffHandler & rhs);           			//a copy constructor,[x]
        //assignment operators
        tiffHandler & operator=(const tiffHandler & rhs);   		//an assignment operator[x] and
        tiffHandler & operator=(tiffHandler && rhs);        		//a move assignment operator[x]
        //accessors
        const int getWidth(void) const;
        const int getHeight(void) const;
        const cv::Mat & data(void) const;
        const std::string & name(void) const;

		//member functions
		void mask(const tiffHandler & tH, const double v);
		void copyTags(const tiffHandler & tH, bool aer=false);
	protected:
		/**
		 * <!--
		 * NAME OF FUNCTION: saveTiff-->
		 * CREDIT: emrchi001@myuct.ac.za
		 * <!--
		 * PURPOSE:-->@brief
		 *    This function writes the contents of tH.TIFFgrid to an already opened tiff file.
		 * 
		 * <!--
		 * PARAMETERS:
		 * 			name 		type 		value/reference 	description
		 * 			----------------------------------------------------------------------------------------->
		 * @param	tempTiff 	TIFF*		value			--- Pointer to open tiff image file. Ensure it 
		 *														points to an open tiff file. No error checks. 
		 *														Make sure you close the tiff file later in the 
		 * 														program.
		 * @param 	tH 			tiffHandler const reference --- tiffHandler object containing image data.
		 * 
		 * <!--
		 * RETURN VALUE:
		 * 			type 	value/reference 	description
		 * 			----------------------------------------------------------------------------------------->
		 * @return	void
		 * 
		 * @see #copyTags, TIFFWriteScanline
		*/
		void saveTiff(TIFF* tempTiff, const tiffHandler & tH){
			//writeToFile
			void * sl = malloc(tH.data().elemSize1()*tH.getWidth());
			for(int i = 0; i < tH.getHeight(); ++i){
				memcpy(sl, tH.data().ptr(i), tH.getWidth() * tH.data().elemSize1());
    			TIFFWriteScanline(tempTiff, sl, i, 0);
			}
			free (sl);
		}
};

// Aerobotics special tiff tags
static const TIFFFieldInfo xtiffFieldInfo[] = {
    { TIFFTAG_33550, 1, 1, TIFF_DOUBLE, FIELD_CUSTOM,	0, 0, const_cast<char*>("TIFFTAG_33550") },
    { TIFFTAG_33922, 1, 1, TIFF_DOUBLE, FIELD_CUSTOM,	0, 0, const_cast<char*>("TIFFTAG_33922") },
    { TIFFTAG_34735, 1, 1, TIFF_SHORT, FIELD_CUSTOM,	0, 0, const_cast<char*>("TIFFTAG_34735") },
    { TIFFTAG_34736, 1, 1, TIFF_DOUBLE, FIELD_CUSTOM,	0, 0, const_cast<char*>("TIFFTAG_34736") },
    { TIFFTAG_34737, 1, 1, TIFF_ASCII, FIELD_CUSTOM,	0, 0, const_cast<char*>("TIFFTAG_34737") },
    { TIFFTAG_42113, 1, 1, TIFF_ASCII, FIELD_CUSTOM,	0, 0, const_cast<char*>("TIFFTAG_42113") }
};
static const int NxtiffFieldInfo = 6;


#endif