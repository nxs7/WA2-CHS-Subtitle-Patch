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
    LPDIRECT3DTEXTURE9 subtitle;
    LPDIRECT3DTEXTURE9 secondarySubtitle;
    LPDIRECT3DTEXTURE9 song;
    LPD3DXSPRITE sprite;
    D3DCOLOR color;
    D3DXVECTOR3 subPosition;
    D3DXVECTOR3 secondarySubPosition;
    D3DXVECTOR3 songPosition;

    TextRenderer() = default;
    TextRenderer(LPDIRECT3DDEVICE9);

    void renderSub(std::vector<short>);
    void renderSecondarySub(std::vector<short>);
    void renderSong(std::vector<short>);
    void renderText(LPDIRECT3DTEXTURE9& dest, LPDIRECT3DTEXTURE9 src, std::vector<short>);
    void updateSub();
    void updateSecondarySub();
    void updateSong();
};