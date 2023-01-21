#include "TextRenderer.h"

TextRenderer::TextRenderer(LPDIRECT3DDEVICE9 device)
{
	this->device = device;

	if (FAILED(D3DXCreateTextureFromFileExA(device, "subfont.tga", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &subTexture)))
	{
		MessageBoxW(NULL, L"subfont.tga£º¼ÓÔØÊ§°Ü¡£", L"×ÖÄ»´íÎó", MB_OK);
		exit(1);
	}
	if (FAILED(D3DXCreateTextureFromFileExA(device, "songfont.tga", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &songTexture)))
	{
		MessageBoxW(NULL, L"songfont.tga£º¼ÓÔØÊ§°Ü¡£", L"×ÖÄ»´íÎó", MB_OK);
		exit(1);
	}
	D3DXCreateSprite(device, &sprite);

	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	rect.top = 0;
	rect.bottom = FONT_OCCUPATION;
}

void TextRenderer::renderSub(std::vector<short> str)
{
	int len = str.size();
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	pos.x = (float)((SCREEN_WIDTH - FONT_SIZE * len) / 2 - FONT_STROKE);
	pos.y = (float)(SCREEN_HEIGHT - SUBTITLE_MARGIN - FONT_SIZE);
	for (int i = 0; i < len; i++)
	{
		rect.top = FONT_OCCUPATION * (str[i] / FONT_PER_LINE);
		rect.bottom = rect.top + FONT_OCCUPATION;
		rect.left = FONT_OCCUPATION * (str[i] % FONT_PER_LINE);
		rect.right = rect.left + FONT_OCCUPATION;
		sprite->Draw(subTexture, &rect, NULL, &pos, color);
		pos.x += FONT_SIZE;
	}
	sprite->End();
}

void TextRenderer::renderSecondarySub(std::vector<short> str)
{
	int len = str.size();
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	pos.x = (float)((SCREEN_WIDTH - FONT_SIZE * len) / 2 - FONT_STROKE);
	pos.y = (float)(SCREEN_HEIGHT - SUBTITLE_MARGIN - FONT_SIZE * 2 - FONT_STROKE);
	for (int i = 0; i < len; i++)
	{
		rect.top = FONT_OCCUPATION * (str[i] / FONT_PER_LINE);
		rect.bottom = rect.top + FONT_OCCUPATION;
		rect.left = FONT_OCCUPATION * (str[i] % FONT_PER_LINE);
		rect.right = rect.left + FONT_OCCUPATION;
		sprite->Draw(subTexture, &rect, NULL, &pos, color);
		pos.x += FONT_SIZE;
	}
	sprite->End();
}

void TextRenderer::renderSong(std::vector<short> str)
{
	int len = str.size();
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	pos.x = (float)(SCREEN_WIDTH - FONT_SIZE * len - SUBTITLE_MARGIN - FONT_STROKE);
	pos.y = (float)(SUBTITLE_MARGIN - FONT_STROKE);
	for (int i = 0; i < len; i++)
	{
		rect.top = FONT_OCCUPATION * (str[i] / FONT_PER_LINE);
		rect.bottom = rect.top + FONT_OCCUPATION;
		rect.left = FONT_OCCUPATION * (str[i] % FONT_PER_LINE);
		rect.right = rect.left + FONT_OCCUPATION;
		sprite->Draw(songTexture, &rect, NULL, &pos, color);
		pos.x += FONT_SIZE;
	}
	sprite->End();
}