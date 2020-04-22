/************************************************************************
 * \file MiniBallCobalt60Source.hh
 *
 * \class MiniBallCobalt60Source
 * \brief simulation of a cobalt 60 source including the angular distribution
 *
 * \author hans.boie@mpi-hd.mpg.de
 *
 ************************************************************************/

#ifndef MiniBallCobalt60Source_H
#define MiniBallCobalt60Source_H 1

#include "MiniBallSource.hh"

class MiniBallCobalt60Source : public MiniBallSource
{

public:
  MiniBallCobalt60Source();
  ~MiniBallCobalt60Source();

public:
  MiniBallSourceLevel* ground;
  MiniBallSourceLevel* l1332;
  MiniBallSourceLevel* l2505;
};

#endif
