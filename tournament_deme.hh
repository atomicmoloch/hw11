#pragma once

#include "climb_chromosome.hh"
#include "deme.hh"
#include <cassert>

class TournamentDeme: public Deme
{
public:
  virtual TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate);
  virtual ~TournamentDeme() = default;
  void compute_next_generation();

protected:
    Chromosome* select_parent();

};
