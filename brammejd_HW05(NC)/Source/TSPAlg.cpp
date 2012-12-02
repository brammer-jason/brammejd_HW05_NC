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
			if(i == totalLocs - 1){
				curTour += graphToTest->weight(locations[totalLocs - 1], locations[0]); //loop back around to the front for total tour length
			} else {
				curTour += graphToTest->weight(locations[i], locations[i + 1]);
			}
		}
		if(bestLength == 0 || curTour < bestLength){
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

	bestLength = 0;
	best = locs;

	for(int i = 0; i < G->size(); i++){
		locs[i] = i;
	}

	tour(locs, locs.size(), start);

	pair<vector<NodeID>, EdgeWeight> bestRoute (best, bestLength);

	return bestRoute;
}



