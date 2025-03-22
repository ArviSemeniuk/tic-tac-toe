#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED


// function to retrieve the vlaues of the diagonals and store then in a 1D vector
vector<string> collectDiag(const vector<vector<string>> grid, const bool collectLeftDiag);
size_t getGridSize(const vector<vector<string>>& grid);


#endif // !COMMON_H_INCLUDED