/***************************************************************************/
/*                                                                         */
/*  basepic.c                                                              */
/*                                                                         */
/*    The FreeType position independent code services for base.            */
/*                                                                         */
/*  Copyright 2009 by                                                      */
/*  Oran Agra and Mickey Gabel.                                            */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/


#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_INTERNAL_OBJECTS_H
#include "basepic.h"

#ifdef FT_CONFIG_OPTION_PIC

  /* forward declaration of PIC init functions from ftglyph.c */
  void ft_pic_init_ft_outline_glyph_class(FT_Glyph_Class*);
  void ft_pic_init_ft_bitmap_glyph_class(FT_Glyph_Class*);

  /* forward declaration of PIC init functions from ftinit.c */
  FT_Error ft_create_default_module_classes(FT_Library);
  void ft_destroy_default_module_classes(FT_Library);

  static void
  pic_base_done( void*  base, FT_PicTable  pic )
  {
    FT_UNUSED(base);

    /* Destroy default module classes (in case FT_Add_Default_Modules was used) */
    ft_destroy_default_module_classes( pic->library );
  }

  static FT_Error
  pic_base_init( void*  data, FT_PicTable  pic )
  {
    BasePIC*   base = (BasePIC*)data;
    FT_Error   error;

    /* initialize default modules list and pointers */
    error = ft_create_default_module_classes( pic->library );
    if ( error )
      goto Exit;

    /* initialize pointer table - this is how the module usually expects this data */
    ft_pic_init_ft_outline_glyph_class(&base->ft_outline_glyph_class);
    ft_pic_init_ft_bitmap_glyph_class(&base->ft_bitmap_glyph_class);

  Exit:
    return error;
  }


  FT_Error
  ft_base_pic_init( FT_Library library )
  {
    FT_PicTable  pic_table = &library->pic_table;

    return ft_pic_table_init_data( pic_table,
                                   pic_table->base,
                                   sizeof(BasePIC),
                                   pic_base_init,
                                   pic_base_done );
  }

#endif /* FT_CONFIG_OPTION_PIC */


/* END */