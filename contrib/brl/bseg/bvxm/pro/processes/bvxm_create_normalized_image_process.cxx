//This is brl/bseg/bvxm/pro/processes/bvxm_create_normalized_image_process.cxx

//:
// \file
// \brief // A class to create a contrast normalized image using the input gain and offset values
//
// \author Ozge Can Ozcanli
// \date Feb 17, 2008
// \verbatim
//
// \Modifications
//   Isabel Restrepo - Jan 27, 2009 - converted process-class to functions which is the new design for bvxm_processes.
// \endverbatim

#include <bprb/bprb_func_process.h>

#include "bvxm_normalize_image_process.cxx"
#include <brdb/brdb_value.h>
#include <bprb/bprb_parameters.h>

#include <vil/vil_image_view_base.h>
#include <brip/brip_vil_float_ops.h>
#include <vpgl/vpgl_camera.h>

#include <bvxm/bvxm_voxel_world.h>
#include <bvxm/bvxm_mog_grey_processor.h>
#include <bvxm/bvxm_image_metadata.h>
#include <bvxm/bvxm_voxel_traits.h>
#include <bvxm/bvxm_util.h>

//:global variables
namespace bvxm_create_normalized_image_process_globals
{
  const unsigned n_inputs_ = 3;
  const unsigned n_outputs_ = 1;
}

//:sets input and output types for bvxm_create_normalized_image_process
bool bvxm_create_normalized_image_process_init(bprb_func_process& pro)
{
  using namespace bvxm_create_normalized_image_process_globals;
  //inputs
  //input 0: image
  //input 1: a-> scale
  //input 2: b-> offset
  vcl_vector<vcl_string> input_types_(n_inputs_);
  input_types_[0] = "vil_image_view_base_sptr";
  input_types_[1] = "float";  // input a
  input_types_[2] = "float";  // input b
  pro.set_input_types(input_types_);

  //output
  vcl_vector<vcl_string> output_types_(n_outputs_);
  output_types_[0]= "vil_image_view_base_sptr";
  pro.set_output_types(output_types_);

  return true;
}

//: create a normalize image
bool bvxm_create_normalized_image_process(bprb_func_process& pro)
{
  //check number of inputs
  if (pro.n_inputs()<3)
  {
    vcl_cout << pro.name()<< "The number of inputs should be 3" << vcl_endl;
    return false;
  }
  //get inputs:
  unsigned i=0;
  vil_image_view_base_sptr input_img = pro.get_input<vil_image_view_base_sptr>(i++);
  float a = pro.get_input<float>(i++);
  float b = pro.get_input<float>(i++);

  //check input's validity
  if (!input_img) {
    vcl_cout << pro.name() <<" :--  Input0  is not valid!\n";
    return false;
  }

  // CAUTION: Assumption: Input image is of type vxl_byte
  if (input_img->pixel_format() != VIL_PIXEL_FORMAT_BYTE) {
    vcl_cout << "In bvxm_create_normalized_image_process::execute() -- Input image pixel format is not VIL_PIXEL_FORMAT_BYTE!\n";
    return false;
  }

  // return the normalized input img
  vil_image_view<vxl_byte> in_image(input_img);
  vil_image_view<vxl_byte> out_image(input_img->ni(), input_img->nj(), input_img->nplanes());
  if (!bvxm_normalize_image_process_globals::normalize_image(in_image, out_image, a, b, (unsigned char)255)) {
    vcl_cout << "In bvxm_create_normalized_image_process::execute() -- Problems during normalization with given inputs\n";
    return false;
  }

  pro.set_output_val<vil_image_view_base_sptr>(0, new vil_image_view<vxl_byte>(out_image));
  return true;
}


