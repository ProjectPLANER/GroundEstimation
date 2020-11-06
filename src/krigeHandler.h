/**
 * @author emrchi001@myuct.ac.za
 * @date August 2020
 * 
 * kriging interpolation handler
**/

#ifndef _CE_KRIGE__
#define _CE_KRIGE__

#include "GsTL/kriging.h"
#include "GsTL/cdf_estimator.h"
#include "GsTL/cdf.h"
#include <vector>
#include <opencv2/opencv.hpp>
#include <algorithm>


namespace krige_ce{
	/**
	 * 	<!--
	 *	Class name: -->@class Node
	 * 	<!--
	 *	Written by:	-->@author GsTL-1.2.1 (Nicolas Remy. Stanford University)
	 * 	<!--
	 *	Purpose: -->@brief
	 *		Objects of this class type will store 2-dimensional coordinates of a 
	 *		point in loc_ and its value in pval_. The program which uses this 
	 *		class can declare and initialise Node objects, access loc_ and pval_, 
	 *		and compare the positions of 2 Node objects.
	 * 
	 * 	@internal
	 *	Member functions:
	 *      Node
	 *          The constructor accepts from the calling program, initial values 
	 *			for loc_ and pval_. Defaults initial values are: loc_ is set to 
	 *			the origin, pval_ == 0.
	 *      location
	 *			This function returns the value of loc_.
	 *		property_value
	 *			This function returns a reference to pval_.
	 *		operator==(const Node & rhs)
	 *			This function compares the coordinates of 2 Node objects. Returns 
	 *			true if they are equal.
	 *
	 * 	Member data:
	 *      loc_
	 *          Coordinates of the Node in a 2-dimensional plane.
	 *		pval_
	 *			Value at the Node coordinates in the 2-dimensional plane.
	 */
	class Node{
		public:
		  typedef double property_type;
		  typedef cv::Point2i location_type;

		  Node():pval_(0) { loc_ = location_type(0,0); }
		  Node(int x, int y, property_type pval)
		  	:pval_(pval) { loc_ = location_type(x,y); }
		  Node(cv::Point2i loc, property_type pval): pval_(pval), loc_(loc) {}
		  inline location_type location() const { return loc_; }
		  inline property_type& property_value(){return pval_;}
		  inline const property_type& property_value() const {return pval_;}
		  bool operator==(const Node & rhs) const
		  	{return rhs.loc_ == this->loc_ && rhs.pval_ == this->pval_;}

		private:
		  location_type loc_;
		  property_type pval_;
	};

	/**
	 * 	<!--
	 *	Class name: -->@class neighbourhood
	 * 	<!--
	 *	Written by:	-->@author emrchi001@myuct.ac.za; 
	 *						   GsTL-1.2.1 (Nicolas Remy. Stanford University)
	 * 	<!--
	 *	Purpose: -->@brief
	 *		Objects of this class store Node objects. The program which uses this 
	 *		class can declare and initialise neighbourhood objects, add node objects 
	 *		to the neighbourhood, iterate through Node objects in the neighbourhood, 
	 *		access the size of the neighbourhood, and access the Node objects in the 
	 *		neighbourhood.
	 *	
	 *	@see std::vector
	 * 
	 * 	@internal
	 *	Member functions:
	 *      neighbourhood
	 *          This constructor accepts from the calling program, an initial value 
	 *			for the neighbourhood size n.
	 *      add_node
	 *			This function adds a node specified by the caller to the calling 
	 *			neighbourhood object.
	 *      begin
	 *			This function returns a pointer to the first Node in the calling 
	 *			neighbourhood object.
	 *      end
	 *			This function returns a pointer to the memory address after the last 
	 *			Node in the calling neighbourhood object.
	 *      size
	 *			This function returns the number of Node objects in the calling 
	 *			neighbourhood object.
	 *      is_empty
	 *			This function return @arg c true if there are nodes in the calling 
	 *			neighbourhood object.
	 *      operator[]
	 *			This function accepts from the calling program an integer index 
	 *			location and returns the Node at that location. @arg c i must be 
	 *			positive and smaller than the size of the calling neighbourhood object.
	 *
	 * 	Member data:
	 *      vec
	 *          Vector that stores the Node objects.
	 */
	class neighbourhood{
		public:
		  std::vector<Node> vec;

		  typedef std::vector<Node>::iterator iterator;
		  typedef std::vector<Node>::const_iterator const_iterator;

		  neighbourhood(){vec = std::vector<Node>();}
		  neighbourhood(size_t n){vec = std::vector<Node>(n);}

		  void add_node(Node n){vec.push_back(n);};
		  iterator begin(){return vec.begin();};
		  iterator end(){return vec.end();};
		  const_iterator begin() const {return vec.begin();};
		  const_iterator end() const {return vec.end();};
		  unsigned int size() const {return vec.size();}
		  bool is_empty() const {return vec.empty();}
		  Node & operator[](size_t i) {return vec[i];}
		  const Node & operator[](size_t i) const {return vec[i];}
	};

	/**
	 * 	<!--
	 *	Class name: -->@class covariance--
	 * 	<!--
	 *	Written by:	-->@author GsTL-1.2.1 (Nicolas Remy. Stanford University)
	 * 	<!--
	 *	Purpose: -->@brief
	 *		This functor calculates the covariance between 2 points on a plane.
	 * 
	 * 	@internal
	 *	Member functions:
	 *      operator(const cv::Point2i& P1,const cv::Point2i& P2)
	 *          This function returns the covariance between the points P1 and P2.
	 */
	class covariance{
		public:
		  /** @param P1 cv::Point2i @param P2 cv::Point2i @return covariance between P1 and P2 */
		  inline double operator()(const cv::Point2i& P1,const cv::Point2i& P2) const {
		    double h=sqrt(pow(P1.x-P2.x,2)+pow(P1.y-P2.y,2));
		    double a=10;
		    double c=1.0;
		    return c * exp(-3*h/a);
		  } 
	};

	neighbourhood convertForKrige(const cv::Mat & data, const double naValue);
	int interpolate(cv::Mat & data, const double naValue, const int blockRadius, const double ignore);
	int iterate(cv::Mat & data, const double naValue, const int blockRadius, const double ignore);
	int krige(cv::Point2i & missing, const neighbourhood & N, std::vector<float> & weights);
	// cv::Mat covarianceMatrix(const neighbourhood & N);
}

#endif