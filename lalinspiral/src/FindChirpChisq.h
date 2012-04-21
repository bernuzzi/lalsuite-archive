/*
*  Copyright (C) 2007 Duncan Brown, Eirini Messaritaki, Jolien Creighton
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with with program; see the file COPYING. If not, write to the
*  Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
*  MA  02111-1307  USA
*/

/*-----------------------------------------------------------------------
 *
 * File Name: FindChirpChisq.h
 *
 * Author: Anderson, W. G., and Brown, D. A.
 *
 *-----------------------------------------------------------------------
 */

#ifndef _FINDCHIRPCHISQH_H
#define _FINDCHIRPCHISQH_H

#include <lal/LALDatatypes.h>
#include <lal/FindChirpDatatypes.h>

#if defined(__cplusplus)
extern "C" {
#elif 0
} /* so that editors will match preceding brace */
#endif


/**
   \addtogroup FindChirpChisq_h
   \author Anderson, W. G., and Brown, D. A.

\brief Provides prototypes and functions to perform a \f$\chi^2\f$ veto on binary
inspiral chirps using data generated by the <tt>FindChirpFilter()</tt>
function.

\heading{Synopsis}
\code
#include <lal/FindChirpChisq.h>
\endcode

*/
/*@{*/

/**\name Error Codes */
/*@{*/
#define FINDCHIRPCHISQH_ENULL 1	/**< Null pointer */
#define FINDCHIRPCHISQH_ENNUL 2	/**< Non-null pointer */
#define FINDCHIRPCHISQH_ENUMZ 3	/**< Number of points is zero or negative */
#define FINDCHIRPCHISQH_ECHIZ 4	/**< Number of chisq bins is zero or negative */
#define FINDCHIRPCHISQH_EALOC 5	/**< Memory allocation error */
#define FINDCHIRPCHISQH_EUAPX 6	/**< Unknown waveform approximant */
#define FINDCHIRPCHISQH_EIAPX 7	/**< Incorrect waveform approximant */
#define FINDCHIRPCHISQH_EBINS 8	/**< Error computing chisq bin boundaries */
/*@}*/

/** \cond DONT_DOXYGEN */
#define FINDCHIRPCHISQH_MSGENULL "Null pointer"
#define FINDCHIRPCHISQH_MSGENNUL "Non-null pointer"
#define FINDCHIRPCHISQH_MSGENUMZ "Number of points is zero or negative"
#define FINDCHIRPCHISQH_MSGECHIZ "Number of chisq bins is zero or negative"
#define FINDCHIRPCHISQH_MSGEALOC "Memory allocation error"
#define FINDCHIRPCHISQH_MSGEUAPX "Unknown waveform approximant"
#define FINDCHIRPCHISQH_MSGEIAPX "Incorrect waveform approximant"
#define FINDCHIRPCHISQH_MSGEBINS "Error computing chisq bin boundaries"
/** \endcond */


/* --- structure for storing input to the chisq veto --------------------- */

/** This structure contains the input to the \f$\chi^2\f$ veto function.
The quantities should be populated by <tt>FindChirpFilter()</tt> on entry.
The fields are:

<dl>
<dt><tt>COMPLEX8Vector *qtildeVec</tt></dt><dd> A vector containing the frequncy
domain quantity \f$\tilde{q}_k\f$ as defined in <tt>FindChirpFilter()</tt>.</dd>

<dt><tt>COMPLEX8Vector *qVec</tt></dt><dd> A vector containing the time
domain quantity \f$q_j\f$ as defined in <tt>FindChirpFilter()</tt>.</dd>
</dl>

*/
typedef struct
tagFindChirpChisqInput
{
  COMPLEX8Vector               *qtildeVec;
  COMPLEX8Vector               *qVec;
}
FindChirpChisqInput;


/* --- parameter structure for the chisq veto ---------------------------- */

/** This structure contains the parameters used by the \f$\chi^2\f$ veto
function <tt>FindChirpChisqVeto()</tt>.  It is created and destroyed by the
<tt>FindChirpChisqVetoInit()</tt> and <tt>FindChirpChisqVetoFinalize()</tt>
functions. The fields are:

<dl>
<dt><tt>REAL4 norm</tt></dt><dd> The normalization factor for the SP templates.
Equals \f$4 \Delta t / (N segNorm)\f$.</dd>

<dt><tt>REAL4 a1</tt></dt><dd> BCV-template normalization parameter.</dd>

<dt><tt>REAL4 b1</tt></dt><dd> BCV-template normalization parameter.</dd>

<dt><tt>REAL4 b2</tt></dt><dd> BCV-template normalization parameter.</dd>

<dt><tt>REAL4 bankMatch</tt></dt><dd> Template bank match...</dd>

<dt><tt>UINT4Vector *chisqBinVec</tt></dt><dd> A vector containing the boundaries
of the bins for the chi-squared veto for the stationary phase chirps, or the
boundaries of the bins for the first sum of the chi-squared veto for the
BCV templates.</dd>

<dt><tt>UINT4Vector *chisqBinVecBCV</tt></dt><dd> A vector containing the boundaries
of the bins for the second part of the chi-squared statistic, for the BCV
templates.</dd>

<dt><tt>ComplexFFTPlan *plan</tt></dt><dd> The FFTW plan used by the inverse DFT.</dd>

<dt><tt>COMPLEX8Vector *qtildeBinVec</tt></dt><dd> ...</dd>

<dt><tt>COMPLEX8Vector *qtildeBinVecBCV</tt></dt><dd> ...</dd>

<dt><tt>COMPLEX8Vector **qBinVecPtr</tt></dt><dd> Pointer to an array of pointers.
Corresponds to \f$q^{(1)}_l(t_j)\f$, which is the contribution of the \f$l\f$-th
frequency
bin to the signal-to-noise ratio at the time \f$t_j\f$ (up to the appropriate
normalization). It is used for both the stationary phase chirps and the
BCV templates.</dd>

<dt><tt>COMPLEX8Vector **qBinVecPtrBCV</tt></dt><dd> Pointer to an array of pointers.
Corresponds to \f$q^{(2)}_l(t_j)\f$, which is the contribution of the \f$l\f$-th
frequency
bin to the signal-to-noise ratio at the time \f$t_j\f$ (up to the appropriate
normalization). It is used only for the BCV templates.
</dd>
</dl>

*/
typedef struct
tagFindChirpChisqParams
{
  REAL4                         norm;
  REAL4                         a1;
  REAL4                         b1;
  REAL4                         b2;
  UINT4Vector                  *chisqBinVec;
  UINT4Vector                  *chisqBinVecBCV;
  ComplexFFTPlan               *plan;
  COMPLEX8Vector               *qtildeBinVec;
  COMPLEX8Vector               *qtildeBinVecBCV;
  COMPLEX8Vector              **qBinVecPtr;
  COMPLEX8Vector              **qBinVecPtrBCV;
  Approximant                   approximant;
}
FindChirpChisqParams;

/*@}*/

/* ---------- Function prototypes ---------- */

void
LALFindChirpChisqVetoInit (
    LALStatus                  *status,
    FindChirpChisqParams       *params,
    UINT4                       numChisqBins,
    UINT4                       numPoints
    );

void
LALFindChirpChisqVetoFinalize (
    LALStatus                  *status,
    FindChirpChisqParams       *params,
    UINT4                       numChisqBins
    );

void
LALFindChirpComputeChisqBins(
    LALStatus                  *status,
    UINT4Vector                *chisqBinVec,
    FindChirpSegment           *fcSeg,
    UINT4                       kmax
    );

void
LALFindChirpChisqVeto (
    LALStatus                  *status,
    REAL4Vector                *chisqVec,
    FindChirpChisqInput        *input,
    FindChirpChisqParams       *params
    );

#if 0
{ /* so that editors will match succeeding brace */
#elif defined(__cplusplus)
}
#endif

#endif /* _FINDCHIRPCHISQH_H */
