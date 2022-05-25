#include "BMP.hpp"
#include <string>
#include <fstream>

namespace image
{

        BMP::BMP()
        {
            m_height = 0;
            m_width = 0;
        }

        BMP::BMP(int width, int height) 
        {
            m_width = width;
            m_height = height;
            m_pixels = new Pixel * [m_height];
            for (int i = 0; i < m_height; i++)
                m_pixels[i] = new Pixel[m_width];

            for (int i = 0; i < m_height; i++)
                for (int j = 0; j < m_width; j++)
                    m_pixels[i][j] = { 255, 0, 0 };
        }

        BMP::BMP(const BMP& bmp)
        {
            if (m_pixels != nullptr)
            {
                for (int i = 0; i < m_height; i++)
                    delete[] m_pixels[i];
                delete[] m_pixels;
            }

            m_width = bmp.m_width;
            m_height = bmp.m_height;

            m_pixels = new Pixel * [m_height];
            for (int i = 0; i < m_height; i++)
                m_pixels[i] = new Pixel[m_width];

            for (int i = 0; i < m_height; i++)
                for (int j = 0; j < m_width; j++)
                    m_pixels[i][j] = bmp.m_pixels[i][j];
        }


        BMP& BMP::operator=(const BMP& bmp)
        {
            if (m_pixels != nullptr)
            {
                for (int i = 0; i < m_height; i++)
                    delete[] m_pixels[i];
                delete[] m_pixels;
            }

            m_width = bmp.m_width;
            m_height = bmp.m_height;

            m_pixels = new Pixel * [m_height];
            for (int i = 0; i < m_height; i++)
                m_pixels[i] = new Pixel[m_width];

            for (int i = 0; i < m_height; i++)
                for (int j = 0; j < m_width; j++)
                    m_pixels[i][j] = bmp.m_pixels[i][j];

            return *this;
        }


        BMP::~BMP()
        {
            for (int i = 0; i < m_height; i++)
                delete[] m_pixels[i];
            delete[] m_pixels;
        }

        void BMP::Read(const std::string& filename)
        {
            // Read file
            std::ifstream in(filename, std::ios::binary); // open file for binary reading

            BMPHEADER bmpHeader;
            in.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHEADER));

            BMPINFO bmpInfo;
            in.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPINFO));

            if (m_pixels != nullptr)
            {
                for (int i = 0; i < m_height; i++)
                    delete[] m_pixels[i];
                delete[] m_pixels;
            }

            m_height = bmpInfo.Height;
            m_width = bmpInfo.Width;

            m_pixels = new Pixel * [bmpInfo.Height];
            for (int i = 0; i < bmpInfo.Height; i++)
                m_pixels[i] = new Pixel[bmpInfo.Width];

            for (int i = 0; i < bmpInfo.Height; i++)
            {
                for (int j = 0; j < bmpInfo.Width; j++)
                    in.read(reinterpret_cast<char*>(&m_pixels[i][j]), sizeof(Pixel));

                if ((3 * bmpInfo.Width) % 4 != 0)
                    for (int j = 0; j < 4 - (3 * bmpInfo.Width) % 4; j++)
                    {
                        char c = 0;
                        in.read(&c, 1);
                    }
            }
        }

        void BMP::Save(const std::string& filename)
        {
            if (m_width == 0 || m_height == 0)
                throw std::exception("Zero height or width");

            // Save file
            std::ofstream out(filename, std::ios::binary);

            // Heading formation
            BMPHEADER bmpHeader_new;
            bmpHeader_new.Type = 0x4D42;
            bmpHeader_new.Size = 14 + 40 + (3 * m_width * m_height);
            if (m_width % 4 != 0)
                bmpHeader_new.Size += (4 - (3 * m_width) % 4) * m_height;
            bmpHeader_new.OffBits = 54;
            bmpHeader_new.Reserved1 = 0;
            bmpHeader_new.Reserved2 = 0;

            out.write(reinterpret_cast<char*>(&bmpHeader_new), sizeof(BMPHEADER));

            // Formation of image information
            BMPINFO bmpInfo_new;
            bmpInfo_new.BitCount = 24;
            bmpInfo_new.ClrImportant = 0;
            bmpInfo_new.ClrUsed = 0;
            bmpInfo_new.Compression = 0;
            bmpInfo_new.Height = m_height;
            bmpInfo_new.Planes = 1;
            bmpInfo_new.Size = 40;
            bmpInfo_new.SizeImage = bmpHeader_new.Size - 54;
            bmpInfo_new.Width = m_width;
            bmpInfo_new.XPelsPerMeter = 0;
            bmpInfo_new.YPelsPerMeter = 0;

            out.write(reinterpret_cast<char*>(&bmpInfo_new), sizeof(BMPINFO));

            // read pixels
            for (int i = 0; i < bmpInfo_new.Height; i++)
            {
                for (int j = 0; j < bmpInfo_new.Width; j++)
                    out.write(reinterpret_cast<char*>(&m_pixels[i][j]), sizeof(Pixel));

                if ((3 * bmpInfo_new.Width) % 4 != 0)
                    for (int j = 0; j < 4 - (3 * bmpInfo_new.Width) % 4; j++)
                    {
                        char c = 0;
                        out.write(&c, 1);
                    }
            }
        }

        void BMP::Filter(unsigned char m_r, unsigned char m_g, unsigned char m_b)
        {
            for (int i = 0; i < m_height; i++)
            {
                for (int j = 0; j < m_width; j++)
                {
                    if ((m_pixels[i][j].b + m_r < 256) || (m_pixels[i][j].b + m_r >= 0))
                        m_pixels[i][j].r += m_r;
                    if ((m_pixels[i][j].b + m_g < 256) || (m_pixels[i][j].b + m_g >= 0))
                        m_pixels[i][j].g += m_g;
                    if ((m_pixels[i][j].b + m_b < 256) || (m_pixels[i][j].b + m_b >= 0))
                        m_pixels[i][j].b += m_b;
                }
            }
        }

}
