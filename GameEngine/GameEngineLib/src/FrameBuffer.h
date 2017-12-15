#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include <vector>

#include "GlUtils.h"
#include "MathAux.h"
#include "Obj_Loader.h"
#include "Texture.h"

class FrameBuffer
{
private:
	unsigned int frameBuffer;
	unsigned int renderbuffer;
	unsigned int renderedTexture;
	int SCR_WIDTH; 
	int SCR_HEIGHT;

public:
	//FrameBuffer(int width, int height);
	FrameBuffer(unsigned int renderedtext, int width, int height);
	//FrameBuffer(std::string filename);
	~FrameBuffer();
	void createFrameBuffer();
	void createRenderedTexture();
	void attachTextureBuffer();
	void createRenderBuffer();
	void attachRenderBuffer();
	void checkBufferStatus();
	void FrameBufferSetup();
	void unbindFrameBuffer();
	void bindFrameBuffer();
	unsigned int getRenderedTex() { return renderedTexture; };
};

#endif // !__FRAMEBUFFER_H__