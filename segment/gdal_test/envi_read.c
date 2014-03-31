#include <stdlib.h>
#include <stdio.h>

#include <gdal.h>
#include "cpl_conv.h"

int main(int argc, char ** argv){

  GDALDatasetH hDataset=NULL;
  char cmd[256];

  char **papszMetadata = NULL;
  int i;

  // initializae GDAL library
  GDALAllRegister();
  
  // make sure we have input and output file
  if(argc <3) {
    //printf("usage: envi_read <inputfile> <outputfile>\n");
    printf("Using default file names!\n");
    sprintf(cmd," echo 'gdal_translate -of ENVI -ot Byte -scale -co INTERLEAVE=BIP -co SUFFIX=ADD testsmall.bsq temp_byte_bip' >our_envi.out" );
  }else{

  // prepare a string for the system command
    sprintf(cmd,"gdal_translate -of ENVI -ot Byte -scale -co INTERLEAVE=BIP -co SUFFIX=ADD %s %s", argv[1], argv[2] );
  }

  // convert input file
  if (! system(cmd) )printf("Conversion of bsq to bip is unseccessful...\n");

  // open bip file
  hDataset = GDALOpen( "temp_byte_bip", GA_ReadOnly );
  if (hDataset == NULL){
    printf("Alas...\n");
  } else{
    printf("Success!\n");
  }

  // read metadata from bip file
  papszMetadata = GDALGetMetadata( hDataset, "ENVI" );
  if (papszMetadata == NULL){
    printf("no metadata...\n");
  } else{
    printf("Read metadata!\n");

    // print the matadata to the screen
    for (i=0; i< 13; i++){
      printf("%s\n",papszMetadata[i]);
    }

  }
  
  // close bip file 
  GDALClose(hDataset);

  return;

}
