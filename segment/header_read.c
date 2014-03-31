#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <gdal.h>
//include "cpl_conv.h"
#include "segport.h"
#include "segment.h"
#include<sys/stat.h>



int file_exists (char * fileName)
{
   struct stat buf;

   if ( stat ( fileName, &buf ) ) return 1;
   else return 0;
}


int header_read( OPTION_T_OP operands, Seg_proc Spr){

  GDALDatasetH hDataset=NULL;

  char **papszMetadata = NULL;
  int i,j;
  char header_name[512];
  char cmd[256];
  int ierr;
  int len;


  // initializae GDAL library
  //printf("In header_read file is %s\n",(operands.args.astr_p)[0]);

  printf("Our header file from command *%s*\n",operands.args.astr_p[0]);

  len=strlen((operands.args.astr_p)[0])-4 ;
  for(i=0; i<len;i++){
      header_name[i]=*((operands.args.astr_p)[0]+i);
      printf("Copied char %c\n",header_name[i]);
  }
  printf("Our new header file  *%s*\n", header_name);


  // register GDAL
  GDALAllRegister();
  
  // convert from BSQ to BIP format
  if (file_exists("temp_bip")) unlink("temp_bip");
  if (file_exists(header_name))printf("Header file *%s* exists!\n", header_name);

  //sprintf(cmd,"gdal_translate -of ENVI -ot Byte -scale -co INTERLEAVE=BIP -co SUFFIX=ADD ../testsmall.bsq temp_bip", header_name);
  sprintf(cmd,"gdal_translate -of ENVI -ot Byte -scale -co INTERLEAVE=BIP -co SUFFIX=ADD %s temp_bip", header_name);
  printf("---- %s\n",cmd);
  ierr= system(cmd) ;
  printf ("Conversion of bsq to bip: error code=%d \n", ierr);

  // open bip file
  hDataset = GDALOpen( "temp_bip", GA_ReadOnly );
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
