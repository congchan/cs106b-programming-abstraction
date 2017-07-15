/* Assignment 7: Trailblazer
 * This program displays various road maps and allows users to find the shortest path between any two nodes.
 * If you click on any two nodes in the world, the program will find a path from the starting position to the ending position. As it does so, it will color the vertexes green and yellow based on the colors assigned to them by the algorithm. Once the path is found, the program will highlight it and display information about the path cost in the console. The user can select one of four path-searching algorithms in the top menu:
 1.Breadth-first search (BFS)
 2.Dijkstra's algorithm
 3.A* search
 4.Alternative Route

 @Author: Cong Chen
 @Version:2017/07
 */

#include "Trailblazer.h"
#include "queue.h"
#include "pqueue.h"
#include "set.h"
#include "map.h"
using namespace std;

static const double SUFFICIENT_DIFFERENCE = 0.2;
/* Define a function that could perform both dijkstrasAlgorithm, aStar and alternativeRoute
 * if dijkstrasAlgorithm, then astar is FALSE; if aStar, then astar is TRUE;
 */

Path generalFind(const RoadGraph& graph, RoadNode* start, RoadNode* end, bool astar = false, RoadEdge* ignore = NULL) {
    int HeuristicIndex=0;
    if (astar) HeuristicIndex=1;
    start->setColor(Color::YELLOW);
    Vector<RoadNode*> path = Vector<RoadNode*>();
    if (start==end) {
        path.add(start);
        return path;
    }
    // The cost of each vertex is the priority
    PriorityQueue<RoadNode*> frontier;
    frontier.enqueue(start,0);
    // keep track of nodes that have already been visited.
    Map<RoadNode*,RoadNode*> came_from = Map<RoadNode*,RoadNode*>();
    came_from.put(start,NULL);
    // keep track of the cost to reach this vertext
    Map<RoadNode*,double> cost_so_far = Map<RoadNode*,double>();
    cost_so_far.put(start,0);
    while(!frontier.isEmpty()) {
        auto visiting = frontier.dequeue();
        visiting->setColor(Color::GREEN);
        if (visiting == end) break;
        Set<RoadNode*> neighbors = graph.neighborsOf(visiting);
        // Ignores the specific edge
        if (ignore!=NULL) {
            if (ignore->from()==visiting) neighbors.remove(ignore->to());
        }

        for(auto& next : neighbors) {
            RoadEdge* between = graph.edgeBetween(visiting,next);
            double Heuristic = graph.crowFlyDistanceBetween(next,end)/graph.maxRoadSpeed();
            double new_cost = cost_so_far[visiting]+ between->cost();
            if (!cost_so_far.containsKey(next) || cost_so_far[next]>new_cost){
                cost_so_far.put(next,new_cost);
                frontier.enqueue(next,new_cost+Heuristic*HeuristicIndex);
                next->setColor(Color::YELLOW);
                came_from.put(next,visiting);
            }
        }
    }

    // Reconstruct paths, if no path found, came_from do not contains key[end]
    auto visiting = end;
    if (came_from.containsKey(visiting)) {
        while(true){
            path.insert(0,visiting);
            if (visiting == start) break;
            visiting = came_from[visiting];
        }
    }
    return path;
}




/* Path is a typedef of a Vector<RoadNode*>. The path returned should be a list of all vertexes along that path,
 * with the starting vertex first (index 0 of the vector) and the ending vertex last.
 * If no path is found, return an empty path.
 * If the start and end vertexes are the same, return a one-element vector containing only that vertex.  */
Path breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    start->setColor(Color::YELLOW);
    Vector<RoadNode*> path = Vector<RoadNode*>();
    if (start==end) {
        path.add(start);
        return path;
    }
    Queue<RoadNode*> frontier = Queue<RoadNode*>();
    frontier.enqueue(start);

    // keep track of nodes that have already been visited.
    Map<RoadNode*,RoadNode*> came_from = Map<RoadNode*,RoadNode*>();
    came_from.put(start,NULL);

    while(!frontier.isEmpty()) {
        auto visiting = frontier.dequeue();
        visiting->setColor(Color::GREEN);
        if (visiting == end) break;
        for(auto& next : graph.neighborsOf(visiting)) {
            if (!came_from.containsKey(next)){
                frontier.add(next);
                next->setColor(Color::YELLOW);
                came_from.put(next,visiting);
            }
        }
    }

    // Reconstruct paths, if no path found, came_from do not contains key[end]
    auto visiting = end;
    if (came_from.containsKey(visiting)) {
        while(true){
            path.insert(0,visiting);
            if (visiting == start) break;
            visiting = came_from[visiting];
        }
    }
    return path;

}

/* Dijkstra’s algorithm proceeds in stages. At each stage, while there are still vertices waiting to be known:
 * Selects a vertex v, which has the smallest dv among all the unknown vertices, and declares v as known stage.
 * For each of v's neighbors, w, if the new path's cost from v to w is better than previous dw, dw will be updated.
 * But w will not be marked as known, unless at next while-loop stage, dw happens to be the smalles. */
Path dijkstrasAlgorithm(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    return generalFind(graph, start, end);
//    start->setColor(Color::YELLOW);
//    Vector<RoadNode*> path = Vector<RoadNode*>();
//    if (start==end) {
//        path.add(start);
//        return path;
//    }
//    // The cost of each vertex is the priority
//    PriorityQueue<RoadNode*> frontier;
//    frontier.enqueue(start,0);
//    // keep track of nodes that have already been visited.
//    Map<RoadNode*,RoadNode*> came_from = Map<RoadNode*,RoadNode*>();
//    came_from.put(start,NULL);
//    // keep track of the cost to reach this vertext
//    Map<RoadNode*,double> cost_so_far = Map<RoadNode*,double>();
//    cost_so_far.put(start,0);
//    while(!frontier.isEmpty()) {
//        auto visiting = frontier.dequeue();
//        visiting->setColor(Color::GREEN);
//        if (visiting == end) break;
//        for(auto& next : graph.neighborsOf(visiting)) {
//            RoadEdge* between = graph.edgeBetween(visiting,next);
//            double new_cost = cost_so_far[visiting]+ between->cost();
//            if (!cost_so_far.containsKey(next) || cost_so_far[next]>new_cost){
//                cost_so_far.put(next,new_cost);
//                frontier.enqueue(next,new_cost);
//                next->setColor(Color::YELLOW);
//                came_from.put(next,visiting);
//            }
//        }
//    }

//    // Reconstruct paths, if no path found, came_from do not contains key[end]
//    auto visiting = end;
//    if (came_from.containsKey(visiting)) {
//        while(true){
//            path.insert(0,visiting);
//            if (visiting == start) break;
//            visiting = came_from[visiting];
//        }
//    }
//    return path;

}

Path aStar(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    return generalFind(graph, start, end, true);
//    start->setColor(Color::YELLOW);
//    Vector<RoadNode*> path = Vector<RoadNode*>();
//    if (start==end) {
//        path.add(start);
//        return path;
//    }
//    // The cost of each vertex is the priority
//    PriorityQueue<RoadNode*> frontier;
//    frontier.enqueue(start,0);
//    // keep track of nodes that have already been visited.
//    Map<RoadNode*,RoadNode*> came_from = Map<RoadNode*,RoadNode*>();
//    came_from.put(start,NULL);
//    // keep track of the cost to reach this vertext
//    Map<RoadNode*,double> cost_so_far = Map<RoadNode*,double>();
//    cost_so_far.put(start,0);
//    while(!frontier.isEmpty()) {
//        auto visiting = frontier.dequeue();
//        visiting->setColor(Color::GREEN);
//        if (visiting == end) break;
//        for(auto& next : graph.neighborsOf(visiting)) {
//            RoadEdge* between = graph.edgeBetween(visiting,next);
//            double Heuristic = graph.crowFlyDistanceBetween(next,end)/graph.maxRoadSpeed();
//            double new_cost = cost_so_far[visiting]+ between->cost();
//            if (!cost_so_far.containsKey(next) || cost_so_far[next]>new_cost){
//                cost_so_far.put(next,new_cost);
//                frontier.enqueue(next,new_cost+Heuristic);
//                next->setColor(Color::YELLOW);
//                came_from.put(next,visiting);
//            }
//        }
//    }

//    // Reconstruct paths, if no path found, came_from do not contains key[end]
//    auto visiting = end;
//    if (came_from.containsKey(visiting)) {
//        while(true){
//            path.insert(0,visiting);
//            if (visiting == start) break;
//            visiting = came_from[visiting];
//        }
//    }
//    return path;
}

Path alternativeRoute(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    Path best = generalFind(graph, start, end, true);
    Set<RoadNode*> best_RoadNode;
    for (auto & vertex : best) {
        best_RoadNode.add(vertex);
    }

    Path alternate = Vector<RoadNode*>();
    double minCost = NULL;
    for(int i=0;i<best.size()-1;i++){

        if (best[i]!=end) {
            RoadEdge* ignore = graph.edgeBetween(best[i], best[i+1]);
            Path new_alternate = generalFind(graph, start, end, true, ignore);
            Set<RoadNode*> new_alternate_RoadNode;
            new_alternate_RoadNode.add(start);
            double new_alternate_cost = NULL;
            for (int j=0;j<new_alternate.size()-1;j++){
                new_alternate_RoadNode.add(new_alternate[j+1]);
                RoadEdge* edge = graph.edgeBetween(new_alternate[j], new_alternate[j+1]);
                new_alternate_cost += edge->cost();
            }

            double difference = 0;
            for (auto & vertex : new_alternate) {
                if (!best_RoadNode.contains(vertex)) difference++;
            }
            difference = difference/best.size();

            if (difference>SUFFICIENT_DIFFERENCE && ( minCost == NULL || minCost > new_alternate_cost) ){
                alternate = new_alternate;
                minCost = new_alternate_cost;
            }
        }
    }
    return alternate;
}

