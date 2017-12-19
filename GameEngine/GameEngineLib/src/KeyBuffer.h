#ifndef __KEYBUFFER_H_
#define __KEYBUFFER_H_

class KeyBuffer
{
	private:
		static KeyBuffer *uniqueInstance;
		bool keyBuffer[256];
		float deltax = 0.0f, deltay = 0.0f, scrollSign = 30.0f;
		KeyBuffer();

	public:
		static KeyBuffer *instance();
		void pressKey(unsigned char key);
		void releaseKey(unsigned char key);
		bool isPressed(unsigned char key);
		void dragX(float xAmount);
		void dragY(float yAmount);
		void scroll(float scroll);
		float getDeltaX() { return deltax; };
		float getDeltaY() { return deltay; };
		float getScrollSign() { return scrollSign; };
};

#endif // !__KEYBUFFER_H_