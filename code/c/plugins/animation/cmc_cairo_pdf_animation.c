#include <stdio.h>

#include <cairo-pdf.h>

#include "color.h"
#include "cmc_cairo_animation_draw_to_file.h"

static void set_version(cairo_surface_t * surface)
{
  cairo_pdf_surface_restrict_to_version(surface, CAIRO_PDF_VERSION_1_5);
}

void cmc_cairo_pdf_animation(
  struct cmc_animation * animation,
  int * status,
  int argc,
  char ** argv,
  const char * filename)
{
  if (filename == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("empty filenames are not allowed\n", stderr);
    *status = 1;
    return;
  }

  cmc_cairo_animation_draw_to_file(
    animation, status, filename, cairo_pdf_surface_create, set_version);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot draw animation to PDF file %s%s%s\n",
      color_variable, filename, color_none);
    return;
  }
}
