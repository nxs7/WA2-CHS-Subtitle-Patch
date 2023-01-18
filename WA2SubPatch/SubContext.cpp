#include "SubContext.h"

SubContext::SubContext(LPDIRECT3DDEVICE9 device)
{
	renderer = TextRenderer(device);
	this->device = device;

	beginTime = std::chrono::steady_clock::now();
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
		beginTime = std::chrono::steady_clock::now();
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
		int duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - beginTime).count();

		// update status
		if (isDisplaying && duration > sub[subIndex].end)
		{
			isDisplaying = false;
			subIndex++;
			if (subIndex == sub.size())
			{
				isPlaying = false;
				return;
			}
		}
		if (!isDisplaying && duration >= sub[subIndex].begin)
		{
			isDisplaying = true;
		}
		// render text
		if (isDisplaying)
			renderer.renderText(sub[subIndex].text);
	}
}