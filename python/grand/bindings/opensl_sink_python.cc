/*
 * Copyright 2022 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(opensl_sink.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(837b246dd4618aac33271b7d23ba6299)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/grand/opensl_sink.h>
// pydoc.h is automatically generated in the build directory
#include <opensl_sink_pydoc.h>

void bind_opensl_sink(py::module& m)
{

    using opensl_sink    = gr::grand::opensl_sink;


    py::class_<opensl_sink,
    gr::sync_block,
        gr::block,
        gr::basic_block,
        PYBIND11_SH_DEF(opensl_sink)>(m, "opensl_sink", D(opensl_sink))

        .def(py::init(&opensl_sink::make),
           py::arg("sampling_rate"),
           D(opensl_sink,make)
        )
        



        ;




}








