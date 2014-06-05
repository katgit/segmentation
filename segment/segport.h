

#ifndef	SEGPORT_H
#define	SEGPORT_H


typedef int     aint_t;
typedef long    along_t;
typedef double  areal_t;
typedef char   *astr_t;

typedef union {
	aint_t         *aint_p;
	along_t        *along_p;
	areal_t        *areal_p;
	astr_t         *astr_p;
} ARGS_T;


typedef struct {
	char            option;
	char           *descrip;
	int             type;
	char           *arg_descrip;
        int          required;
	int             min_nargs;
	int             max_nargs;
	int             nargs;
	ARGS_T          args;
} OPTION_T_OP;

int get_header_field_value(char* line, const char* field_name, int field_type, int* pval, char sval[]);

#endif
