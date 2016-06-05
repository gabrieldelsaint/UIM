//-------------------------------------
//  PNGFILE.C -- Image File Functions
//-------------------------------------

// Copyright 2000, Willem van Schaik.  For conditions of distribution and
// use, see the copyright/license/disclaimer notice in png.h

#include <stdio.h>
#include <stdlib.h>


#include "pnghelper.h"
#include "cexcept.h"

define_exception_type(const char *);
extern struct exception_context the_exception_context[1];
struct exception_context the_exception_context[1];
png_const_charp msg;

static OPENFILENAME ofn;

static png_structp png_ptr = NULL;
static png_infop info_ptr = NULL;


// cexcept interface

static void
png_cexcept_error(png_structp png_ptr, png_const_charp msg)
{
   if(png_ptr)
     ;
#ifndef PNG_NO_CONSOLE_IO
   fprintf(stderr, "libpng error: %s\n", msg);
#endif
   {
      Throw msg;
   }
}

// PNG image handler functions

BOOL PngLoadImage (LPBYTE pBuffer, int nSize, png_byte **ppbImageData,
                   int *piWidth, int *piHeight, int *piChannels, png_color *pBkgColor)
{
    png_byte            pbSig[8];
    int                 iBitDepth;
    int                 iColorType;
    double              dGamma;
    png_color_16       *pBackground;
    png_uint_32         ulChannels;
    png_uint_32         ulRowBytes;
    png_byte           *pbImageData = *ppbImageData;
    static png_byte   **ppbRowPointers = NULL;
    int                 i;

    // open the PNG input file

    if (!nSize)
    {
        *ppbImageData = pbImageData = NULL;
        return FALSE;
    }


    // first check the eight byte PNG signature
    
	CopyMemory(pbSig, pBuffer, 8);	
	pBuffer += 8;

    if (!png_check_sig(pbSig, 8))
    {
        *ppbImageData = pbImageData = NULL;
        return FALSE;
    }

    // create the two png(-info) structures

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
      (png_error_ptr)png_cexcept_error, (png_error_ptr)NULL);
    if (!png_ptr)
    {
        *ppbImageData = pbImageData = NULL;
        return FALSE;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        *ppbImageData = pbImageData = NULL;
        return FALSE;
    }

    Try
    {
        
        // initialize the png structure        

		png_set_read_fn(png_ptr, (png_voidp)pBuffer, png_read_data);
        
        png_set_sig_bytes(png_ptr, 8);
        
        // read all PNG info up to image data
        
        png_read_info(png_ptr, info_ptr);
        
        // get width, height, bit-depth and color-type
        
        png_get_IHDR(png_ptr, info_ptr, piWidth, piHeight, &iBitDepth,
            &iColorType, NULL, NULL, NULL);
        
        // expand images of all color-type and bit-depth to 3x8 bit RGB images
        // let the library process things like alpha, transparency, background
        
        if (iBitDepth == 16)
            png_set_strip_16(png_ptr);
        if (iColorType == PNG_COLOR_TYPE_PALETTE)
            png_set_expand(png_ptr);
        if (iBitDepth < 8)
            png_set_expand(png_ptr);
        if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
            png_set_expand(png_ptr);
        if (iColorType == PNG_COLOR_TYPE_GRAY ||
            iColorType == PNG_COLOR_TYPE_GRAY_ALPHA)
            png_set_gray_to_rgb(png_ptr);
        
        // set the background color to draw transparent and alpha images over.
        if (png_get_bKGD(png_ptr, info_ptr, &pBackground))
        {
            png_set_background(png_ptr, pBackground, PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
            pBkgColor->red   = (byte) pBackground->red;
            pBkgColor->green = (byte) pBackground->green;
            pBkgColor->blue  = (byte) pBackground->blue;
        }
        else
        {
            pBkgColor = NULL;
        }
        
        // if required set gamma conversion
        if (png_get_gAMA(png_ptr, info_ptr, &dGamma))
            png_set_gamma(png_ptr, (double) 2.2, dGamma);
        
        // after the transformations have been registered update info_ptr data
        
        png_read_update_info(png_ptr, info_ptr);
        
        // get again width, height and the new bit-depth and color-type
        
        png_get_IHDR(png_ptr, info_ptr, piWidth, piHeight, &iBitDepth,
            &iColorType, NULL, NULL, NULL);
        
        
        // row_bytes is the width x number of channels
        
        ulRowBytes = png_get_rowbytes(png_ptr, info_ptr);
        ulChannels = png_get_channels(png_ptr, info_ptr);
        
        *piChannels = ulChannels;
        
        // now we can allocate memory to store the image
        
        if (pbImageData)
        {
            free (pbImageData);
            pbImageData = NULL;
        }
        if ((pbImageData = (png_byte *) malloc(ulRowBytes * (*piHeight)
                            * sizeof(png_byte))) == NULL)
        {
            png_error(png_ptr, "Visual PNG: out of memory");
        }
        *ppbImageData = pbImageData;
        
        // and allocate memory for an array of row-pointers
        
        if ((ppbRowPointers = (png_bytepp) malloc((*piHeight)
                            * sizeof(png_bytep))) == NULL)
        {
            png_error(png_ptr, "Visual PNG: out of memory");
        }
        
        // set the individual row-pointers to point at the correct offsets
        
        for (i = 0; i < (*piHeight); i++)
            ppbRowPointers[i] = pbImageData + i * ulRowBytes;
        
        // now we can go ahead and just read the whole image
        
        png_read_image(png_ptr, ppbRowPointers);
        
        // read the additional chunks in the PNG file (not really needed)
        
        png_read_end(png_ptr, NULL);
        
        // and we're done
        
        free (ppbRowPointers);
        ppbRowPointers = NULL;
        
        // yepp, done
    }

    Catch (msg)
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

        *ppbImageData = pbImageData = NULL;
        
        if(ppbRowPointers)
            free (ppbRowPointers);
     
        return FALSE;
    }    

    return TRUE;
}
	
BOOL PngFreeImage()
{
	if (png_ptr)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	}	

	return TRUE;
}

//
//BOOL PngSaveImage (PTSTR pstrFileName, png_byte *pDiData,
//                   int iWidth, int iHeight, png_color bkgColor)
//{
//    const int           ciBitDepth = 8;
//    const int           ciChannels = 3;
//
//    static FILE        *pfFile;
//    png_uint_32         ulRowBytes;
//    static png_byte   **ppbRowPointers = NULL;
//    int                 i;
//
//    // open the PNG output file
//
//    if (!pstrFileName)
//        return FALSE;
//
//    if (!(pfFile = fopen(pstrFileName, "wb")))
//        return FALSE;
//
//    // prepare the standard PNG structures
//
//    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL,
//      (png_error_ptr)png_cexcept_error, (png_error_ptr)NULL);
//    if (!png_ptr)
//    {
//        fclose(pfFile);
//        return FALSE;
//    }
//
//    info_ptr = png_create_info_struct(png_ptr);
//    if (!info_ptr) {
//        fclose(pfFile);
//        png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
//        return FALSE;
//    }
//
//    Try
//    {
//        // initialize the png structure
//        
//#if !defined(PNG_NO_STDIO)
//        png_init_io(png_ptr, pfFile);
//#else
//        png_set_write_fn(png_ptr, (png_voidp)pfFile, png_write_data, png_flush);
//#endif
//        
//        // we're going to write a very simple 3x8 bit RGB image
//        
//        png_set_IHDR(png_ptr, info_ptr, iWidth, iHeight, ciBitDepth,
//            PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
//            PNG_FILTER_TYPE_BASE);
//        
//        // write the file header information
//        
//        png_write_info(png_ptr, info_ptr);
//        
//        // swap the BGR pixels in the DiData structure to RGB
//        
//        png_set_bgr(png_ptr);
//        
//        // row_bytes is the width x number of channels
//        
//        ulRowBytes = iWidth * ciChannels;
//        
//        // we can allocate memory for an array of row-pointers
//        
//        if ((ppbRowPointers = (png_bytepp) malloc(iHeight * sizeof(png_bytep))) == NULL)
//            Throw "Visualpng: Out of memory";
//        
//        // set the individual row-pointers to point at the correct offsets
//        
//        for (i = 0; i < iHeight; i++)
//            ppbRowPointers[i] = pDiData + i * (((ulRowBytes + 3) >> 2) << 2);
//        
//        // write out the entire image data in one call
//        
//        png_write_image (png_ptr, ppbRowPointers);
//        
//        // write the additional chunks to the PNG file (not really needed)
//        
//        png_write_end(png_ptr, info_ptr);
//        
//        // and we're done
//        
//        free (ppbRowPointers);
//        ppbRowPointers = NULL;
//        
//        // clean up after the write, and free any memory allocated
//        
//        png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
//        
//        // yepp, done
//    }
//
//    Catch (msg)
//    {
//        png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
//
//        if(ppbRowPointers)
//            free (ppbRowPointers);
//
//        fclose(pfFile);
//
//        return FALSE;
//    }
//    
//    fclose (pfFile);
//    
//    return TRUE;
//}

static void
png_read_data(png_structp png_ptr, png_bytep data, png_size_t length)
{
   CopyMemory(data, png_ptr->io_ptr, length);

   png_ptr->io_ptr = ((LPBYTE)png_ptr->io_ptr + length);
  
}
//
//static void
//png_write_data(png_structp png_ptr, png_bytep data, png_size_t length)
//{
//   png_uint_32 check;
//
//   check = fwrite(data, 1, length, (FILE *)(png_ptr->io_ptr));
//   if (check != length)
//   {
//      png_error(png_ptr, "Write Error");
//   }
//}

static void
png_flush(png_structp png_ptr)
{
   FILE *io_ptr;
   io_ptr = (FILE *)CVT_PTR((png_ptr->io_ptr));
   if (io_ptr != NULL)
      fflush(io_ptr);
}


//-----------------
//  end of source
//-----------------
