#include "AstarSearch.h"

void AstarSearch::init() {
    m_openSet.push_back({r_grid.getStart(), 0});
    return;
}

void AstarSearch::search() {
    if (m_openSet.empty() || is_done()) {
        return;
    }
    // 1. Find lowest fscore in openSet
    AstarNode Current = lowest_fscore();

    // 2. Check if we are at the end
    if (Current.pos == r_grid.getEnd()) {
        m_done = true;
        m_closedSet.push_back(Current.pos);
        return;
    }

    // 3. Add neighbors to open set

    auto neighbors = r_grid.neighbors_for_cell(Current.pos);

    for (auto neighbor : neighbors) {
        if (is_in_closedSet(neighbor)  ) {
            continue;
        }

        int tentative_gScore = Current.gscore + heuristic(Current.pos, neighbor);

        // 4. Check if neighbor is in open set, if so check if we have a better path
        if (is_in_openSet(neighbor)) {
            AstarNode neighborNode = node_at_pos(neighbor);
            if (tentative_gScore >= neighborNode.gscore) {
                continue;
            } else {
                remove_from_openSet(neighbor);
                
            }
        }

        m_openSet.push_back({neighbor, 
                             calc_fscore(tentative_gScore,neighbor),
                             tentative_gScore});
        m_cameFrom[neighbor] = Current.pos;
    }   

    // 5. Move current to closed set

    remove_from_openSet(Current.pos);
    m_closedSet.push_back(Current.pos);

    return;
}

void AstarSearch::reset() {
    m_openSet.clear();
    m_closedSet.clear();
    m_cameFrom.clear();
    m_done = false;

    init();
    return;
}

std::vector<Pos> AstarSearch::get_openSet()  {
    std::vector<Pos> openSet;
    for (auto node : m_openSet) {
        openSet.push_back(node.pos);
    }

    return openSet;
}

std::vector<Pos> AstarSearch::get_closedSet()  {
    return m_closedSet;
}


std::vector<Pos> AstarSearch::get_path() {
    std::vector<Pos> path;
    Pos current = r_grid.getEnd();
    path.push_back(current);
    while (current != r_grid.getStart()) {
        current = m_cameFrom[current];
        path.push_back(current);
    }
    return path;
}

int AstarSearch::calc_fscore( int g, Pos pos) {
    return heuristic(r_grid.getEnd(), pos) + g;
}

int AstarSearch::heuristic(Pos a, Pos b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

AstarSearch::AstarNode AstarSearch::lowest_fscore() {
    AstarNode winner  = m_openSet.at(0);
    for (int i = 0; i < m_openSet.size(); i++) {
        if (m_openSet.at(i).fscore <= winner.fscore) {
            winner = m_openSet.at(i);
        }
    }

    return winner;
}

AstarSearch::AstarNode AstarSearch::node_at_pos(Pos pos) {
    for (auto node : m_openSet) {
        if (node.pos == pos) {
            return node;
        }
    }
    return m_openSet.at(0);
}

bool AstarSearch::is_in_openSet(Pos pos) {
    for (auto node : m_openSet) {
        if (node.pos == pos) {
            return true;
        }
    }
    return false;
}

bool AstarSearch::is_in_closedSet(Pos pos) {
    return std::find(m_closedSet.begin(), m_closedSet.end(), pos) != m_closedSet.end();
}

void AstarSearch::remove_from_openSet(Pos pos) {
    for (int i = 0; i < m_openSet.size(); i++) {
        if (m_openSet.at(i).pos == pos) {
            m_openSet.erase(m_openSet.begin() + i);
            return;
        }
    }
    return;
}