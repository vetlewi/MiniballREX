/************************************************************************
 * \file MiniBallEuropium152Source.hh
 *
 * \class MiniBallEuropium152Source
 * \brief simulation of a europium 152 source
 *
 * This is a brief simulation of an europium 152 source. Be aware that
 * the angular distribution of the gammas is not simulated (all gammas
 * are distributed isotropicly)
 *
 * \author hans.boie@mpi-hd.mpg.de
 *
 ************************************************************************/

#ifndef MiniBallEuropium152Source_H
#define MiniBallEuropium152Source_H 1

#include "MiniBallSource.hh"

class MiniBallEuropium152Source : public MiniBallSource
{

public:
  MiniBallEuropium152Source();
  ~MiniBallEuropium152Source();
};

#endif
