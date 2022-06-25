#include "SubLoader.h"

DialogueMap loadSub()
{
	int magicNumber, dialogueCount, subCount, stringLength, id;
	short character;
	std::ifstream file("subtext.dat", std::ios::binary);
	DialogueMap dialogues;
	if (!file)
	{
		MessageBoxW(NULL, L"subtext.dat£ºÕÒ²»µ½ÎÄ¼ş¡£", L"×ÖÄ»´íÎó", MB_OK);
		exit(1);
	}

	file.read((char*)&magicNumber, 4);
	if (magicNumber != 0x3773786E)
	{
		MessageBoxW(NULL, L"subtext.dat£º¸ñÊ½´íÎó¡£", L"×ÖÄ»´íÎó", MB_OK);
		exit(1);
	}

	file.read((char*)&dialogueCount, 4);
	dialogues.reserve(dialogueCount);
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
		dialogues[id] = subtitles;
	}
	if (file.gcount() != 2) // checks if file ended unexpectedly. ignores possible remaining section.
	{
		MessageBoxW(NULL, L"subtext.dat£ºÊı¾İ´íÎó¡£", L"×ÖÄ»´íÎó", MB_OK);
		exit(1);
	}
	return dialogues;
}