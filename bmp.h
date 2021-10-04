#ifndef BMP_H
#define BMP_H

// Bitmap file header
#define BITMAPFILEHEADER 14

// DIB header (Windows NT, 3.1x or later)
#define BITMAPINFOHEADER 40

// Compression method
#define BI_RGB 0

// Color Table (palette)
#define COLORS 256
#define CTSZ (COLORS*4)

#endif // BMP_H
