/**
 * @author emrchi001@myuct.ac.za
 * @date August 2020
 * <!--
 * Contextual Void Patching interpolation handler header file <br>
 * -------------------------------------------------------------->
 * <!--
 * PURPOSE: -->@details
 * The functions in this namespace handle all manipulation of data 
 * required to perform the contextual void patching interpolation method.
 *
 * @anchor DIRECTIONS
 * @static cv::Point2i <b>u</b>(0,1) --- static variable representing 'u' direction vector <br>
 * @static cv::Point2i <b>v</b>(1,0) --- static variable representing 'v' direction vector <br>
 * @static cv::Point2i <b>w</b>(-1,1) --- static variable representing 'w' direction vector <br>
 * @static cv::Point2i <b>t</b>(1,1) --- static variable representing 't' direction vector <br>
 * @internal
 * FUNCTIONS:
 *  
 * findVoids
 *    will locate the end points on any continuous line of missing data points in all {@link DIRECTIONS directions} 
 *	  and store them.
 *  
 * hermiteSmooth
 *    will perform hermite curve interpolation between given points in the provided direction
 *  
 * interpolate
 *    will estimate the missing values of "dataset" indicated by "mask" using the Contextual Void Patching algorithm
**/

#ifndef __CE_CVP__
#define __CE_CVP__

#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector>
#include <utility>
#include <mutex>

namespace cvp_ce{
	typedef std::vector< std::pair<cv::Point2i, cv::Point2i> > curvePatch;
	static std::mutex u_mtx, v_mtx, w_mtx, t_mtx;
	// directions
	static const cv::Point2i u( 0, 1 ); //2d int point
	static const cv::Point2i v( 1, 0 ); 
	static const cv::Point2i w(-1, 1 ); 
	static const cv::Point2i t( 1, 1 ); 
	// methods:
	void findVoids(const cv::Mat & grid, const double noValue, curvePatch & u_curve, curvePatch & v_curve, curvePatch & w_curve, curvePatch & t_curve);
	void hermiteSmooth(cv::Mat & grid, const double noValue, const cv::Point2i beg, const cv::Point2i end, const cv::Point2i direction);
	
	void interpolate(cv::Mat & grid, const cv::Mat & mask);
}

#endif