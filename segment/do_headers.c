
#include <memory.h>
#include <math.h>
#include <string.h>

#include "segment.h"
#include "gethdrs.h"

void
do_headers(Spr, ifd, mfd)
Seg_proc        Spr;
int             ifd;
int             mfd;
{
    int             band;	/* band index */
    BIH_T         **i_bihpp;	/* -> input BIH */
    BIH_T         **m_bihpp;	/* -> mask BIH */

    FILE *fp;

printf("do_headers step 1\n");

 /*
  * read input BIH
  */
    i_bihpp = bihread(ifd);
printf("do_headers step 2\n");
    if (i_bihpp == NULL) {
	error("can't read basic image header for input file");
    }
    Spr->i_bihpp = i_bihpp;

    Spr->nlines = hnlines(ifd);
    if (Spr->nlines > MAXSHORT)
	error("Image has too many (%d) lines\n", Spr->nlines);
    Spr->nsamps = hnsamps(ifd);
    if (Spr->nsamps > MAXSHORT)
	error("Image has too many (%d) samps\n", Spr->nsamps);
    Spr->nbands = hnbands(ifd);
    if (Spr->nbands > MAXSHORT)
	error("Image has too many (%d) bands\n", Spr->nbands);

 /*
  * Check that all bands are 8 bit
  */
printf("do_headers step 3\n");
    for (band = 0; band < Spr->nbands; band++) {
	if (bih_nbytes(i_bihpp[band]) != 1 ||
	    bih_nbits(i_bihpp[band]) != 8)
	    error("Band #%d is %d bits per pixel\n",
		  band,
		  bih_nbits(i_bihpp[band]));
    }

 /*
  * Skip other input headers
  */
printf("do_headers step 4\n");
    skiphdrs(ifd);

 /*
  * If there is a mask image, process its headers and make sure it is
  * compatible with the input image.
  */
    if (sf_get(Spr, SF_MASK)) {
	m_bihpp = bihread(mfd);
	if (m_bihpp == NULL) {
	    error("can't read basic image header for mask file");
	}
	if (hnbands(mfd) != 1)
	    error("Mask image has %d bands", hnbands(mfd));
	if (Spr->nlines != hnlines(mfd))
	    error("Input and mask images have different number of lines");
	if (Spr->nsamps != hnsamps(mfd))
	    error("Input and mask images have different number of samples");
	if (bih_nbytes(m_bihpp[0]) != 1)
	    error("The mask image is not 1 byte per pixel");

	skiphdrs(mfd);
    }

printf("do_headers step 5\n");
    fp=fopen("original_spr_bin","wb");
printf("do_headers step 6\n");

    if (!fp){
      printf("Unable to open file!");
      return;
    }

    fwrite(&Spr, sizeof(Spr), 1, fp);

    fclose(fp);
printf("do_headers step 7\n");

}

