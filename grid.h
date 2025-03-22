#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

vector<vector<string>> createDisplayGrid();
vector<vector<string>> showGrid(const vector<vector<string>>& matrix, const size_t& gridSize);
vector<vector<string>> updateGrid(vector<vector<string>>& oldGrid, const int& playerMove, const string& symbol, const bool& isHuman, const vector<vector<string>>& helpGrid, const size_t& gridSize);
size_t getGridSize(const vector<vector<string>>& grid);

#endif // !GRID_H_INCLUDED