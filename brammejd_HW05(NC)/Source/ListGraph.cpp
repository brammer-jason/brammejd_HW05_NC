#include <ListGraph.h>

using namespace std;


/*
 *Constructor for the ListGraph
 *
 *@param numNodes the size that edgelist should be
 */ 
ListGraph::ListGraph(int numNodes){
	num_edges = 0;
	
	edgeList.resize(numNodes); //Example in class is easier to understand than original code
}

ListGraph::~ListGraph(){}

/*
 * Add a weighted, undirected edge between nodes u and v.
 * 
 * Preconditions: 
 *     u and v are legal labels (i.e. 0 <= u < G.size(), 0 <= v < G.size())
 *     u != v
 *     There is no edge between u and v.
 *     weight > 0
 */
void ListGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight){
	//check for duplicates!
	edgeList[u].push_back(NWPair(v, weight));
	edgeList[v].push_back(NWPair(u, weight));

	num_edges++;
}

/*
 * Get the weight between nodes u and v; return 0 if there is no edge.
 *
 * Preconditions: 
 *     u and v are legal labels (i.e. 0 <= u < G.size(), 0 <= v < G.size())
 */
EdgeWeight ListGraph::weight(NodeID u, NodeID v) const{
	EList list = edgeList[u];
	//do I need to use const_iterator? No, I created a deep copy of the edgeList[u], const not needed
	for(EList::iterator iterator = list.begin(); iterator != list.end(); iterator++){
		if(iterator->first == v){
			return iterator->second;
		}
	}

	//return 0.0 if these nodes are not connected
	return 0;
}

/*
 * Return a list of NodeID/EdgeWeight pairs describing the nodes adjacent to edge w.
 *
 * Preconditions: u is a legal label.
 */
std::list<NWPair> ListGraph::getAdj(NodeID u) const{
	return edgeList[u];
}

/*
 * Return the degree (i.e. the number of neighorbs) of node u.
 *
 * Preconditions: u is a legal label;
 */
unsigned ListGraph::degree(NodeID u) const{

	return edgeList[u].size();

}

/*
 * Return the number of nodes in the graph.
 */
unsigned ListGraph::size() const{
	return edgeList.size();
}

/* 
 * Return the number of edges in the graph.
 */
unsigned ListGraph::numEdges() const{
	return num_edges;
}