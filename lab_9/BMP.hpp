#pragma once
#include <string>
#include <fstream>


namespace image
{
#pragma pack(1)
    struct Pixel
    {
        unsigned char b;
        unsigned char g;
        unsigned char r;
    };
#pragma pack()

    class BMP
    {
    public:

        BMP();

        BMP(int width, int height);

        BMP(const BMP& bmp);

        BMP& operator=(const BMP& bmp);
        
        ~BMP();
        
        void Read(const std::string& filename);
        
        void Save(const std::string& filename);
      
        void Filter(unsigned char m_b, unsigned char m_g, unsigned char m_r);
        
       
    private:
        int m_width, m_height;
        Pixel** m_pixels = nullptr;
    private:
#pragma pack(1) 
        struct BMPHEADER
        {
            unsigned short    Type;
            unsigned int      Size;
            unsigned short    Reserved1;
            unsigned short    Reserved2;
            unsigned int      OffBits;
        };
#pragma pack()

#pragma pack(1)
        struct BMPINFO
        {
            unsigned int    Size;
            int             Width;
            int             Height;
            unsigned short  Planes;
            unsigned short  BitCount;
            unsigned int    Compression;
            unsigned int    SizeImage;
            int             XPelsPerMeter;
            int             YPelsPerMeter;
            unsigned int    ClrUsed;
            unsigned int    ClrImportant;
        };
#pragma pack()
    };
}
