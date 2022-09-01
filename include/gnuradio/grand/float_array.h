/* -*- c++ -*- */
/*
 * Copyright 2022 gr-grand author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_GRAND_FLOAT_ARRAY_H
#define INCLUDED_GRAND_FLOAT_ARRAY_H

#include <gnuradio/grand/api.h>
#include <gnuradio/sync_block.h>
#include <jni.h>

namespace gr {
  namespace grand {

    /*!
     * \brief Fills an array created in the Java app with samples
     * passed into this block from the flowgraph.
     * \ingroup grand
     *
     */
    class GRAND_API float_array : virtual public gr::sync_block
    {
     public:
      typedef std::shared_ptr<float_array> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of
       * grand::float_array.
       *
       * \param array A global reference to the array from the Java
       *  app. Use (jfloatArray)env->NewGlobalRef([array]).
       * \param len Length of \p array.
       * \param vm Pointer to the Java Virtual Machine, from which we
       *  will extract the JNI Environment from for the work thread.
       */
      static sptr make(jfloatArray array, int len, JavaVM *vm);

      /*!
       * Set the internal array to a new value. Make sure that this is
       * a global reference to the Java array.
       *
       * \param array A global reference to the array from the Java
       *  app. Use (jfloatArray)env->NewGlobalRef([array]).
       * \param len Length of \p array.
       */
      virtual void set_array(jfloatArray array, int len) = 0;
    };

  } // namespace grand
} // namespace gr

#endif /* INCLUDED_GRAND_FLOAT_ARRAY_H */
