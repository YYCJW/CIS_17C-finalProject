/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mazebox.h
 * Author: Yan
 *
 * Created on June 12, 2022, 10:37 AM
 */

#ifndef MAZEBOX_H
#define MAZEBOX_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<list>
#include<string>

using namespace std;
typedef struct SBox
{
public:
	SBox(){};
	SBox(int row,int col,char val)
	{
		x = row;
		y = col;
		value = val;
	}
public:
	int x;//row
	int y;//column
	int visited;
	char value;
}SBox;

#endif /* MAZEBOX_H */

