#pragma once

namespace tmz
{
namespace Lambdas
{
// Extract the keys of the map.
inline auto extractKey = [](const auto& pair) {
    return pair.first;
};

} // namespace Lambdas
} // namespace tmz
