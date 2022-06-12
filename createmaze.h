/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   createmaze.h
 * Author: Yan
 *
 * Created on June 12, 2022, 10:38 AM
 */

#ifndef CREATEMAZE_H
#define CREATEMAZE_H

#include "mazebox.h"

#define  mazeSize 21

class CMazeMap
{
public:
	CMazeMap()
	{
		init();
	};
	
	CMazeMap(const CMazeMap& mazeMap)
	{
		for(int i = 0;i < mazeSize;i++ )
		{
			for(int j = 0;j < mazeSize; j++)
			{
				map[i][j].x = mazeMap.map[i][j].x;
				map[i][j].y = mazeMap.map[i][j].y; 
				map[i][j].value = mazeMap.map[i][j].value;
			}
		}
		
		start = mazeMap.start;
		end = mazeMap.end;
		pepole = mazeMap.pepole;
		mapSize = mazeMap.mapSize;
	}
	
	~CMazeMap()
	{
		listPath.clear();
	}
	
public:
	int init();
	int DFS();
	int Prim_generator();
	int DFS_generator(int x,int y);
	int createMaze();
	int printMaze();
	int findPath();
	int printPath();
	int Move();
	int saveGame(const char* szFile);
	int loadGame(const char* szFile);
	int convertChar(char c,char* szTemp);
public:
	int 	mapSize;
	SBox 	map[mazeSize][mazeSize];
	SBox 	start;
	SBox	end;
	SBox	pepole;
	list<SBox> listPath;
};

#endif /* CREATEMAZE_H */

