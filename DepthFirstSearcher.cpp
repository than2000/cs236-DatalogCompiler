#ifndef CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_CPP
#define CS236_PROJECT5_T2K_DATALOG_DEPTH_FIRST_SEARCHER_CPP

#include <iostream>
#include "DepthFirstSearcher.h"

std::vector<int> DepthFirstSearcher::generatePostorder(Graph &graph)
{
    DepthFirstSearcher searcher(&graph);
    graph.setAllNodesUnvisited();
    searcher.search();
    return searcher.postOrderSequence;
}

std::vector<int> DepthFirstSearcher::generatePostorderWithRootPriorityList(
    Graph &graph, std::vector<int> rootPriorityList)
{
    // TODO generatePostorderWithRootPriorityList
}

void DepthFirstSearcher::search()
{
    while (!isSearchComplete())
    {
        Node root = getNextRoot();
        searchTree(root);
    }
}

void DepthFirstSearcher::searchTree(Node root)
{
    recurseDepthFirstSearch(root);
}

void DepthFirstSearcher::recurseDepthFirstSearch(Node &node)
{
    if (!node.hasBeenVisited)
    {
        recordVisit(node);
        visitNeighborsOf(node);
        postOrderSequence.push_back(node.nodeId);
    }
}

void DepthFirstSearcher::recordVisit(Node &node)
{
    node.hasBeenVisited = true;
    visitSequence.push_back(node.nodeId);
    updateNextRootNode(node.nodeId);
}

void DepthFirstSearcher::visitNeighborsOf(Node &node)
{
    for (int neighborId : node.adjacentNodeIds)
    {
        Node &neighbor = graphPtr->nodes.at(neighborId);
        recurseDepthFirstSearch(neighbor);
    }
}

Node DepthFirstSearcher::getNextRoot()
{
    return graphPtr->nodes.at(nextRootNode);
}

bool DepthFirstSearcher::isSearchComplete()
{
    // BUG! Infinite loop!
    // return nextRootNode >= graphPtr->numNodes;
    return true;
}

void DepthFirstSearcher::updateNextRootNode(int nodeId)
{
    if (nextRootNode == nodeId)
    {
        nextRootNode++;
    }
}

bool PrioritizedDepthFirstSearcher::isSearchComplete()
{
    return nextRootNode < static_cast<int>(rootPriorityList.size());
}

void PrioritizedDepthFirstSearcher::updateNextRootNode(int nodeId)
{
    // TODO getNextRoot
    if (nextRootNode == nodeId)
    {
        nextRootNode++;
    }
}

#endif
