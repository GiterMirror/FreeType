/***************************************************************************/
/*                                                                         */
/*  afpic.c                                                                */
/*                                                                         */
/*    The FreeType position independent code services for autofit module.  */
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
#include "afpic.h"

#ifdef FT_CONFIG_OPTION_PIC

  /* forward declaration of PIC init functions from afmodule.c */
  void ft_pic_init_af_autofitter_service( FT_Library, FT_AutoHinter_ServiceRec*);

  /* forward declaration of PIC init functions from script classes */
#include "aflatin.h"
#include "aflatin2.h"
#include "afcjk.h"
#include "afdummy.h"
#include "afindic.h"

  static FT_Error
  pic_autofit_init( void*  _autofit, FT_PicTable  pic )
  {
    AFModulePIC*  container = _autofit;
    FT_UInt       ss;

    /* initialize pointer table - this is how the module usually expects this data */
    for ( ss = 0 ; ss < AF_SCRIPT_CLASSES_REC_COUNT ; ss++ )
    {
      container->af_script_classes[ss] = &container->af_script_classes_rec[ss];
    }
    container->af_script_classes[AF_SCRIPT_CLASSES_COUNT-1] = NULL;

    /* add call to initialization function when you add new scripts */
    ss = 0;
    ft_pic_init_af_dummy_script_class (&container->af_script_classes_rec[ss++]);
#ifdef FT_OPTION_AUTOFIT2
    ft_pic_init_af_latin2_script_class(&container->af_script_classes_rec[ss++]);
#endif
    ft_pic_init_af_latin_script_class (&container->af_script_classes_rec[ss++]);
    ft_pic_init_af_cjk_script_class   (&container->af_script_classes_rec[ss++]);
    ft_pic_init_af_indic_script_class (&container->af_script_classes_rec[ss++]);

    ft_pic_init_af_autofitter_service(pic->library, &container->af_autofitter_service);

    return 0;
  }


  FT_Error
  autofit_module_class_pic_init( FT_Library  library )
  {
    FT_PicTable  pic = &library->pic_table;

    return ft_pic_table_init_data( pic, pic->autofit,
                                   sizeof(AFModulePIC),
                                   pic_autofit_init,
                                   NULL );
  }

#endif /* FT_CONFIG_OPTION_PIC */


/* END */