#include <GraphAlgs.h>
#include <iostream>

using namespace std;


vector<NodeID> best;
double bestLength = 0;
int start = 0;
bool h = false;

Graph* graphToTest;

void swap(vector<NodeID> &nodes, int first, int second){
	NodeID swapper = nodes[first];
	nodes[first] = nodes[second];
	nodes[second] = swapper;
}

void tour(vector<NodeID> locations, int totalLocs, int start){
	if(totalLocs - start == 1){
		double curTour = 0;
		for(int i = 0; i < totalLocs - 1; i++){
			curTour += graphToTest->weight(locations[i], locations[i + 1]);
			if(h){
				if(curTour > bestLength) return;
			}
		}
		curTour += graphToTest->weight(locations[totalLocs - 1], locations[0]); //loop back around to the front for total tour length
		

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

std::vector<NodeID> heuristicBegin(int totalLocs){

	EdgeWeight curWeight = 0;
	EdgeWeight bestW = 0;

	bool done = false;

	vector<NodeID> hRoute = vector<NodeID>(totalLocs);

	vector<NodeID> visitedList = vector<NodeID>(totalLocs);
	int counter = 0;
	NodeID curPos = 0;
	NodeID next = 0;

	while(!done){
		hRoute[counter] = curPos; //plots our heuristic route as we go
		//list<NWPair> set = graphToTest->getAdj(curPos);
		visitedList[curPos] = curPos; //updates our visitedList at the beginning of every loop so that we don't visit places twice

		for(int j = 0; j < totalLocs; j++){
			bestW = 0;
			if(curPos!=j){
				curWeight = graphToTest->weight(curPos, j);
			}
			if((curWeight < bestW || bestW == 0) && !visitedList[j]){ //Test to see if the current weight is better than the best weight (or if best is 0) and that
																	//We have not visited that node yet.
				bestW = curWeight;
				next = j;  //The next node we look at if it's the smallest weight connected to the curPos
			}
		}

		curPos = next; //now we go to the position that was a result of or shortest connected algorithm

		counter++;
		if(counter == totalLocs){
			done = true;
		}

	}

	return hRoute;

}

double heuristicTour(){
	double tourLen = 0;
	for (int i=0; i < graphToTest->size()-1; i++){
		tourLen += graphToTest->weight(i, i+1);
	}
	tourLen += graphToTest->weight(graphToTest->size()-1, 0);

	return tourLen;
}

std::pair<std::vector<NodeID>, EdgeWeight> TSP(Graph* G, bool heur){
	h = heur;
	graphToTest = G;
	vector<NodeID> locs = vector<NodeID>(G->size());

	best = heuristicBegin(G->size());

	bestLength = heuristicTour();

	//cout << "Hueristic Length: " << bestLength << endl;

	for(int i = 0; i < G->size(); i++){
		locs[i] = i;
	}

	tour(locs, locs.size(), start);

	//cout << "Actual Length: " << bestLength << endl;

	pair<vector<NodeID>, EdgeWeight> bestRoute (best, bestLength);

	return bestRoute;
}





