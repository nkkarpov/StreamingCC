//
// Created by nk-karpov on 2019-05-30.
//

#ifndef STREAMINGCC_MISRA_GRIES_H
#define STREAMINGCC_MISRA_GRIES_H

#include "../streamingcc_include/streaming_algorithm.h"

#include <algorithm>
#include <vector>

namespace streamingcc {

namespace integer {

class MisraGriesInt : public StreamingAlgorithmWeightedInt {
 public:
  explicit MisraGriesInt(const size_t capacity)
      : capacity_(capacity) {}
  void ProcessItem(const uint32_t item, const double weight) override;
  double GetEstimation(const uint32_t item) const;
  ~MisraGriesInt() override = default;
 private:
  using counter = std::pair<uint32_t, double>;
  std::vector<counter> counters_;
  size_t capacity_;
};

}  // namespace integer

}  // namespace streamingcc

#endif //STREAMINGCC_MISRA_GRIES_H
