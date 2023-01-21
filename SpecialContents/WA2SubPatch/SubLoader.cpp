#include "SubLoader.h"

void loadSub(DialogueMap* subs, DialogueMap* songs)
{
	int magicNumber, dialogueCount, subCount, stringLength, id;
	short character;
	std::ifstream file("subtext.dat", std::ios::binary);
	if (!file)
	{
		MessageBoxW(NULL, L"subtext.dat£ºÕÒ²»µ½ÎÄ¼þ¡£", L"×ÖÄ»´íÎó", MB_OK);
		exit(1);
	}

	file.read((char*)&magicNumber, 4);
	if (magicNumber != 0x376E7378)
	{
		MessageBoxW(NULL, L"subtext.dat£º¸ñÊ½´íÎó¡£", L"×ÖÄ»´íÎó", MB_OK);
		exit(1);
	}

	// voice dramas
	file.read((char*)&dialogueCount, 4);
	subs->reserve(dialogueCount);
	for (int i = 0; i < dialogueCount; i++)
	{
		file.read((char*)&id, 4);
		file.read((char*)&subCount, 4);
		std::vector<Subtitle> subtitles;
		subtitles.reserve(subCount);
		for (int j = 0; j < subCount; j++)
		{
			Subtitle sub;
			file.read((char*)&sub.begin, 4);
			file.read((char*)&sub.end, 4);
			file.read((char*)&stringLength, 4);
			sub.text.reserve(stringLength);
			for (int k = 0; k < stringLength; k++)
			{
				file.read((char*)&character, 2);
				sub.text.push_back(character);
			}
			file.read((char*)&stringLength, 4);
			sub.text2.reserve(stringLength);
			for (int k = 0; k < stringLength; k++)
			{
				file.read((char*)&character, 2);
				sub.text2.push_back(character);
			}
			subtitles.push_back(sub);
		}
		(*subs)[id] = subtitles;
	}

	// songs
	file.read((char*)&dialogueCount, 4);
	songs->reserve(dialogueCount);
	for (int i = 0; i < dialogueCount; i++)
	{
		file.read((char*)&id, 4);
		file.read((char*)&subCount, 4);
		std::vector<Subtitle> subtitles;
		subtitles.reserve(subCount);
		for (int j = 0; j < subCount; j++)
		{
			Subtitle sub;
			file.read((char*)&sub.begin, 4);
			file.read((char*)&sub.end, 4);
			file.read((char*)&stringLength, 4);
			sub.text.reserve(stringLength);
			for (int k = 0; k < stringLength; k++)
			{
				file.read((char*)&character, 2);
				sub.text.push_back(character);
			}
			subtitles.push_back(sub);
		}
		(*songs)[id] = subtitles;
	}
	if (file.gcount() != 2) // checks if file ended unexpectedly. ignores possible remaining section.
	{
		MessageBoxW(NULL, L"subtext.dat£ºÊý¾Ý´íÎó¡£", L"×ÖÄ»´íÎó", MB_OK);
		exit(1);
	}
}