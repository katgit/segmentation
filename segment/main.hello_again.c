

#ifndef lint
static char     SCCS_ID[] = "main.c 2.11  6/22/92";

#endif

#include "segment.h"

#include "getargs.h"

int header_read(OPTION_T operands,seg_proc *);

main(argc, argv)
int             argc;
char          **argv;
{
    static OPTION_T opt_t = {
	't',
	"segmentation tolerances",
	REAL_OPTARGS,
	"toler",
	REQUIRED,
    };

    static OPTION_T opt_l = {
	'l',
	"threshold base and increment",
	REAL_OPTARGS,
	"real",
	OPTIONAL, 2, 2
    };

    static OPTION_T opt_o = {
	'o',
	"basename for output files",
	STR_OPTARGS,
	"basename",
	REQUIRED, 1, 1
    };

    static OPTION_T opt_b = {
	'b',
	"index of band for output",
	INT_OPTARGS,
	"band",
	OPTIONAL, 1, 1
    };

    static OPTION_T opt_m = {
	'm',
	"merge coefficient",
	REAL_OPTARGS,
	"mrg_coef",
	OPTIONAL, 1, 1
    };

    static OPTION_T opt_n = {
	'n',
	"region size restrictions",
	INT_OPTARGS,
	"int",
	OPTIONAL, 1, 5
    };

    static OPTION_T opt_B = {
	'B',
	"index of band for normality criterion",
	INT_OPTARGS,
	"band",
	OPTIONAL, 1, 1
    };

    static OPTION_T opt_N = {
	'N',
	"normality interval",
	REAL_OPTARGS,
	"real",
	OPTIONAL, 2, 2
    };

    static OPTION_T opt_8 = {
	'8',
	"8-way neighbors",
    };

    static OPTION_T opt_A = {
	'A',
	"auxiliary region map mask",
    };

    static OPTION_T opt_h = {
	'h',
	"output hsegment files",
    };

    static OPTION_T opt_M = {
	'M',
	"mask image",
	STR_OPTARGS,
	"maskfile",
	OPTIONAL, 1, 1
    };

    static OPTION_T operands = {
	OPERAND,
	"input image file",
	STR_OPERANDS,
	"image",
	OPTIONAL, 1, 1
    };

    static OPTION_T *optv[] = {
	&opt_t,
	&opt_l,
	&opt_o,
	&opt_b,
	&opt_m,
	&opt_n,
	&opt_B,
	&opt_N,
	&opt_8,
	&opt_A,
	&opt_h,
	&opt_M,
	&operands,
	0
    };


    seg_proc        sproc;	/* struct that maintains segmentation state */
    int             fdi = -1;	/* input image file descriptor	 */
    int             fdm = -1;	/* mask image file descriptor	 */
    int             i;		/* index */

printf("hello world again\n");
    return(0);
}
