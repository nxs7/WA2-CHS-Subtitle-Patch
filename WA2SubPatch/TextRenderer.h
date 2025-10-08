#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

const int SCREEN_WIDTH = 1280;
const int SUBTITLE_TOP = 40;

const int FONT_SIZE = 28;
const int FONT_STROKE = 2;
const int FONT_OCCUPATION = FONT_SIZE + 2 * FONT_STROKE;
const int FONT_PER_LINE = 20;

struct TextRenderer
{
    LPDIRECT3DDEVICE9 device;
    LPDIRECT3DTEXTURE9 texture;
    LPDIRECT3DTEXTURE9 subtitle;
    LPD3DXSPRITE sprite;
    D3DCOLOR color;
    D3DXVECTOR3 position;

    TextRenderer() = default;
    TextRenderer(LPDIRECT3DDEVICE9);

    void renderText(std::vector<short>);
    void update();
};