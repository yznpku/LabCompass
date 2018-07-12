///////////////////////////////////////////////////////////////////////////////
// Hungarian.h: Header file for Class HungarianAlgorithm.
// 
// This is a C++ wrapper with slight modification of a hungarian algorithm implementation by Markus Buehren.
// The original implementation is a few mex-functions for use in MATLAB, found here:
// http://www.mathworks.com/matlabcentral/fileexchange/6543-functions-for-the-rectangular-assignment-problem
// 
// Both this code and the orignal code are published under the BSD license.
// by Cong Ma, 2016
// 

#ifndef HUNGARIAN_H
#define HUNGARIAN_H


class HungarianAlgorithm
{
public:
	HungarianAlgorithm();
	~HungarianAlgorithm();

  template<template<class> class Container1, template<class> class Container2>
  double Solve(Container1<Container1<double>>& DistMatrix, Container2<int>& Assignment);

private:
	void assignmentoptimal(int *assignment, double *cost, double *distMatrix, int nOfRows, int nOfColumns);
	void buildassignmentvector(int *assignment, bool *starMatrix, int nOfRows, int nOfColumns);
	void computeassignmentcost(int *assignment, double *cost, double *distMatrix, int nOfRows);
	void step2a(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim);
	void step2b(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim);
	void step3(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim);
	void step4(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim, int row, int col);
	void step5(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim);
};

template<template<class> class Container1, template<class> class Container2>
double HungarianAlgorithm::Solve(Container1<Container1<double>>& DistMatrix, Container2<int>& Assignment)
{
  unsigned int nRows = DistMatrix.size();
  unsigned int nCols = DistMatrix[0].size();

  double *distMatrixIn = new double[nRows * nCols];
  int *assignment = new int[nRows];
  double cost = 0.0;

  // Fill in the distMatrixIn. Mind the index is "i + nRows * j".
  // Here the cost matrix of size MxN is defined as a double precision array of N*M elements.
  // In the solving functions matrices are seen to be saved MATLAB-internally in row-order.
  // (i.e. the matrix [1 2; 3 4] will be stored as a vector [1 3 2 4], NOT [1 2 3 4]).
  for (unsigned int i = 0; i < nRows; i++)
    for (unsigned int j = 0; j < nCols; j++)
      distMatrixIn[i + nRows * j] = DistMatrix[i][j];

  // call solving function
  assignmentoptimal(assignment, &cost, distMatrixIn, nRows, nCols);

  Assignment.clear();
  for (unsigned int r = 0; r < nRows; r++)
    Assignment.push_back(assignment[r]);

  delete[] distMatrixIn;
  delete[] assignment;
  return cost;
}

#endif
