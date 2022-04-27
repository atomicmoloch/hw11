#pragma once

#include "climb_chromosome.hh"
#include "deme.hh"
#include <cassert>

class TournamentDeme : Deme
{
public:
  virtual void compute_next_generation();


protected:

    virtual Chromosome* select_parent();

}
