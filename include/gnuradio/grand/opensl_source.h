/* -*- c++ -*- */
/*
 * Copyright 2022 gr-grand author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_GRAND_OPENSL_SOURCE_H
#define INCLUDED_GRAND_OPENSL_SOURCE_H

#include <gnuradio/grand/api.h>
#include <gnuradio/sync_block.h>
#include "gnuradio/grand/basic_logger.h"

namespace gr {
  namespace grand {

    /*!
     * \brief <+description of block+>
     * \ingroup grand
     *
     */
    class GRAND_API opensl_source : virtual public gr::sync_block
    {
     public:
      typedef std::shared_ptr<opensl_source> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of grand::opensl_source.
       *
       * To avoid accidental use of raw pointers, grand::opensl_source's
       * constructor is in a private implementation
       * class. grand::opensl_source::make is the public interface for
       * creating new instances.
       */
      static sptr make(int sampling_rate);
    };

  } // namespace grand
} // namespace gr

#endif /* INCLUDED_GRAND_OPENSL_SOURCE_H */
