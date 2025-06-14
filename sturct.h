#pragma once
#include <vector>


using namespace std;

struct CircleInfo
{
	float fcx;
	float fcy;
	float fradius;
	bool bvalid;
};

struct POINTINFO
{
	vector<POINT> Points;
	vector<int> Pointsize;
	int iColor;
};