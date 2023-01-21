#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SUBTITLE_MARGIN = 40;

const int FONT_SIZE = 28;
const int FONT_STROKE = 2;
const int FONT_OCCUPATION = FONT_SIZE + 2 * FONT_STROKE;
const int FONT_PER_LINE = 30;

struct TextRenderer
{
    LPDIRECT3DDEVICE9 device;
    LPDIRECT3DTEXTURE9 subTexture;
    LPDIRECT3DTEXTURE9 songTexture;
    LPD3DXSPRITE sprite;
    D3DCOLOR color;
    D3DXVECTOR3 pos;
    RECT rect;

    TextRenderer() = default;
    TextRenderer(LPDIRECT3DDEVICE9);

    void renderSub(std::vector<short>);
    void renderSecondarySub(std::vector<short>);
    void renderSong(std::vector<short>);
};