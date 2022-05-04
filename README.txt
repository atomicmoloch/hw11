hw11
Adam Snelling
Kavi Wilson

To compile the program, use 'make tsp', and then run it with these three
arguments: cities filename, population, and a mutation rate between 0 and 1.
Example:
>> make tsp
>> ./tsp cities.tsv 1000 0.1

Here are some of the things we ran into while making the updated classes:

In ClimbChromosome, the new mutate() method is a fairly straightforward
algorithm, but with a lot of edge cases regarding the chosen gene being at the
end or the beginning of the chromosome. There is probably a more elegant
solution to this issue, but I believe my solution works, and I've tried to
comment it in such a way that you can follow the algorithm as it goes.

There were also some issues with the clone method that were solved when I
realized that Chromosome's constructors were private, not protected.

There are memory errors. I fixed some of them. I tried to fix the rest. It was a failure.
