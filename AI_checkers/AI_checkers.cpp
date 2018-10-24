// AI_checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>

#include <map>
#include <stack>
#include "graph.h"

/*
const int m[SIZE][SIZE] = {
	{1, 1, 1, -1, -1},
	{1, 1, 1, -1, -1},
	{1, 1, 0,	2, 2},
	{-1, -1, 2, 2, 2},
	{-1, -1, 2, 2, 2}
};

const int result[SIZE][SIZE] = {
	{2, 2, 2, -1, -1},
	{2, 2, 2, -1, -1},
	{2, 2, 0,	1, 1},
	{-1, -1, 1, 1, 1},
	{-1, -1, 1, 1, 1}
};*/



const int m[SIZE][SIZE] = {
	{1, 1, -1},
	{1, 0, 2},
	{-1, 2, 2},
};

const int result[SIZE][SIZE] = {
	{2, 2, -1},
	{2, 0, 1},
	{-1, 1, 1},
};

/*
const int m[SIZE][SIZE] = {
	{1, 2, -1},
	{3, 0, 4},
	{-1, 5, 6},
};

const int result[SIZE][SIZE] = {
	{6, 5, -1},
	{4, 0, 3},
	{-1, 2, 1},
};*/

int main()
{
	std::vector<std::vector<int>> start = std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE));

	for(u32 i = 0; i < SIZE; ++i) {
		for (u32 j = 0; j < SIZE; ++j) {
			start[i][j] = m[i][j];
		}
	}

	std::vector<std::vector<int>> goal = std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE));

	for(u32 i = 0; i < SIZE; ++i) {
		for (u32 j = 0; j < SIZE; ++j) {
			goal[i][j] = result[i][j];
		}
	}

	graph *g = new graph();
	//g->depth_first_traversal(start, goal);
	//g->breadth_first_traversal(start, goal);
	g->A_star_search(start, goal);

	delete g;

	system("pause");
    return 0;

}