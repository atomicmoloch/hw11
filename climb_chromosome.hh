

#pragma once

#include "chromosome.hh"
#include <cassert>

class ClimbChromosome: public Chromosome {
  ClimbChromosome(const ClimbChromosome&) = default;
  ClimbChromosome(ClimbChromosome&&) = default;
public:
  virtual void mutate() override;

  virtual Chromosome* clone() const override {
    return new ClimbChromosome(*this);
  }
};
