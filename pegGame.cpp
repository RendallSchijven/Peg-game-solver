// pegGame.cpp

#include <queue>
#include <string>
#include <algorithm>
#include <iostream>
#include "pegGame.h"

typename std::vector<Vertex>::const_iterator Graph::cbegin(Vertex v) const
{
    adjacents.clear();

    for (int r=0; r<5; r++) {
        for (int c=0; c<5; c++) {
            if (v[r][c] == 2) {
                if (v[r][c - 2] == 1 && v[r][c - 1] == 2) adjacents.push_back(doMove(v,Move::l,r,c));
                if (v[r][c + 2] == 1 && v[r][c + 1] == 2) adjacents.push_back(doMove(v,Move::r,r,c));
                if (v[r-2][c + 2] == 1 && v[r-1][c + 1] == 2) adjacents.push_back(doMove(v,Move::ur,r,c));
                if (v[r-2][c] == 1 && v[r-1][c] == 2) adjacents.push_back(doMove(v,Move::ul,r,c));
                if (v[r+2][c] == 1 && v[r+1][c] == 2) adjacents.push_back(doMove(v,Move::dr,r,c));
                if (v[r+2][c - 2] == 1 && v[r + 1][c - 1] == 2) adjacents.push_back(doMove(v,Move::dl,r,c));
            }
        }
    }
    return adjacents.cbegin();
}

typename std::vector<Vertex>::const_iterator Graph::cend() const
{
    return adjacents.cend();
}

Vertex doMove(const Vertex &v, const Move &m, int r, int c)
{
    Vertex n = v;

    switch(m) {
        case Move::l:
            std::swap(n[r][c], n[r][c - 2]);
            n[r][c - 1] = 1;
            break;
        case Move::r:
            std::swap(n[r][c], n[r][c + 2]);
            n[r][c + 1] = 1;
            break;
        case Move::ur:
            std::swap(n[r][c], n[r - 2][c + 2]);
            n[r-1][c + 1] = 1;
            break;
        case Move::ul:
            std::swap(n[r][c], n[r - 2][c]);
            n[r-1][c] = 1;
            break;
        case Move::dr:
            std::swap(n[r][c], n[r + 2][c]);
            n[r+1][c] = 1;
            break;
        case Move::dl:
            std::swap(n[r][c], n[r + 2][c - 2]);
            n[r + 1][c - 1] = 1;
            break;
    }
    return n;
}
/*Vertex doMove(const Vertex &v, const Move &m, int row, int column)
{
    bool done=false;
    Vertex n = v;

    for (int r=0; r<5 && !done; r++) {
        for (int c=0; c<5 && !done; c++) {
            if (v[r][c] == 0) {
                switch(m) {
                    case Move::l:
                        std::swap(n[r][c], n[r][c - 2]);
                        n[r][c - 1] = 1;
                        done = true;
                        break;
                    case Move::r:
                        std::swap(n[r][c], n[r][c + 2]);
                        n[r][c + 1] = 1;
                        done = true;
                        break;
                    case Move::ur:
                        std::swap(n[r][c], n[r - 2][c + 2]);
                        n[r-1][c + 1] = 1;
                        done = true;
                        break;
                    case Move::ul:
                        std::swap(n[r][c], n[r - 2][c]);
                        n[r-1][c] = 1;
                        done = true;
                        break;
                    case Move::dr:
                        std::swap(n[r][c], n[r + 2][c]);
                        n[r+1][c] = 1;
                        done = true;
                        break;
                    case Move::dl:
                        std::swap(n[r][c], n[r + 2][c - 2]);
                        n[r + 1][c - 1] = 1;
                        done = true;
                        break;
                }
            }
        }
    }
    return n;
}*/

std::ostream &operator<<(std::ostream &os, const Vertex &state)
{
    for (int r=0; r<5; r++) {
        for (int c=0; c<5; c++) {
            if (state[r][c] != 0) {
                os << state[r][c];
            } else {
                os << " ";
            }
        }
        os << std::endl;
    }
    return os;
}

Path dfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest)
{
    std::stack<Path> queue;
    std::set<Vertex> visited;
    Path path;

    queue.push(path);
    while (!queue.empty()) {
        path = queue.top();
        queue.pop();

        Vertex last;
        if (path.size() == 0) {
            last = start;
        } else {
            last = path.back();
        }
        if (goalTest(last))
            return path; // path is a vector of Vertices

        if (visited.find(last) == visited.end()) {
            visited.insert(last);
            for (auto it = graph.cbegin(last); it != graph.cend(); it++) { // extend path with new Vertex
                Path n = path;
                n.push_back(*it);
                queue.push(n);
            }
        }
    }
    return Path();
}

Path bfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest)
{
    std::queue<Path> queue;
    std::set<Vertex> visited;
    Path path;

    queue.push(path);
    while (!queue.empty()) {
        path = queue.front();
        queue.pop();

        Vertex last;
        if (path.size() == 0) {
            last = start;
        } else {
            last = path.back();
        }
        if (goalTest(last))
            return path; // path is a vector of Vertices

        for (auto it = graph.cbegin(last); it != graph.cend(); it++) { // extend path with new Vertex
            Path n = path;
            if (visited.find(*it) == visited.end()) {
                visited.insert(*it);
                n.push_back(*it);
                queue.push(n);
            }
        }

    }
    return Path(); // return empty path
}

int main()
{
    Graph graph;

    Vertex start = {{
                            {{0,0,0,0,1}},
                            {{0,0,0,2,2}},
                            {{0,0,2,2,2}},
                            {{0,2,2,2,2}},
                            {{2,2,2,2,2}}
                    }};

    Vertex goal = {{
                           {{0,0,0,0,1}},
                           {{0,0,0,1,1}},
                           {{0,0,1,1,1}},
                           {{0,1,1,2,1}},
                           {{1,1,1,1,1}}
                   }};

    Path path = bfs(graph, start, [&](Vertex v) { return (v == goal); });

    std::cout << start << std::endl;
    for (auto it = path.cbegin(); it != path.cend(); it++)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}

