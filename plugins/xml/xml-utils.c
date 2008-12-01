/* 
Gregorio xml output format.
Copyright (C) 2006 Elie Roux <elie.roux@enst-bretagne.fr>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config.h"
#include <stdio.h>
#include "gettext.h"
#define _(str) gettext(str)
#define N_(str) str
#include "messages.h"
#include "struct.h"
#include "xml.h"

const char *
libgregorio_xml_shape_to_str (char shape)
{
  const char *str;

  switch (shape)
    {
    case S_PUNCTUM:
      str = "punctum";
      break;
    case S_PUNCTUM_INCLINATUM:
      str = "punctum_inclinatum";
      break;
    case S_PUNCTUM_INCLINATUM_DEMINUTUS:
      str = "punctum_inclinatum_deminutus";
      break;
    case S_PUNCTUM_INCLINATUM_AUCTUS:
      str = "punctum_inclinatum_auctus";
      break;
    case S_VIRGA:
      str = "virga";
      break;
    case S_ORISCUS:
      str = "oriscus";
      break;
    case S_ORISCUS_AUCTUS:
      str = "oriscus_auctus";
      break;
    case S_QUILISMA:
      str = "quilisma";
      break;
    case S_STROPHA:
      str = "stropha";
      break;
    case S_PUNCTUM_CAVUM:
      str = "punctum_cavum";
      break;
    case S_LINEA_PUNCTUM:
      str = "linea_punctum";
      break;
    case S_LINEA_PUNCTUM_CAVUM:
      str = "linea_punctum_cavum";
      break;
    default:
      str = "punctum";
      libgregorio_message (_("unknown shape, `punctum' assumed"),
		      "libgregorio_xml_shape_to_str", WARNING, 0);
      break;
    }
  return str;
}

const char *
libgregorio_xml_signs_to_str (char signs)
{
  const char *str;

  switch (signs)
    {
    case _PUNCTUM_MORA:
      str = "<right>auctum</right>";
      break;
    case _AUCTUM_DUPLEX:
      str = "<right>auctum_duplex</right>";
      break;
    case _V_EPISEMUS:
      str = "<bottom>v_episemus</bottom>";
      break;
    case _V_EPISEMUS_PUNCTUM_MORA:
      str = "<right>auctum</right>\n<bottom>v_episemus</bottom>";
      break;
    case _V_EPISEMUS_AUCTUM_DUPLEX:
      str = "<right>auctum_duplex</right>\n<bottom>v_episemus</bottom>";
      break;
    case _ACCENTUS:
      str = "<above>accentus</above>";
      break;
    case _ACCENTUS_REVERSUS:
      str = "<above>reversed_accentus</above>";
      break;
    case _CIRCULUS:
      str = "<above>circulus</above>";
      break;
    case _SEMI_CIRCULUS:
      str = "<above>semi_circulus</above>";
      break;
    case _SEMI_CIRCULUS_REVERSUS:
      str = "<above>reversed_semi_circulus</above>";
      break;
    default:
      str = "";
      break;
    }
  return str;
}

void
libgregorio_xml_write_signs (FILE * f, char signs, char h_episemus_type, char rare_sign)
{
  const char *str;
  if (signs != _NO_SIGN || rare_sign != _NO_SIGN || h_episemus_type == H_ALONE)
    {
      fprintf (f, "<signs>");
      if (h_episemus_type == H_ALONE)
	{
	  fprintf (f, "<top>h_episemus</top>");
	}
      if (signs != _NO_SIGN)
	{
	  str = libgregorio_xml_signs_to_str (signs);
	  fprintf (f, "%s", str);
	}
      if (rare_sign != _NO_SIGN)
	{
	  str = libgregorio_xml_signs_to_str (rare_sign);
	  fprintf (f, "%s", str);
	}
      fprintf (f, "</signs>");
    }
  if (h_episemus_type == H_MULTI_BEGINNING)
    {
      fprintf (f, "<multi-h-episemus position=\"beginning\" />");
    }
  if (h_episemus_type == H_MULTI_MIDDLE)
    {
      fprintf (f, "<multi-h-episemus position=\"middle\" />");
    }
  if (h_episemus_type == H_MULTI_END)
    {
      fprintf (f, "<multi-h-episemus position=\"end\" />");
    }
}


void
libgregorio_xml_write_note (FILE * f, char signs, char step,
		      int octave, char shape,
		      char h_episemus_type, char alteration, char rare_sign)
{
  const char *shape_str = libgregorio_xml_shape_to_str (shape);

  fprintf (f,
	   "<note><pitch><step>%c</step><octave>%d</octave>",
	   step, octave);
  if (alteration == FLAT)
    {
      fprintf (f, "<flated />");
    }
  fprintf (f, "</pitch>");
  fprintf (f, "<shape>%s</shape>", shape_str);
  libgregorio_xml_write_signs (f, signs, h_episemus_type, rare_sign);
  fprintf (f, "</note>");
}

const char *
libgregorio_xml_glyph_type_to_str (char name)
{
  const char *str;

  switch (name)
    {
    case G_PUNCTUM_INCLINATUM:
      str = "punctum-inclinatum";
      break;
    case G_2_PUNCTA_INCLINATA_DESCENDENS:
      str = "2-puncta-inclinata-descendens";
      break;
    case G_3_PUNCTA_INCLINATA_DESCENDENS:
      str = "3-puncta-inclinata-descendens";
      break;
    case G_4_PUNCTA_INCLINATA_DESCENDENS:
      str = "4-puncta-inclinata-descendens";
      break;
    case G_5_PUNCTA_INCLINATA_DESCENDENS:
      str = "5-puncta-inclinata-descendens";
      break;
    case G_2_PUNCTA_INCLINATA_ASCENDENS:
      str = "2-puncta-inclinata-ascendens";
      break;
    case G_3_PUNCTA_INCLINATA_ASCENDENS:
      str = "3-puncta-inclinata-ascendens";
      break;
    case G_4_PUNCTA_INCLINATA_ASCENDENS:
      str = "4-puncta-inclinata-ascendens";
      break;
    case G_5_PUNCTA_INCLINATA_ASCENDENS:
      str = "5-puncta-inclinata-ascendens";
      break;
    case G_TRIGONUS:
      str = "trigonus";
      break;
    case G_PUNCTA_INCLINATA:
      str = "puncta-inclinata";
      break;
    case G_VIRGA:
      str = "virga";
      break;
    case G_STROPHA:
      str = "stropha";
      break;
    case G_PUNCTUM:
      str = "punctum";
      break;
    case G_PODATUS:
      str = "podatus";
      break;
    case G_FLEXA:
      str = "flexa";
      break;
    case G_TORCULUS:
      str = "torculus";
      break;
    case G_TORCULUS_RESUPINUS:
      str = "torculus-resupinus";
      break;
    case G_TORCULUS_RESUPINUS_FLEXUS:
      str = "torculus-resupinus-flexus";
      break;
    case G_PORRECTUS:
      str = "porrectus";
      break;
    case G_PORRECTUS_FLEXUS:
      str = "porrectus-flexus";
      break;
    case G_BIVIRGA:
      str = "bivirga";
      break;
    case G_TRIVIRGA:
      str = "trivirga";
      break;
    case G_DISTROPHA:
      str = "distropha";
      break;
    case G_TRISTROPHA:
      str = "tristropha";
      break;
    case G_SCANDICUS:
      str = "scandicus";
    default:
      str = "";
      break;
    }
  return str;
}

void
libgregorio_xml_set_pitch_from_octave_and_step (char step,
					  int octave, char *pitch, int clef)
{
  *pitch=libgregorio_det_pitch(clef, step, octave);
}

void
libgregorio_xml_write_liquescentia (FILE * f, char liquescentia)
{
  if (liquescentia == L_NO_LIQUESCENTIA)
    {
      return;
    }
  if (is_initio_debilis (liquescentia))
    {
      fprintf (f, "<initio_debilis />");
    }
  if (liquescentia == L_DEMINUTUS
      || liquescentia == L_DEMINUTUS_INITIO_DEBILIS)
    {
      fprintf (f, "<figura>deminutus</figura>");
    }
  if (liquescentia == L_AUCTUS_ASCENDENS
      || liquescentia == L_AUCTUS_ASCENDENS_INITIO_DEBILIS)
    {
      fprintf (f, "<figura>auctus-ascendens</figura>");
    }
  if (liquescentia == L_AUCTUS_DESCENDENS
      || liquescentia == L_AUCTUS_DESCENDENS_INITIO_DEBILIS)
    {
      fprintf (f, "<figura>auctus-descendens</figura>");
    }
  if (liquescentia == L_AUCTA || liquescentia == L_AUCTA_INITIO_DEBILIS)
    {
      fprintf (f, "<figura>auctus</figura>");
    }
}

void
libgregorio_xml_write_alteration (FILE * f, char type, char pitch, int clef, char *tab)
{
  char step;
  int octave;

  libgregorio_set_octave_and_step_from_pitch (&step, &octave, pitch, clef);
  switch (type)
    {
    case GRE_FLAT:
      tab[pitch - 'a'] = FLAT;
      fprintf (f, "<flat><step>%c</step><octave>%d</octave></flat>",
	       step, octave);
      break;
    case GRE_NATURAL:
      tab[pitch - 'a'] = NO_ALTERATION;
      fprintf (f,
	       "<natural><step>%c</step><octave>%d</octave></natural>",
	       step, octave);
      break;
    }
}

const char *
libgregorio_xml_bar_to_str (char type)
{
  const char *str;

  switch (type)
    {
    case B_VIRGULA:
      str = "virgula";
      break;
    case B_DIVISIO_MINIMA:
      str = "divisio-minima";
      break;
    case B_DIVISIO_MINOR:
      str = "divisio-minor";
      break;
    case B_DIVISIO_MAIOR:
      str = "divisio-maior";
      break;
    case B_DIVISIO_FINALIS:
      str = "divisio-finalis";
      break;
    default:
      str = "";
      libgregorio_message (_("unknown bar type, nothing will be done"),
		      "libgregorio_xml_bar_to_str", ERROR, 0);
      break;
    }
  return str;
}
