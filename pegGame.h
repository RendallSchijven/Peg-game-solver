// pegGame.h

#ifndef _PEGGAME_H
#define _PEGGAME_H

#include <array>
#include <vector>
#include <iostream>
#include <functional>
#include <stack>
#include <set>

enum class Move { l, r, ur, ul, dr, dl };
using State = std::array<std::array<int,5>,5>;

using Vertex = State;
using Path = std::vector<Vertex>;

class Graph
{
public:
    typename std::vector<Vertex>::const_iterator cbegin(Vertex v) const;
    typename std::vector<Vertex>::const_iterator cend() const;
private:
    mutable std::vector<Vertex> adjacents;
};

std::ostream &operator<<(std::ostream &os, const Vertex &state);

Vertex doMove(const Vertex &v, const Move &m, int r, int c);
Path dfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest);
Path bfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest);
bool finished(Vertex &v);
Vertex updateStart(Vertex &v);

#endif // _PEGGAME_H

