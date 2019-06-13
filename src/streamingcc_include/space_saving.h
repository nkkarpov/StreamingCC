//
// Created by nk-karpov on 2019-05-30.
//

#ifndef STREAMINGCC_SPACE_SAVING_H
#define STREAMINGCC_SPACE_SAVING_H

#include "../streamingcc_include/streaming_algorithm.h"

namespace streamingcc {

namespace integer {

class SpaceSavingInt : public StreamingAlgorithmWeightedInt {
 public:
  explicit SpaceSavingInt(const size_t capacity)
      : capacity_(capacity) {}
  void ProcessItem(const uint32_t item, const double weight) override;
  double GetEstimation(const uint32_t item) const;
  ~SpaceSavingInt() override = default;
 private:
  using counter = std::pair<uint32_t, double>;
  std::vector<counter> counters_;
  size_t capacity_;
};

}  // namespace integer

}  // namespace streamingcc

#endif //STREAMINGCC_SPACE_SAVING_H
