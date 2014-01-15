/*
 * Author:  Chris Holden (ceholden@bu.edu)
 * Date:    11/13/2012
 * Purpose: To mask observations in Landsat time series that are not observed
 *          throughout the entire time series. In practice, this means we cut
 *          off the edges of the scene where observations may be missing due
 *          to differences in image collection points.
 *
 * NOTE:    To get this fully working, I need to create a mask for Landsat 7
 *          SLC-off gaps because this data is probably good to keep.
 *          Alternatively, I could create a threshold (i.e. 66% of 
 *          observations missing) that would define the mask.
 *
 */

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include "gdal_priv.h"
#include "cpl_conv.h"


using namespace std;

int fmaskNoDataValue = 255;
int ledapsNoDataValue = -9999;
int fmaskBand = 8;
string stackName = "MTLstack";
int stackNameLength = strlen(stackName.c_str());

string dirImages = "/net/casfsc/fs/scratch24/ceholden/p013r031/images";
string dirPrefix = "LND";

string testimg = "/net/casfsc/fs/scratch24/ceholden/p013r031/images/LND0130311984162XXX08/L5013031_03119840610_MTLstack";
//string testimg = "/net/casfsb/vol/ssrchome/active_users/ceholden/test_stack";

string findStartImage() {
    // Find directories with images
    struct dirent *de = NULL;
    DIR *d = NULL;
    d = opendir(dirImages.c_str());
    if (d == NULL) {
        printf("Error: could not open %s\n", dirImages.c_str());
        exit(1);
    }
    int lenPrefix = strlen(dirPrefix.c_str());

    // Get first directory
    bool found = false;
    string dirStart, dirTest;

    while ((de = readdir(d)) != NULL && found == false) {
        dirTest = de->d_name;

        if (strncmp(dirTest.c_str(), 
                    dirPrefix.c_str(), 
                    lenPrefix) == 0) {
            dirStart = de->d_name;
            found = true;
        }
    }
    printf("Found first directory: %s\n", dirStart.c_str());
    printf("\n\n"); 
    dirStart = dirImages + "/" + dirStart;

    // Look inside this first directory for image
    d = opendir(dirStart.c_str());
    if (d == NULL) {
        printf("Error: could not open %s\n", dirStart.c_str());
        exit(1);
    }
    // Look for image stack
    found = false;
    string fileTest, fileTestLast, fileStart;
    while ((de = readdir(d)) != NULL && found == false) {
        // Get file
        fileTest = de->d_name;
        // If file length is more than stack name
        int fileTestLength = strlen(fileTest.c_str());
        if (fileTestLength > stackNameLength) {
            // Get last N length of test file
            fileTestLast = &fileTest[fileTestLength - stackNameLength];
            // Test if file is stack
            if (strcmp(fileTestLast.c_str(), stackName.c_str()) == 0) {
                fileStart = fileTest;
                found = true;
            }
        }    
    }
    fileStart = dirStart + "/" + fileStart;

    return (fileStart);
}

int findNumberOfImages() {
    // Number of images (what we return)
    int nImages = 0;
    
    // Find directories with images
    struct dirent *de = NULL;
    DIR *d = NULL;
    d = opendir(dirImages.c_str());
    if (d == NULL) {
        printf("Error: could not open %s\n", dirImages.c_str());
        exit(1);
    }
    int lenPrefix = strlen(dirPrefix.c_str());

    // Get first directory
    bool found = false;
    string dirTest, dirStart, dirImages;

    while ((de = readdir(d)) != NULL) {
        dirTest = de->d_name;

        if (strncmp(dirTest.c_str(), 
                    dirPrefix.c_str(), 
                    lenPrefix) == 0) {
            nImages++;            
        }
    }
    dirStart = dirImages + "/" + dirStart;

    return (nImages);
}
void getImageMetadata(string startImageName, int &nXSize, int &nYSize) { 
   // Read in starting image
    GDALDataset *poInDs;
    poInDs = (GDALDataset*) GDALOpen(startImageName.c_str(), GA_ReadOnly);
    if (poInDs == NULL) {
        printf("Error: could not open %s\n", startImageName.c_str());
        exit(1);
    }

    // Open band in dataset
    GDALRasterBand *poInBand;
    poInBand = poInDs->GetRasterBand(fmaskBand);
    nXSize = poInBand->GetXSize();
    nYSize = poInBand->GetYSize();
   
    GDALClose( (GDALDatasetH) poInDs);
}

// May not use this...
void checkImageNoOverlap(string fname, GByte *poMask) {
    // Open dataset
    GDALDataset *poDs;
    poDs = (GDALDataset*) GDALOpen(fname.c_str(), GA_ReadOnly);
    if (poDs == NULL ) {
        printf("Error: could not open %s\n", fname.c_str());
        exit(1);
    }

    // Open band in dataset
    GDALRasterBand *poBand;
    poBand = poDs->GetRasterBand(fmaskBand);

    // Read in band from dataset band
    int nXSize = poBand->GetXSize();
    int nYSize = poBand->GetYSize();
    int nBands = poDs->GetRasterCount();
    /*
    printf("Size is: %ix%i\n", nYSize, nXSize);
    printf("Data type size: %i\n", 
            GDALGetDataTypeSize(GDALGetRasterDataType(poBand)) *
            nXSize * nYSize);
    */

    int nXBlockSize, nYBlockSize;
    poBand->GetBlockSize(&nXBlockSize, &nYBlockSize);
    int nXBlocks = (nXSize + nXBlockSize - 1) / nXSize;
    int nYBlocks = (nYSize + nYBlockSize - 1) / nYSize;
    // printf("Block sizes: %ix%i\n", nXBlockSize, nYBlockSize);
    
    // Allocate memory for each band and for the image's edgemask
    GInt16 *poImage = 
        (GInt16*) CPLCalloc(sizeof(GInt16), nXSize * nYSize);
    
    GByte *poImageHasData =
        (GByte*) CPLCalloc(sizeof(GByte), nXSize * nYSize);
    
    // Loop through bands counting number of observations
    
    for (int b = 0; b < (nBands - 1); b++) {
        poBand = poDs->GetRasterBand(b + 1);
        for (int iYBlock = 0; iYBlock < nYBlocks; iYBlock++) {
            for (int jXBlock = 0; jXBlock < nXBlocks; jXBlock++) {
                int nXOff = jXBlock * nXSize;
                int nYOff = iYBlock * nYSize;
                poBand->RasterIO(GF_Read, nXOff, nYOff, nXSize, nYSize,
                        poImage, nXSize, nYSize,
                        GDALGetRasterDataType(poBand),
                        0, 0);
            }
        }    
        //printf("Read in data...\n");
    
        for (int row = 0; row < nYSize; row++) {
            for (int col = 0; col < nXSize; col++) {
                if (poImage[row * nXSize + col] != ledapsNoDataValue) {
                    poImageHasData[row * nXSize + col]++;
                } 
            }
        }
    }
    int masked = 0;
    for (int row = 0; row < nYSize; row++) {
        for (int col = 0; col < nXSize; col++) {
            if (poImageHasData[row * nXSize + col] > 0 &&
                    poImageHasData[row * nXSize + col] != (nBands - 1)) {
                poMask[row * nXSize + col] = 0;
                masked++;
            }
        }
    }
    printf("%i masked pixels\n", masked);

    // Free memory for exit
    CPLFree(poImage);
    CPLFree(poImageHasData);
    GDALClose( (GDALDatasetH) poDs);
}


void checkImageAllDataFmask(string fname, GByte *poMask) {
    // Open dataset
    GDALDataset *poDs;
    poDs = (GDALDataset*) GDALOpen(fname.c_str(), GA_ReadOnly);
    if (poDs == NULL ) {
        printf("Error: could not open %s\n", fname.c_str());
        exit(1);
    }

    // Open band in dataset
    GDALRasterBand *poBand;
    poBand = poDs->GetRasterBand(fmaskBand);

    // Read in band from dataset band
    int nXSize = poBand->GetXSize();
    int nYSize = poBand->GetYSize();
    int nBands = poDs->GetRasterCount();
    /*
    printf("Size is: %ix%i\n", nYSize, nXSize);
    printf("Data type size: %i\n", 
            GDALGetDataTypeSize(GDALGetRasterDataType(poBand)) *
            nXSize * nYSize);
    */

    int nXBlockSize, nYBlockSize;
    poBand->GetBlockSize(&nXBlockSize, &nYBlockSize);
    int nXBlocks = (nXSize + nXBlockSize - 1) / nXSize;
    int nYBlocks = (nYSize + nYBlockSize - 1) / nYSize;
    // printf("Block sizes: %ix%i\n", nXBlockSize, nYBlockSize);
    
    // Allocate memory for each band and for the image's edgemask
    GInt16 *poImage = 
        (GInt16*) CPLCalloc(sizeof(GInt16), nXSize * nYSize);
    
    // JUST USING FMASK VALUE
    int masked = 0;
    for (int iYBlock = 0; iYBlock < nYBlocks; iYBlock++) {
        for (int jXBlock = 0; jXBlock < nXBlocks; jXBlock++) {
        int nXOff = jXBlock * nXSize;
        int nYOff = iYBlock * nYSize;
        poBand->RasterIO(GF_Read, nXOff, nYOff, nXSize, nYSize,
            poImage, nXSize, nYSize,
            GDALGetRasterDataType(poBand),
            0, 0);
        }
    }
    for (int row = 0; row < nYSize; row++) {
        for (int col = 0; col < nXSize; col++) {
            if (poImage[row * nXSize + col] == fmaskNoDataValue) {
                poMask[row * nXSize + col] = 0;
                masked++;
            }
        }
    }

        
    printf("%i masked pixels\n", masked);

    // Free memory for exit
    CPLFree(poImage);
    GDALClose( (GDALDatasetH) poDs);
}

void checkAllImages(GByte *poMask) {
    // Setup for image archive location
    struct dirent *de = NULL;
    DIR *d = NULL;
    // Setup for individual image directories
    struct dirent *de_img = NULL;
    DIR *d_img = NULL;
    
    // Find directories with images
    d = opendir(dirImages.c_str());
    if (d == NULL) {
        printf("Error: could not open %s\n", dirImages.c_str());
        exit(1);
    }
    int lenPrefix = strlen(dirPrefix.c_str());

    // Get first directory
    string dirImage, fileTest, fileImage, fileImageLast;
    bool foundImage = false;
    int count = 0;
    while ((de = readdir(d)) != NULL) {
        dirImage = de->d_name;
        // Check if this directory starts with prefix
        if (strncmp(dirImage.c_str(), 
                    dirPrefix.c_str(), 
                    lenPrefix) == 0) {
            // Found one
            dirImage = dirImages + "/" + dirImage;
            // Look inside...
            foundImage = false;
            d_img = opendir(dirImage.c_str());
            while ((de_img = readdir(d_img)) != NULL && foundImage == false) {
                fileTest = de_img->d_name;
                // If file length is more than stack name,
                int fileImageLength = strlen(fileTest.c_str());
                if (fileImageLength > stackNameLength) {
                    fileImageLast = &fileTest[fileImageLength - 
                        stackNameLength];
                    // Test if file is stack
                    if (strcmp(fileImageLast.c_str(),
                                stackName.c_str()) == 0) {
                        // We found one, add on filename to fileImage
                        fileImage = dirImage + "/" + fileTest;
                        foundImage = true;
                    }
                }
            }
            // TODO: remove this anti-L7 check
            if (strncmp(fileTest.c_str(), "LE7", 3) != 0 &&
                    strncmp(fileTest.c_str(), "L7", 2) != 0) {
                // We've found our stack image, let's check mask agaisnt it
                printf("Checking mask against %s\n", fileImage.c_str());
                //checkImageNoOverlap(fileImage, poMask);
                checkImageAllDataFmask(fileImage, poMask);
                count++;
            }
            // TODO: Other technique - number of observations > value
        }
    }
    printf("Created mask based on %i images.\n", count);
}

int main(int argc, char *argv[]) {
    // Handle command line arguments
    for (int nArg=0; nArg < argc; ++nArg) {
        cout << nArg << ": " << argv[nArg] << endl;
    }
    return 0;

    printf("Image archive: %s\n", dirImages.c_str());
    printf("Prefix: %s\n", dirPrefix.c_str());
    
    // Register all drivers
    GDALAllRegister();
    
    // Find a directory with image
    string imageStart = findStartImage();
    int nImages = findNumberOfImages();

    // Setup mask
    int nXSize, nYSize;
    getImageMetadata(imageStart, nXSize, nYSize);
    
    // Allocate memory for mask
    GByte *poMask = (GByte*) CPLCalloc(sizeof(GByte), nXSize * nYSize);
    // Initalize to 1 (on)
    for (int row = 0; row < nYSize; row++) {
        for (int col = 0; col < nXSize; col++) {
            poMask[row * nXSize + col] = 1;        
        }
    }

    // Check all images in archive for mask
    checkAllImages(poMask);

    // Write out data
    string dstFilename = dirImages + "/" + "edgemask";
    printf("Writing out mask values to %s\n", dstFilename.c_str());
   
    // Setup output options
    const char *pszFormat = "ENVI";
    char **papszOptions = NULL;
    GDALDriver *poDstDriver;
    poDstDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);

    // Use starting image to create driver so we preserve metadata
    GDALDataset *poSrcDs = (GDALDataset*) GDALOpen(imageStart.c_str(),
            GA_ReadOnly);
    if (poSrcDs == NULL) {
        exit(1);
    }
    GDALDataset *poDstDs;
    // Createa  copy for new dataset
    poDstDs = poDstDriver->Create(dstFilename.c_str(), nXSize, nYSize,
            1, GDT_Byte, papszOptions);
    if (poDstDs == NULL) {
        printf("Error: could not create output dataset %s\n",
                dstFilename.c_str());
    }
    // Write out data
    GDALRasterBand *poDstBand;
    poDstBand = poDstDs->GetRasterBand(1);
    poDstBand->RasterIO(GF_Write, 0, 0, nXSize, nYSize,
            poMask, nXSize, nYSize, GDT_Byte, 0, 0);
    // Setup projection and geo-transform information
    poDstDs->SetProjection(poSrcDs->GetProjectionRef());
    double adfGeoTransform[6];
    poSrcDs->GetGeoTransform(adfGeoTransform);
    poDstDs->SetGeoTransform(adfGeoTransform);

    // Close and exit
    GDALClose((GDALDatasetH) poSrcDs);
    GDALClose((GDALDatasetH) poDstDs); 

}
