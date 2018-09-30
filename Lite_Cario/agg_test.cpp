
#include <windows.h>
 
#include "agg_platform_support.h"
#include "agg_win32_bmp.h" 
 

#include "cairo.h"


class the_application : public  platform_support
{


public:
	the_application() 
	{

	}

	void on_init(HWND hwnd)
	{
		HDC hdc = GetDC(hwnd);
		m_pixel_map.create(800,600, pixel_map::org_color32,255);
		ReleaseDC(hwnd,hdc);	

		//声明了一个 Cairo 外观与一个 Cairo 环境。 
		cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 800, 600);
		cairo_t *cr = cairo_create();
		cairo_set_target_surface(cr, surface); 

		//====================================================================
		/*
		cairo_set_rgb_color(cr, 0, 0, 0);
		cairo_move_to(cr, 100, 100);
		cairo_line_to(cr, 400, 400);
		cairo_move_to(cr, 400, 100);
		cairo_line_to(cr, 100, 400);
		cairo_set_line_width(cr, 20);
		cairo_stroke(cr);
		*/
		cairo_rectangle(cr, 100, 100, 150, 150);
		cairo_set_rgb_color(cr, 10, 0, 0);
		cairo_set_alpha(cr, 0.80);
		cairo_fill(cr);
	 /*	
		cairo_rectangle(cr, 100, 250, 150, 150);
		cairo_set_rgb_color(cr, 0, 1, 0);
		cairo_set_alpha(cr, 0.60);
		cairo_fill(cr);

		cairo_rectangle(cr, 250, 100, 150, 150);
		cairo_set_rgb_color(cr, 0, 0, 1);
		cairo_set_alpha(cr, 0.40);
		cairo_fill(cr);

		*/
		//---------------------------------------------------------------------
		/*
		//圆形 
		 cairo_arc (cr, 90, 200, 40, 0, 2 * 3.1415/2);
		 cairo_stroke_preserve ( cr) ;
		 cairo_stroke ( cr) ;
		 
		//实心矩形
		 cairo_set_source_rgb ( cr, 0.6 , 0.6 , 0.0 ) ;
		 cairo_rectangle ( cr, 250 , 20 , 100 , 100 ) ;
		 cairo_fill ( cr) ; 
		  
		//空心矩形
	    cairo_set_source_rgb (cr,  0.627, 0, 0);
		cairo_rectangle ( cr, 320 , 320 , 120 , 80 ) ; 
		cairo_stroke ( cr) ;
		 

 
		 //画直线 
		cairo_set_line_width(cr, 20.0);
		cairo_set_rgb_color (cr,  0.627, 0, 0);
		cairo_move_to( cr, 40, 120) ;
		cairo_line_to( cr, 500 , 300); 
		cairo_line_to(cr, 500, 500);
		cairo_stroke( cr) ;
	*/	
		//把图像内存数据拿走
        m_pixel_map.copy_bits( cairo_image_surface_get_data(surface), false);

		//回收所有 Cairo 环境与外观所占用的内存资源。
		cairo_destroy(cr);
		cairo_surface_destroy(surface);
		
		 
	}

	void on_draw(HDC hdc)
	{
		 
		m_pixel_map.blend(hdc,0,0);
		
	}

private:
	pixel_map  m_pixel_map;
	bool      m_flip_y;


};
 
//******************************************************************************
 


 
//*******************************************************************************
int agg_main()
{
 	 the_application app;
 	 app.caption("cario Test");
 
 	 if(app.init(800,600, 0))
 	 {
 		 app.run();
 	 }
	 return 0;
}



