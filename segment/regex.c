#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <gdal.h>
#include "segport.h"
#include "segment.h"
#include<sys/stat.h>

#include <regex.h>        

int file_exists (char * fileName)
{
   struct stat buf;

   if ( stat ( fileName, &buf ) ) return 1;
   else return 0;
}

void main(){
    int reti;
    char msgbuf[256];
    regex_t regex;

  /* Compile regular expression */
  reti = regcomp(&regex, "^samples", 0);
  if( reti ){ fprintf(stderr, "Could not compile regex\n"); exit(1); }

  /* Execute regular expression */
  reti = regexec(&regex, "samples = 19",0, NULL, 0);
  if( !reti ){
    puts("Match");
  }
  else if( reti == REG_NOMATCH ){
    puts("No match");
  }
  else{
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    exit(1);
  }

/* Free compiled regular expression if you want to use the regex_t again */
    regfree(&regex);

  return;

}
