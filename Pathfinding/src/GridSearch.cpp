#include "GridSearch.h"

Search::Search(Grid& grid) : m_grid(grid) {
    init();
    return;
}

void Search::init() {
    m_openSet.push_back(m_grid.getStart());
    return;
}

void Search::search() {
    if (m_openSet.empty()) {
        return;
    }

    auto Current = std::move(m_openSet.back()); 
    m_openSet.erase(m_openSet.end()-1);
    

    std::cout << "Current: " << Current.x << ", " << Current.y << std::endl;
    Pos End = m_grid.getEnd();
    if (Current.x == End.x && Current.y == End.y) {
        return;
    }

    auto neighbors = m_grid.neighbors_for_cell(Current);

    for (auto neighbor : neighbors) {
        if (std::find(m_closedSet.begin(), m_closedSet.end(), neighbor) != m_closedSet.end()  
            || std::find(m_openSet.begin(), m_openSet.end(), neighbor) != m_openSet.end()) {
            continue;
        }
        m_openSet.push_back(neighbor);
    }   

    m_closedSet.push_back(Current);
}

void Search::reset() {
    return;
}


std::vector<Pos> Search::get_openSet()  {
    return m_openSet;
}

std::vector<Pos> Search::get_closedSet()  {
    return m_closedSet;
}