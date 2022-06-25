#pragma once

#include <Windows.h>
#include <fstream>
#include <vector>
#include <unordered_map>

struct Subtitle
{
	int begin;
	int end;
	std::vector<short> text;
};

typedef std::unordered_map<int, std::vector<Subtitle>> DialogueMap;

DialogueMap loadSub();
