#pragma once

#include "climb_chromosome.hh"
#include "deme.hh"
#include <cassert>

class TournamentDeme: public Deme
{
public:
  TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate);
  ~TournamentDeme();
  void compute_next_generation();
  int get_size();

protected:
    Chromosome* select_parent();
};
