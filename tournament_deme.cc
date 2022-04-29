#include "tournament_deme.hh"

TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
{
    this.Deme(cities_ptr, pop_size, mut_rate);
}

void TournamentDeme::compute_next_generation()
{
    std::vector<Chromosome*> newchroms;
    while (newchroms.size() < pop_.size())
    {
        auto chrom1 = select_parent();
        auto chrom2 = select_parent();
//        std::cout << "Parents selected.\n";
        if (rand() < mut_rate_)
        {
            chrom1->mutate();
        }
        if (rand() < mut_rate_)
        {
            chrom2->mutate();
        }
        auto tempchroms = chrom1->recombine(chrom2);
        newchroms.push_back(tempchroms.first);
        newchroms.push_back(tempchroms.second);
    }

    if (newchroms.size() > pop_.size())
    {
        newchroms.pop_back();
    }
    pop_ = newchroms;
}

Chromosome* TournamentDeme::select_parent()
{
    Chromosome* retval;

    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<> between(0, pop_.size() - 1);

    int indx = between(gen);
    int ind2 = between(gen);
    while (indx == ind2)
    {
        indx = between(gen);
    }

    if (pop_[indx]->get_fitness() > pop_[ind2]->get_fitness()) //sets retval depending on which is better
    {
        retval = pop_[indx];
    }
    else
    {
        retval = pop_[ind2];
    }

    if (indx > ind2) //erases both from pop_
    {
        pop_.erase(pop_.begin() + indx);
        pop_.erase(pop_.begin() + ind2);
    }
    else
    {
        pop_.erase(pop_.begin() + ind2);
        pop_.erase(pop_.begin() + indx);

    }
    return retval; //returns better chromosome
}
