#include "SubContext.h"

SubContext::SubContext(LPDIRECT3DDEVICE9 device)
{
	renderer = TextRenderer(device);
	this->device = device;

	beginTime = std::chrono::steady_clock::now();
	loadSub(&subs, &songs);
	subIndex = 0;
	isSubPlaying = false;
	isSongPlaying = false;
}

bool SubContext::tryPlay(int id)
{
	size_t subCount = subs.count(id);
	size_t songCount = songs.count(id);
	if (subCount || songCount)
	{
		beginTime = std::chrono::steady_clock::now();
		if (subCount)
		{
			sub = subs[id];
			subIndex = 0;
			isSubPlaying = true;
			isSubDisplaying = false;
		}
		else isSubPlaying = false;
		if (songCount)
		{
			song = songs[id];
			songIndex = 0;
			isSongPlaying = true;
			isSongDisplaying = false;
		}
		else isSongPlaying = false;
		return true;
	}
	return false;
}

void SubContext::shiftBeginTime(int ms)
{
	beginTime += std::chrono::milliseconds(ms);
}

void SubContext::update()
{
	if (isSubPlaying)
	{
		int duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - beginTime).count();

		// update status
		if (isSubDisplaying && duration > sub[subIndex].end)
		{
			isSubDisplaying = false;
			subIndex++;
			if (subIndex == sub.size())
			{
				isSubPlaying = false;
				return;
			}
		}
		if (!isSubDisplaying && duration >= sub[subIndex].begin)
		{
			isSubDisplaying = true;
		}
		// render text
		if (isSubDisplaying)
		{
			renderer.renderSub(sub[subIndex].text);
			if (!sub[subIndex].text2.empty())
				renderer.renderSecondarySub(sub[subIndex].text2);
		}
	}
	if (isSongPlaying)
	{
		int duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - beginTime).count();

		// update status
		if (isSongDisplaying && duration > song[songIndex].end)
		{
			isSongDisplaying = false;
			songIndex++;
			if (songIndex == song.size())
			{
				isSongPlaying = false;
				return;
			}
		}
		if (!isSongDisplaying && duration >= song[songIndex].begin)
		{
			isSongDisplaying = true;
		}
		// render text
		if (isSongDisplaying)
			renderer.renderSong(song[songIndex].text);
	}
}