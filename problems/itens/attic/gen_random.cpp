#include "testlib.h"
#include <cassert>
#include <cstdlib>
#include <queue>
#include <set>

using Position = std::pair<int, int>;

Position RandomPosition(const int n, const int m) {
  return {rnd.next(n), rnd.next(m)};
}

std::set<Position>
GenerateSeeds(const int n, const int m, const int num_seeds,
              std::set<Position> *forbiden_positions = nullptr) {
  std::set<Position> seeds;
  while (seeds.size() < num_seeds) {
    const Position candidate = RandomPosition(n, m);
    if (!seeds.count(candidate) && (forbiden_positions == nullptr ||
                                    !forbiden_positions->count(candidate))) {
      seeds.insert(candidate);
    }
  }
  return seeds;
}

Position RandomFreePosition(const std::vector<std::vector<char>> &grid) {
  std::vector<Position> free_positions;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == '.') {
        free_positions.push_back({i, j});
      }
    }
  }
  return rnd.wany(free_positions, 0);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  const int n = std::atoi(argv[2]);
  const int m = std::atoi(argv[3]);
  assert(n > 0);
  assert(m > 0);

  // This generator will try to create an instance for which the answer will
  // be close to target_prob.
  const double target_prob = std::atof(argv[4]);
  assert(target_prob >= 0. && target_prob <= 1.);

  // Grid cells will be marked as free/occupied according to the closest seed.
  //
  // To get more(less) free cells, increase(decrease) 
  // num_free_seeds/num_occupied seeds.
  //
  // Higher values of num_*_seeds tend to produce more complicated grids.
  const int num_free_seeds = std::atoi(argv[5]);
  const int num_occupied_seeds = std::atoi(argv[6]);
  assert(num_free_seeds > 0); // The starting position needs to be free.
  assert(num_occupied_seeds >= 0);

  // Leave enough room so that the we can use random sampling without
  // replacement to generate the seeds quickly and easily.
  assert(3 * (num_free_seeds + num_occupied_seeds) <= 2 * n * m);

  std::set<Position> free_seeds = GenerateSeeds(n, m, num_free_seeds);
  std::set<Position> occupied_seeds =
      GenerateSeeds(n, m, num_occupied_seeds, &free_seeds);

  // Initially, all grid positions have an unknown state.
  std::vector<std::vector<char>> grid(n, std::vector<char>(m, '?'));

  // BFS from the seeds, copying the states.
  std::queue<Position> positions_queue;
  for (const Position seed : free_seeds) {
    grid[seed.first][seed.second] = '.';
    positions_queue.push(seed);
  }
  for (const Position seed : occupied_seeds) {
    grid[seed.first][seed.second] = '#';
    positions_queue.push(seed);
  }
  while (!positions_queue.empty()) {
    Position current = positions_queue.front();
    positions_queue.pop();

    const std::vector<Position> deltas = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const Position &delta : deltas) {
      const Position next = {current.first + delta.first,
                             current.second + delta.second};
      if (next.first < 0 || next.first >= n || next.second < 0 ||
          next.second >= m || grid[next.first][next.second] != '?') {
        continue;
      }

      grid[next.first][next.second] = grid[current.first][current.second];
      positions_queue.push(next);
    }
  }

  const Position starting_position = RandomFreePosition(grid);

  // Do another BFS from the starting position to figure out the T that will
  // lead to an answer close to the target_prob, if possible.
  int num_free = 0;
  for (const auto &row : grid) {
    for (const char cell : row) {
      if (cell == '.') {
        num_free++;
      }
    }
  }
  const int target_free = num_free * target_prob;
  std::vector<std::vector<int>> dist(n, std::vector<int>(m, n * m));
  dist[starting_position.first][starting_position.second] = 0;
  positions_queue.push(starting_position);
  int num_reached = 1;
  int T = 1;
  while (!positions_queue.empty()) {
    Position current = positions_queue.front();
    positions_queue.pop();
    num_reached++;
    T = std::max(1, dist[current.first][current.second]);
    if (num_reached >= target_free) {
      break;
    }

    const std::vector<Position> deltas = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const Position &delta : deltas) {
      const Position next = {current.first + delta.first,
                             current.second + delta.second};
      if (next.first < 0 || next.first >= n || next.second < 0 ||
          next.second >= m || grid[next.first][next.second] == '#' ||
          dist[next.first][next.second] <=
              dist[current.first][current.second] + 1) {
        continue;
      }

      dist[next.first][next.second] = dist[current.first][current.second] + 1;
      positions_queue.push(next);
    }
  }

  // Finally, output the generate instance.
  std::cout << n << ' ' << m << ' ' << T << ' ' << (starting_position.first + 1)
            << ' ' << (starting_position.second + 1) << std::endl;
  for (const auto &row : grid) {
    for (const char cell : row) {
      assert(cell == '.' || cell == '#');
      std::cout << cell;
    }
    std::cout << std::endl;
  }
}
