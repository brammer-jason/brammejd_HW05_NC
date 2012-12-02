#include <GraphAlgs.h>

using namespace std;


vector<NodeID> best;
double bestLength = 0;
int start = 0;

Graph* graphToTest;

void swap(vector<NodeID> &nodes, int first, int second){
	NodeID swapper = nodes[first];
	nodes[first] = nodes[second];
	nodes[second] = swapper;
}

void tour(vector<NodeID> locations, int totalLocs, int start){
	if(totalLocs - start == 1){
		double curTour = 0;
		for(int i = 0; i < totalLocs; i++){
			curTour += graphToTest->weight(locations[i], locations[i + 1]);
		}
		if(curTour < bestLength){
			bestLength = curTour;
			best = locations;
		}
	} else {
		for(int i = start; i < totalLocs; i++){
			swap(locations, start, i);
			tour(locations, totalLocs, start + 1);
			swap(locations, start, i);
		}
	}
}


std::pair<std::vector<NodeID>, EdgeWeight> TSP(Graph* G){
	graphToTest = G;
	vector<NodeID> locs = vector<NodeID>(G->size());

	for(int i = 0; i < G->size(); i++){
		locs[i] = i;
	}

	tour(locs, locs.size(), start);

	pair<vector<NodeID>, EdgeWeight> bestRoute (best, bestLength);

	return bestRoute;
}



