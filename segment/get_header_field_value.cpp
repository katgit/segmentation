#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>        

#define DEBUG 1

// field type 1=integer 2=string
int get_header_field_value(const char* line, const char* field_name, int field_type, int* pval, char* sval){
	const int PMATCH_SIZE=30;
	const int BUFFER_SIZE=255;	
    int reti;
    char msgbuf[BUFFER_SIZE];
	int slen=0;
	char sregex[BUFFER_SIZE];
	sregex[slen]='\n';
    regex_t regex;
	regmatch_t pmatch[PMATCH_SIZE];

	const char* s1="^(";
	strncpy(sregex+slen,s1,strlen(s1));
	slen+=strlen(s1);

	strncpy(sregex+slen,field_name,strlen(field_name));	
	slen+=strlen(field_name);

	char* s2;
	if(field_type == 1){
		s2="[[:blank:]]*=[[:blank:]]*)([0-9]+)([[:blank:]]*)$";
	} else if(field_type == 2){
		s2="[[:blank:]]*=[[:blank:]]*)([[:alnum:]]+)([[:blank:]]*)$";
	} else {
		fprintf(stderr, "Field type can be only 1 or 2\n");
		return(1);
	}

	strncpy(sregex+slen,s2,strlen(s2));
	slen+=strlen(s2);
	sregex[slen]='\0';
	if(DEBUG){
		printf("Regex string: %s\n",sregex);
		printf("line: %s\n",line);
	}	
	
  	/* Compile regular expression */
  	reti = regcomp(&regex, sregex, REG_EXTENDED);
  	if( reti ){ fprintf(stderr, "Could not compile regex\n"); exit(1); }

  	/* Execute regular expression */
	// int regexec(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
	// return value = 0 for match, otherwise error code
	// preg = precompiled regex expression
	// string = string to match
	// nmatch = number of pmatch elements
	// pmatch = array of two integer structure containing begin and end offset of match
    reti = regexec(&regex,line,PMATCH_SIZE,pmatch,0);

  	if( !reti ){
		if(DEBUG){
			puts("Match");
			for(int i=0;i<PMATCH_SIZE;i++){
				if(pmatch[i].rm_so == -1) break;
				printf("pmatch[%d] rm_so: %d rm_eo: %d\n",i,pmatch[i].rm_so,pmatch[i].rm_eo); 
			}
		}
		char stemp[256];
		strncpy(stemp, line+pmatch[2].rm_so, pmatch[2].rm_eo - pmatch[2].rm_so);
		stemp[pmatch[2].rm_eo-pmatch[2].rm_so]='\0';
		if(field_type == 1){
			*pval = atoi(stemp);
			if(DEBUG){
				printf("Val: *%s* %d\n",stemp,atoi(stemp));
			}
		} else if(field_type == 2){
			strcpy(sval,stemp);
			if(DEBUG){
				printf("Val: *%s*\n",sval);
			}
		}
	}
  	else if(DEBUG && reti == REG_NOMATCH ){
    	puts("No match");
  	}
  	else if (DEBUG){
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		fprintf(stderr, "Regex match failed: %s\n", msgbuf);
		return(1);
  	}

	/* Free compiled regular expression if you want to use the regex_t again */
    regfree(&regex);

  	return(0);
}
