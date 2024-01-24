#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "GL/glew.h"
#include "../extra/picopng.h"
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include <cmath>


Image::Image() {
	width = 0; height = 0;
	pixels = NULL;
}

Image::Image(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	pixels = new Color[width*height];
	memset(pixels, 0, width * height * sizeof(Color));
}

// Copy constructor
Image::Image(const Image& c)
{
	pixels = NULL;
	width = c.width;
	height = c.height;
	bytes_per_pixel = c.bytes_per_pixel;
	if(c.pixels)
	{
		pixels = new Color[width*height];
		memcpy(pixels, c.pixels, width*height*bytes_per_pixel);
	}
}

// Assign operator
Image& Image::operator = (const Image& c)
{
	if(pixels) delete pixels;
	pixels = NULL;

	width = c.width;
	height = c.height;
	bytes_per_pixel = c.bytes_per_pixel;

	if(c.pixels)
	{
		pixels = new Color[width*height*bytes_per_pixel];
		memcpy(pixels, c.pixels, width*height*bytes_per_pixel);
	}
	return *this;
}

Image::~Image()
{
	if(pixels) 
		delete pixels;
}

void Image::Render()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glDrawPixels(width, height, bytes_per_pixel == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}



// Change image size (the old one will remain in the top-left corner)
void Image::Resize(unsigned int width, unsigned int height)
{
	Color* new_pixels = new Color[width*height];
	unsigned int min_width = this->width > width ? width : this->width;
	unsigned int min_height = this->height > height ? height : this->height;

	for(unsigned int x = 0; x < min_width; ++x)
		for(unsigned int y = 0; y < min_height; ++y)
			new_pixels[ y * width + x ] = GetPixel(x,y);

	delete pixels;
	this->width = width;
	this->height = height;
	pixels = new_pixels;
}

// Change image size and scale the content
void Image::Scale(unsigned int width, unsigned int height)
{
	Color* new_pixels = new Color[width*height];

	for(unsigned int x = 0; x < width; ++x)
		for(unsigned int y = 0; y < height; ++y)
			new_pixels[ y * width + x ] = GetPixel((unsigned int)(this->width * (x / (float)width)), (unsigned int)(this->height * (y / (float)height)) );

	delete pixels;
	this->width = width;
	this->height = height;
	pixels = new_pixels;
}

Image Image::GetArea(unsigned int start_x, unsigned int start_y, unsigned int width, unsigned int height)
{
	Image result(width, height);
	for(unsigned int x = 0; x < width; ++x)
		for(unsigned int y = 0; y < height; ++x)
		{
			if( (x + start_x) < this->width && (y + start_y) < this->height) 
				result.SetPixel( x, y, GetPixel(x + start_x,y + start_y) );
		}
	return result;
}

void Image::FlipY()
{
	int row_size = bytes_per_pixel * width;
	Uint8* temp_row = new Uint8[row_size];
#pragma omp simd
	for (int y = 0; y < height * 0.5; y += 1)
	{
		Uint8* pos = (Uint8*)pixels + y * row_size;
		memcpy(temp_row, pos, row_size);
		Uint8* pos2 = (Uint8*)pixels + (height - y - 1) * row_size;
		memcpy(pos, pos2, row_size);
		memcpy(pos2, temp_row, row_size);
	}
	delete[] temp_row;
}

bool Image::LoadPNG(const char* filename, bool flip_y)
{
	std::string sfullPath = absResPath(filename);
	std::ifstream file(sfullPath, std::ios::in | std::ios::binary | std::ios::ate);

	// Get filesize
	std::streamsize size = 0;
	if (file.seekg(0, std::ios::end).good()) size = file.tellg();
	if (file.seekg(0, std::ios::beg).good()) size -= file.tellg();

	if (!size)
		return false;

	std::vector<unsigned char> buffer;

	// Read contents of the file into the vector
	if (size > 0)
	{
		buffer.resize((size_t)size);
		file.read((char*)(&buffer[0]), size);
	}
	else
		buffer.clear();

	std::vector<unsigned char> out_image;

	if (decodePNG(out_image, width, height, buffer.empty() ? 0 : &buffer[0], (unsigned long)buffer.size(), true) != 0)
		return false;

	size_t bufferSize = out_image.size();
	unsigned int originalBytesPerPixel = (unsigned int)bufferSize / (width * height);
	
	// Force 3 channels
	bytes_per_pixel = 3;

	if (originalBytesPerPixel == 3) {
		pixels = new Color[bufferSize];
		memcpy(pixels, &out_image[0], bufferSize);
	}
	else if (originalBytesPerPixel == 4) {

		unsigned int newBufferSize = width * height * bytes_per_pixel;
		pixels = new Color[newBufferSize];

		unsigned int k = 0;
		for (unsigned int i = 0; i < bufferSize; i += originalBytesPerPixel) {
			pixels[k] = Color(out_image[i], out_image[i + 1], out_image[i + 2]);
			k++;
		}
	}

	// Flip pixels in Y
	if (flip_y)
		FlipY();

	return true;
}

// Loads an image from a TGA file
bool Image::LoadTGA(const char* filename, bool flip_y)
{
	unsigned char TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char TGAcompare[12];
	unsigned char header[6];
	unsigned int imageSize;
	unsigned int bytesPerPixel;

    std::string sfullPath = absResPath( filename );

	FILE * file = fopen( sfullPath.c_str(), "rb");
   	if ( file == NULL || fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||
		fread(header, 1, sizeof(header), file) != sizeof(header))
	{
		std::cerr << "File not found: " << sfullPath.c_str() << std::endl;
		if (file == NULL)
			return NULL;
		else
		{
			fclose(file);
			return NULL;
		}
	}

	TGAInfo* tgainfo = new TGAInfo;
    
	tgainfo->width = header[1] * 256 + header[0];
	tgainfo->height = header[3] * 256 + header[2];
    
	if (tgainfo->width <= 0 || tgainfo->height <= 0 || (header[4] != 24 && header[4] != 32))
	{
		fclose(file);
		delete tgainfo;
		return NULL;
	}
    
	tgainfo->bpp = header[4];
	bytesPerPixel = tgainfo->bpp / 8;
	imageSize = tgainfo->width * tgainfo->height * bytesPerPixel;
    
	tgainfo->data = new unsigned char[imageSize];
    
	if (tgainfo->data == NULL || fread(tgainfo->data, 1, imageSize, file) != imageSize)
	{
		if (tgainfo->data != NULL)
			delete tgainfo->data;
            
		fclose(file);
		delete tgainfo;
		return false;
	}

	fclose(file);

	// Save info in image
	if(pixels)
		delete pixels;

	width = tgainfo->width;
	height = tgainfo->height;
	pixels = new Color[width*height];

	// Convert to float all pixels
	for (unsigned int y = 0; y < height; ++y) {
		for (unsigned int x = 0; x < width; ++x) {
			unsigned int pos = y * width * bytesPerPixel + x * bytesPerPixel;
			// Make sure we don't access out of memory
			if( (pos < imageSize) && (pos + 1 < imageSize) && (pos + 2 < imageSize))
				SetPixel(x, height - y - 1, Color(tgainfo->data[pos + 2], tgainfo->data[pos + 1], tgainfo->data[pos]));
		}
	}

	// Flip pixels in Y
	if (flip_y)
		FlipY();

	delete tgainfo->data;
	delete tgainfo;

	return true;
}

// Saves the image to a TGA file
bool Image::SaveTGA(const char* filename)
{
	unsigned char TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	std::string fullPath = absResPath(filename);
	FILE *file = fopen(fullPath.c_str(), "wb");
	if ( file == NULL )
	{
		perror("Failed to open file: ");
		return false;
	}

	unsigned short header_short[3];
	header_short[0] = width;
	header_short[1] = height;
	unsigned char* header = (unsigned char*)header_short;
	header[4] = 24;
	header[5] = 0;

	fwrite(TGAheader, 1, sizeof(TGAheader), file);
	fwrite(header, 1, 6, file);

	// Convert pixels to unsigned char
	unsigned char* bytes = new unsigned char[width*height*3];
	for(unsigned int y = 0; y < height; ++y)
		for(unsigned int x = 0; x < width; ++x)
		{
			Color c = pixels[y*width+x];
			unsigned int pos = (y*width+x)*3;
			bytes[pos+2] = c.r;
			bytes[pos+1] = c.g;
			bytes[pos] = c.b;
		}

	fwrite(bytes, 1, width*height*3, file);
	fclose(file);

	return true;
}

//
//LINEA
//

void Image::DrawLineDDA(int x0, int y0, int x1, int y1, const Color& c)
{
	int dx = x1 - x0;
	int dy = y1 - y0;

	//powerpoint
	int d = std::max(std::abs(dx), std::abs(dy)); //d indicates how many pixels we must draw


	//punts inicials 
	float x = (float)x0;
	float y = (float)y0;

	//x-increment i y-increment; STEP VECTOR 
	float x_incr = (float)dx / d;
	float y_incr = (float)dy / d;

	for (int i = 0; i <= d; i++) { //
		int X = int(std::floor(x));
		int Y = int(std::floor(y));

		SetPixelSafe(X, Y, c);
		x += x_incr;
		y += y_incr;

	}


}

//
//RECTANGLE
//
void Image::DrawRectangle(int startX, int startY, int width, int height, const Color& borderColor, int borderWidth, bool isFilled, const Color& fillColor) {

	if (isFilled) {
		// omplim el rectangle si es vol omplert
		for (int x = startX + 1; x < (startX + width - 1); ++x) {
			for (int y = startY + 1; y < (startY + height - 1); ++y) {
				SetPixel(x, y, fillColor);
			}
		}
	}

	// dibuixem el borde, b ens determina l'espai que ocupa
    for (int b = 0; b < borderWidth; ++b) {
            // Dibuixem linies horitzontals segons la mida del borde
            for (int x = startX - b; x < (startX + width + b); ++x) {
                SetPixelSafe(x, startY - b, borderColor);
                //b per afegir linia, fer mes ample el borde
                SetPixelSafe(x, startY + height - 1 + b, borderColor);
            }
        // Dibuixem linies verticals segons la mida del borde
            for (int y = startY - b; y < (startY + height + b); ++y) {
                SetPixelSafe(startX - b, y, borderColor);
                SetPixelSafe(startX + width - 1 + b, y, borderColor);
            }
        }
}


/*void Image::DrawRect(int x, int y, int w, int h, const Color& c)
{
	for (int i = 0; i < w; ++i) {
		SetPixel(x + i, y, c);
		SetPixel(x + i, y + h - 1, c);
	}

	for (int j = 0; j < h; ++j) {
		SetPixel(x, y + j, c);
		SetPixel(x + w - 1, y + j, c);
	}
}*/


//
//CERCLE
//
void Image::DrawCircle(int x, int y, int r, const Color& borderColor, int borderWidth, bool isFilled, const Color& fillColor) {
    // CIRCUMFERENCIA
    //creem un quadrat de mida de costat 2*radi que contingui el cercle
    for (int dy = -r; dy <= r; ++dy) {
        for (int dx = -r; dx <= r; ++dx) {
            // Amb lequacio x^2+y^2<=r^2 comprovarem si el punt es troba dins del cercle
            if (dx * dx + dy * dy <= r * r) {
                // si tenim un minim valor de borde, podrem dibuixar
                if (borderWidth > 1) {
                    // verifiquem si el punt està fora del cercle interior (radi-borde), i si per tant forma part del borde
                    if (dx * dx + dy * dy > (r - borderWidth) * (r - borderWidth)) {
                        SetPixelSafe(x + dx, y + dy, borderColor);
                    }
                    
                }
            }
        }
    }

    // RELLENAR
    if (isFilled) {
        //per tots els punts que queden dins del cercle i del borde cercle amb radi (radi-borde)
        for (int dx = -r + borderWidth; dx <= r - borderWidth; ++dx) {
            for (int dy = -r + borderWidth; dy <= r - borderWidth; ++dy) {
                // verifiquem si formen part del cercle
                if (dx * dx + dy * dy <= (r - borderWidth) * (r - borderWidth)) {
                    SetPixelSafe(x + dx, y + dy, fillColor);
                }
            }
        }
    }

}

//
//TRIANGLE
//
//

//Algoritme actualitzat
void Image::ScanLineDDA(int x0, int y0, int x1, int y1, std::vector<Cell>& table) {
	int dx = x1 - x0;
	int dy = y1 - y0;

	//d=num pixel a dibuixar
	int d = std::max(std::abs(dx), std::abs(dy));

	//punts inicials
	float x = (float)x0;
	float y = (float)y0;

	//step vector
	float x_incr = (float)dx / d;
	float y_incr = (float)dy / d;

	for (int i = 0; i <= d; i++) {
		int X = int(std::floor(x));
		int Y = int(std::floor(y));
		//update minX i minY per la current cell
		if (Y >= 0 && Y < table.size()) {
			table[Y].minX = std::min(table[Y].minX, X);
			table[Y].maxX = std::max(table[Y].maxX, X);
		}
		x += x_incr;
		y += y_incr;
	}

}

//Triangle
void Image::DrawTriangle(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Color& borderColor, bool isFilled, const Color& fillColor) {
	
	//creation container (AETVariable)
	std::vector<Cell> table;
	table.resize(this->height);
	
	//scan min i max amb el ScanlineDDA
	ScanLineDDA(p0.x, p0.y, p1.x, p1.y, table);
	ScanLineDDA(p1.x, p1.y, p2.x, p2.y, table);
	ScanLineDDA(p2.x, p2.y, p0.x, p0.y, table);

	//iterar la taula

	for (int y = 0; y < this->height; y++){
		//valors per linea actual
		int min_x = INT_MAX;
		int max_x = INT_MIN;
		for (int x = 0; x < this->width; x++) {//iterar per amplada de triangle (anar fent lineas)
			if (table[y].minX <= x && x <= table[y].maxX) {
				if (isFilled) {
					//fill interior and border
					if (x == table[y].minX || x == table[y].maxX || y == 0 || y == this->height - 1) {
						this->SetPixelSafe(x, y, borderColor);
					}
					else {
						this->SetPixelSafe(x, y, fillColor);
					}
				
				}else{
					//dibuixar nomes el border si isfilled=false
					if (x == table[y].minX || x == table[y].maxX || y == 0 || y == this->height - 1) {
						this->SetPixel(x, y, borderColor);
					}
				}
			}
		}
	}
}

//
//IMAGES TOOL DRAWING
//

void Image::DrawImage(const Image & image, int x, int y, bool top) {

        int startRow = top ? y : y - image.height + 1;

        for (int row = 0; row < image.height; ++row)
        {
            for (int col = 0; col < image.width; ++col)
            {
                int destX = x + col;
                int destY = startRow + row;

                if (destX >= 0 && destX < static_cast<int>(width) && destY >= 0 && destY < static_cast<int>(height))
                {
                    SetPixel(destX, destY, image.GetPixel(col, row));
                }
            }
        }
    }
    /*int image_width = image.width;
	int image_height = image.height;
	int start_x = x;
	int start_y = y;

	if (top) {
		start_y = height - y - image_height;
	}

	for (int i = 0; i < image_height; i++) {
		for (int j = 0; j < image_width; j++) {
			Color pixel = image.GetPixel(j, i);
			SetPixel(start_x + j, start_y + i, pixel);
		}
	}
}*/

//
//POSICIO MOUSE
//

bool Button::IsMouseInside(const Vector2& mousePosition){
    // Calculate button boundaries based on image size and position
    float left = position.x;
    float right = position.x + this->image->width();
    float top = position.y;
    float bottom = position.y + image->height();
    
    // Check if the mouse position is within the button boundaries
    return (mousePosition.x >= left && mousePosition.x <= right &&
            mousePosition.y >= top && mousePosition.y <= bottom);
}



#ifndef IGNORE_LAMBDAS

// You can apply and algorithm for two images and store the result in the first one
// ForEachPixel( img, img2, [](Color a, Color b) { return a + b; } );
template <typename F>
void ForEachPixel(Image& img, const Image& img2, F f) {
	for(unsigned int pos = 0; pos < img.width * img.height; ++pos)
		img.pixels[pos] = f( img.pixels[pos], img2.pixels[pos] );
}

#endif

FloatImage::FloatImage(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	pixels = new float[width * height];
	memset(pixels, 0, width * height * sizeof(float));
}

// Copy constructor
FloatImage::FloatImage(const FloatImage& c) {
	pixels = NULL;

	width = c.width;
	height = c.height;
	if (c.pixels)
	{
		pixels = new float[width * height];
		memcpy(pixels, c.pixels, width * height * sizeof(float));
	}
}



// Assign operator
FloatImage& FloatImage::operator = (const FloatImage& c)
{
	if (pixels) delete pixels;
	pixels = NULL;

	width = c.width;
	height = c.height;
	if (c.pixels)
	{
		pixels = new float[width * height * sizeof(float)];
		memcpy(pixels, c.pixels, width * height * sizeof(float));
	}
	return *this;
}

FloatImage::~FloatImage()
{
	if (pixels)
		delete pixels;
}

// Change image size (the old one will remain in the top-left corner)
void FloatImage::Resize(unsigned int width, unsigned int height)
{
	float* new_pixels = new float[width * height];
	unsigned int min_width = this->width > width ? width : this->width;
	unsigned int min_height = this->height > height ? height : this->height;

	for (unsigned int x = 0; x < min_width; ++x)
		for (unsigned int y = 0; y < min_height; ++y)
			new_pixels[y * width + x] = GetPixel(x, y);

	delete pixels;
	this->width = width;
	this->height = height;
	pixels = new_pixels;
}
