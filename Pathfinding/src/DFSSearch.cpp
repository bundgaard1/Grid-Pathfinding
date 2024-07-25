#include "DFSSearch.h"

void DFSSearch::init() {
    m_openSet.push_back(m_grid.getStart());
    return;
}

void DFSSearch::search() {
    if (m_openSet.empty() || is_done()) {
        return;
    }

    auto Current = std::move(m_openSet.back()); 
    m_openSet.erase(m_openSet.end()-1);
        
    Pos End = m_grid.getEnd(); 
    if (Current.x == End.x && Current.y == End.y) {
        m_done = true;
        return;
    }

    auto neighbors = m_grid.neighbors_for_cell(Current);

    for (auto neighbor : neighbors) {
        if (std::find(m_closedSet.begin(), m_closedSet.end(), neighbor) != m_closedSet.end()  
            || std::find(m_openSet.begin(), m_openSet.end(), neighbor) != m_openSet.end()) {
            continue;
        }
        m_openSet.push_back(neighbor);
        m_cameFrom[neighbor] = Current;
    }   

    m_closedSet.push_back(Current);
}

void DFSSearch::reset() {
    m_openSet.clear();
    m_closedSet.clear();

    init();
    return;
}

bool DFSSearch::is_done() {
    return m_done;
}


std::vector<Pos> DFSSearch::get_openSet()  {
    return m_openSet;
}

std::vector<Pos> DFSSearch::get_closedSet()  {
    return m_closedSet;
}


std::vector<Pos> DFSSearch::get_path() {
    std::vector<Pos> path;
    Pos current = m_grid.getEnd();
    path.push_back(current);
    while (current != m_grid.getStart()) {
        current = m_cameFrom[current];
        path.push_back(current);
    }
    return path;
}