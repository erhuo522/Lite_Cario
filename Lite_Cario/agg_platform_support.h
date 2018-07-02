

#ifndef AGG_PLATFORM_SUPPORT_INCLUDED
#define AGG_PLATFORM_SUPPORT_INCLUDED

#include <windows.h>

class platform_support
{
public:        
	platform_support();
	virtual ~platform_support();

public:      
	void        caption(const char* cap);
	const char* caption() const { return m_caption; }  

	void message(const char* msg);
	bool init(unsigned width, unsigned height, unsigned flags);
	int  run(); 

	//--------------------------------------------------------------------        
	virtual void on_init(HWND hwnd);
	virtual void on_resize(int sx, int sy);
	virtual void on_mouse_move(int x, int y, int flags);
	virtual void on_left_button_down(int x, int y, int flags);
	virtual void on_left_button_up(int x, int y, int  flags);
	virtual void on_key(int x, int y, unsigned key, int flags);
	virtual void on_draw(HDC hdc); 
protected:


private:
	platform_support(const platform_support&);
	const platform_support& operator = (const platform_support&);
	 
 
	 
	char    m_caption[256];
};


#endif

