//------------------------------------------------------------------------
// Copyright(c) 2023 TNZNT Music.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace stx {
//------------------------------------------------------------------------
static const Steinberg::FUID kIntrumentTestProcessorUID (0xED28E080, 0xCE765E3B, 0x80F211BA, 0x77607903);
static const Steinberg::FUID kIntrumentTestControllerUID (0x7E852932, 0x251557C3, 0x8064422F, 0xCB257BA8);

#define IntrumentTestVST3Category "Instrument"

//------------------------------------------------------------------------
} // namespace stx
