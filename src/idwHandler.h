/**
 * @author emrchi001@myuct.ac.za
 * @date August 2020 <br>
 * <!--
 * Inverse Distance Weighting interpolation handler
 * ------------------------------------------------>
 * <!--
 * PURPOSE: -->@details
 * The functions in this namespace handle all manipulation of data 
 * required to perform inverse distance weighting interpolation method.
 *
 * @anchor THRESHOLD
 * @static double <b>SURROUND_THRESHOLD</b> --- with default value of 0.4 used to determine if there are enough 
 * 												neighbourhood points for estimation
 *
 * @internal
 * FUNCTIONS:
 *  
 * nearestNeighbour
 *    will estimate value for missing data points using values of its nearest neighbours
 *  
 * iterate
 *    will perform one iteration of local modified Shephard algorithm with the neighbourhood radius set to blockRadius
 *  
 * interpolate
 *    will estimate the missing values of "dataset" indicated by "mask" using an iterative version of local 
 *	  modified Shephard algorithm with the neighbourhood radius set to blockRadius   
*/

#ifndef __CE_IDW__
#define __CE_IDW__

#include <opencv2/opencv.hpp>
#include <cmath>
#include <atomic>

namespace idw_ce{
	static double SURROUND_THRESHOLD = 0.4; //range: (0,1]
	void nearestNeighbour(cv::Mat & dataset, const double& noValue, const double& ignore);
	void iterate(cv::Mat & dataset, const cv::Mat & mask, const int blockRadius, const double& noValue, const double& ignore);
	// ignore is value not to use in calculations eg. external points
	int interpolate(cv::Mat & dataset, const cv::Mat & mask, const int blockRadius, const double& noValue, const double& ignore);

}

#endif