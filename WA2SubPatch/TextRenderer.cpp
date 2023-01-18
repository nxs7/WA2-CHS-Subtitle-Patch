#include "TextRenderer.h"

TextRenderer::TextRenderer(LPDIRECT3DDEVICE9 device)
{
	this->device = device;

	if (FAILED(D3DXCreateTextureFromFileExA(device, "subfont.tga", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texture)))
	{
		MessageBoxW(NULL, L"subfont.tga£º¼ÓÔØÊ§°Ü¡£", L"×ÖÄ»´íÎó", MB_OK);
		exit(1);
	}
	D3DXCreateSprite(device, &sprite);

	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	pos.x = 0;
	pos.y = SUBTITLE_TOP - FONT_STROKE;
	pos.z = 0;

	rect.top = 0;
	rect.bottom = FONT_OCCUPATION;
}

void TextRenderer::renderText(std::vector<short> str)
{
	int len = str.size();
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	pos.x = (float)((SCREEN_WIDTH - FONT_SIZE * len) / 2 - FONT_STROKE);
	for (int i = 0; i < len; i++)
	{
		rect.top = FONT_OCCUPATION * (str[i] / FONT_PER_LINE);
		rect.bottom = rect.top + FONT_OCCUPATION;
		rect.left = FONT_OCCUPATION * (str[i] % FONT_PER_LINE);
		rect.right = rect.left + FONT_OCCUPATION;
		sprite->Draw(texture, &rect, NULL, &pos, color);
		pos.x += FONT_SIZE;
	}
	sprite->End();
}