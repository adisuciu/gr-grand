/* -*- c++ -*- */
/*
 * Copyright 2022 gr-grand author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_GRAND_FLOAT_ARRAY_IMPL_H
#define INCLUDED_GRAND_FLOAT_ARRAY_IMPL_H

#include <gnuradio/grand/float_array.h>

namespace gr {
  namespace grand {

    class float_array_impl : public float_array
    {
     private:
      JavaVM *d_vm;
      JNIEnv *d_env;
      jfloatArray d_array;

      int d_len;
      int d_index;
      float * d_cpp_array;

     public:
      float_array_impl(jfloatArray array, int len, JavaVM *vm);
      ~float_array_impl();

      void set_array(jfloatArray array, int len);

      bool start() override;
      bool stop() override;

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      ) override;
    };

  } // namespace grand
} // namespace gr

#endif /* INCLUDED_GRAND_FLOAT_ARRAY_IMPL_H */
