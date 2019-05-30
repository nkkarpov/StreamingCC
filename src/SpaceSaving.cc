//
// Created by nk-karpov on 2019-05-30.
//

#include "streamingcc_include/SpaceSaving.h"

#include <cassert>

namespace streamingcc {

namespace integer {

void SpaceSavingInt::ProcessItem(const uint32_t item, const double weight) {
  assert(weight >= 0.);
  auto pred = [&](const counter &x) { return x.first == item; };
  auto ind = std::distance(counters_.begin(), std::find_if(counters_.begin(), counters_.end(), pred));
  auto min_value = !counters_.empty() ? counters_.back().second : 0.;
  if (ind == counters_.size()) {
    if (counters_.size() == capacity_) {
      counters_.emplace_back(counter(item, min_value + weight));
    } else {
      counters_.emplace_back(counter(item, weight));
    }
  } else {
    counters_[ind].second += weight;
  }
  std::sort(counters_.begin(),
            counters_.end(),
            [](const counter &a, const counter &b) { return a.second > b.second; });
  if (counters_.size() > capacity_) {
    counters_.pop_back();
  }
}

double SpaceSavingInt::GetEstimation(const uint32_t item) const {
  auto pred = [&](const counter &x) { return x.first == item; };
  auto it = std::find_if(counters_.begin(), counters_.end(), pred);
  auto min_value = !counters_.empty() ? counters_.back().second : 0;
  if (it != counters_.end()) {
    return it->second;
  } else {
    return min_value;
  }
}

} //namespace integer

} //namespace streamingcc