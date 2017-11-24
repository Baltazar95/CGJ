#ifndef __KEYBUFFER_H_
#define __KEYBUFFER_H_

class KeyBuffer
{
	private:
		static KeyBuffer *uniqueInstance;
		bool keyBuffer[256];
		KeyBuffer();

	public:
		static KeyBuffer *instance();
		void pressKey(unsigned char key);
		void releaseKey(unsigned char key);
		bool isPressed(unsigned char key);

};

#endif // !__KEYBUFFER_H_