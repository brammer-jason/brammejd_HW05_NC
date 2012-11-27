#include <MatrixGraph.h>

using namespace std;

/*
 *Constructor for the MatrixGraph
 *Makes M a num_nodes x num_nodes matrix of weights
 */
MatrixGraph::MatrixGraph(unsigned num_nodes){
	M = vector<vector<EdgeWeight>>(num_nodes);
	num_edges = 0;
	for(int i = 0; i < num_nodes; i++){
		M[i] = vector<EdgeWeight>(num_nodes); //i = what row we are on, now we have a row of EdgeWeights
		for(int j = 0; j < num_nodes; j++){
			M[i][j] = -1; //sets all of our weights to -1 by default
		}
	}
}

MatrixGraph::~MatrixGraph(){}

/*
 * Add a weighted, undirected edge between nodes u and v.
 * 
 * Preconditions: 
 *     u and v are legal labels (i.e. 0 <= u < G.size(), 0 <= v < G.size())
 *     u != v
 *     There is no edge between u and v.
 *     weight > 0
 */
void MatrixGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight){
	M[u][v] = weight;
	M[v][u] = weight;
	num_edges++;
}

/*
 * Get the weight between nodes u and v; return -1 if there is no edge.
 *
 * Preconditions: 
 *     u and v are legal labels (i.e. 0 <= u < G.size(), 0 <= v < G.size())
 */
EdgeWeight MatrixGraph::weight(NodeID u, NodeID v) const{
	return M[u][v];
}

/*
 * Return a list of NodeID/EdgeWeight pairs describing the nodes adjacent to edge w.
 *
 * Preconditions: u is a legal label.
 */
std::list<NWPair> MatrixGraph::getAdj(NodeID u) const{
	list<NWPair> pairs;
	for(int i = 0; i < M.size(); i++){
		if(M[u][i] > 0){
			//NWPair p = new NWPair(i, M[u][i]);
			pairs.push_back(NWPair(i, M[u][i]));
		}
	}
	return pairs;
}

/*
 * Return the degree (i.e. the number of neighorbs) of node u.
 *
 * Preconditions: u is a legal label;
 */
unsigned MatrixGraph::degree(NodeID u) const{
	unsigned degreeCount = 0;
	for(int i = 0; i < M.size(); i++){
		if(M[u][i] > 0){
			degreeCount++;
		}
	}
	return degreeCount;
}

/*
 * Return the number of nodes in the graph.
 */
unsigned MatrixGraph::size() const{
	return M.size();
}

/* 
 * Return the number of edges in the graph.
 */
unsigned MatrixGraph::numEdges() const{
	return num_edges;
}