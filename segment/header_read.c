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
  int i;
  char* header_name;
  char cmd[256];

  // initializae GDAL library

  //system("pwd");
  printf("Before dying\n");

  printf("In header_read file is %s\n",(operands.args.astr_p)[0]);
  printf("After dying\n");


  strncpy(header_name,(operands.args.astr_p)[0],strlen((operands.args.astr_p)[0])-7);

  header_name = strcat(header_name,"bsq\0");
  //strcpy(header_name, header_name+1);
  printf("header_name = *%s*\n", header_name);
  printf("String compare %d\n",strcmp(header_name,"../testsmall.bsq"));


  // register GDAL
  GDALAllRegister();

  
  // convert from BSQ to BIP format
  if (file_exists("temp.bip")) unlink("temp.bip");
  if (file_exists(header_name))printf("Header file exists!\n");

  sprintf(cmd,"gdal_translate -of ENVI -ot Byte -scale -co INTERLEAVE=BIP -co SUFFIX=ADD testsmall.bsq temp_bip");
  printf("---- %s\n",cmd);
  if( ! system(cmd) )printf ("Conversion of bsq to bip is unsecceeful ...\n");

  // open bip file
  //hDataset = GDALOpen("../testsmall.bsq" , GA_ReadOnly ); 
  //hDataset = GDALOpen("/projectnb/scv/katia/projects/segmentation/2014_segment/testsmall.bsq" , GA_ReadOnly ); 
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
