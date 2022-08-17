/* -*- c++ -*- */
/*
 * Copyright 2022 gr-grand author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <volk/volk.h>
#include <gnuradio/io_signature.h>
#include "float_array_impl.h"

namespace gr {
  namespace grand {

    #pragma message("set the following appropriately and remove this warning")
    using input_type = float;
    float_array::sptr
    float_array::make(jfloatArray array, int len, JavaVM *vm)
    {
      return gnuradio::make_block_sptr<float_array_impl>(
        array, len, vm);
    }


    /*
     * The private constructor
     */
    float_array_impl::float_array_impl(jfloatArray array, int len, JavaVM *vm)
      : gr::sync_block("float_array",
                       gr::io_signature::make(1, 1, sizeof(float)),
                       gr::io_signature::make(0, 0, 0))
    {
      d_vm = vm;
      d_array = array;
      d_env = NULL;
      d_index = 0;
      d_len = len;
      d_cpp_array = (float*)volk_malloc(d_len*sizeof(float),
                                        volk_get_alignment());
    }

    /*
     * Our virtual destructor.
     */
    float_array_impl::~float_array_impl()
    {
      volk_free(d_cpp_array);
    }

    bool
    float_array_impl::start()
    {
      // We need to get the Java environment from the JVM for the work
      // thread fo the block. Almost certainly the first call to
      // GetEnv will fail since we haven't attached it, yet, but this
      // will take care of that.

      int ret = d_vm->GetEnv((void**)&d_env, JNI_VERSION_1_6);
      if(ret == JNI_EDETACHED) {
        GR_WARN("float_array", "GetEnv: not attached");
        if(d_vm->AttachCurrentThread(&d_env, NULL) != 0) {
          GR_ERROR("float_array", "Failed AttachCurrentThread");
          throw std::runtime_error("Failed AttachCurrentThread");
        }
      }
      else if(ret == JNI_EVERSION) {
        GR_ERROR("float_array", "JNI Version not supported");
        throw std::runtime_error("JNI Version not supported");
      }

      return block::start();
    }

    bool
    float_array_impl::stop()
    {
      d_vm->DetachCurrentThread();
      return block::stop();
    }

    void
    float_array_impl::set_array(jfloatArray array, int len)
    {
      d_array = array;
      d_len = len;
      d_index = 0;

      delete [] d_cpp_array;
      d_cpp_array = (float*)volk_malloc(d_len*sizeof(float),
                                        volk_get_alignment());
    }

    int
    float_array_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float*)input_items[0];

      // Lock access to the array until we've written the full d_len
      if(d_index == 0) {
        d_env->MonitorEnter(d_array);
      }

      int ncopy = std::min((d_len-d_index), noutput_items);
      memcpy(&d_cpp_array[d_index], in, ncopy*sizeof(float));
      d_index += ncopy;

      // Have the full array, copy it back to the Java array and
      // unlock our hold on the data.
      if(d_index == d_len) {
        d_env->SetFloatArrayRegion(d_array, 0, d_len, d_cpp_array);
        d_env->MonitorExit(d_array);
        d_index = 0;
      }

      return ncopy;
    }

  } /* namespace grand */
} /* namespace gr */
