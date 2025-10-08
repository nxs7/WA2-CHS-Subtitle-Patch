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
	subtitle = nullptr;
	D3DXCreateSprite(device, &sprite);

	color = D3DCOLOR_ARGB(255, 255, 255, 255);
	position = { 0, SUBTITLE_TOP - FONT_STROKE, 0 };
}

void TextRenderer::renderText(std::vector<short> str)
{
	int len = str.size();
	if (subtitle)
		subtitle->Release();
	device->CreateTexture(FONT_SIZE * len + FONT_STROKE * 2, FONT_OCCUPATION, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &subtitle, NULL);
	LPDIRECT3DSURFACE9 target, origTarget;
	subtitle->GetSurfaceLevel(0, &target);
	device->GetRenderTarget(0, &origTarget);
	device->SetRenderTarget(0, target);
	device->Clear(0, NULL, D3DCLEAR_TARGET, 0, 1.0f, 0);

	RECT rect;
	D3DXVECTOR3 pos(0, 0, 0);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
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

	device->SetRenderTarget(0, origTarget);
	target->Release();
	origTarget->Release();

	position.x = (float)((SCREEN_WIDTH - FONT_SIZE * len) / 2 - FONT_STROKE);
}

void TextRenderer::update()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(subtitle, NULL, NULL, &position, color);
	sprite->End();
}