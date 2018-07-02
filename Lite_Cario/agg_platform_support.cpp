


#include "agg_platform_support.h"
 

//------------------------------------------------------------------------
HINSTANCE g_windows_instance = 0;   
HWND      m_hwnd = 0;


platform_support::platform_support()
{
 

}


//------------------------------------------------------------------------
platform_support::~platform_support()
{
        
}

//------------------------------------------------------------------------
void platform_support::caption(const char* cap)
{
     strcpy(m_caption, cap);
     if(m_hwnd)
     {
         SetWindowTextA(m_hwnd, m_caption);
      }
}


 //------------------------------------------------------------------------
LRESULT CALLBACK window_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
        PAINTSTRUCT ps;
		HDC paintDC; 

        void* user_data = reinterpret_cast<void*>(::GetWindowLong(hWnd, GWL_USERDATA));
        platform_support* app = 0;

        if(user_data)
        {
            app = reinterpret_cast<platform_support*>(user_data);
        }

        if(app == 0)
        {
            if(msg == WM_DESTROY)
            {
                ::PostQuitMessage(0);
                return 0;
            }
            return ::DefWindowProc(hWnd, msg, wParam, lParam);
		}
        
        LRESULT ret = 0;

        switch(msg) 
        {
        //--------------------------------------------------------------------
        case WM_CREATE:			
            break;        
        //--------------------------------------------------------------------
        case WM_SIZE:           
            app->on_resize(LOWORD(lParam), HIWORD(lParam));
            break;        
        //--------------------------------------------------------------------
         case WM_ERASEBKGND:
            break;        
        //--------------------------------------------------------------------
        case WM_LBUTTONDOWN:
			app->on_left_button_down(LOWORD(lParam), HIWORD(lParam),  wParam); 
			break;
        //--------------------------------------------------------------------
        case WM_LBUTTONUP:            
			app->on_left_button_up(LOWORD(lParam), HIWORD(lParam),  wParam);
            break; 
        //--------------------------------------------------------------------
        case WM_MOUSEMOVE:          
			app->on_mouse_move(LOWORD(lParam), HIWORD(lParam),  wParam); 
			break;
        //--------------------------------------------------------------------
		case WM_KEYDOWN:
			break;
		//--------------------------------------------------------------------
		case WM_KEYUP:           
            break;
        //--------------------------------------------------------------------
        case WM_CHAR:   
			break;       
        //--------------------------------------------------------------------
        case WM_PAINT:
			{
				 paintDC = ::BeginPaint(hWnd, &ps);				 
				 app->on_draw(paintDC);	                
     			::EndPaint(hWnd, &ps);
			}
			break;        
        //--------------------------------------------------------------------
        case WM_COMMAND:
            break;        
        //--------------------------------------------------------------------
        case WM_DESTROY:
			{
				::PostQuitMessage(0);
			}
			break;
        //--------------------------------------------------------------------
		default:
			{
				ret = ::DefWindowProc(hWnd, msg, wParam, lParam);
				break;
			}
		}		
		return ret;
}


//------------------------------------------------------------------------
void platform_support::message(const char* msg)
{
	::MessageBoxA(m_hwnd, msg, "AGG Message", MB_OK);
}


//------------------------------------------------------------------------
bool platform_support::init(unsigned width, unsigned height, unsigned flags)
{

	int wflags = CS_OWNDC ;

	WNDCLASS wc;
	wc.lpszClassName = TEXT("AGGAppClass");
	wc.lpfnWndProc = window_proc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = g_windows_instance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	::RegisterClass(&wc);

	wflags = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX|WS_MINIMIZEBOX; 

	m_hwnd = ::CreateWindowA("AGGAppClass",
		m_caption,
		WS_OVERLAPPEDWINDOW,
		100,
		50,
		width,
		height,
		0,
		0,
		g_windows_instance,
		0);

	if(m_hwnd == 0)
	{
		return false;
	}

	this->on_init(m_hwnd);

	::SetWindowLong(m_hwnd, GWL_USERDATA, (LONG)this);    
	::ShowWindow(m_hwnd, SW_SHOW|SW_NORMAL);

	return true;
}

//------------------------------------------------------------------------
int platform_support::run()
{
	MSG msg;
	while(::GetMessage(&msg, 0, 0, 0))
	{   
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


     

    



    //------------------------------------------------------------------------
 

    


    //------------------------------------------------------------------------
	void platform_support::on_init(HWND hwnd) {} 
    void platform_support::on_resize(int sx, int sy) {} 
    void platform_support::on_mouse_move(int x, int y, int flags) {}
    void platform_support::on_left_button_down(int x, int y, int flags) {}
    void platform_support::on_left_button_up(int x, int y, int flags) {}
    void platform_support::on_key(int x, int y, unsigned key, int flags) {} 
    void platform_support::on_draw(HDC hdc) {}
   
 

 

//----------------------------------------------------------------------------
int agg_main();



//----------------------------------------------------------------------------
int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int nCmdShow)
{
    g_windows_instance = hInstance;
 

    int ret = agg_main();   

    return ret;
}




