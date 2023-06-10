#ifndef HYBRID_PERIOD_H
#define HYBRID_PERIOD_H


#include <vector>


class HybridPeriod
{
public:

   HybridPeriod(const std::vector<double>& previous,
                const std::vector<double>& after,
                unsigned int position);

   ~HybridPeriod();

   std::vector<double> frames_;
   unsigned int position_;
   double difference_;
   double weight_;
};























#endif // HYBRID_PERIOD_H
