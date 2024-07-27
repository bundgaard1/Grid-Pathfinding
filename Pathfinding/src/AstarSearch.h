#pragma once

#include "Grid.h"
#include "Pos.h"
#include "GridSearchBase.h"
#include <set>
#include <queue>
#include <map>
#include <tuple>

class AstarSearch : public BaseSearch {
   public:
    AstarSearch(Grid& grid) : BaseSearch(grid) {
        init();
    };
    void init() override;
    void search() override; 
    void reset() override; 

    std::vector<Pos> get_openSet() override;
    std::vector<Pos> get_closedSet()override ;
    std::vector<Pos> get_path() override;

   private:
    struct AstarNode {
       Pos pos;
       int fscore;
       int gscore;
    };

    std::vector<AstarNode> m_openSet;
    std::vector<Pos> m_closedSet;
    std::map<Pos, Pos> m_cameFrom;

	// Helper functions for A* search
    int calc_fscore(int g,Pos pos);
    int heuristic(Pos a, Pos b);
    AstarNode lowest_fscore();
    AstarNode node_at_pos(Pos pos);
    bool is_in_openSet(Pos pos);
    bool is_in_closedSet(Pos pos);
    void remove_from_openSet(Pos pos);
};
