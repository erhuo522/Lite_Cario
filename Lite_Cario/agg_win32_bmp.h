#ifndef AGG_WIN32_BMP_INCLUDED
#define AGG_WIN32_BMP_INCLUDED


#include <windows.h>
#include <stdio.h>


    

    class pixel_map
    {
	public:
		enum org_e
		{
			org_mono8   = 8,
			org_color16 = 16,
			org_color24 = 24,
			org_color32 = 32     
		};

    public:
        ~pixel_map();
        pixel_map();

    public:
        void        destroy();
        void        create(unsigned width, 
                           unsigned height, 
                           org_e    org,
                           unsigned clear_val=256);
        HBITMAP     create_dib_section(HDC h_dc,
                                       unsigned width, 
                                       unsigned height, 
                                       org_e    org,
                                       unsigned clear_val=256);

        void        clear(unsigned clear_val=256);
        void        attach_to_bmp(BITMAPINFO* bmp);
        BITMAPINFO* bitmap_info() { return m_bmp; }
        bool        load_from_bmp(FILE* fd);
        bool        save_as_bmp(FILE* fd) const;
        bool        load_from_bmp(const char* filename);
        bool        save_as_bmp(const char* filename) const;

        void        draw(HDC h_dc, 
                         const RECT* device_rect=0, 
                         const RECT* bmp_rect=0) const;
        void        draw(HDC h_dc, int x, int y, double scale=1.0) const;

        void        blend(HDC h_dc, 
                          const RECT* device_rect=0, 
                          const RECT* bmp_rect=0) const;
        void        blend(HDC h_dc, int x, int y, double scale=1.0) const;

		void         copy_bits(unsigned char* data, bool flp);
 
		unsigned       bits_size(){return m_img_size;}
        unsigned char* buf();
        unsigned       width() const;
        unsigned       height() const;
        int            stride() const;
        unsigned       bpp() const { return m_bpp; }

        //Auxiliary static functions
        static unsigned calc_full_size(BITMAPINFO *bmp);
        static unsigned calc_header_size(BITMAPINFO *bmp);
        static unsigned calc_palette_size(unsigned clr_used, 
                                          unsigned bits_per_pixel);
        static unsigned calc_palette_size(BITMAPINFO *bmp);
        static unsigned char* calc_img_ptr(BITMAPINFO *bmp);
        static BITMAPINFO* create_bitmap_info(unsigned width, 
                                              unsigned height, 
                                              unsigned bits_per_pixel);
        static void     create_gray_scale_palette(BITMAPINFO *bmp);
        static unsigned calc_row_len(unsigned width, unsigned bits_per_pixel);
        
    private:
        pixel_map(const pixel_map&);
        const pixel_map& operator = (const pixel_map&);
        void create_from_bmp(BITMAPINFO *bmp);
        
        HBITMAP create_dib_section_from_args(HDC h_dc,
                                             unsigned width,
                                             unsigned height,
                                             unsigned bits_per_pixel);

    private:
        BITMAPINFO*    m_bmp;
        unsigned char* m_buf;
        unsigned       m_bpp;
        bool           m_is_internal;
        unsigned       m_img_size;
        unsigned       m_full_size;
    };

 

#endif //