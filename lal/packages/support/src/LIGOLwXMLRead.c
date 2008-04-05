/*
*  Copyright (C) 2007 Andres C. Rodriguez, Alexander Dietz, Duncan Brown, Jolien Creighton, Kipp Cannon, Lisa M. Goggin, Patrick Brady, Robert Adam Mercer, Saikat Ray-Majumder, Anand Sengupta, Stephen Fairhurst, Xavier Siemens, Craig Robinson , Sean Seader, Thomas Cokelaer
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
 * File Name: LIGOLwXMLRead.c
 *
 * Author: Brown, D. A.
 * 
 * Revision: $Id$
 * 
 *-----------------------------------------------------------------------
 */

#if 0
<lalVerbatim file="LIGOLwXMLReadCV">
Author: Brown, D. A. and Fairhurst, S.
$Id$
</lalVerbatim> 
#endif

#include <string.h>
#include <lal/LALStdio.h>
#include <lal/LALStdlib.h>
#include <lal/LALConstants.h>
#include <lal/LALInspiral.h>
#include <lal/LALInspiralBank.h>
#include <lal/LIGOMetadataTables.h>
#include <lal/LIGOMetadataUtils.h>
#include <lal/LIGOLwXMLRead.h>
#include <lal/Date.h>

NRCSID( LIGOLWXMLREADC, "$Id$" );

#if 0
<lalLaTeX>
\subsection{Module \texttt{LIGOLwXMLRead.c}}

Routines to write LIGO metadata database structures to LIGO lightweight XML
files.

\subsubsection*{Prototypes}
\input{LIGOLwXMLReadCP}
\idx{LALSnglBurstTableFromLIGOLw()}
\idx{LALSnglInspiralTableFromLIGOLw()}
\idx{InspiralTmpltBankFromLIGOLw()}
\idx{SimInspiralTableFromLIGOLw()}
\idx{XLALSearchSummaryTableFromLIGOLw()}
\idx{SummValueTableFromLIGOLw()}
\idx{LALStochasticTableFromLIGOLw()}
\idx{LALStochSummTableFromLIGOLw()}

\subsubsection*{Description}

  The routine \verb+LALSnglBurstTableFromLIGOLw+ reads in a \verb+single_burst+
  table from a LIGOLwXML file  specified in \verb+fileName+; \verb+eventHead+
  provides a pointer to the head of a linked list of \verb+SnglBurstTable+s
  containing the events.  The routine is passed the \verb+fileName+ of an XML file
  containing a \verb+sngl_burst+ table.  First, the table is opened using
  \verb+MetaioOpenTable+.  Then a directory of the table is generated using
  \verb+LALCreateMetaTableDir+.  Rows of the table are read in sequentially from
  the file.  Each entry in the row is stored in the appopriate entry of a
  \verb+SnglBurstTable+ which is appended to the end of a linked list of such
  tables.  When all rows have been read in, the file is closed using
  \verb+MetaioClose+.  \verb+eventHead+ is set to point to the head of the linked
  list of \verb+SnglBurstTable+s.  

  The routine \verb+LALSnglInspiralTableFromLIGOLw+ reads in a
  \verb+sngl_inspiral+ table from the LIGOLwXML file specified in \verb+fileName+.
  It returns the number of triggers read in and \verb+eventHead+ provides a
  pointer to the head of a linked list of \verb+SnglInspiralTable+s containing the
  events.  It will return all events between the \verb+startEvent+ and
  \verb+stopEvent+; if these are set to 0 and -1 respectively, all events are
  returned.

  The routine \verb+InspiralTmpltBankFromLIGOLw+ reads in a \verb+sngl_inspiral+
  table from the LIGOLwXML file specified in \verb+fileName+. It returns the
  number of templates read in and \verb+bankHead+ provides a pointer to the head
  of a linked list of \verb+InspiralTemplate+s containing the templates read in.
  It will return all events between the \verb+startTmplt+ and \verb+stopTmplt+; if
  these are set to 0 and -1 respectively, all events are returned.  Although a
  \verb+sngl_inspiral+ table is read in, only those entries relevant for an
  InspiralTemplate are read in and stored.

  The routine \verb+SimInspiralTableFromLIGOLw+ reads in a \verb+sim_inspiral+
  table from the LIGOLwXML file specified in \verb+fileName+.  It returns the
  number of rows read in and \verb+SimHead+ provides a pointer to the head of a
  linked list of \verb+SimInspiralTable+s containing the events.  Additionally, a
  \verb+startTime+ and \verb+endTime+ are specified.  Only simulated events
  occuring between these times are returned.  If the \verb+endTime+ is set to
  zero, then all events are returned.

  The routine \verb+XLALSearchSummaryTableFromLIGOLw+ reads in a
  \verb+search_summary+ table from the LIGOLwXML file specified in
  \verb+fileName+.  It returns a pointer to the head of a linked list of
  \verb+SearchSummaryTable+s.

  The routine \verb+SummValueTableFromLIGOLw+ reads in a \verb+summ_value+
  table from the LIGOLwXML file specified in \verb+fileName+.  It returns the
  number of rows read in and \verb+sumHead+ provides a pointer to the head of a
  linked list of \verb+SummValueTable+s.

  The routine \verb+LALStochasticTableFromLIGOLw+ reads in a
  \verb+stochastic_table+ table from the LIGOLwXML file specified in
  \verb+fileName+.  It returns the number of rows read in and
  \verb+stochHead+ provides a pointer to the head of a linked list of
  \verb+StochasticTable+s.

  The routine \verb+LALStochSummTableFromLIGOLw+ reads in a
  \verb+stoch_summ_table+ table from the LIGOLwXML file specified in
  \verb+fileName+.  It returns the number of rows read in and
  \verb+stochSummHead+ provides a pointer to the head of a linked list of
  \verb+StochSummTable+s.


  \subsubsection*{Algorithm}

  None.

  \subsubsection*{Uses}
  Functions in the Metaio library:
  \begin{itemize}
  \item \verb+MetaioFindColumn+
  \item \verb+MetaioGetRow+
  \item \verb+MetaioOpenTable+
  \item \verb+MetaioClose+
  \end{itemize}
  \subsubsection*{Notes}

  %% Any relevant notes.

  \vfill{\footnotesize\input{LIGOLwXMLReadCV}}

  </lalLaTeX>
#endif

#define XLAL_CLOBBER_EVENTS \
  while ( eventHead ); \
{ \
  thisEvent = eventHead; \
  eventHead = (eventHead)->next; \
  LALFree( thisEvent ); \
  thisEvent = NULL; \
}


/* <lalVerbatim file="LIGOLwXMLReadCP"> */
ProcessTable    * XLALProcessTableFromLIGOLw (
    CHAR               *fileName
    )
/* </lalVerbatim> */
{
  static const char   *func = "XLALProcessTableFromLIGOLw";
  int                                   i, j, nrows;
  int                                   mioStatus=0;
  ProcessTable                         *thisEvent = NULL;
  ProcessTable                         *eventHead = NULL;
  struct MetaioParseEnvironment         parseEnv;
  const  MetaioParseEnv                 env = &parseEnv;
  MetaTableDirectory                   *tableDir = NULL;

  /* open the XML file */
  mioStatus = MetaioOpenTable( env, fileName, "process" );
  if ( mioStatus )
  {
    XLAL_ERROR_NULL( func, XLAL_EIO );
  }

  /* create table directory to find columns in file*/
  tableDir = XLALCreateMetaTableDir(env, process_table);

  /* loop over the rows in the file */
  i = nrows = 0;
  while ( (mioStatus = MetaioGetRow(env)) == 1 ) 
  {
    /* count the rows in the file */
    i++;

    /* allocate memory for the template we are about to read in */
    if ( ! eventHead )
    {
      thisEvent = eventHead = (ProcessTable *) 
        LALCalloc( 1, sizeof(ProcessTable) );
    }
    else
    {
      thisEvent = thisEvent->next = (ProcessTable *) 
        LALCalloc( 1, sizeof(ProcessTable) );
    }
    if ( ! thisEvent )
    {
      fprintf( stderr, "could not allocate process table\n" );
      XLAL_CLOBBER_EVENTS;
      MetaioClose( env );
      XLAL_ERROR_NULL( func, XLAL_ENOMEM );
    }

    /* parse the contents of the row into the ProcessTable structure */
    for ( j = 0; tableDir[j].name; ++j )
    {
      REAL4 r4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_4;
      /* REAL8 r8colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_8; */
      INT4  i4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_4s;

      if ( tableDir[j].idx == 0 )
      {
        LALSnprintf( thisEvent->program, LIGOMETA_PROGRAM_MAX * sizeof(CHAR), 
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 1 )
      {
        LALSnprintf( thisEvent->version, LIGOMETA_VERSION_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 2 )
      {
        LALSnprintf( thisEvent->cvs_repository, LIGOMETA_CVS_REPOSITORY_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 3 )
      {
        thisEvent->cvs_entry_time.gpsSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 4 )
      {
        LALSnprintf( thisEvent->comment, LIGOMETA_COMMENT_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 5 )
      {
        thisEvent->is_online = i4colData;
      }
      else if ( tableDir[j].idx == 6 )
      {
        LALSnprintf( thisEvent->node, LIGOMETA_NODE_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 7 )
      {
        LALSnprintf( thisEvent->username, LIGOMETA_USERNAME_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 8 )
      {
        thisEvent->start_time.gpsSeconds = i4colData;
        thisEvent->start_time.gpsNanoSeconds = 0;
      }
      else if ( tableDir[j].idx == 9 )
      {
        thisEvent->end_time.gpsSeconds = i4colData;
        thisEvent->end_time.gpsNanoSeconds = 0;
      }
      else if ( tableDir[j].idx == 10 )
      {
        thisEvent->jobid = i4colData;
      }
      else if ( tableDir[j].idx == 11 )
      {
        LALSnprintf( thisEvent->domain, LIGOMETA_DOMAIN_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 12 )
      {
        LALSnprintf( thisEvent->ifos, LIGOMETA_IFOS_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else
      {
        XLAL_CLOBBER_EVENTS;
        XLAL_ERROR_NULL( func, XLAL_EIO);
      }
    }
    /* count the number of triggers parsed */
    nrows++;
  }

  if ( mioStatus == -1 )
  {
    fprintf( stderr, "error parsing after row %d\n", i );
    XLAL_CLOBBER_EVENTS;
    MetaioClose( env );
    XLAL_ERROR_NULL( func, XLAL_EIO);
  }

  /* Normal exit */
  LALFree( tableDir );
  MetaioClose( env );

  return eventHead;
}



/* <lalVerbatim file="LIGOLwXMLReadCP"> */
ProcessParamsTable    * XLALProcessParamsTableFromLIGOLw (
    CHAR               *fileName
    )
/* </lalVerbatim> */
{
  static const char   *func = "XLALProcessParamsTableFromLIGOLw";
  int                                   i, j, nrows;
  int                                   mioStatus=0;
  ProcessParamsTable                       *thisEvent = NULL;
  ProcessParamsTable                       *eventHead = NULL;
  struct MetaioParseEnvironment         parseEnv;
  const  MetaioParseEnv                 env = &parseEnv;
  MetaTableDirectory                   *tableDir = NULL;

  /* open the process params XML file */
  mioStatus = MetaioOpenTable( env, fileName, "process_params" );
  if ( mioStatus )
  {
    XLAL_ERROR_NULL( func, XLAL_EIO );
  }

  /* create table directory to find columns in file*/
  tableDir = XLALCreateMetaTableDir(env, process_params_table);

  /* loop over the rows in the file */
  i = nrows = 0;
  while ( (mioStatus = MetaioGetRow(env)) == 1 ) 
  {
    /* count the rows in the file */
    i++;

    /* allocate memory for the template we are about to read in */
    if ( ! eventHead )
    {
      thisEvent = eventHead = (ProcessParamsTable *) 
        LALCalloc( 1, sizeof(ProcessParamsTable) );
    }
    else
    {
      thisEvent = thisEvent->next = (ProcessParamsTable *) 
        LALCalloc( 1, sizeof(ProcessParamsTable) );
    }
    if ( ! thisEvent )
    {
      fprintf( stderr, "could not allocate process params event\n" );
      XLAL_CLOBBER_EVENTS;
      MetaioClose( env );
      XLAL_ERROR_NULL( func, XLAL_ENOMEM );
    }

    /* parse the contents of the row into the process params structure */
    for ( j = 0; tableDir[j].name; ++j )
    {
      if ( tableDir[j].idx == 0 )
      {
        LALSnprintf( thisEvent->program, LIGOMETA_PROGRAM_MAX * sizeof(CHAR), 
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 1 )
      {
        LALSnprintf( thisEvent->param, LIGOMETA_PARAM_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 2 )
      {
        LALSnprintf( thisEvent->type, LIGOMETA_TYPE_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 3 )
      {
        LALSnprintf( thisEvent->value, LIGOMETA_VALUE_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else
      {
        XLAL_CLOBBER_EVENTS;
        XLAL_ERROR_NULL( func, XLAL_EIO);
      }
    }
    /* count the number of triggers parsed */
    nrows++;
  }

  if ( mioStatus == -1 )
  {
    fprintf( stderr, "error parsing after row %d\n", i );
    XLAL_CLOBBER_EVENTS;
    MetaioClose( env );
    XLAL_ERROR_NULL( func, XLAL_EIO);
  }

  /* Normal exit */
  LALFree( tableDir );
  MetaioClose( env );

  return eventHead;
}


/* <lalVerbatim file="LIGOLwXMLReadCP"> */
MultiInspiralTable    * XLALMultiInspiralTableFromLIGOLw (
    CHAR               *fileName
    )
/* </lalVerbatim> */
{
  static const char   *func = "XLALMultiInspiralTableFromLIGOLw";
  int                                   i, j, nrows;
  int                                   mioStatus=0;
  MultiInspiralTable                   *thisEvent = NULL;
  MultiInspiralTable                   *eventHead = NULL;
  struct MetaioParseEnvironment         parseEnv;
  const  MetaioParseEnv                 env = &parseEnv;
  MetaTableDirectory                   *tableDir = NULL;

  /* open the multi_inspiral XML file */
  mioStatus = MetaioOpenTable( env, fileName, "multi_inspiral" );
  if ( mioStatus )
  {
    XLAL_ERROR_NULL( func, XLAL_EIO );
  }

  /* create table directory to find columns in file*/
  tableDir = XLALCreateMetaTableDir(env, multi_inspiral_table);

  /* loop over the rows in the file */
  i = nrows = 0;
  while ( (mioStatus = MetaioGetRow(env)) == 1 ) 
  {
    /* count the rows in the file */
    i++;
    /* allocate memory for the template we are about to read in */
    if ( ! eventHead )
    {
      thisEvent = eventHead = (MultiInspiralTable *) 
        LALCalloc( 1, sizeof(MultiInspiralTable) );
    }
    else
    {
      thisEvent = thisEvent->next = (MultiInspiralTable *) 
        LALCalloc( 1, sizeof(MultiInspiralTable) );
    }
    if ( ! thisEvent )
    {
      fprintf( stderr, "could not allocate multi inspiral event\n" );
      XLAL_CLOBBER_EVENTS;
      MetaioClose( env );
      XLAL_ERROR_NULL( func, XLAL_ENOMEM );
    }

    /* parse the contents of the row into the InspiralTemplate structure */
    for ( j = 0; tableDir[j].name; ++j )
    {
      REAL4 r4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_4;
      REAL8 r8colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_8; 
      INT4  i4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_4s;
      UINT8 i8colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_8s;
      if ( tableDir[j].idx == 0 )
      {
        LALSnprintf( thisEvent->ifos, LIGOMETA_IFO_MAX * sizeof(CHAR), 
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 1 )
      {
        LALSnprintf( thisEvent->search, LIGOMETA_SEARCH_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 2 )
      {
        thisEvent->end_time.gpsSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 3 )
      {
        thisEvent->end_time.gpsNanoSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 4 )
      {
        thisEvent->end_time_gmst = r8colData;
      }
      else if ( tableDir[j].idx == 5 )
      {
        thisEvent->impulse_time.gpsSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 6 )
      {
        thisEvent->impulse_time.gpsNanoSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 7 )
      {
        thisEvent->amplitude = r4colData;
      }
      else if ( tableDir[j].idx == 8 )
      {
        thisEvent->ifo1_eff_distance = r4colData;
      }
      else if ( tableDir[j].idx == 9 )
      {
        thisEvent->ifo2_eff_distance = r4colData;
      }
      else if ( tableDir[j].idx == 10 )
      {
        thisEvent->eff_distance = r4colData;
      }
      else if ( tableDir[j].idx == 11 )
      {
        thisEvent->coa_phase = r4colData;
      }
      else if ( tableDir[j].idx == 12 )
      {
        thisEvent->mass1 = r4colData;
      }
      else if ( tableDir[j].idx == 13 )
      {
        thisEvent->mass2 = r4colData;
      }
      else if ( tableDir[j].idx == 14 )
      {
        thisEvent->mchirp = r4colData;
      }
      else if ( tableDir[j].idx == 15 )
      {
        thisEvent->eta = r4colData;
      }
      else if ( tableDir[j].idx == 16 )
      {
        thisEvent->tau0 = r4colData;
      }
      else if ( tableDir[j].idx == 17 )
      {
        thisEvent->tau2 = r4colData;
      }
      else if ( tableDir[j].idx == 18 )
      {
        thisEvent->tau3 = r4colData;
      }
      else if ( tableDir[j].idx == 19 )
      {
        thisEvent->tau4 = r4colData;
      }
      else if ( tableDir[j].idx == 20 )
      {
        thisEvent->tau5 = r4colData;
      }
      else if ( tableDir[j].idx == 21 )
      {
        thisEvent->ttotal = r4colData;
      }
      else if ( tableDir[j].idx == 22 )
      {
        thisEvent->ifo1_snr = r4colData;
      }
      else if ( tableDir[j].idx == 23 )
      {
        thisEvent->ifo2_snr = r4colData;
      }
      else if ( tableDir[j].idx == 24 )
      {
        thisEvent->snr = r4colData;
      }
      else if ( tableDir[j].idx == 25 )
      {
        thisEvent->chisq = r4colData;
      }
      else if ( tableDir[j].idx == 26 )
      {
        thisEvent->chisq_dof = i4colData;
      }
      else if ( tableDir[j].idx == 27 )
      {
        thisEvent->bank_chisq = r4colData;
      }
      else if ( tableDir[j].idx == 28 )
      {
        thisEvent->bank_chisq_dof = i4colData;
      }
      else if ( tableDir[j].idx == 29 )
      {
        thisEvent->cont_chisq = r4colData;
      }
      else if ( tableDir[j].idx == 30 )
      {
        thisEvent->cont_chisq_dof = i4colData;
      }
      else if ( tableDir[j].idx == 31 )
      {
        thisEvent->sigmasq = r8colData;
      }
      else if ( tableDir[j].idx == 32 )
      {
        thisEvent->ligo_axis_ra = r4colData;
      }
      else if ( tableDir[j].idx == 33 )
      {
        thisEvent->ligo_axis_dec = r4colData;
      }
      else if ( tableDir[j].idx == 34 )
      {
        thisEvent->ligo_angle = r4colData;
      }
      else if ( tableDir[j].idx == 35 )
      {
        thisEvent->ligo_angle_sig = r4colData;
      }
      else if ( tableDir[j].idx == 36 )
      {
        thisEvent->inclination = r4colData;
      }
      else if ( tableDir[j].idx == 37 )
      {
        thisEvent->polarization = r4colData;
      }
      else if ( tableDir[j].idx == 38 )
      {
        if ( tableDir[j].pos > 0 && i8colData )
        {
          thisEvent->event_id = (EventIDColumn *)
            LALCalloc( 1, sizeof(EventIDColumn) );
          thisEvent->event_id->id = i8colData;
          thisEvent->event_id->multiInspiralTable = thisEvent;
        }
      }
      else if ( tableDir[j].idx == 39 )
      {
        thisEvent->null_statistic = r8colData;
      }
      else if ( tableDir[j].idx == 40 )
      {
        thisEvent->h1quad.re = r4colData;
      }
      else if ( tableDir[j].idx == 41 )
      {
        thisEvent->h1quad.im = r4colData;
      }
      else if ( tableDir[j].idx == 42 )
      {
        thisEvent->h2quad.re = r4colData;
      }
      else if ( tableDir[j].idx == 43 )
      {
        thisEvent->h2quad.im = r4colData;
      }
      else if ( tableDir[j].idx == 44 )
      {
        thisEvent->l1quad.re = r4colData;
      }
      else if ( tableDir[j].idx == 45 )
      {
        thisEvent->l1quad.im = r4colData;
      }
      else if ( tableDir[j].idx == 46 )
      {
        thisEvent->v1quad.re = r4colData;
      }
      else if ( tableDir[j].idx == 47 )
      {
        thisEvent->v1quad.im = r4colData;
      }
      else if ( tableDir[j].idx == 48 )
      {
        thisEvent->g1quad.re = r4colData;
      }
      else if ( tableDir[j].idx == 49 )
      {
        thisEvent->g1quad.im = r4colData;
      }
      else if ( tableDir[j].idx == 50 )
      {
        thisEvent->t1quad.re = r4colData;
      }
      else if ( tableDir[j].idx == 51 )
      {
        thisEvent->t1quad.im = r4colData;
      }
      else
      {
        XLAL_CLOBBER_EVENTS;
        XLAL_ERROR_NULL( func, XLAL_EIO);
      }
    }
    /* count the number of triggers parsed */
    nrows++;
  }

  if ( mioStatus == -1 )
  {
    fprintf( stderr, "error parsing after row %d\n", i );
    XLAL_CLOBBER_EVENTS;
    MetaioClose( env );
    XLAL_ERROR_NULL( func, XLAL_EIO);
  }

  /* Normal exit */
  LALFree( tableDir );
  MetaioClose( env );

  return eventHead;
}

#undef XLAL_CLOBBER_EVENTS

/*
 *
 * LAL Functions
 *
 */

#define CLOBBER_EVENTS \
  while ( *eventHead ); \
{ \
  thisEvent = *eventHead; \
  *eventHead = (*eventHead)->next; \
  LALFree( thisEvent ); \
  thisEvent = NULL; \
}


/**
 * Convenience wrapper for MetaioFindColumn(), translating to XLAL-style
 * error reporting and printing useful error messages on failure.
 */


static int XLALLIGOLwFindColumn(
	struct MetaioParseEnvironment *env,
	const char *name,
	int required
)
{
	static const char func[] = "XLALLIGOLwFindColumn";
	int pos = MetaioFindColumn(env, name);
	if(pos < 0 && required) {
		XLALPrintError("missing required column '%s'\n", name);
		XLAL_ERROR(func, XLAL_EIO);
	}
	return pos;
}


/**
 * Convenience function to extract the integer part of an ilwd:char ID
 * string with some error checking.
 */


static long XLALLIGOLwParseIlwdChar(
	const struct MetaioParseEnvironment *env,
	int column_number,
	const char *ilwd_char_table_name,
	const char *ilwd_char_column_name
)
{
	static const char func[] = "XLALLIGOLwParseIlwdChar";
	char *fmt;
	const char *ilwd_char = (char *) env->ligo_lw.table.elt[column_number].data.ilwd_char.data;
	long id;

	fmt = malloc(strlen(ilwd_char_table_name) + strlen(ilwd_char_column_name) + 7);
	if(!fmt)
		XLAL_ERROR(func, XLAL_ENOMEM);

	sprintf(fmt, "%s:%s:%%ld", ilwd_char_table_name, ilwd_char_column_name);

	if(sscanf(ilwd_char, fmt, &id) < 1) {
		free(fmt);
		XLALPrintError("invalid %s '%s'\n", ilwd_char_column_name, ilwd_char);
		XLAL_ERROR(func, XLAL_EIO);
	}

	free(fmt);

	return id;
}


/**
 * Read the sngl_burst table from a LIGO Light Weight XML file into a
 * linked list of SnglBurst structures.
 */


SnglBurst *XLALSnglBurstTableFromLIGOLw(
	const CHAR *filename
)
{
	static const char func[] = "XLALSnglBurstTableFromLIGOLw";
	int miostatus;
	SnglBurst *head = NULL;
	SnglBurst **next = &head;
	struct MetaioParseEnvironment env;
	struct {
		int process_id;
		int ifo;
		int search;
		int channel;
		int start_time;
		int start_time_ns;
		int peak_time;
		int peak_time_ns;
		int duration;
		int central_freq;
		int bandwidth;
		int amplitude;
		int snr;
		int confidence;
		int event_id;
	} column_pos;

	/* open the file and find table */

	if(MetaioOpenFile(&env, filename)) {
		XLALPrintError("error opening '%s'\n", filename);
		XLAL_ERROR_NULL(func, XLAL_EIO);
	}
	if(MetaioOpenTableOnly(&env, "sngl_burst")) {
		MetaioAbort(&env);
		XLALPrintError("cannot find sngl_burst table\n");
		XLAL_ERROR_NULL(func, XLAL_EIO);
	}

	/* find columns */

	XLALClearErrno();
	column_pos.process_id = XLALLIGOLwFindColumn(&env, "process_id", 1);
	column_pos.ifo = XLALLIGOLwFindColumn(&env, "ifo", 1);
	column_pos.search = XLALLIGOLwFindColumn(&env, "search", 1);
	column_pos.channel = XLALLIGOLwFindColumn(&env, "channel", 1);
	column_pos.start_time = XLALLIGOLwFindColumn(&env, "start_time", 1);
	column_pos.start_time_ns = XLALLIGOLwFindColumn(&env, "start_time_ns", 1);
	column_pos.peak_time = XLALLIGOLwFindColumn(&env, "peak_time", 1);
	column_pos.peak_time_ns = XLALLIGOLwFindColumn(&env, "peak_time_ns", 1);
	column_pos.duration = XLALLIGOLwFindColumn(&env, "duration", 1);
	column_pos.central_freq = XLALLIGOLwFindColumn(&env, "central_freq", 1);
	column_pos.bandwidth = XLALLIGOLwFindColumn(&env, "bandwidth", 1);
	column_pos.amplitude = XLALLIGOLwFindColumn(&env, "amplitude", 1);
	column_pos.snr = XLALLIGOLwFindColumn(&env, "snr", 1);
	column_pos.confidence = XLALLIGOLwFindColumn(&env, "confidence", 1);
	column_pos.event_id = XLALLIGOLwFindColumn(&env, "event_id", 1);

	/* check for failure (== a required column is missing) */

	if(XLALGetBaseErrno()) {
		MetaioAbort(&env);
		XLALPrintError("failure reading sngl_burst table\n");
		XLAL_ERROR_NULL(func, XLAL_EFUNC);
	}

	/* loop over the rows in the file */

	while((miostatus = MetaioGetRow(&env)) > 0) {
		/* create a new row */

		SnglBurst *row = XLALCreateSnglBurst();

		if(!row) {
			XLALDestroySnglBurstTable(head);
			MetaioAbort(&env);
			XLAL_ERROR_NULL(func, XLAL_EFUNC);
		}

		/* populate the columns */

		if((row->process_id = XLALLIGOLwParseIlwdChar(&env, column_pos.process_id, "process", "process_id")) < 0) {
			XLALDestroySnglBurstTable(head);
			MetaioAbort(&env);
			XLAL_ERROR_NULL(func, XLAL_EFUNC);
		}
		strncpy(row->ifo, env.ligo_lw.table.elt[column_pos.ifo].data.lstring.data, sizeof(row->ifo) - 1);
		strncpy(row->search, env.ligo_lw.table.elt[column_pos.search].data.lstring.data, sizeof(row->search) - 1);
		strncpy(row->channel, env.ligo_lw.table.elt[column_pos.channel].data.lstring.data, sizeof(row->channel) - 1);
		XLALGPSSet(&row->start_time, env.ligo_lw.table.elt[column_pos.start_time].data.int_4s, env.ligo_lw.table.elt[column_pos.start_time_ns].data.int_4s);
		XLALGPSSet(&row->peak_time, env.ligo_lw.table.elt[column_pos.peak_time].data.int_4s, env.ligo_lw.table.elt[column_pos.peak_time_ns].data.int_4s);
		row->duration = env.ligo_lw.table.elt[column_pos.duration].data.real_4;
		row->central_freq = env.ligo_lw.table.elt[column_pos.central_freq].data.real_4;
		row->bandwidth = env.ligo_lw.table.elt[column_pos.bandwidth].data.real_4;
		row->amplitude = env.ligo_lw.table.elt[column_pos.amplitude].data.real_4;
		row->snr = env.ligo_lw.table.elt[column_pos.snr].data.real_4;
		row->confidence = env.ligo_lw.table.elt[column_pos.confidence].data.real_4;
		if((row->event_id = XLALLIGOLwParseIlwdChar(&env, column_pos.event_id, "sngl_burst", "event_id")) < 0) {
			XLALDestroySnglBurstTable(head);
			MetaioAbort(&env);
			XLAL_ERROR_NULL(func, XLAL_EFUNC);
		}

		/* append to linked list */

		*next = row;
		next = &(*next)->next;
	}
	if(miostatus < 0) {
		XLALDestroySnglBurstTable(head);
		MetaioAbort(&env);
		XLALPrintError("I/O error parsing sngl_burst table\n");
		XLAL_ERROR_NULL(func, XLAL_EIO);
	}

	/* close file */

	if(MetaioClose(&env)) {
		XLALDestroySnglBurstTable(head);
		XLALPrintError("error parsing document after sngl_burst table\n");
		XLAL_ERROR_NULL(func, XLAL_EIO);
	}

	/* done */

	return head;
}


/**
 * Read the sim_burst table from a LIGO Light Weight XML file into a linked
 * list of SimBurst structures.  If start is not NULL, then only rows whose
 * geocentre peak times are >= the given GPS time will be loaded, similarly
 * if end is not NULL.
 */


SimBurst *XLALSimBurstTableFromLIGOLw(
	const CHAR *filename,
	const LIGOTimeGPS *start,
	const LIGOTimeGPS *end
)
{
	static const char func[] = "XLALSimBurstTableFromLIGOLw";
	int miostatus;
	SimBurst *head = NULL;
	SimBurst **next = &head;
	struct MetaioParseEnvironment env;
	struct {
		int process_id;
		int waveform;
		int ra;
		int dec;
		int psi;
		int time_geocent_gps;
		int time_geocent_gps_ns;
		int time_geocent_gmst;
		int duration;
		int frequency;
		int bandwidth;
		int q;
		int pol_ellipse_angle;
		int pol_ellipse_e;
		int amplitude;
		int hrss;
		int egw_over_rsquared;
		int waveform_number;
		int simulation_id;
	} column_pos;

	/* open the file and find table */

	if(MetaioOpenFile(&env, filename)) {
		XLALPrintError("error opening '%s'\n", filename);
		XLAL_ERROR_NULL(func, XLAL_EIO);
	}
	if(MetaioOpenTableOnly(&env, "sim_burst")) {
		MetaioAbort(&env);
		XLALPrintError("cannot find sim_burst table\n");
		XLAL_ERROR_NULL(func, XLAL_EIO);
	}

	/* find columns */

	XLALClearErrno();
	column_pos.process_id = XLALLIGOLwFindColumn(&env, "process_id", 1);
	column_pos.waveform = XLALLIGOLwFindColumn(&env, "waveform", 1);
	column_pos.ra = XLALLIGOLwFindColumn(&env, "ra", 0);
	column_pos.dec = XLALLIGOLwFindColumn(&env, "dec", 0);
	column_pos.psi = XLALLIGOLwFindColumn(&env, "psi", 0);
	column_pos.time_geocent_gps = XLALLIGOLwFindColumn(&env, "time_geocent_gps", 1);
	column_pos.time_geocent_gps_ns = XLALLIGOLwFindColumn(&env, "time_geocent_gps_ns", 1);
	column_pos.time_geocent_gmst = XLALLIGOLwFindColumn(&env, "time_geocent_gmst", 0);
	column_pos.duration = XLALLIGOLwFindColumn(&env, "duration", 0);
	column_pos.frequency = XLALLIGOLwFindColumn(&env, "frequency", 0);
	column_pos.bandwidth = XLALLIGOLwFindColumn(&env, "bandwidth", 0);
	column_pos.q = XLALLIGOLwFindColumn(&env, "q", 0);
	column_pos.pol_ellipse_angle = XLALLIGOLwFindColumn(&env, "pol_ellipse_angle", 0);
	column_pos.pol_ellipse_e = XLALLIGOLwFindColumn(&env, "pol_ellipse_e", 0);
	column_pos.amplitude = XLALLIGOLwFindColumn(&env, "amplitude", 0);
	column_pos.hrss = XLALLIGOLwFindColumn(&env, "hrss", 0);
	column_pos.egw_over_rsquared = XLALLIGOLwFindColumn(&env, "egw_over_rsquared", 0);
	column_pos.waveform_number = XLALLIGOLwFindColumn(&env, "waveform_number", 0);
	column_pos.simulation_id = XLALLIGOLwFindColumn(&env, "simulation_id", 1);

	/* check for failure (== a required column is missing) */

	if(XLALGetBaseErrno()) {
		MetaioAbort(&env);
		XLALPrintError("failure reading sim_burst table\n");
		XLAL_ERROR_NULL(func, XLAL_EFUNC);
	}

	/* loop over the rows in the file */

	while((miostatus = MetaioGetRow(&env)) > 0) {
		/* create a new row */

		SimBurst *row = XLALCreateSimBurst();

		if(!row) {
			XLALDestroySimBurstTable(head);
			MetaioAbort(&env);
			XLAL_ERROR_NULL(func, XLAL_EFUNC);
		}

		/* populate the columns */

		if((row->process_id = XLALLIGOLwParseIlwdChar(&env, column_pos.process_id, "process", "process_id")) < 0) {
			XLALDestroySimBurstTable(head);
			MetaioAbort(&env);
			XLAL_ERROR_NULL(func, XLAL_EFUNC);
		}
		strncpy(row->waveform, env.ligo_lw.table.elt[column_pos.waveform].data.lstring.data, sizeof(row->waveform) - 1);
		if(column_pos.ra >= 0)
			row->ra = env.ligo_lw.table.elt[column_pos.ra].data.real_8;
		if(column_pos.dec >= 0)
			row->dec = env.ligo_lw.table.elt[column_pos.dec].data.real_8;
		if(column_pos.psi >= 0)
			row->psi = env.ligo_lw.table.elt[column_pos.psi].data.real_8;
		XLALGPSSet(&row->time_geocent_gps, env.ligo_lw.table.elt[column_pos.time_geocent_gps].data.int_4s, env.ligo_lw.table.elt[column_pos.time_geocent_gps_ns].data.int_4s);
		if(column_pos.time_geocent_gmst >= 0)
			row->time_geocent_gmst = env.ligo_lw.table.elt[column_pos.time_geocent_gmst].data.real_8;
		if((row->simulation_id = XLALLIGOLwParseIlwdChar(&env, column_pos.simulation_id, "sim_burst", "simulation_id")) < 0) {
			XLALDestroySimBurstTable(head);
			MetaioAbort(&env);
			XLAL_ERROR_NULL(func, XLAL_EFUNC);
		}

		if(!strcmp(row->waveform, "StringCusp")) {
			if(column_pos.duration < 0 || column_pos.frequency < 0 || column_pos.amplitude < 0) {
				XLALDestroySimBurstTable(head);
				MetaioAbort(&env);
				XLALPrintError("missing required column in sim_burst table\n");
				XLAL_ERROR_NULL(func, XLAL_EIO);
			}
			row->duration = env.ligo_lw.table.elt[column_pos.duration].data.real_8;
			row->frequency = env.ligo_lw.table.elt[column_pos.frequency].data.real_8;
			row->amplitude = env.ligo_lw.table.elt[column_pos.amplitude].data.real_8;
		} else if(!strcmp(row->waveform, "SineGaussian")) {
			if(column_pos.duration < 0 || column_pos.frequency < 0 || column_pos.bandwidth < 0 || column_pos.q < 0 || column_pos.pol_ellipse_angle < 0 || column_pos.pol_ellipse_e < 0 || column_pos.hrss < 0) {
				XLALDestroySimBurstTable(head);
				MetaioAbort(&env);
				XLALPrintError("missing required column in sim_burst table\n");
				XLAL_ERROR_NULL(func, XLAL_EIO);
			}
			row->duration = env.ligo_lw.table.elt[column_pos.duration].data.real_8;
			row->frequency = env.ligo_lw.table.elt[column_pos.frequency].data.real_8;
			row->bandwidth = env.ligo_lw.table.elt[column_pos.bandwidth].data.real_8;
			row->q = env.ligo_lw.table.elt[column_pos.q].data.real_8;
			row->pol_ellipse_angle = env.ligo_lw.table.elt[column_pos.pol_ellipse_angle].data.real_8;
			row->pol_ellipse_e = env.ligo_lw.table.elt[column_pos.pol_ellipse_e].data.real_8;
			row->hrss = env.ligo_lw.table.elt[column_pos.hrss].data.real_8;
		} else if(!strcmp(row->waveform, "BTLWNB")) {
			if(column_pos.duration < 0 || column_pos.frequency < 0 || column_pos.bandwidth < 0 || column_pos.egw_over_rsquared < 0 || column_pos.waveform_number < 0) {
				XLALDestroySimBurstTable(head);
				MetaioAbort(&env);
				XLALPrintError("missing required column in sim_burst table\n");
				XLAL_ERROR_NULL(func, XLAL_EIO);
			}
			row->duration = env.ligo_lw.table.elt[column_pos.duration].data.real_8;
			row->frequency = env.ligo_lw.table.elt[column_pos.frequency].data.real_8;
			row->bandwidth = env.ligo_lw.table.elt[column_pos.bandwidth].data.real_8;
			row->egw_over_rsquared = env.ligo_lw.table.elt[column_pos.egw_over_rsquared].data.real_8;
			/* FIXME:  waveform is an unsigned long, but metaio
			 * doesn't support int_8u columns */
			row->waveform_number = env.ligo_lw.table.elt[column_pos.waveform_number].data.int_8s;
		} else {
			/* unrecognized waveform */
			XLALDestroySimBurstTable(head);
			MetaioAbort(&env);
			XLALPrintError("unrecognized waveform '%s' in sim_burst table\n", row->waveform);
			XLAL_ERROR_NULL(func, XLAL_EIO);
		}

		/* if outside accepted time window, discard */

		if((start && XLALGPSDiff(start, &row->time_geocent_gps) > 0) || (end && XLALGPSDiff(end, &row->time_geocent_gps) < 0)) {
			XLALDestroySimBurst(row);
			continue;
		}

		/* append to linked list */

		*next = row;
		next = &(*next)->next;
	}
	if(miostatus < 0) {
		XLALDestroySimBurstTable(head);
		MetaioAbort(&env);
		XLALPrintError("I/O error parsing sim_burst table\n");
		XLAL_ERROR_NULL(func, XLAL_EIO);
	}

	/* close file */

	if(MetaioClose(&env)) {
		XLALDestroySimBurstTable(head);
		XLALPrintError("error parsing document after sim_burst table\n");
		XLAL_ERROR_NULL(func, XLAL_EIO);
	}

	/* done */

	return head;
}


/* <lalVerbatim file="LIGOLwXMLReadCP"> */
int
LALSnglInspiralTableFromLIGOLw (
    SnglInspiralTable **eventHead,
    CHAR               *fileName,
    INT4                startEvent,
    INT4                stopEvent
    )
/* </lalVerbatim> */
{
  int                                   i, j, nrows;
  int                                   mioStatus;
  SnglInspiralTable                    *thisEvent = NULL;
  struct MetaioParseEnvironment         parseEnv;
  const  MetaioParseEnv                 env = &parseEnv;
  MetaTableDirectory tableDir[] =
  {
    {"ifo",                     -1, 0},
    {"search",                  -1, 1},
    {"channel",                 -1, 2},
    {"end_time",                -1, 3},
    {"end_time_ns",             -1, 4},
    {"end_time_gmst",           -1, 5},
    {"impulse_time",            -1, 6},
    {"impulse_time_ns",         -1, 7},
    {"template_duration",       -1, 8},
    {"event_duration",          -1, 9},
    {"amplitude",               -1, 10},
    {"eff_distance",            -1, 11},
    {"coa_phase",               -1, 12},
    {"mass1",                   -1, 13},
    {"mass2",                   -1, 14},
    {"mchirp",                  -1, 15},
    {"mtotal",                  -1, 16},
    {"eta",                     -1, 17},
    {"tau0",                    -1, 18},
    {"tau2",                    -1, 19},
    {"tau3",                    -1, 20},
    {"tau4",                    -1, 21},
    {"tau5",                    -1, 22},
    {"ttotal",                  -1, 23},
    {"psi0",                    -1, 24},
    {"psi3",                    -1, 25},
    {"alpha",                   -1, 26},
    {"alpha1",                  -1, 27},
    {"alpha2",                  -1, 28},
    {"alpha3",                  -1, 29},
    {"alpha4",                  -1, 30},
    {"alpha5",                  -1, 31},
    {"alpha6",                  -1, 32},
    {"beta",                    -1, 33},
    {"f_final",                 -1, 34}, 
    {"snr",                     -1, 35},
    {"chisq",                   -1, 36},
    {"chisq_dof",               -1, 37},
    {"bank_chisq",                   -1, 38},
    {"bank_chisq_dof",               -1, 39},
    {"cont_chisq",                   -1, 40},
    {"cont_chisq_dof",               -1, 41},
    {"sigmasq",                 -1, 42},
    {"rsqveto_duration",        -1, 43},
    {"event_id",                -1, 44},
    {"Gamma0",                  -1, 45},
    {"Gamma1",                  -1, 46},
    {"Gamma2",                  -1, 47},
    {"Gamma3",                  -1, 48},
    {"Gamma4",                  -1, 49},
    {"Gamma5",                  -1, 50},
    {"Gamma6",                  -1, 51},
    {"Gamma7",                  -1, 52},
    {"Gamma8",                  -1, 53},
    {"Gamma9",                  -1, 54},
    {"kappa",                   -1, 55},
    {"chi",                     -1, 56},
    {NULL,                       0, 0}
  };

  /* check that the bank handle and pointer are vaid */
  if ( ! eventHead )
  {
    fprintf( stderr, "null pointer passed as handle to event list" );
    return -1;
  }
  if ( *eventHead )
  {
    fprintf( stderr, "non-null pointer passed as pointer to event list" );
    return -1;
  }

  /* open the sngl_inspiral table template bank file */
  mioStatus = MetaioOpenFile( env, fileName );
  if ( mioStatus )
  {
    fprintf( stderr, "unable to open file %s\n", fileName );
    return -1;
  }

  /* open the sngl_inspiral table template bank file */
  mioStatus = MetaioOpenTableOnly( env, "sngl_inspiral" );
  if ( mioStatus )
  {
    fprintf( stdout, "no sngl_inspiral table in file %s\n", fileName );
    return 0;
  }

  /* figure out the column positions of the template parameters */
  for ( i = 0; tableDir[i].name; ++i )
  {
    if ( (tableDir[i].pos = MetaioFindColumn( env, tableDir[i].name )) < 0 
        &&  tableDir[i].idx != 39 )
    {
      fprintf( stderr, "unable to find column %s\n", tableDir[i].name );

      if ( ! strcmp(tableDir[i].name, "event_id") )
      {
        fprintf( stderr, 
            "The event_id column is not populated, continuing anyway\n");
      } 
      else if ( strstr(tableDir[i].name, "Gamma") )
      {
        fprintf( stderr, 
            "The %s column is not populated, continuing anyway\n", tableDir[i].name);
      }
      else
      {
        MetaioClose(env);
        return -1;
      }
    }
  }

  /* loop over the rows in the file */
  i = nrows = 0;
  while ( (mioStatus = MetaioGetRow(env)) == 1 ) 
  {
    /* count the rows in the file */
    i++;

    /* stop parsing if we have reach the last row requested */
    if ( stopEvent > -1 && i > stopEvent )
    {
      break;
    }

    /* if we have reached the first requested row, parse the row */
    if ( i > startEvent )
    {
      /* allocate memory for the template we are about to read in */
      if ( ! *eventHead )
      {
        thisEvent = *eventHead = (SnglInspiralTable *) 
          LALCalloc( 1, sizeof(SnglInspiralTable) );
      }
      else
      {
        thisEvent = thisEvent->next = (SnglInspiralTable *) 
          LALCalloc( 1, sizeof(SnglInspiralTable) );
      }
      if ( ! thisEvent )
      {
        fprintf( stderr, "could not allocate inspiral template\n" );
        CLOBBER_EVENTS;
        MetaioClose( env );
        return -1;
      }

      /* parse the contents of the row into the InspiralTemplate structure */
      for ( j = 0; tableDir[j].name; ++j )
      {
        REAL4 r4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_4;
        REAL8 r8colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_8;
        INT4  i4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_4s;
        UINT8 i8colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_8s;

        if ( tableDir[j].pos < 0 ) continue;

        if ( tableDir[j].idx == 0 )
        {
          LALSnprintf( thisEvent->ifo, LIGOMETA_IFO_MAX * sizeof(CHAR), 
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 1 )
        {
          LALSnprintf( thisEvent->search, LIGOMETA_SEARCH_MAX * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 2 )
        {
          LALSnprintf( thisEvent->channel, LIGOMETA_CHANNEL_MAX * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 3 )
        {
          thisEvent->end_time.gpsSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 4 )
        {
          thisEvent->end_time.gpsNanoSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 5 )
        {
          thisEvent->end_time_gmst = r8colData;
        }
        else if ( tableDir[j].idx == 6 )
        {
          thisEvent->impulse_time.gpsSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 7 )
        {
          thisEvent->impulse_time.gpsNanoSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 8 )
        {
          thisEvent->template_duration = r8colData;
        }
        else if ( tableDir[j].idx == 9 )
        {
          thisEvent->event_duration = r8colData;
        }
        else if ( tableDir[j].idx == 10 )
        {
          thisEvent->amplitude = r4colData;
        }
        else if ( tableDir[j].idx == 11 )
        {
          thisEvent->eff_distance = r4colData;
        }
        else if ( tableDir[j].idx == 12 )
        {
          thisEvent->coa_phase = r4colData;
        }
        else if ( tableDir[j].idx == 13 )
        {
          thisEvent->mass1 = r4colData;
        }
        else if ( tableDir[j].idx == 14 )
        {
          thisEvent->mass2 = r4colData;
        }
        else if ( tableDir[j].idx == 15 )
        {
          thisEvent->mchirp = r4colData;
        }
        else if ( tableDir[j].idx == 16 )
        {
          thisEvent->mtotal = r4colData;
        }
        else if ( tableDir[j].idx == 17 )
        {
          thisEvent->eta = r4colData;
        }
        else if ( tableDir[j].idx == 18 )
        {
          thisEvent->tau0 = r4colData;
        }
        else if ( tableDir[j].idx == 19 )
        {
          thisEvent->tau2 = r4colData;
        }
        else if ( tableDir[j].idx == 20 )
        {
          thisEvent->tau3 = r4colData;
        }
        else if ( tableDir[j].idx == 21 )
        {
          thisEvent->tau4 = r4colData;
        }
        else if ( tableDir[j].idx == 22 )
        {
          thisEvent->tau5 = r4colData;
        }
        else if ( tableDir[j].idx == 23 )
        {
          thisEvent->ttotal = r4colData;
        }
        else if ( tableDir[j].idx == 24 )
        {
          thisEvent->psi0 = r4colData;
        }
        else if ( tableDir[j].idx == 25 )
        {
          thisEvent->psi3 = r4colData;
        }
        else if ( tableDir[j].idx == 26 )
        {
          thisEvent->alpha = r4colData;
        }
        else if ( tableDir[j].idx == 27 )
        {
          thisEvent->alpha1 = r4colData;
        }
        else if ( tableDir[j].idx == 28 )
        {
          thisEvent->alpha2 = r4colData;
        }
        else if ( tableDir[j].idx == 29 )
        {
          thisEvent->alpha3 = r4colData;
        }
        else if ( tableDir[j].idx == 30 )
        {
          thisEvent->alpha4 = r4colData;
        }
        else if ( tableDir[j].idx == 31 )
        {
          thisEvent->alpha5 = r4colData;
        }
        else if ( tableDir[j].idx == 32 )
        {
          thisEvent->alpha6 = r4colData;
        }
        else if ( tableDir[j].idx == 33 )
        {
          thisEvent->beta = r4colData;
        }
        else if ( tableDir[j].idx == 34 )
        {
          thisEvent->f_final = r4colData;
        }
        else if ( tableDir[j].idx == 35 )
        {
          thisEvent->snr = r4colData;
        }
        else if ( tableDir[j].idx == 36 )
        {
          thisEvent->chisq = r4colData;
        }
        else if ( tableDir[j].idx == 37 )
        {
          thisEvent->chisq_dof = i4colData;
        }
        else if ( tableDir[j].idx == 38 )
        {
          thisEvent->bank_chisq = r4colData;
        }
        else if ( tableDir[j].idx == 39 )
        {
          thisEvent->bank_chisq_dof = i4colData;
        }
        else if ( tableDir[j].idx == 40 )
        {
          thisEvent->cont_chisq = r4colData;
        }
        else if ( tableDir[j].idx == 41 )
        {
          thisEvent->cont_chisq_dof = i4colData;
        }
        else if ( tableDir[j].idx == 42 )
        {
          thisEvent->sigmasq = r8colData;
        }
        else if ( tableDir[j].idx == 43 )
        {
          thisEvent->rsqveto_duration = r4colData;
        }
        else if ( tableDir[j].idx == 44 )
        {
          if ( tableDir[j].pos > 0 && i8colData )
          {
            thisEvent->event_id = (EventIDColumn *) 
              LALCalloc( 1, sizeof(EventIDColumn) );
            thisEvent->event_id->id = i8colData;
            thisEvent->event_id->snglInspiralTable = thisEvent;
          }
        }
        else if ( tableDir[j].idx == 45 )
        {
          thisEvent->Gamma[0] = r4colData;
        }
        else if ( tableDir[j].idx == 46 )
        {
          thisEvent->Gamma[1] = r4colData;
        }
        else if ( tableDir[j].idx == 47 )
        {
          thisEvent->Gamma[2] = r4colData;
        }
        else if ( tableDir[j].idx == 48 )
        {
          thisEvent->Gamma[3] = r4colData;
        }
        else if ( tableDir[j].idx == 49 )
        {
          thisEvent->Gamma[4] = r4colData;
        }
        else if ( tableDir[j].idx == 50 )
        {
          thisEvent->Gamma[5] = r4colData;
        }
        else if ( tableDir[j].idx == 51 )
        {
          thisEvent->Gamma[6] = r4colData;
        }
        else if ( tableDir[j].idx == 52 )
        {
          thisEvent->Gamma[7] = r4colData;
        }
        else if ( tableDir[j].idx == 53 )
        {
          thisEvent->Gamma[8] = r4colData;
        }
        else if ( tableDir[j].idx == 54 )
        {
          thisEvent->Gamma[9] = r4colData;
        }
        else if ( tableDir[j].idx == 55 )
        {
          thisEvent->kappa = r4colData;
        }
        else if ( tableDir[j].idx == 56 )
        {
          thisEvent->chi = r4colData;
        }        
        else
        {
          CLOBBER_EVENTS;
          fprintf( stderr, "unknown column while parsing sngl_inspiral\n" );
          return -1;
        }
      }

      /* count the number of template parsed */
      nrows++;
    }
  }

  if ( mioStatus == -1 )
  {
    fprintf( stderr, "error parsing after row %d\n", i );
    CLOBBER_EVENTS;
    MetaioClose( env );
    return -1;
  }

  /* we have sucesfully parsed temples */
  MetaioClose( env );
  return nrows;  
}

#undef CLOBBER_EVENTS

#define CLOBBER_BANK \
  while ( *bankHead ); \
{ \
  thisTmplt = *bankHead; \
  *bankHead = (*bankHead)->next; \
  LALFree( thisTmplt ); \
  thisTmplt = NULL; \
}

/* <lalVerbatim file="LIGOLwXMLReadCP"> */
int
InspiralTmpltBankFromLIGOLw (
    InspiralTemplate  **bankHead,
    CHAR               *fileName,
    INT4                startTmplt,
    INT4                stopTmplt
    )
/* </lalVerbatim> */
{
  int                                   i, j, nrows;
  int                                   mioStatus;
  InspiralTemplate                     *thisTmplt = NULL;
  struct MetaioParseEnvironment         parseEnv;
  const  MetaioParseEnv                 env = &parseEnv;
  int   pParParam;
  int   pParValue;
  REAL4 minMatch = 0;
  MetaTableDirectory tableDir[] =
  {
    {"mass1",   -1, 0},
    {"mass2",   -1, 1},
    {"mchirp",  -1, 2},
    {"eta",     -1, 3},
    {"tau0",    -1, 4},
    {"tau2",    -1, 5},
    {"tau3",    -1, 6},
    {"tau4",    -1, 7},
    {"tau5",    -1, 8},
    {"ttotal",  -1, 9},
    {"psi0",    -1, 10},
    {"psi3",    -1, 11},
    {"beta",    -1, 12},
    {"f_final", -1, 13},
    {"end_time", -1, 14},
    {"end_time_ns", -1, 15},
    {"event_id", -1, 16},
    {"ifo", -1, 17},
    {"Gamma0", -1, 18},
    {"Gamma1", -1, 19},
    {"Gamma2", -1, 20},
    {"Gamma3", -1, 21},
    {"Gamma4", -1, 22},
    {"Gamma5", -1, 23},
    {"Gamma6", -1, 24},
    {"Gamma7", -1, 25},
    {"Gamma8", -1, 26},
    {"Gamma9", -1, 27},
    {"kappa", -1, 28},
    {"chi", -1, 29},
    {NULL,      0, 0}
  };

  /* check that the bank handle and pointer are vaid */
  if ( ! bankHead )
  {
    fprintf( stderr, "null pointer passed as handle to template bank" );
    return -1;
  }
  if ( *bankHead )
  {
    fprintf( stderr, "non-null pointer passed as pointer to template bank" );
    return -1;
  }


  /* open the procress_params table from the bank file */
  mioStatus = MetaioOpenTable( env, fileName, "process_params" );
  if ( mioStatus )
  {
    fprintf( stderr, "error opening process_params table from file %s\n", 
        fileName );
    return -1;
  }

  /* figure out where the param and value columns are */
  if ( (pParParam = MetaioFindColumn( env, "param" )) < 0 )
  {
    fprintf( stderr, "unable to find column param in process_params\n" );
    MetaioClose(env);
    return -1;
  }
  if ( (pParValue = MetaioFindColumn( env, "value" )) < 0 )
  {
    fprintf( stderr, "unable to find column value in process_params\n" );
    MetaioClose(env);
    return -1;
  }

  /* get the minimal match of the bank from the process params */
  while ( (mioStatus = MetaioGetRow(env)) == 1 )
  {
    if ( ! strcmp( env->ligo_lw.table.elt[pParParam].data.lstring.data, 
          "--minimal-match" ) )
    {
      minMatch = (REAL4) 
        atof( env->ligo_lw.table.elt[pParValue].data.lstring.data );
    }
  }

  MetaioClose( env );

  /* open the sngl_inspiral table template bank file */
  mioStatus = MetaioOpenTable( env, fileName, "sngl_inspiral" );
  if ( mioStatus )
  {
    fprintf( stdout, "no sngl_inspiral table in file %s\n", fileName );
    return 0;
  }

  /* figure out the column positions of the template parameters */
  for ( i = 0; tableDir[i].name; ++i )
  {
    if ( (tableDir[i].pos = MetaioFindColumn( env, tableDir[i].name )) < 0 )
    {
      fprintf( stderr, "unable to find column %s\n", tableDir[i].name );

      if ( ! strcmp(tableDir[i].name, "event_id") )
      {
        fprintf( stderr, 
            "The event_id column is not populated, continuing anyway\n");
      }
      else if ( strstr(tableDir[i].name, "Gamma") )
      {
        fprintf( stderr, 
            "The %s column is not populated, continuing anyway\n", tableDir[i].name);
      }
      else
      {
        MetaioClose(env);
        return -1;
      }
    }
  }

  /* loop over the rows in the file */
  i = nrows = 0;
  while ( (mioStatus = MetaioGetRow(env)) == 1 ) 
  {
    /* count the rows in the file */
    i++;

    /* stop parsing if we have reach the last row requested */
    if ( stopTmplt > -1 && i > stopTmplt )
    {
      break;
    }

    /* if we have reached the first requested row, parse the row */
    if ( i > startTmplt )
    {
      /* allocate memory for the template we are about to read in */
      if ( ! *bankHead )
      {
        thisTmplt = *bankHead = (InspiralTemplate *) 
          LALCalloc( 1, sizeof(InspiralTemplate) );
      }
      else
      {
        thisTmplt = thisTmplt->next = (InspiralTemplate *) 
          LALCalloc( 1, sizeof(InspiralTemplate) );
      }
      if ( ! thisTmplt )
      {
        fprintf( stderr, "could not allocate inspiral template\n" );
        CLOBBER_BANK;
        MetaioClose( env );
        return -1;
      }

      /* parse the contents of the row into the InspiralTemplate structure */
      for ( j = 0; tableDir[j].name; ++j )
      {
        REAL4 colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_4;
        INT4 i4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_4s;
        UINT8 i8colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_8s;
        if ( tableDir[j].pos < 0 ) continue;
        if ( tableDir[j].idx == 0 )
        {
          thisTmplt->mass1 = colData;
        }
        else if ( tableDir[j].idx == 1 )
        {
          thisTmplt->mass2 = colData;
        }
        else if ( tableDir[j].idx == 2 )
        {
          thisTmplt->chirpMass = colData;
        }
        else if ( tableDir[j].idx == 3 )
        {
          thisTmplt->eta = colData;
        }
        else if ( tableDir[j].idx == 4 )
        {
          thisTmplt->t0 = colData;
        }
        else if ( tableDir[j].idx == 5 )
        {
          thisTmplt->t2 = colData;
        }
        else if ( tableDir[j].idx == 6 )
        {
          thisTmplt->t3 = colData;
        }
        else if ( tableDir[j].idx == 7 )
        {
          thisTmplt->t4 = colData;
        }
        else if ( tableDir[j].idx == 8 )
        {
          thisTmplt->t5 = colData;
        }
        else if ( tableDir[j].idx == 9 )
        {
          thisTmplt->tC = colData;
        }
        else if ( tableDir[j].idx == 10 )
        {
          thisTmplt->psi0 = colData;
        }
        else if ( tableDir[j].idx == 11 )
        {
          thisTmplt->psi3 = colData;
        }
        else if ( tableDir[j].idx == 12 )
        {
          thisTmplt->beta = colData;
        }
        else if ( tableDir[j].idx == 13 )
        {
          thisTmplt->fFinal = colData;
        }
        else if ( tableDir[j].idx == 14 )
        {
          thisTmplt->end_time.gpsSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 15 )
        {
          thisTmplt->end_time.gpsNanoSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 16 )
        {
          if ( tableDir[j].pos > 0 && i8colData )
          {
            thisTmplt->event_id = (EventIDColumn *) 
              LALCalloc( 1, sizeof(EventIDColumn) );
            thisTmplt->event_id->id = i8colData;
            thisTmplt->event_id->inspiralTemplate = thisTmplt;
          }
        }
        else if ( tableDir[j].idx == 17 )
        {
          LALSnprintf( thisTmplt->ifo, LIGOMETA_IFO_MAX * sizeof(CHAR), 
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 18 )
        {
          thisTmplt->Gamma[0] = colData;
        }
        else if ( tableDir[j].idx == 19 )
        {
          thisTmplt->Gamma[1] = colData;
        }
        else if ( tableDir[j].idx == 20 )
        {
          thisTmplt->Gamma[2] = colData;
        }
        else if ( tableDir[j].idx == 21 )
        {
          thisTmplt->Gamma[3] = colData;
        }
        else if ( tableDir[j].idx == 22 )
        {
          thisTmplt->Gamma[4] = colData;
        }
        else if ( tableDir[j].idx == 23 )
        {
          thisTmplt->Gamma[5] = colData;
        }
        else if ( tableDir[j].idx == 24 )
        {
          thisTmplt->Gamma[6] = colData;
        }
        else if ( tableDir[j].idx == 25 )
        {
          thisTmplt->Gamma[7] = colData;
        }
        else if ( tableDir[j].idx == 26 )
        {
          thisTmplt->Gamma[8] = colData;
        }
        else if ( tableDir[j].idx == 27 )
        {
          thisTmplt->Gamma[9] = colData;
        }
        else if ( tableDir[j].idx == 28 )
        {
          thisTmplt->kappa = colData;
        }
        else if ( tableDir[j].idx == 29 )
        {
          thisTmplt->chi = colData;
        }        
        else
        {
          CLOBBER_BANK;
          fprintf( stderr, "unknown column while parsing\n" );
          return -1;
        }
      }

      /* compute derived mass parameters */
      thisTmplt->totalMass = thisTmplt->mass1 + thisTmplt->mass2;
      if ( thisTmplt->totalMass > 0 )
      {
        thisTmplt->mu = thisTmplt->mass1 * thisTmplt->mass2 / 
          thisTmplt->totalMass;
      }

      /* set the match determined from the bank generation process params */
      thisTmplt->minMatch = minMatch;

      /* count the number of template parsed */
      thisTmplt->number = nrows++;
    }
  }

  if ( mioStatus == -1 )
  {
    fprintf( stderr, "error parsing after row %d\n", i );
    CLOBBER_BANK;
    MetaioClose( env );
    return -1;
  }

  /* we have sucesfully parsed temples */
  MetaioClose( env );
  return nrows;  
}

#define CLOBBER_SIM \
  while ( *simHead ); \
{ \
  thisSim = *simHead; \
  *simHead = (*simHead)->next; \
  LALFree( thisSim ); \
  thisSim = NULL; \
}

/* <lalVerbatim file="LIGOLwXMLReadCP"> */
int
SimInspiralTableFromLIGOLw (
    SimInspiralTable   **simHead,
    CHAR                *fileName,
    INT4                 startTime,
    INT4                 endTime
    )
/* </lalVerbatim> */
{
  int                                   i, j, nrows;
  int                                   mioStatus;
  SimInspiralTable                     *thisSim = NULL;
  struct MetaioParseEnvironment         parseEnv;
  const  MetaioParseEnv                 env = &parseEnv;
  MetaTableDirectory tableDir[] =
  {
    {"waveform",            -1, 0},
    {"geocent_end_time",    -1, 1},
    {"geocent_end_time_ns", -1, 2},
    {"h_end_time",          -1, 3},
    {"h_end_time_ns",       -1, 4},
    {"l_end_time",          -1, 5},
    {"l_end_time_ns",       -1, 6},
    {"g_end_time",          -1, 7},
    {"g_end_time_ns",       -1, 8},
    {"t_end_time",          -1, 9},
    {"t_end_time_ns",       -1, 10},
    {"v_end_time",          -1, 11},
    {"v_end_time_ns",       -1, 12},
    {"end_time_gmst",       -1, 13},
    {"source",              -1, 14},
    {"mass1",               -1, 15},
    {"mass2",               -1, 16},
    {"eta",                 -1, 17},
    {"distance",            -1, 18},
    {"longitude",           -1, 19},
    {"latitude",            -1, 20},
    {"inclination",         -1, 21},
    {"coa_phase",           -1, 22},
    {"polarization",        -1, 23},
    {"psi0",                -1, 24},
    {"psi3",                -1, 25},
    {"alpha",               -1, 26},
    {"alpha1",              -1, 27},
    {"alpha2",              -1, 28},
    {"alpha3",              -1, 29},
    {"alpha4",              -1, 30},
    {"alpha5",              -1, 31},
    {"alpha6",              -1, 32},
    {"beta",                -1, 33},
    {"spin1x",              -1, 34},
    {"spin1y",              -1, 35},
    {"spin1z",              -1, 36},
    {"spin2x",              -1, 37},
    {"spin2y",              -1, 38},
    {"spin2z",              -1, 39},
    {"theta0",              -1, 40},
    {"phi0",                -1, 41},
    {"f_lower",             -1, 42},
    {"f_final",             -1, 43},
    {"mchirp",              -1, 44},
    {"eff_dist_h",          -1, 45},
    {"eff_dist_l",          -1, 46},
    {"eff_dist_g",          -1, 47},
    {"eff_dist_t",          -1, 48},
    {"eff_dist_v",          -1, 49},
    {"numrel_mode_min",     -1, 50},
    {"numrel_mode_max",     -1, 51},
    {"numrel_data",         -1, 52},
    {NULL,                   0, 0}
  };

  /* check that the bank handle and pointer are valid */
  if ( ! simHead )
  {
    fprintf( stderr, "null pointer passed as handle to simulation list" );
    return -1;
  }
  if ( *simHead )
  {
    fprintf( stderr, "non-null pointer passed as pointer to simulation list" );
    return -1;
  }

  /* open the sim_inspiral table file */
  mioStatus = MetaioOpenTable( env, fileName, "sim_inspiral" );
  if ( mioStatus )
  {
    fprintf( stderr, "error opening sim_inspiral table from file %s\n", 
        fileName );
    return -1;
  }

  /* figure out the column positions of the simulated parameters */
  for ( i = 0; tableDir[i].name; ++i )
  {
    if ( (tableDir[i].pos = MetaioFindColumn( env, tableDir[i].name )) < 0 )
    {
      fprintf( stderr, "unable to find column %s\n", tableDir[i].name );
      MetaioClose(env);
      return -1;
    }
  }

  /* loop over the rows in the file */
  i = nrows = 0;
  while ( (mioStatus = MetaioGetRow(env)) == 1 ) 
  {
    INT4 geo_time = env->ligo_lw.table.elt[tableDir[1].pos].data.int_4s;

    /* get the injetcion time and check that it is within the time window */
    /* JC: AGAIN... HOPE PARENTHESES ARE RIGHT! */
    if ( ! endTime || ( geo_time > startTime && geo_time < endTime ) )
    {
      /* allocate memory for the template we are about to read in */
      if ( ! *simHead )
      {
        thisSim = *simHead = (SimInspiralTable *) 
          LALCalloc( 1, sizeof(SimInspiralTable) );
      }
      else
      {
        thisSim = thisSim->next = (SimInspiralTable *) 
          LALCalloc( 1, sizeof(SimInspiralTable) );
      }
      if ( ! thisSim )
      {
        fprintf( stderr, "could not allocate inspiral simulation\n" );
        CLOBBER_SIM;
        MetaioClose( env );
        return -1;
      }

      /* parse the row into the SimInspiralTable structure */
      for ( j = 0; tableDir[j].name; ++j )
      {
        REAL4 r4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_4;
        REAL8 r8colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_8;
        INT4  i4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_4s;
        if ( tableDir[j].idx == 0 )
        {
          LALSnprintf(thisSim->waveform, LIGOMETA_WAVEFORM_MAX * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data);
        }    
        else if ( tableDir[j].idx == 1 )    
        {
          thisSim->geocent_end_time.gpsSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 2 )
        {
          thisSim->geocent_end_time.gpsNanoSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 3 )    
        {
          thisSim->h_end_time.gpsSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 4 )
        {
          thisSim->h_end_time.gpsNanoSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 5 )    
        {
          thisSim->l_end_time.gpsSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 6 )
        {
          thisSim->l_end_time.gpsNanoSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 7 )    
        {
          thisSim->g_end_time.gpsSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 8 )
        {
          thisSim->g_end_time.gpsNanoSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 9 )    
        {
          thisSim->t_end_time.gpsSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 10 )
        {
          thisSim->t_end_time.gpsNanoSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 11 )     
        {
          thisSim->v_end_time.gpsSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 12 )
        {
          thisSim->v_end_time.gpsNanoSeconds = i4colData;
        }
        else if ( tableDir[j].idx == 13 )
        {
          thisSim->end_time_gmst = r8colData;
        }
        else if ( tableDir[j].idx == 14 )
        {
          LALSnprintf(thisSim->source, LIGOMETA_SOURCE_MAX * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data);
        }
        else if ( tableDir[j].idx == 15 )
        {
          thisSim->mass1 = r4colData;
        }
        else if ( tableDir[j].idx == 16 )
        {
          thisSim->mass2 = r4colData;
        }
        else if ( tableDir[j].idx == 17 )
        {
          thisSim->eta = r4colData;
        }
        else if ( tableDir[j].idx == 18 )
        {
          thisSim->distance = r4colData;
        }
        else if ( tableDir[j].idx == 19 )
        {
          thisSim->longitude = r4colData;
        }
        else if ( tableDir[j].idx == 20 )
        {
          thisSim->latitude = r4colData;
        }
        else if ( tableDir[j].idx == 21 )
        {
          thisSim->inclination = r4colData;
        }
        else if ( tableDir[j].idx == 22 )
        {
          thisSim->coa_phase = r4colData;
        } 
        else if ( tableDir[j].idx == 23 )
        {
          thisSim->polarization = r4colData;
        }
        else if ( tableDir[j].idx == 24 )
        {
          thisSim->psi0 = r4colData;
        }
        else if ( tableDir[j].idx == 25 )
        {
          thisSim->psi3 = r4colData;
        }
        else if ( tableDir[j].idx == 26 )
        {
          thisSim->alpha = r4colData;
        }
        else if ( tableDir[j].idx == 27 )
        {
          thisSim->alpha1 = r4colData;
        }
        else if ( tableDir[j].idx == 28 )
        {
          thisSim->alpha2 = r4colData;
        }	
        else if ( tableDir[j].idx == 29 )
        {
          thisSim->alpha3 = r4colData;
        }	
        else if ( tableDir[j].idx == 30 )
        {
          thisSim->alpha4 = r4colData;
        }
        else if ( tableDir[j].idx == 31 )
        {
          thisSim->alpha5 = r4colData;
        }
        else if ( tableDir[j].idx == 32 )
        {
          thisSim->alpha6 = r4colData;
        }
        else if ( tableDir[j].idx == 33 )
        {
          thisSim->beta = r4colData;
        }    
        else if ( tableDir[j].idx == 34 )
        {
          thisSim->spin1x = r4colData;
        }
        else if ( tableDir[j].idx == 35 )
        {
          thisSim->spin1y = r4colData;
        }
        else if ( tableDir[j].idx == 36 )
        {
          thisSim->spin1z = r4colData;
        }
        else if ( tableDir[j].idx == 37 )
        {
          thisSim->spin2x = r4colData;
        }
        else if ( tableDir[j].idx == 38 )
        {
          thisSim->spin2y = r4colData;
        }
        else if ( tableDir[j].idx == 39 )
        {
          thisSim->spin2z = r4colData;
        }
        else if ( tableDir[j].idx == 40 )
        {
          thisSim->theta0 = r4colData;
        }
        else if ( tableDir[j].idx == 41 )
        {
          thisSim->phi0 = r4colData;
        }
        else if ( tableDir[j].idx == 42 )
        {
          thisSim->f_lower = r4colData;
        }
        else if ( tableDir[j].idx == 43 )
        {
          thisSim->f_final = r4colData;
        }
        else if ( tableDir[j].idx == 44 )
        {
          thisSim->mchirp = r4colData;
        }
        else if ( tableDir[j].idx == 45 )
        {
          thisSim->eff_dist_h = r4colData;
        }
        else if ( tableDir[j].idx == 46 )
        {
          thisSim->eff_dist_l = r4colData;
        }
        else if ( tableDir[j].idx == 47 )
        {
          thisSim->eff_dist_g = r4colData;
        }
        else if ( tableDir[j].idx == 48 )
        {
          thisSim->eff_dist_t = r4colData;
        }
        else if ( tableDir[j].idx == 49 )
        {
          thisSim->eff_dist_v = r4colData;
        }
	else if ( tableDir[j].idx == 50 )
	{
	  thisSim->numrel_mode_min = i4colData;
	}
	else if ( tableDir[j].idx == 51 )
	{
	  thisSim->numrel_mode_max = i4colData;
	}
	else if ( tableDir[j].idx == 52 )
	{
          LALSnprintf(thisSim->numrel_data, LIGOMETA_STRING_MAX * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data);
	}
        else
        {
          CLOBBER_SIM;
          fprintf( stderr, "unknown column while parsing\n" );
          return -1;
        }
      }

      /* increase the count of rows parsed */
      ++nrows;       
    }
  }

  if ( mioStatus == -1 )
  {
    fprintf( stderr, "error parsing after row %d\n", i );
    CLOBBER_SIM;
    MetaioClose( env );
    return -1;
  }

  /* we have sucesfully parsed temples */
  MetaioClose( env );
  return nrows;  
}

#undef CLOBBER_SIM


/* <lalVerbatim file="LIGOLwXMLReadCP"> */
SearchSummaryTable *
XLALSearchSummaryTableFromLIGOLw (
    const CHAR *fileName
)
/* </lalVerbatim> */
{
  const char *func = "XLALSearchSummaryTableFromLIGOLw";
  SearchSummaryTable *head = NULL;
  SearchSummaryTable *oldhead;
  struct MetaioParseEnvironment parser;
  MetaTableDirectory tableDir[] = {
    {"comment",           -1, 0},
    {"ifos",              -1, 1},
    {"in_start_time",     -1, 2},
    {"in_start_time_ns",  -1, 3},
    {"in_end_time",       -1, 4},
    {"in_end_time_ns",    -1, 5},
    {"out_start_time",    -1, 6},
    {"out_start_time_ns", -1, 7},
    {"out_end_time",      -1, 8},
    {"out_end_time_ns",   -1, 9},
    {"nevents",           -1, 10},
    {"nnodes",            -1, 11},
    {NULL,                 0, 0}
  };
  int i;

  /* open the search_summary table */
  if(MetaioOpenTable(&parser, fileName, "search_summary")) {
    XLALPrintError("error opening search_summary table from file %s\n", fileName);
    XLAL_ERROR_NULL(func, XLAL_EIO);
  }

  /* determine column positions */
  for(i = 0; tableDir[i].name; i++)
    if((tableDir[i].pos = MetaioFindColumn(&parser, tableDir[i].name)) < 0) {
      /* no optional columns! */
      XLALPrintError("unable to find column %s\n", tableDir[i].name);
      MetaioClose(&parser);
      XLAL_ERROR_NULL(func, XLAL_EIO);
    }

  /* loop over rows */
  do switch(MetaioGetRow(&parser)) {
  case -1: /* error */
  default: /* ??? */
    XLALPrintError("error parsing row\n");
    while(head) {
      oldhead = head;
      head = head->next;
      LALFree(oldhead);
    }
    MetaioClose(&parser);
    XLAL_ERROR_NULL(func, XLAL_EIO);

  case 0: /* end of table */
    MetaioClose(&parser);
    return head;

  case 1: /* found a row */
    /* prepend an entry to the linked list */
    oldhead = head;
    head = LALCalloc(1, sizeof(*head));
    head->next = oldhead;

    /* loop over columns */
    for(i = 0; tableDir[i].name; i++) {
      /* was column found in table? */
      if(tableDir[i].pos < 0)
        continue;

      /* which is it? */
      switch(tableDir[i].idx) {
      case 0:
        LALSnprintf(head->comment, LIGOMETA_COMMENT_MAX * sizeof(CHAR), "%s", parser.ligo_lw.table.elt[tableDir[i].pos].data.lstring.data);
        break;

      case 1:
        LALSnprintf(head->ifos, LIGOMETA_COMMENT_MAX * sizeof(CHAR), "%s", parser.ligo_lw.table.elt[tableDir[i].pos].data.lstring.data );
        break;

      case 2:
        head->in_start_time.gpsSeconds = parser.ligo_lw.table.elt[tableDir[i].pos].data.int_4s;
        break;

      case 3:
        head->in_start_time.gpsNanoSeconds = parser.ligo_lw.table.elt[tableDir[i].pos].data.int_4s;
        break;

      case 4:
        head->in_end_time.gpsSeconds = parser.ligo_lw.table.elt[tableDir[i].pos].data.int_4s;
        break;

      case 5:
        head->in_end_time.gpsNanoSeconds = parser.ligo_lw.table.elt[tableDir[i].pos].data.int_4s;
        break;

      case 6:
        head->out_start_time.gpsSeconds = parser.ligo_lw.table.elt[tableDir[i].pos].data.int_4s;
        break;

      case 7:
        head->out_start_time.gpsNanoSeconds = parser.ligo_lw.table.elt[tableDir[i].pos].data.int_4s;
        break;

      case 8:
        head->out_end_time.gpsSeconds = parser.ligo_lw.table.elt[tableDir[i].pos].data.int_4s;
        break;

      case 9:
        head->out_end_time.gpsNanoSeconds = parser.ligo_lw.table.elt[tableDir[i].pos].data.int_4s;
        break;

      case 10:
        head->nevents = parser.ligo_lw.table.elt[tableDir[i].pos].data.int_4s;
        break;

      case 11:
        head->nnodes = parser.ligo_lw.table.elt[tableDir[i].pos].data.int_4s;
        break;
      }
    }
  } while(1);
}


#define CLOBBER_VAL \
  while ( *sumHead ); \
{ \
  thisValue = *sumHead; \
  *sumHead = (*sumHead)->next; \
  LALFree( thisValue ); \
  thisValue = NULL; \
}


/* <lalVerbatim file="LIGOLwXMLReadCP"> */
int
SummValueTableFromLIGOLw (
    SummValueTable **sumHead,
    CHAR           *fileName
    )
/* </lalVerbatim> */
{
  int                                   i, j, nrows;
  int                                   mioStatus;
  SummValueTable                       *thisValue = NULL;
  struct MetaioParseEnvironment         parseEnv;
  const  MetaioParseEnv                 env = &parseEnv;
  MetaTableDirectory tableDir[] =
  {
    {"program",               -1, 0},
    {"start_time",            -1, 1},
    {"start_time_ns",         -1, 2},
    {"end_time",              -1, 3},
    {"end_time_ns",           -1, 4},
    {"ifo",                   -1, 5},
    {"name",                  -1, 6},
    {"value",                 -1, 7},
    {"comment",               -1, 8},
    {NULL,                     0, 0}
  };

  /* check that the bank handle and pointer are vaid */
  if ( ! sumHead )
  {
    fprintf( stderr, "null pointer passed as handle to summ value" );
    return -1;
  }
  if ( *sumHead )
  {
    fprintf( stderr, "non-null pointer passed as pointer to summ value" );
    return -1;
  }

  /* open the summ_value table in the file file */
  mioStatus = MetaioOpenTable( env, fileName, "summ_value" );
  if ( mioStatus )
  {
    fprintf( stderr, 
        "warning: unable to opening summ_value table from file %s\n", 
        fileName );
    return -1;
  }

  /* figure out the column positions */
  for ( i = 0; tableDir[i].name; ++i )
  {
    if ( (tableDir[i].pos = MetaioFindColumn( env, tableDir[i].name )) < 0 )
    {
      fprintf( stderr, "unable to find column %s\n", tableDir[i].name );
      MetaioClose(env);
      return -1;
    }
  }

  /* loop over the rows in the file */
  i = nrows = 0;
  while ( (mioStatus = MetaioGetRow(env)) == 1 ) 
  {
    /* allocate memory for the table */
    if ( ! *sumHead )
    {
      thisValue = *sumHead = (SummValueTable *) 
        LALCalloc( 1, sizeof(SummValueTable) );
    }
    else
    {
      thisValue = thisValue->next = (SummValueTable *) 
        LALCalloc( 1, sizeof(SummValueTable) );
    }
    if ( ! thisValue )
    {
      fprintf( stderr, "could not allocate summ value\n" );
      CLOBBER_VAL;
      MetaioClose( env );
      return -1;
    }

    /* parse the rows into the SummValue structure */
    for ( j = 0; tableDir[j].name; ++j )
    {
      REAL4 r4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_4;
      INT4  i4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_4s;

      if ( tableDir[j].idx == 0 )
      {
        LALSnprintf( thisValue->program, LIGOMETA_PROGRAM_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 1 )
      {
        thisValue->start_time.gpsSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 2 )
      {
        thisValue->start_time.gpsNanoSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 3 )
      {
        thisValue->end_time.gpsSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 4 )
      {
        thisValue->end_time.gpsNanoSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 5 )
      {
        LALSnprintf( thisValue->ifo, LIGOMETA_IFO_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 6 )
      {
        LALSnprintf( thisValue->name, LIGOMETA_SUMMVALUE_NAME_MAX * 
            sizeof(CHAR), "%s",
            env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 7 )
      {
        thisValue->value = r4colData;
      }
      else if ( tableDir[j].idx == 8 )
      {
        LALSnprintf( thisValue->comment, LIGOMETA_SUMMVALUE_NAME_MAX * 
            sizeof(CHAR), "%s",
            env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else
      {
        CLOBBER_VAL;
        fprintf( stderr, "unknown column while parsing\n" );
        return -1;
      }
    }

    /* increase the count of rows parsed */
    ++nrows;
  }

  if ( mioStatus == -1 )
  {
    fprintf( stderr, "error parsing after row %d\n", i );
    CLOBBER_VAL;
    MetaioClose( env );
    return -1;
  }

  /* we have sucesfully parsed table */
  MetaioClose( env );
  return nrows;  
}

#undef CLOBBER_VAL

#define CLOBBER_STOCH_VAL \
  while (*stochHead); \
{ \
  thisValue = *stochHead; \
  *stochHead = (*stochHead)->next; \
  LALFree( thisValue ); \
  thisValue = NULL; \
}

/* <lalVerbatim file="LIGOLwXMLReadCP"> */
int
LALStochasticTableFromLIGOLw (
    StochasticTable **stochHead,
    CHAR *fileName)
/* </lalVerbatim> */
{
  int i, j, nrows;
  int mioStatus;
  StochasticTable *thisValue = NULL;

  struct MetaioParseEnvironment parseEnv;
  const MetaioParseEnv env = &parseEnv;
  MetaTableDirectory tableDir[] =
  {
    {"ifo_one",       -1,  0},
    {"ifo_two",       -1,  1},
    {"channel_one",   -1,  2},
    {"channel_two",   -1,  3},
    {"start_time",    -1,  4},
    {"start_time_ns", -1,  5},
    {"duration",      -1,  6},
    {"duration_ns",   -1,  7},
    {"f_min",         -1,  8},
    {"f_max",         -1,  9},
    {"cc_stat",       -1, 10},
    {"cc_sigma",      -1, 11},
    {NULL,             0,  0}
  };

  /* check that the table handle and pointer are valid */
  if (!stochHead)
  {
    fprintf(stderr, "null pointer passed as handle to stochastic value\n");
    return -1;
  }
  if (*stochHead)
  {
    fprintf(stderr, "non-null pointer passed as pointer to stochastic value\n");
    return -1;
  }

  /* open the stochastic)table in the file file */
  mioStatus = MetaioOpenTable(env, fileName, "stochastic");
  if (mioStatus)
  {
    fprintf(stderr, "error opening stochastic table from file %s\n", \
        fileName);
    return -1;
  }

  /* figure out the column positions */
  for (i = 0; tableDir[i].name; ++i)
  {
    if ((tableDir[i].pos = MetaioFindColumn(env, tableDir[i].name)) < 0)
    {
      fprintf(stderr, "unable to find column %s\n", tableDir[i].name);
      MetaioClose(env);
      return -1;
    }
  }

  /* loop over the rows in the file */
  i = nrows = 0;
  while ((mioStatus = MetaioGetRow(env)) == 1) 
  {
    /* allocate memory for the table */
    if (!*stochHead)
    {
      thisValue = *stochHead = (StochasticTable *) \
                  LALCalloc(1, sizeof(StochasticTable));
    }
    else
    {
      thisValue = thisValue->next = (StochasticTable *) \
                  LALCalloc( 1, sizeof(StochasticTable) );
    }
    if (!thisValue)
    {
      fprintf(stderr, "could not allocate stochastic table\n");
      CLOBBER_STOCH_VAL;
      MetaioClose(env);
      return -1;
    }

    /* parse the rows into the StochasticTable structure */
    for ( j = 0; tableDir[j].name; ++j )
    {
      REAL8 r8colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_8;
      INT4  i4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_4s;

      if (tableDir[j].idx == 0)
      {
        LALSnprintf(thisValue->ifo_one, LIGOMETA_IFO_MAX * sizeof(CHAR), \
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data);
      }
      else if (tableDir[j].idx == 1)
      {
        LALSnprintf(thisValue->ifo_two, LIGOMETA_IFO_MAX * sizeof(CHAR), \
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data);
      }
      else if ( tableDir[j].idx == 2 )
      {
        LALSnprintf(thisValue->channel_one, LIGOMETA_CHANNEL_MAX * \
            sizeof(CHAR), "%s", \
            env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data);
      }
      else if ( tableDir[j].idx == 3 )
      {
        LALSnprintf(thisValue->channel_two, LIGOMETA_CHANNEL_MAX * \
            sizeof(CHAR), "%s", \
            env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data);
      }
      else if ( tableDir[j].idx == 4 )
      {
        thisValue->start_time.gpsSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 5 )
      {
        thisValue->start_time.gpsNanoSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 6 )
      {
        thisValue->duration.gpsSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 7 )
      {
        thisValue->duration.gpsNanoSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 8 )
      {
        thisValue->f_min = r8colData;
      }
      else if ( tableDir[j].idx == 9 )
      {
        thisValue->f_max = r8colData;
      }
      else if ( tableDir[j].idx == 10 )
      {
        thisValue->cc_stat = r8colData;
      }
      else if ( tableDir[j].idx == 11 )
      {
        thisValue->cc_sigma = r8colData;
      }
      else
      {
        CLOBBER_STOCH_VAL;
        fprintf(stderr, "unknown column while parsing\n");
        return -1;
      }
    }

    /* increase the count of rows parsed */
    ++nrows;
  }

  if (mioStatus == -1)
  {
    fprintf(stderr, "error parsing after row %d\n", i);
    CLOBBER_STOCH_VAL;
    MetaioClose(env);
    return -1;
  }

  /* we have sucesfully parsed table */
  MetaioClose(env);
  return nrows;  
}

#undef CLOBBER_STOCH_VAL

#define CLOBBER_STOCH_SUMM_VAL \
  while (*stochSummHead); \
{ \
  thisValue = *stochSummHead; \
  *stochSummHead = (*stochSummHead)->next; \
  LALFree( thisValue ); \
  thisValue = NULL; \
}

/* <lalVerbatim file="LIGOLwXMLReadCP"> */
int
LALStochSummTableFromLIGOLw (
    StochSummTable **stochSummHead,
    CHAR *fileName)
/* </lalVerbatim> */
{
  int i, j, nrows;
  int mioStatus;
  StochSummTable *thisValue = NULL;

  struct MetaioParseEnvironment parseEnv;
  const MetaioParseEnv env = &parseEnv;
  MetaTableDirectory tableDir[] =
  {
    {"ifo_one",       -1,  0},
    {"ifo_two",       -1,  1},
    {"channel_one",   -1,  2},
    {"channel_two",   -1,  3},
    {"start_time",    -1,  4},
    {"start_time_ns", -1,  5},
    {"end_time",      -1,  6},
    {"end_time_ns",   -1,  7},
    {"f_min",         -1,  8},
    {"f_max",         -1,  9},
    {"y_opt",         -1, 10},
    {"error",         -1, 11},
    {NULL,             0,  0}
  };

  /* check that the table handle and pointer are valid */
  if (!stochSummHead)
  {
    fprintf(stderr, "null pointer passed as handle to stoch_summ value\n");
    return -1;
  }
  if (*stochSummHead)
  {
    fprintf(stderr, "non-null pointer passed as pointer to stoch_summ value\n");
    return -1;
  }

  /* open the stoch_summ_table in the file file */
  mioStatus = MetaioOpenTable(env, fileName, "stoch_summ");
  if (mioStatus)
  {
    fprintf(stderr, "error opening stoch_summ table from file %s\n", \
        fileName);
    return -1;
  }

  /* figure out the column positions */
  for (i = 0; tableDir[i].name; ++i)
  {
    if ((tableDir[i].pos = MetaioFindColumn(env, tableDir[i].name)) < 0)
    {
      fprintf(stderr, "unable to find column %s\n", tableDir[i].name);
      MetaioClose(env);
      return -1;
    }
  }

  /* loop over the rows in the file */
  i = nrows = 0;
  while ((mioStatus = MetaioGetRow(env)) == 1) 
  {
    /* allocate memory for the table */
    if (!*stochSummHead)
    {
      thisValue = *stochSummHead = (StochSummTable *) \
                  LALCalloc(1, sizeof(StochSummTable));
    }
    else
    {
      thisValue = thisValue->next = (StochSummTable *) \
                  LALCalloc( 1, sizeof(StochSummTable) );
    }
    if (!thisValue)
    {
      fprintf(stderr, "could not allocate stoch_summ table\n");
      CLOBBER_STOCH_SUMM_VAL;
      MetaioClose(env);
      return -1;
    }

    /* parse the rows into the StochSummTable structure */
    for ( j = 0; tableDir[j].name; ++j )
    {
      REAL8 r8colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_8;
      INT4  i4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_4s;

      if (tableDir[j].idx == 0)
      {
        LALSnprintf(thisValue->ifo_one, LIGOMETA_IFO_MAX * sizeof(CHAR), \
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data);
      }
      else if (tableDir[j].idx == 1)
      {
        LALSnprintf(thisValue->ifo_two, LIGOMETA_IFO_MAX * sizeof(CHAR), \
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data);
      }
      else if ( tableDir[j].idx == 2 )
      {
        LALSnprintf(thisValue->channel_one, LIGOMETA_CHANNEL_MAX * \
            sizeof(CHAR), "%s", \
            env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data);
      }
      else if ( tableDir[j].idx == 3 )
      {
        LALSnprintf(thisValue->channel_two, LIGOMETA_CHANNEL_MAX * \
            sizeof(CHAR), "%s", \
            env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data);
      }
      else if ( tableDir[j].idx == 4 )
      {
        thisValue->start_time.gpsSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 5 )
      {
        thisValue->start_time.gpsNanoSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 6 )
      {
        thisValue->end_time.gpsSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 7 )
      {
        thisValue->end_time.gpsNanoSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 8 )
      {
        thisValue->f_min = r8colData;
      }
      else if ( tableDir[j].idx == 9 )
      {
        thisValue->f_max = r8colData;
      }
      else if ( tableDir[j].idx == 10 )
      {
        thisValue->y_opt = r8colData;
      }
      else if ( tableDir[j].idx == 11 )
      {
        thisValue->error = r8colData;
      }
      else
      {
        CLOBBER_STOCH_SUMM_VAL;
        fprintf(stderr, "unknown column while parsing\n");
        return -1;
      }
    }

    /* increase the count of rows parsed */
    ++nrows;
  }

  if (mioStatus == -1)
  {
    fprintf(stderr, "error parsing after row %d\n", i);
    CLOBBER_STOCH_SUMM_VAL;
    MetaioClose(env);
    return -1;
  }

  /* we have sucesfully parsed table */
  MetaioClose(env);
  return nrows;  
}

#undef CLOBBER_STOCH_SUMM_VAL


#define CLOBBER_EVENTS \
  while ( *eventHead ); \
{ \
  thisEvent = *eventHead; \
  *eventHead = (*eventHead)->next; \
  LALFree( thisEvent ); \
  thisEvent = NULL; \
}



/* <lalVerbatim file="LIGOLwXMLReadCP"> */
int
LALExtTriggerTableFromLIGOLw (
    ExtTriggerTable   **eventHead,
    CHAR               *fileName,
    INT4                startEvent,
    INT4                stopEvent
    )
/* </lalVerbatim> */
{
  int                                   i, j, nrows;
  int                                   mioStatus;
  ExtTriggerTable                       *thisEvent = NULL;
  struct MetaioParseEnvironment         parseEnv;
  const  MetaioParseEnv                 env = &parseEnv;
  MetaTableDirectory tableDir[] =
  {
    {"det_alts",               -1,  0},
    {"det_band",               -1,  1},
    {"det_fluence",            -1,  2},
    {"det_fluence_int",        -1,  3},
    {"det_name",               -1,  4},
    {"det_peak",               -1,  5},
    {"det_peak_int",           -1,  6},
    {"det_snr",                -1,  7},
    {"email_time",             -1,  8},
    {"event_dec",              -1,  9},
    {"event_dec_err",          -1, 10},
    {"event_epoch",            -1, 11},
    {"event_err_type",         -1, 12},
    {"event_ra",               -1, 13},
    {"event_ra_err",           -1, 14},
    {"start_time",             -1, 15},
    {"start_time_ns",          -1, 16},
    {"event_type",             -1, 17},
    {"event_z",                -1, 18},
    {"event_z_err",            -1, 19},
    {"notice_comments",        -1, 20},
    {"notice_id",              -1, 21},
    {"notice_sequence",        -1, 22},
    {"notice_time",            -1, 23},
    {"notice_type",            -1, 24},
    {"notice_url",             -1, 25},
    {"obs_fov_dec",            -1, 26},
    {"obs_fov_dec_width",      -1, 27},
    {"obs_fov_ra",             -1, 28},
    {"obs_fov_ra_width",       -1, 29},   
    {"obs_loc_ele",            -1, 30},
    {"obs_loc_lat",            -1, 31},
    {"obs_loc_long",           -1, 32},
    {"ligo_fave_lho",          -1, 33},
    {"ligo_fave_llo",          -1, 34},
    {"ligo_delay",             -1, 35},
    {"event_number_gcn",       -1, 36},
    {"event_number_grb",       -1, 37},
    {"event_status",           -1, 38},
    {NULL,                      0, 0}
  };


  /* check that the bank handle and pointer are void */
  if ( ! eventHead )
  {
    fprintf( stderr, "null pointer passed as handle to event list" );
    return -1;
  }
  if ( *eventHead )
  {
    fprintf( stderr, "non-null pointer passed as pointer to event list" );
    return -1;
  }

  /* open the sngl_inspiral table template bank file */
  mioStatus = MetaioOpenTable( env, fileName, "external_trigger" );
  if ( mioStatus )
  {
    fprintf( stdout, "no ext_trigger table in file %s\n", fileName );
    return 0;
  }

  /* figure out the column positions of the template parameters */
  for ( i = 0; tableDir[i].name; ++i )
  {
    if ( (tableDir[i].pos = MetaioFindColumn( env, tableDir[i].name )) < 0 )
    {
      fprintf( stderr, "unable to find column %s\n", tableDir[i].name );
      MetaioClose(env);
      return -1;
    }
  }

  /* loop over the rows in the file */
  i = nrows = 0;
  while ( (mioStatus = MetaioGetRow(env)) == 1 ) 
  {
    /* count the rows in the file */
    i++;

    /* stop parsing if we have reach the last row requested */
    if ( stopEvent > -1 && i > stopEvent )
    {
      break;
    }

    /* if we have reached the first requested row, parse the row */
    if ( i > startEvent )
    {
      /* allocate memory for the template we are about to read in */
      if ( ! *eventHead )
      {
        thisEvent = *eventHead = (ExtTriggerTable*) 
          LALCalloc( 1, sizeof(ExtTriggerTable) );
      }
      else
      {
        thisEvent = thisEvent->next = (ExtTriggerTable *) 
          LALCalloc( 1, sizeof(ExtTriggerTable) );
      }
      if ( ! thisEvent )
      {
        fprintf( stderr, "could not allocate inspiral template\n" );
        CLOBBER_EVENTS;
        MetaioClose( env );
        return -1;
      }

      /* parse the contents of the row into the InspiralTemplate structure */
      for ( j = 0; tableDir[j].name; ++j )
      {
        REAL4 r4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_4;
        /* REAL8 r8colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_8; */
        INT4  i4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_4s;

        if ( tableDir[j].idx == 0 )
        {
          LALSnprintf( thisEvent->det_alts, LIGOMETA_STD * sizeof(CHAR), 
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 1 )
        {
          LALSnprintf( thisEvent->det_band, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 2 )
        {
          LALSnprintf( thisEvent->det_fluence, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }  
        else if ( tableDir[j].idx == 3 )
        {
          LALSnprintf( thisEvent->det_fluence_int, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }  
        else if ( tableDir[j].idx == 4 )
        {
          LALSnprintf( thisEvent->det_name, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 5 )
        {
          LALSnprintf( thisEvent->det_peak, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }  
        else if ( tableDir[j].idx == 6 )
        {
          LALSnprintf( thisEvent->det_peak_int, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }  
        else if ( tableDir[j].idx == 7 )
        {
          LALSnprintf( thisEvent->det_snr, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        } 
        else if ( tableDir[j].idx == 8 )
        {
          thisEvent->email_time = i4colData;
        }
        else if ( tableDir[j].idx == 9 )
        {
          thisEvent->event_dec = r4colData;
        }
        else if ( tableDir[j].idx == 10 )
        {
          thisEvent->event_dec_err = r4colData;
        }
        else if ( tableDir[j].idx == 11 )
        {  
          LALSnprintf( thisEvent->event_epoch, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 12 )
        {
          LALSnprintf( thisEvent->event_err_type, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 13 )
        {
          thisEvent->event_ra = r4colData;
        }
        else if ( tableDir[j].idx == 14 )
        {
          thisEvent->event_ra_err = r4colData;
        }
        else if ( tableDir[j].idx == 15 )
        {
          thisEvent->start_time = i4colData;
          /*  printf("start time:%d\n",i4colData); */
        }
        else if ( tableDir[j].idx == 16 )
        {
          thisEvent->start_time_ns = i4colData;
        }	
        else if ( tableDir[j].idx == 17 )
        {
          LALSnprintf( thisEvent->event_type, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 18 )
        {
          thisEvent->event_z = r4colData;
        }
        else if ( tableDir[j].idx == 19 )
        {
          thisEvent->event_z_err = r4colData;
        }
        else if ( tableDir[j].idx == 20 )
        {
          LALSnprintf( thisEvent->notice_comments, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }	
        else if ( tableDir[j].idx == 21 )
        {
          LALSnprintf( thisEvent->notice_id, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 22 )
        {
          LALSnprintf( thisEvent->notice_sequence, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 23 )
        {
          thisEvent->notice_time = i4colData;
        }
        else if ( tableDir[j].idx == 24 )
        {
          LALSnprintf( thisEvent->notice_type, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 25 )
        {
          LALSnprintf( thisEvent->notice_url, LIGOMETA_STD * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }	
        else if ( tableDir[j].idx == 26 )
        {
          thisEvent->obs_fov_dec = r4colData;
        }
        else if ( tableDir[j].idx == 27 )
        {
          thisEvent->obs_fov_dec_width = r4colData;
        }
        else if ( tableDir[j].idx == 28 )
        {
          thisEvent->obs_fov_ra = r4colData;
        }
        else if ( tableDir[j].idx == 29 )
        {
          thisEvent->obs_fov_ra_width = i4colData;
        }
        else if ( tableDir[j].idx == 30 )
        {
          thisEvent->obs_loc_ele = r4colData;
        }
        else if ( tableDir[j].idx == 31 )
        {
          thisEvent->obs_loc_lat = r4colData;
        }
        else if ( tableDir[j].idx == 32 )
        {
          thisEvent->obs_loc_long = r4colData;
        }
        else if ( tableDir[j].idx == 33 )
        {
          thisEvent->ligo_fave_lho = r4colData;
        }
        else if ( tableDir[j].idx == 34 )
        {
          thisEvent->ligo_fave_llo = r4colData;
        }
        else if ( tableDir[j].idx == 35 )
        {
          thisEvent->ligo_delay = r4colData;
        }
        else if ( tableDir[j].idx == 36 )
        {
          thisEvent->event_number_gcn= i4colData;
        }
        else if ( tableDir[j].idx == 37 )
        {
          LALSnprintf( thisEvent->event_number_grb, 8 * sizeof(CHAR),
              "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
        }
        else if ( tableDir[j].idx == 38 )
        {
          thisEvent->event_status = i4colData;
        }
        else
        {
          CLOBBER_EVENTS;
          fprintf( stderr, "unknown column while parsing ext_trigger\n" );
          return -1;
        }
      }

      /* count the number of template parsed */
      nrows++;
    }
  }

  /* must be reduced to avoid stopping psocessing with triggers.xml
     because that file is generated corrupted (by just adding new triggers
     in new lines */
  /*
     if ( mioStatus == -1 )
     {
     fprintf( stderr, "error parsing after row %d\n", i );
     CLOBBER_EVENTS;
     MetaioClose( env );
     return -1;
     }
   */

  /* we have sucesfully parsed temples */
  MetaioClose( env );
  return nrows;  
}


#undef CLOBBER_EVENTS


int 
XLALReadSummValueFile (
    SummValueTable **summValueList,
    CHAR                  *fileName
    )
/* </lalVerbatim> */
{
  const char *func = "XLALReadSummValueFile";
  INT4 numFileTriggers = 0;
  INT4 haveSummValue = 0;
  SummValueTable  *thisSummValue = NULL;
  SummValueTable  *inputSummValue = NULL;


  /* read in the summ value table and store */ 
  XLALPrintInfo( 
      "XLALReadSummValueFile(): Reading summ_value table\n");

  haveSummValue = SummValueTableFromLIGOLw(&inputSummValue, fileName);

  if ( ! inputSummValue || haveSummValue < 1)
  {
    XLALPrintInfo("No valid summ_value table in %s\n", fileName );
  }
  else
  {
    /* store the summ value table in SummValueList list */
    XLALPrintInfo("XLALReadSummValueFile(): Checking summ_value_table\n"); 
    
    /* keep only relevant information (inspiral_effective_distance)*/  
    XLALCleanSummValueTable(&inputSummValue);
    
    if ( ! *summValueList )
    {
      *summValueList = thisSummValue = inputSummValue;
    }
    else
    {
      for ( thisSummValue = *summValueList; thisSummValue->next; 
          thisSummValue = thisSummValue->next);
      thisSummValue = thisSummValue->next = inputSummValue;    
    }
  }
 return 1;
}

/* <lalVerbatim file="LIGOLwXMLReadCP"> */
int
XLALReadInspiralTriggerFile (
    SnglInspiralTable    **inspiralEventList,
    SnglInspiralTable    **lastTrigger,
    SearchSummaryTable   **searchSummList,
    SearchSummvarsTable  **inputFileList,
    CHAR                  *fileName
    )
/* </lalVerbatim> */
{
  const char *func = "XLALReadInspiralTriggerFile";
  INT4 numFileTriggers = 0;
  INT4 haveSummValue = 0;
  SnglInspiralTable  *inputData = NULL;
  SearchSummaryTable *inputSummary = NULL;
  SearchSummaryTable *thisSearchSumm = NULL;
  SearchSummvarsTable  *thisInputFile = NULL;
#if 0
  SummValueTable  *thisSummValue = NULL;
  SummValueTable  *inputSummValue = NULL;
#endif


  /* store the file name in search summvars */
  XLALPrintInfo(
      "XLALReadInspiralTriggerFile(): storing input file name %s\n"
      "in search summvars table\n", fileName );

  if ( ! *inputFileList )
  {
    *inputFileList = thisInputFile = (SearchSummvarsTable *)
      LALCalloc( 1, sizeof(SearchSummvarsTable) );
  }
  else
  {
    for ( thisInputFile = *inputFileList; thisInputFile->next; 
        thisInputFile = thisInputFile->next );
    thisInputFile = thisInputFile->next = (SearchSummvarsTable *)
      LALCalloc( 1, sizeof(SearchSummvarsTable) );
  }
  LALSnprintf( thisInputFile->name, LIGOMETA_NAME_MAX, 
      "input_file" );
  LALSnprintf( thisInputFile->string, LIGOMETA_NAME_MAX, 
      "%s", fileName );      


  /* read in the search summary and store */ 
  XLALPrintInfo( 
      "XLALReadInspiralTriggerFile(): Reading search_summary table\n");

  inputSummary = XLALSearchSummaryTableFromLIGOLw(fileName);

  if ( ! inputSummary )
  {
    XLALPrintError("No valid search_summary table in %s, exiting\n",
        fileName );
    LALFree(thisInputFile);
    XLAL_ERROR(func, XLAL_EIO);
  }
  else
  {
    /* store the search summary table in searchSummList list */
    if ( ! *searchSummList )
    {
      *searchSummList = thisSearchSumm = inputSummary;
    }
    else
    {
      for ( thisSearchSumm = *searchSummList; thisSearchSumm->next; 
          thisSearchSumm = thisSearchSumm->next);
      thisSearchSumm = thisSearchSumm->next = inputSummary;
    }
  }
#if 0
  /* read in the summ value table and store */ 
  XLALPrintInfo( 
      "XLALReadInspiralTriggerFile(): Reading summ_value table\n");

  haveSummValue = SummValueTableFromLIGOLw(&inputSummValue, fileName);

  if ( ! inputSummValue || haveSummValue < 1)
  {
    XLALPrintError("No valid summ_value table in %s, exiting\n",
        fileName );
    LALFree(thisInputFile);
    XLAL_ERROR(func, XLAL_EIO);
  }
  else
  {
    /* store the summ value table in SummValueList list */
    XLALPrintInfo("XLALReadInspiralTriggerFile(): Checking summ_value_table\n"); 
    
    /* keep only relevant information (inspiral_effective_distance)*/  
    XLALCleanSummValueTable(&inputSummValue);
    
    if ( ! *summValueList )
    {
      *summValueList = thisSummValue = inputSummValue;
    }
    else
    {
      for ( thisSummValue = *summValueList; thisSummValue->next; 
          thisSummValue = thisSummValue->next);
      thisSummValue = thisSummValue->next = inputSummValue;    
    }
  }
#endif
  /* read in the triggers */
  numFileTriggers = 
    LALSnglInspiralTableFromLIGOLw( &inputData, fileName, 0, -1 );

  if ( numFileTriggers < 0 )
  {
    XLALPrintError("Unable to read sngl_inspiral table from %s\n", 
        fileName );
    LALFree(thisInputFile);
    XLAL_ERROR(func, XLAL_EIO);
  }
  else if ( numFileTriggers > 0 )
  {

    XLALPrintInfo( 
        "XLALReadInspiralTriggerFile(): Got %d sngl_inspiral rows from %s\n", 
        numFileTriggers, fileName );

    /* store the triggers */
    if ( ! *inspiralEventList )
    {
      /* store the head of the linked list */
      *inspiralEventList = *lastTrigger = inputData;
    }
    else
    {
      /* append to the end of the linked list and set current    */
      /* trigger to the first trigger of the list being appended */
      *lastTrigger = (*lastTrigger)->next = inputData;
    }

    /* scroll to the end of the linked list of triggers */
    for ( ; (*lastTrigger)->next; *lastTrigger = (*lastTrigger)->next );
  }

  return( numFileTriggers );
}

      

/* function which reads a summ_value table and remove
   all rows which do not contain name set 
   to "effective_inspiral_distance". */
void XLALCleanSummValueTable(SummValueTable **inputSummValue)
{
  SummValueTable *this = NULL;
  SummValueTable *prev = NULL;
  SummValueTable *head = NULL;
  
  this  = *inputSummValue;
  head = NULL;
      
  while( this )
  {
    INT4 discard = 0;
    SummValueTable *tmp = this;

    this = this->next;

    if (strncmp( tmp->name, "inspiral_effective_distance", 
	LIGOMETA_SUMMVALUE_NAME_MAX) )
    {      
      /* not an effective distance -- discard */
      XLALPrintInfo(
  	"XLALReadIspiralTriggerFile(): Removing entry with  \"%s\" name \n",
  	 tmp->name);
      discard = 1;
    }
    else
    {
      discard = 0; 
      XLALPrintInfo( 
	"XLALReadIspiralTriggerFile(): Got inspiral effective distance of %f for a %s system.\n",
	tmp->value, tmp->comment);     
    }

    if (discard)
    {
      LALFree(tmp);
    }
    else
    {
      if (!head)
      {
        head = tmp;
      }
      else
      {
        prev->next = tmp;
      }
      tmp->next = NULL;
      prev = tmp;
    }
  }
  *inputSummValue = head;
}


#define CLOBBER_EVENTS \
  while ( *eventHead ); \
{ \
  thisEvent = *eventHead; \
  *eventHead = (*eventHead)->next; \
  LALFree( thisEvent ); \
  thisEvent = NULL; \
}

/* <lalVerbatim file="LIGOLwXMLReadCP"> */
int
LALMultiInspiralTableFromLIGOLw (
    MultiInspiralTable **eventHead,
    CHAR                *fileName
    )
/* </lalVerbatim> */
{
  int                                   i, j, nrows;
  int                                   mioStatus;
  MultiInspiralTable                   *thisEvent = NULL;
  struct MetaioParseEnvironment         parseEnv;
  const  MetaioParseEnv                 env = &parseEnv;
  MetaTableDirectory tableDir[] =
    {
          {"ifos",                    -1, 0},
          {"search",                  -1, 1},
          {"end_time",                -1, 2},
          {"end_time_ns",             -1, 3},
          {"end_time_gmst",           -1, 4},
          {"impulse_time",            -1, 5},
          {"impulse_time_ns",         -1, 6},
          {"amplitude",               -1, 7},
          {"ifo1_eff_distance",       -1, 8},
          {"ifo2_eff_distance",       -1, 9},
          {"eff_distance",            -1, 10},
          {"coa_phase",               -1, 11},
          {"mass1",                   -1, 12},
          {"mass2",                   -1, 13},
          {"mchirp",                  -1, 14},
          {"eta",                     -1, 15},
          {"tau0",                    -1, 16},
          {"tau2",                    -1, 17},
          {"tau3",                    -1, 18},
          {"tau4",                    -1, 19},
          {"tau5",                    -1, 20},
          {"ttotal",                  -1, 21},
          {"ifo1_snr",                -1, 22},
          {"ifo2_snr",                -1, 23},
          {"snr",                     -1, 24},
          {"chisq",                   -1, 25},
          {"chisq_dof",               -1, 26},
          {"bank_chisq",              -1, 27},
          {"bank_chisq_dof",          -1, 28},
          {"cont_chisq",              -1, 29},
          {"cont_chisq_dof",          -1, 30},
          {"sigmasq",                 -1, 31},
          {"ligo_axis_ra",            -1, 32},
          {"ligo_axis_dec",           -1, 33},
          {"ligo_angle",              -1, 34},
          {"ligo_angle_sig",          -1, 35},
          {"inclination",             -1, 36},
          {"polarization",            -1, 37},
          {"event_id",                -1, 38},
          {"null_statistic",          -1, 39},
          {"h1quad_re",               -1, 40},
          {"h1quad_im",               -1, 41},
          {"h2quad_re",               -1, 42},
          {"h2quad_im",               -1, 43},
          {"l1quad_re",               -1, 44},
          {"l1quad_im",               -1, 45},
          {"v1quad_re",               -1, 46},
          {"v1quad_im",               -1, 47},
          {"g1quad_re",               -1, 48},
          {"g1quad_im",               -1, 49},
          {"t1quad_re",               -1, 50},
          {"t1quad_im",               -1, 51},
          {NULL,                       0, 0}
    };

  /* check that the bank handle and pointer are valid */
  if ( ! eventHead )
  {
    fprintf( stderr, "null pointer passed as handle to event list" );
    return -1;
  }
  if ( *eventHead )
  {
    fprintf( stderr, "non-null pointer passed as pointer to event list" );
    return -1;
  }

  /* open the multi_inspiral XML file */
  mioStatus = MetaioOpenFile( env, fileName );
  if ( mioStatus )
  {
    fprintf( stderr, "unable to open file %s\n", fileName );
    return -1;
  }

  /* open the multi_inspiral table template bank file */
  mioStatus = MetaioOpenTableOnly( env, "multi_inspiral" );
  if ( mioStatus )
  {
    fprintf( stdout, "no multi_inspiral table in file %s\n", fileName );
    return 0;
  }

  /* figure out the column positions of the template parameters */
  for ( i = 0; tableDir[i].name; ++i )
  {
    if ( (tableDir[i].pos = MetaioFindColumn( env, tableDir[i].name )) < 0 )
    {
      fprintf( stderr, "unable to find column %s\n", tableDir[i].name );

      if ( ! strcmp(tableDir[i].name, "event_id") )
      {
        fprintf( stderr,
            "The event_id column is not populated, continuing anyway\n");
      }
      else
      {
        MetaioClose(env);
        return -1;
      }
    }
  }

  /* loop over the rows in the file */
  i = nrows = 0;
  while ( (mioStatus = MetaioGetRow(env)) == 1 )
  {
    /* count the rows in the file */
    i++;
    /* allocate memory for the template we are about to read in */
    if ( ! *eventHead )
    {
      thisEvent = *eventHead = (MultiInspiralTable *)
        LALCalloc( 1, sizeof(MultiInspiralTable) );
    }
    else
    {
      thisEvent = thisEvent->next = (MultiInspiralTable *)
        LALCalloc( 1, sizeof(MultiInspiralTable) );
    }
    if ( ! thisEvent )
    {
      fprintf( stderr, "could not allocate multi inspiral event\n" );
        CLOBBER_EVENTS;
        MetaioClose( env );
        return -1;
    }

    /* parse the contents of the row into the MultiInspiralTable structure */
    for ( j = 0; tableDir[j].name; ++j )
    {
      REAL4 r4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_4;
      REAL8 r8colData = env->ligo_lw.table.elt[tableDir[j].pos].data.real_8;
      INT4  i4colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_4s;
      UINT8 i8colData = env->ligo_lw.table.elt[tableDir[j].pos].data.int_8s;

      if ( tableDir[j].pos < 0 ) continue;

      /* dereference the data stored in the table */
      if ( tableDir[j].idx == 0 )
      {
        LALSnprintf( thisEvent->ifos, LIGOMETA_IFO_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 1 )
      {
        LALSnprintf( thisEvent->search, LIGOMETA_SEARCH_MAX * sizeof(CHAR),
            "%s", env->ligo_lw.table.elt[tableDir[j].pos].data.lstring.data );
      }
      else if ( tableDir[j].idx == 2 )
      {
        thisEvent->end_time.gpsSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 3 )
      {
        thisEvent->end_time.gpsNanoSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 4 )
      {
        thisEvent->end_time_gmst = r8colData;
      }
      else if ( tableDir[j].idx == 5 )
      {
        thisEvent->impulse_time.gpsSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 6 )
      {
        thisEvent->impulse_time.gpsNanoSeconds = i4colData;
      }
      else if ( tableDir[j].idx == 7 )
      {
        thisEvent->amplitude = r4colData;
      }
      else if ( tableDir[j].idx == 8 )
      {
        thisEvent->ifo1_eff_distance = r4colData;
      }
      else if ( tableDir[j].idx == 9 )
      {
        thisEvent->ifo2_eff_distance = r4colData;
      }
      else if ( tableDir[j].idx == 10 )
      {
        thisEvent->eff_distance = r4colData;
      }
      else if ( tableDir[j].idx == 11 )
      {
        thisEvent->coa_phase = r4colData;
      }
      else if ( tableDir[j].idx == 12 )
      {
        thisEvent->mass1 = r4colData;
      }
      else if ( tableDir[j].idx == 13 )
      {
        thisEvent->mass2 = r4colData;
      }
      else if ( tableDir[j].idx == 14 )
      {
        thisEvent->mchirp = r4colData;
      }
      else if ( tableDir[j].idx == 15 )
      {
        thisEvent->eta = r4colData;
      }
      else if ( tableDir[j].idx == 16 )
      {
        thisEvent->tau0 = r4colData;
      }
      else if ( tableDir[j].idx == 17 )
      {
        thisEvent->tau2 = r4colData;
      }
      else if ( tableDir[j].idx == 18 )
      {
        thisEvent->tau3 = r4colData;
      }
      else if ( tableDir[j].idx == 19 )
      {
        thisEvent->tau4 = r4colData;
      }
      else if ( tableDir[j].idx == 20 )
      {
        thisEvent->tau5 = r4colData;
      }
      else if ( tableDir[j].idx == 21 )
      {
        thisEvent->ttotal = r4colData;
      }
      else if ( tableDir[j].idx == 22 )
      {
        thisEvent->ifo1_snr = r4colData;
      }
      else if ( tableDir[j].idx == 23 )
      {
        thisEvent->ifo2_snr = r4colData;
      }
      else if ( tableDir[j].idx == 24 )
      {
        thisEvent->snr = r4colData;
      }
      else if ( tableDir[j].idx == 25 )
      {
        thisEvent->chisq = r4colData;
      }
      else if ( tableDir[j].idx == 26 )
      {
        thisEvent->chisq_dof = i4colData;
      }
      else if ( tableDir[j].idx == 27 )
      {
        thisEvent->bank_chisq = r4colData;
      }
      else if ( tableDir[j].idx == 28 )
      {
        thisEvent->bank_chisq_dof = i4colData;
      }
      else if ( tableDir[j].idx == 29 )
      {
        thisEvent->cont_chisq = r4colData;
      }
      else if ( tableDir[j].idx == 30 )
      {
        thisEvent->cont_chisq_dof = i4colData;
      }
      else if ( tableDir[j].idx == 31 )
      {
        thisEvent->sigmasq = r8colData;
      }
      else if ( tableDir[j].idx == 32 )
      {
        thisEvent->ligo_axis_ra = r4colData;
      }
      else if ( tableDir[j].idx == 33 )
      {
        thisEvent->ligo_axis_dec = r4colData;
      }
      else if ( tableDir[j].idx == 34 )
      {
        thisEvent->ligo_angle = r4colData;
      }
      else if ( tableDir[j].idx == 35 )
      {
        thisEvent->ligo_angle_sig = r4colData;
      }
      else if ( tableDir[j].idx == 36 )
      {
        thisEvent->inclination = r4colData;
      }
      else if ( tableDir[j].idx == 37 )
      {
        thisEvent->polarization = r4colData;
      }
      else if ( tableDir[j].idx == 38 )
      {
        if ( tableDir[j].pos > 0 && i8colData )
        {
          thisEvent->event_id = (EventIDColumn *)
            LALCalloc( 1, sizeof(EventIDColumn) );
          thisEvent->event_id->id = i8colData;
          thisEvent->event_id->multiInspiralTable = thisEvent;
        }
      }
      else if ( tableDir[j].idx == 39 )
      {
        thisEvent->null_statistic = r8colData;
      }
      else if ( tableDir[j].idx == 40 )
      {
        thisEvent->h1quad.re = r4colData;
      }
      else if ( tableDir[j].idx == 41 )
      {
        thisEvent->h1quad.im = r4colData;
      }
      else if ( tableDir[j].idx == 42 )
      {
        thisEvent->h2quad.re = r4colData;
      }
      else if ( tableDir[j].idx == 43 )
      {
        thisEvent->h2quad.im = r4colData;
      }
      else if ( tableDir[j].idx == 44 )
      {
        thisEvent->l1quad.re = r4colData;
      }
      else if ( tableDir[j].idx == 45 )
      {
        thisEvent->l1quad.im = r4colData;
      }
      else if ( tableDir[j].idx == 46 )
      {
        thisEvent->v1quad.re = r4colData;
      }
      else if ( tableDir[j].idx == 47 )
      {
        thisEvent->v1quad.im = r4colData;
      }
      else if ( tableDir[j].idx == 48 )
      {
        thisEvent->g1quad.re = r4colData;
      }
      else if ( tableDir[j].idx == 49 )
      {
        thisEvent->g1quad.im = r4colData;
      }
      else if ( tableDir[j].idx == 50 )
      {
        thisEvent->t1quad.re = r4colData;
      }
      else if ( tableDir[j].idx == 51 )
      {
        thisEvent->t1quad.im = r4colData;
      }
      else
      {
        CLOBBER_EVENTS;
        fprintf( stderr, "unknown column while parsing multi_inspiral\n" );
        return -1;
      }
    }

    /* count the number of triggers parsed */
    nrows++;
  }

  if ( mioStatus == -1 )
  {
    fprintf( stderr, "error parsing after row %d\n", i );
    CLOBBER_EVENTS;
    MetaioClose( env );
    return -1;
  }

  /* Normal exit */
  MetaioClose( env );
  return nrows;
}

#undef CLOBBER_EVENTS

/* <lalVerbatim file="LIGOLwXMLReadCP"> */
int
XLALReadMultiInspiralTriggerFile (
    MultiInspiralTable    **inspiralEventList,
    MultiInspiralTable    **lastTrigger,
    SearchSummaryTable    **searchSummList,
    SearchSummvarsTable   **inputFileList,
    CHAR                   *fileName
    )
/* </lalVerbatim> */
{
  const char *func = "XLALReadMultiInspiralTriggerFile";
  INT4 numFileTriggers = 0;
  INT4 haveSummValue = 0;
  MultiInspiralTable   *inputData = NULL;
  SearchSummaryTable   *inputSummary = NULL;
  SearchSummaryTable   *thisSearchSumm = NULL;
  SearchSummvarsTable  *thisInputFile = NULL;
#if 0
  SummValueTable  *thisSummValue = NULL;
  SummValueTable  *inputSummValue = NULL;
#endif


  /* store the file name in search summvars */
  XLALPrintInfo(
      "XLALReadMultiInspiralTriggerFile(): storing input file name %s\n"
      "in search summvars table\n", fileName );

  if ( ! *inputFileList )
  {
    *inputFileList = thisInputFile = (SearchSummvarsTable *)
      LALCalloc( 1, sizeof(SearchSummvarsTable) );
  }
  else
  {
    for ( thisInputFile = *inputFileList; thisInputFile->next;
        thisInputFile = thisInputFile->next );
    thisInputFile = thisInputFile->next = (SearchSummvarsTable *)
      LALCalloc( 1, sizeof(SearchSummvarsTable) );
  }
  LALSnprintf( thisInputFile->name, LIGOMETA_NAME_MAX,
      "input_file" );
  LALSnprintf( thisInputFile->string, LIGOMETA_NAME_MAX,
      "%s", fileName );


  /* read in the search summary and store */
  XLALPrintInfo(
      "XLALReadMultiInspiralTriggerFile(): Reading search_summary table\n");

  inputSummary = XLALSearchSummaryTableFromLIGOLw(fileName);

  if ( ! inputSummary )
  {
    XLALPrintError("No valid search_summary table in %s, exiting\n",
        fileName );
    LALFree(thisInputFile);
    XLAL_ERROR(func, XLAL_EIO);
  }
  else
  {
    /* store the search summary table in searchSummList list */
    if ( ! *searchSummList )
    {
      *searchSummList = thisSearchSumm = inputSummary;
    }
    else
    {
      for ( thisSearchSumm = *searchSummList; thisSearchSumm->next;
          thisSearchSumm = thisSearchSumm->next);
      thisSearchSumm = thisSearchSumm->next = inputSummary;
    }
  }
#if 0
  /* read in the summ value table and store */
  XLALPrintInfo(
      "XLALReadMultiInspiralTriggerFile(): Reading summ_value table\n");

  haveSummValue = SummValueTableFromLIGOLw(&inputSummValue, fileName);

  if ( ! inputSummValue || haveSummValue < 1)
  {
    XLALPrintError("No valid summ_value table in %s, exiting\n",
        fileName );
    LALFree(thisInputFile);
    XLAL_ERROR(func, XLAL_EIO);
  }
  else
  {
    /* store the summ value table in SummValueList list */
    XLALPrintInfo("XLALReadMultiInspiralTriggerFile(): Checking summ_value_table\n");

    /* keep only relevant information (inspiral_effective_distance)*/
    XLALCleanSummValueTable(&inputSummValue);

    if ( ! *summValueList )
    {
      *summValueList = thisSummValue = inputSummValue;
    }
    else
    {
      for ( thisSummValue = *summValueList; thisSummValue->next;
          thisSummValue = thisSummValue->next);
      thisSummValue = thisSummValue->next = inputSummValue;
    }
  }
#endif
  /* read in the triggers */
  numFileTriggers =
    LALMultiInspiralTableFromLIGOLw( &inputData, fileName);

  if ( numFileTriggers < 0 )
  {
    XLALPrintError("Unable to read multi_inspiral table from %s\n",
        fileName );
    LALFree(thisInputFile);
    XLAL_ERROR(func, XLAL_EIO);
  }
  else if ( numFileTriggers > 0 )
  {

    XLALPrintInfo(
        "XLALReadMultiInspiralTriggerFile(): Got %d multi_inspiral rows from %s\n",
        numFileTriggers, fileName );

    /* store the triggers */
    if ( ! *inspiralEventList )
    {
      /* store the head of the linked list */
      *inspiralEventList = *lastTrigger = inputData;
    }
    else
    {
      /* append to the end of the linked list and set current    */
      /* trigger to the first trigger of the list being appended */
      *lastTrigger = (*lastTrigger)->next = inputData;
    }

    /* scroll to the end of the linked list of triggers */
    for ( ; (*lastTrigger)->next; *lastTrigger = (*lastTrigger)->next );
  }

  return( numFileTriggers );
}

