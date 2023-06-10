#include "HybridPeriod.h"



HybridPeriod::HybridPeriod(const std::vector<double>& previous,
                           const std::vector<double>& after,
                           unsigned int position)
{
   position_ = position;

   difference_ = 0;
   for(unsigned int i = 0; i<previous.size() || i<after.size(); i++)
   {
      if(i < previous.size() && i < after.size())
      {
         double diff = previous[i] - after[i];
         if(diff < 0) diff *= -1;
         difference_ += diff;

         frames_.push_back( (previous[i] + after[i]) / 2);
      }
      else if(i < previous.size())
      {
         if(previous[i] > 0) difference_ += previous[i];
         else difference_ += previous[i] * -1;
      }
      else if(i < after.size())
      {
         if(after[i] > 0) difference_ += after[i];
         else difference_ += after[i] * -1;
      }
   }

   const std::vector<double>& longer = (previous.size() > after.size()) ? previous : after;

   if(frames_.size() < 3) return;

   while(frames_[frames_.size()-1] > 0
      && frames_[frames_.size()-1] > longer[longer.size()-1]
      && frames_.size() < longer.size())
   {
      double value = frames_[frames_.size()-1];
      double diff = frames_[frames_.size()-1] - frames_[frames_.size()-2];
      double longerDiff = longer[frames_.size()-1] - longer[frames_.size()-2];
      if(longerDiff < 0) longerDiff *= -1;
      diff = (diff + longerDiff) / 2;
      if(diff < 0) diff *= -1;
      if(value < 0) value = 0;
      frames_.push_back(value);
   }

   weight_ = difference_;
}


HybridPeriod::~HybridPeriod()
{

}
