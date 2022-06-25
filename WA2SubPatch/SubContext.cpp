#include "SubContext.h"

SubContext::SubContext(LPDIRECT3DDEVICE9 device)
{
	renderer = TextRenderer(device);
	this->device = device;

	beginTick = GetTickCount64();
	dialogues = loadSub();
	subIndex = 0;
	isPlaying = false;
}

bool SubContext::tryPlay(int id, bool voice)
{
	if (dialogues.count(id))
	{
		sub = dialogues[id];
		subIndex = 0;
		beginTick = GetTickCount64();
		isPlaying = true;
		isVoicePlaying = voice;
		isDisplaying = false;
		return true;
	}
	return false;
}

void SubContext::update()
{
	if (isPlaying)
	{
		ULONGLONG ticks = GetTickCount64() - beginTick;

		// update status
		if (isDisplaying && ticks > sub[subIndex].end)
		{
			isDisplaying = false;
			subIndex++;
			if (subIndex == sub.size())
			{
				isPlaying = false;
				return;
			}
		}
		if (!isDisplaying && ticks >= sub[subIndex].begin)
		{
			isDisplaying = true;
		}
		// render text
		if (isDisplaying)
			renderer.renderText(sub[subIndex].text);
	}
}