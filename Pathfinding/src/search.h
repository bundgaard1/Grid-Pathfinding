
// void Grid::search() {
//     // if (m_paused)
//     //	return;

//     if (m_openSet.size() > 0 && !m_done) {
//         // find next best
//         int winner = 0;
//         float bestFScore = INT32_MAX;
//         // std::cout << m_openSet.size() << " ";
//         for (int i = 0; i < m_openSet.size(); i++) {
//             float currFScore = m_openSet.at(i).get()->m_f;
//             if (currFScore <= bestFScore) {
//                 winner = i;
//                 bestFScore = currFScore;
//             }
//         }
//         // std::cout << bestFScore << std::endl;

//         std::shared_ptr<Cell> current(m_openSet.at(winner));

//         // Check for end
//         if (current == m_end) {
//             std::cout << "DONE!" << std::endl;
//             // make path
//             std::shared_ptr<Cell> temp = current;
//             m_done = true;
//             m_win = true;
//             while (temp != m_start) {
//                 if (temp->m_state != s_Start && temp->m_state != s_End) temp->m_state = s_Path;
//                 m_path.push_back(temp);
//                 temp = temp->m_previous;
//             }

//             return;
//         }

//         // move to closed set from open set
//         m_closedSet.push_back(current);
//         if (current->m_state != s_Start) current->m_state = s_Closed;

//         m_openSet.erase(m_openSet.begin() + winner);

//         std::vector<std::shared_ptr<Cell>> neighbors = neighbors_for_cell(current);

//         bool neighbor_added = false;

//         // Go through every neighbor
//         for (int i = 0; i < neighbors.size(); i++) {
//             std::shared_ptr<Cell> neighbor = neighbors.at(i);
//             if (neighbor->m_state == s_Closed || neighbor->m_state == s_Wall) {
//                 continue;
//             } else {
//                 float tempG = current->m_g + heuristic(*current, *neighbor);
//                 bool newPath = false;
//                 if (neighbor->m_state == s_Open) {
//                     if (tempG < neighbor->m_g) {
//                         neighbor->m_g = tempG;
//                         newPath = true;
//                     }
//                 } else {
//                     neighbor->m_g = tempG;

//                     neighbor_added = true;

//                     m_openSet.push_back(neighbor);

//                     if (neighbor->m_state != s_Start && neighbor->m_state != s_End) neighbor->m_state = s_Open;

//                     newPath = true;
//                 }

//                 if (newPath) {
//                     neighbor->m_h = heuristic(*m_end.get(), *neighbor.get());
//                     neighbor->m_f = neighbor->m_h + neighbor->m_g;
//                     neighbor->m_previous = current;
//                 }
//             }
//         }

//     } else {
//         if (!m_done) {
//             std::cout << "No Solution!" << std::endl;
//             m_done = true;
//         } else {
//             return;
//         }
//     }

//     return;
// }

//     std::vector<pos> m_openSet;
//    std::vector<pos> m_closedSet;