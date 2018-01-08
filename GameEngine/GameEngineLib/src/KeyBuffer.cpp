#include "KeyBuffer.h"

KeyBuffer *KeyBuffer::uniqueInstance = 0;

KeyBuffer::KeyBuffer()
{
	for (int i = 0; i < 256; i++)
	{
		keyBuffer[i] = false;
	}
}

KeyBuffer *KeyBuffer::instance()
{
	if (!uniqueInstance)
	{
		uniqueInstance = new KeyBuffer();
	}
	return uniqueInstance;
}

void KeyBuffer::pressKey(unsigned char key)
{
	keyBuffer[key] = true;
}

void KeyBuffer::releaseKey(unsigned char key)
{
	keyBuffer[key] = false;
}

bool KeyBuffer::isPressed(unsigned char key)
{
	return keyBuffer[key];
}

void KeyBuffer::dragX(float xAmount)
{
	deltax = xAmount;
}

void KeyBuffer::dragY(float yAmount)
{
	deltax = yAmount;
}

void KeyBuffer::scroll(float scroll)
{
	scrollSign = scroll;
}