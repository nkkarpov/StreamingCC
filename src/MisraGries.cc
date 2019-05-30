//
// Created by Nikolai Karpov on 2019-02-24.
//
#include "streamingcc_include/MisraGries.h"

namespace streamingcc {

namespace integer {

void MisraGriesInt::ProcessItem(const uint32_t item, const double weight) {
  assert(weight >= 0.);
  auto pred = [&](const counter &x) { return x.first == item; };
  auto ind = std::distance(counters_.begin(), std::find_if(counters_.begin(), counters_.end(), pred));
  if (ind == counters_.size()) {
    counters_.emplace_back(counter(item, weight));
  } else {
    counters_[ind].second += weight;
  }
  std::sort(counters_.begin(),
            counters_.end(),
            [](const counter &a, const counter &b) { return a.second > b.second; });
  if (counters_.size() > capacity_) {
    auto val = counters_.back().second;
    counters_.pop_back();
    for (auto &x : counters_) {
      x.second -= val;
    }
  }
}

double MisraGriesInt::GetEstimation(const uint32_t item) const {
  auto pred = [&](const counter &x) { return x.first == item; };
  auto it = std::find_if(counters_.begin(), counters_.end(), pred);
  if (it != counters_.end()) {
    return it->second;
  } else {
    return 0.;
  }
}

} //namespace integer

} //namespace streamingcc

