#pragma once

#include <vector>
#include <chrono>

#include "TextRenderer.h"
#include "SubLoader.h"

/*
    Context object for the subtitling system.
    This is intended to be used as a singleton, initialized
    as soon as the D3D9 hooks are in place in dllmain.cpp.
*/

struct SubContext
{
    TextRenderer renderer;
    LPDIRECT3DDEVICE9 device;

    std::chrono::steady_clock::time_point beginTime;

    DialogueMap dialogues;
    std::vector<Subtitle> sub;

    unsigned subIndex;

    bool isPlaying;
    bool isVoicePlaying;
    bool isDisplaying;

    SubContext() = default;
    SubContext(LPDIRECT3DDEVICE9 device);
    bool tryPlay(int, bool);
    void update(); // called every frame by d3d9 hook
};