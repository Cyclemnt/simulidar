#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>

namespace Types {
    enum class CellState {
        Wall = 1,
        Free = 0,
        Unknown = -1
    };

    using Grid = std::vector<std::vector<CellState>>;

    enum class Direction { N, S, E, W };
}

#endif // TYPES_HPP
