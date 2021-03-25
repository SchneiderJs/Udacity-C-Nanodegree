#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2 - DONE: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
    this->start_node = &m_Model.FindClosestNode(start_x, start_y);
    this->end_node = &m_Model.FindClosestNode(end_x, end_y);
}


// TODO 3 - DONE: Implement the CalculateHValue method.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*this->end_node);
}


// TODO 4 - DONE: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    // populate current_node.neighbors vector with all the neighbors
    current_node->FindNeighbors();

    for (RouteModel::Node* neighbor: current_node->neighbors){
        // for each node in current_node.neighbors, set the parent, the h_value, the g_value. 
        neighbor->parent  = current_node;
        neighbor->h_value = this->CalculateHValue(neighbor);
        neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);

        // add the neighbor to open_list 
        this->open_list.push_back(neighbor);

        // set the node's visited attribute to true
        neighbor->visited = true;
    }
}


// TODO 5 - DONE: Complete the NextNode method to sort the open list and return the next node.

bool RoutePlanner::CompareNodes(const RouteModel::Node *node_1, const RouteModel::Node *node_2) {
    float f1 = node_1->g_value + node_1->h_value;
    float f2 = node_2->g_value + node_2->h_value;

    return f1 > f2;
}

RouteModel::Node *RoutePlanner::NextNode() {
    // Sort the open_list according to the sum of the h value and g value.
    std::sort(this->open_list.begin(), this->open_list.end(), RoutePlanner::CompareNodes); 

    // Create a pointer to the node in the list with the lowest sum.
    RouteModel::Node* lowest_sum_node = open_list.back();

    // Remove that node from the open_list.
    open_list.pop_back();

    // Return the pointer.
    return lowest_sum_node;
}

// TODO 6 - DONE: Complete the ConstructFinalPath method to return the final path found from your A* search.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.
    while(current_node != this->start_node) {
        path_found.push_back(*current_node);
        distance += current_node->distance(*current_node->parent);
        current_node = current_node->parent;
    }
    path_found.push_back(*current_node);

    // reverse the order of the path
    std::reverse(path_found.begin(), path_found.end());
    
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;
}


// TODO 7 - DONE: Write the A* Search algorithm here.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here. 

    current_node = this->start_node;
    current_node->visited = true;

    // for each node
    while (current_node != this->end_node)
    {
        // Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
        this->AddNeighbors(current_node);

        // Use the NextNode() method to sort the open_list and return the next node.
        current_node = this->NextNode();
    }

    // Use the ConstructFinalPath method to return the final path that was found.
    // and store the final path in the m_Model.path attribute before the method exits
    m_Model.path = ConstructFinalPath(current_node);

}
