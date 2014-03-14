#include <stdlib.h>
#include <stdio.h>

#include <gdal.h>
//include "cpl_conv.h"
#include "segport.h"
#include "segment.h"


int header_read( OPTION_T_OP operands, Seg_proc Spr){

  GDALDatasetH hDataset=NULL;

  char **papszMetadata = NULL;
  int i;

  // initializae GDAL library


  printf("In header_read file is %s\n",(operands.args.astr_p)[0]);
  return(0);

  GDALAllRegister();


  char* header_name;

  // open bip file
  hDataset = GDALOpen( header_name, GA_ReadOnly );
  if (hDataset == NULL){
    printf("Error openning header bip file\n");
    return(-1);
  } else{
    printf("Header Bip file openned correctly!\n");
  }

  
  // read metadata from bip file
  papszMetadata = GDALGetMetadata( hDataset, "ENVI" );
  if (papszMetadata == NULL){
    printf("no metadata...\n");
    return(-2);
  } else{
    printf("Read metadata!\n");

    // print the matadata to the screen
    for (i=0; i< 13; i++){
      printf("%s\n",papszMetadata[i]);
    }

  }
  
  // close bip file 
  GDALClose(hDataset);

  printf("End of header_read function.\n");

  return(0);

}
