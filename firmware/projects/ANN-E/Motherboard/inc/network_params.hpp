#pragma once

constexpr size_t kLayerBoard0NumInputs = 12;
constexpr size_t kLayerBoard0NumOutputs = 12;

constexpr size_t kLayerBoard1NumInputs = kLayerBoard0NumOutputs;
constexpr size_t kLayerBoard1NumOutputs = 10;

constexpr size_t kNumNetworkOutputs = kLayerBoard1NumOutputs;
constexpr size_t kNumNetworkInputs = kLayerBoard0NumInputs;
constexpr size_t kNumLayerBoards = 2;
