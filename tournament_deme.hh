#pragma once

#include "climbchromosome.hh"
#include "deme.hh"
#include <cassert>

class TournamentDeme: public Deme
{
  virtual void compute_next_generation();


protected:

    virtual Chromosome* select_parent();

}
