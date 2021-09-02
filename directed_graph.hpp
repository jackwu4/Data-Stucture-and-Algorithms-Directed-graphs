#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

//A large selection of data structures from the standard
//library. You need not feel compelled to use them all,
//but as you can't add any, they're all here just in case.
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <map>
#include <cstddef>
#include <string>

//Forward declarations for classes below so they can be used below without worrying too much about the ordering.
template <typename vertex> class vertex_iterator;
template <typename vertex> class neighbour_iterator;
template <typename vertex> class directed_graph;


template <typename vertex>
class directed_graph {

private:

  //You will need to add some data members here
  //to actually represent the graph internally,
  //and keep track of whatever you need to.
std::vector<vertex> vertices;
std::vector<std::vector<bool> > adj_matrix;
//size_t size = 0;
size_t adj_size = 0;

public:


  directed_graph(); //A constructor for directed_graph. The graph should start empty.
  ~directed_graph(); //A destructor. Depending on how you do things, this may
  //not be necessary.
  
  bool contains(const vertex&) const; //Returns true if the given vertex is in the graph, false otherwise.
  int find_pos(const vertex&) const; //Return the position from the vertex given.
  void resize_adj(const size_t&);

  bool adjacent(const vertex&, const vertex&) const; //Returns true if the first vertex is adjacent to the second, false otherwise.

  void add_vertex(const vertex&); //Adds the passed in vertex to the graph (with no edges).
  void add_edge(const vertex&, const vertex&); //Adds an edge from the first vertex to the second.

  void remove_vertex(const vertex&); //Removes the given vertex. Should also clear any incident edges.
  void remove_edge(const vertex&, const vertex&); //Removes the edge between the two vertices, if it exists.

  std::size_t in_degree(const vertex&) const; //Returns number of edges coming in to a vertex.
  std::size_t out_degree(const vertex&) const; //Returns the number of edges leaving a vertex.
  std::size_t degree(const vertex&) const; //Returns the degree of the vertex (both in and out edges).
  
  std::size_t num_vertices() const; //Returns the total number of vertices in the graph.
  std::size_t num_edges() const; //Returns the total number of edges in the graph.

  std::vector<vertex> get_vertices(); //Returns a vector containing all the vertices.
  std::vector<vertex> get_neighbours(const vertex&); //Returns a vector containing the neighbours of the given vertex.
  vertex get_vertice(const int&); //not really being used dw about it

  vertex_iterator<vertex> begin(); //Returns a graph_iterator pointing to the start of the vertex set.
  vertex_iterator<vertex> end(); //Returns a graph_iterator pointing to one-past-the-end of the vertex set.

  neighbour_iterator<vertex> nbegin(const vertex&); //Returns a neighbour_iterator pointing to the start of the neighbour set for the given vertex.
  neighbour_iterator<vertex> nend(const vertex&); //Returns a neighbour_iterator pointing to one-past-the-end of the neighbour set for the given vertex.

  std::vector<vertex> depth_first(const vertex&); //Returns the vertices of the graph in the order they are visited in by a depth-first traversal starting at the given vertex.
  std::vector<vertex> breadth_first(const vertex&); //Returns the vertices of the graph in the order they are visisted in by a breadth-first traversal starting at the given vertex.

  directed_graph<vertex> out_tree(const vertex&) const; //Returns a spanning tree of the graph starting at the given vertex using the out-edges.
  directed_graph<vertex> in_tree(const vertex&); //Returns a spanning tree of the graph starting at the given vertex using the in-edges.

  bool reachable(const vertex&, const vertex&) const; //Returns true if the second vertex is reachable from the first (can you follow a path of out-edges to get from the first to the second?). Returns false otherwise.

};

//The vertex_iterator class provides an iterator
//over the vertices of the graph.
//This is one of the harder parts, so if you're
//not too comfortable with C++ leave this for last.
//If you are, there are many ways of doing this,
//as long as it passes the tests, it's okay.
//You may want to watch the videos on iterators before starting.
template <typename vertex>
class vertex_iterator {

private:

  //You may need data members here.
  std::vector<vertex> vertices;
  std::size_t position;
public:
  vertex_iterator(const vertex_iterator<vertex>&);
  vertex_iterator(const directed_graph<vertex>&, std::size_t);
  ~vertex_iterator();
  vertex_iterator<vertex> operator=(const vertex_iterator<vertex>&);
  bool operator==(const vertex_iterator<vertex>&) const;
  bool operator!=(const vertex_iterator<vertex>&) const;
  vertex_iterator<vertex> operator++();
  vertex_iterator<vertex> operator++(int);
  vertex operator*();
  vertex* operator->();
};

//The neighbour_iterator class provides an iterator
//over the neighbours of a given vertex. This is
//probably harder (conceptually) than the graph_iterator.
//Unless you know how iterators work.
template <typename vertex>
class neighbour_iterator {

private:

  //You may need data members here.
  std::vector<vertex> neighbours;
  std::size_t position;
public:
  neighbour_iterator(const neighbour_iterator<vertex>&);
  neighbour_iterator(const directed_graph<vertex>&, const vertex&, std::size_t);
  ~neighbour_iterator();
  neighbour_iterator<vertex> operator=(const neighbour_iterator<vertex>&);
  bool operator==(const neighbour_iterator<vertex>&) const;
  bool operator!=(const neighbour_iterator<vertex>&) const;
  neighbour_iterator<vertex> operator++();
  neighbour_iterator<vertex> operator++(int);			
  vertex operator*();
  vertex* operator->();
};


//Define all your methods down here (or move them up into the header, but be careful you don't double up). If you want to move this into another file, you can, but you should #include the file here.
//Although these are just the same names copied from above, you may find a few more clues in the full
//method headers. Note also that C++ is sensitive to the order you declare and define things in - you
//have to have it available before you use it.

template <typename vertex> directed_graph<vertex>::directed_graph() {
	
}
template <typename vertex> directed_graph<vertex>::~directed_graph() {}
template <typename vertex> bool directed_graph<vertex>::contains(const vertex& u) const {
	if(find_pos(u) == -1) 							//the find pos will return -1 if the given vertex is not found
		return false;
	else											//with the -1 given from findpos can determine if the vertex is contained in the graph
		return true;
}
template <typename vertex> int directed_graph<vertex>::find_pos(const vertex& u) const {
	size_t pos;
	for(pos = 0; pos < num_vertices(); pos++){ 		//looping through all the vertices
		if(vertices[pos] == u)
		{
			return pos; 							//return pos of the given vertex when found.
		}
	}
	return -1; //not found return -1.
}
template <typename vertex> void directed_graph<vertex>::resize_adj(const size_t& s) {
	adj_matrix.resize(s); 							//resizing adj_matrix outter vector
	for (unsigned i = 0; i < s; i++){
		adj_matrix[i].resize(s,false); 				//for each outter vector resize each inner vector
	}
}
template <typename vertex> bool directed_graph<vertex>::adjacent(const vertex& u, const vertex& v) const {
	if(find_pos(u) == -1 || find_pos(v) == -1) 		//check if given vertex is in the graph
		return false;
	return adj_matrix[find_pos(u)][find_pos(v)]; 	//return if there is a edge from u->v
}
template <typename vertex> void directed_graph<vertex>::add_vertex(const vertex& u) {
	vertices.push_back(u); 							//add given vertex to vertices vector
	resize_adj(vertices.size()+1); 					//resize adj_matrix to be just one bigger (each dimension) than the current size of the vertices
	//size++;
}
template <typename vertex> void directed_graph<vertex>::add_edge(const vertex& u, const vertex& v) {
	int first = find_pos(u); 						//locate vertex u's position
	int second = find_pos(v); 						//locate v's position
	
	if(first != -1 && second != -1 && !adj_matrix[first][second] && first != second){ //check if both u v are in the vertices vector and also u is not equal to v
		adj_matrix[first][second] = true; 			//create the edge from u to v (u->v)
		//std::cout << vertices[first] << " -> " << vertices[second] << std::endl;
		adj_size++; 								//increase the counter for the number of edges.
	}
}
template <typename vertex> void directed_graph<vertex>::remove_vertex(const vertex& u) {
	int pos = find_pos(u); 							//locate the position of the given vertex in the vertices vector
	if(pos != -1){	
		vertices.erase(vertices.begin()+ pos); 		//when found remove the vertex in the vertices vector
		//size--;
	}
}
template <typename vertex> void directed_graph<vertex>::remove_edge(const vertex& u, const vertex& v) {
	int first = find_pos(u); 						//locate position of u
	int second = find_pos(v); 						//locate posiotion of v
	if(first != -1 && second != -1 && adj_matrix[first][second] && first != second){ // if both found in vertices vector and u is not equal to v
		adj_matrix[first][second] = false; 			//remove the edge from u to v (u->v)
		adj_size--; 								//decrease the number of edges by one
	}
}
template <typename vertex> std::size_t directed_graph<vertex>::in_degree(const vertex& u) const { 
	size_t count = 0; 								//counter for counting the number of in degree
	int position = find_pos(u); 					//get the position of the given vertex
	if(position != -1) 								//only go forward when vertex given is located in the vertices vector
	for(unsigned i = 0; i < num_vertices(); i++){	//loop through vertices
		if(adj_matrix[i][position])					//when the looping index has an edge to the given vertex i -> u
			count++; 								// increase the number of in degree by one
	}
	return count;									//return the final result
}
template <typename vertex> std::size_t directed_graph<vertex>::out_degree(const vertex& u) const { 
	size_t count = 0; 								//counter for counting the number of in degree
	int position = find_pos(u); 					//get the position of the given vertex
	if(position != -1)								//only go forward when vertex given is located in the vertices vector
	for(unsigned i = 0; i < num_vertices(); i++){
		if(adj_matrix[position][i])					//when the looping index has an edge to the given vertex u -> i
			count++;								//increase the number of out degree by one
	}
	return count;									//return the final result
}
template <typename vertex> std::size_t directed_graph<vertex>::degree(const vertex& u) const { 
	size_t count = 0;
	int position = find_pos(u); 					//get the position of the given vertex
	if(position != -1)								//only go forward when vertex given is located in the vertices vector
	for(unsigned i = 0; i < num_vertices(); i++){	//one for loop faster
		if(adj_matrix[position][i])					//from u -> i
			count++;
		if(adj_matrix[i][position])					//from i -> u
			count++;
	}
	return count;
	//return in_degree(u) + out_degree(u);			//two for loop slower but less code
}
template <typename vertex> std::size_t directed_graph<vertex>::num_vertices() const { 
	return vertices.size();  						//returning the size of the vertices vector
}
template <typename vertex> std::size_t directed_graph<vertex>::num_edges() const { 
	return adj_size; 								//returning the adj_size which been used to count the number of edges.
}
template <typename vertex> std::vector<vertex> directed_graph<vertex>::get_vertices() { 
	return vertices; 								//return the vector of vertices
}
template <typename vertex> std::vector<vertex> directed_graph<vertex>::get_neighbours(const vertex& u) {
	std::vector<vertex> neighbours;					//create an empty neighbours vector
	for(unsigned i = 0; i < num_vertices(); i++){	
		if(adj_matrix[find_pos(u)][i])				//when u has an edge to i (u -> i)
			neighbours.push_back(vertices[i]);		//add i's vertex to the vector neighbours
	}
	return neighbours;
}
template <typename vertex> vertex directed_graph<vertex>::get_vertice(const int& a){
	return vertices[a];								//return the vertice with the given index. used only in testing
}
template <typename vertex> vertex_iterator<vertex> directed_graph<vertex>::begin() { 
	return vertex_iterator<vertex>(*this, 0); 		//return a vertex iterator using the constructor with the graph and the begin position 0
}
template <typename vertex> vertex_iterator<vertex> directed_graph<vertex>::end() { 
	return vertex_iterator<vertex>(*this, this->vertices.size()); //return a vertex iterator using the constructor with the graph and the end position (vertices.size())
}
template <typename vertex> neighbour_iterator<vertex> directed_graph<vertex>::nbegin(const vertex& u) { 
	return neighbour_iterator<vertex>(*this, u ,0); //return a neighbour iterator using the constructor with the graph, the starting vertex and the starting position
}
template <typename vertex> neighbour_iterator<vertex> directed_graph<vertex>::nend(const vertex& u) { 
	return neighbour_iterator<vertex>(*this, u , this->get_neighbours(u).size()); //return a neighbour iterator using the constructor with the graph, the starting vertex and the last position
}
template <typename vertex> std::vector<vertex> directed_graph<vertex>::depth_first(const vertex& u) {
	bool visited[num_vertices()];					//create a visited bool vector
	for (unsigned i = 0; i < num_vertices(); i++){
		visited[i] = false;							//set all value in visited vector to false
	}
	
	std::stack<vertex> unprocessed;					//a stack for storing the unprocessed vertices wait in line to be processed
	unprocessed.push(u);							//add the given u to the unprocessed stack as the starting point
	
	std::vector<vertex> ordered;					//an empty vector to store vertices in order
	
	while (!unprocessed.empty()){					//check if unprocessed vector is not empty
		vertex n = unprocessed.top();				//copy the top item of the stack and save it in a local attribute 'n'
		unprocessed.pop();							//remove the top item from the stack
		if (!visited[find_pos(n)]){					//check if the position of the n has already been visited
			visited[find_pos(n)] = true;			//if not visited then set it to visited
			ordered.push_back(n);					//add n to the ordered vector
			for (unsigned i = num_vertices(); i != 0; i--){ //looping through all vertices's index
				if (adj_matrix[find_pos(n)][i-1]){	//if the n's index has an edge with another index
					unprocessed.push(vertices[i-1]);//add index's value to the unprocessed stack
				}
			}
		}
	}
		
	return ordered;
}
template <typename vertex> std::vector<vertex> directed_graph<vertex>::breadth_first(const vertex& u) {
	bool visited[num_vertices()];					
	for (unsigned i = 0; i < num_vertices(); i++){
		visited[i] = false;
	}
	
	std::queue<vertex> unprocessed;					//only difference between depth_first to breath_first is one using a stack and the other using a queue
	unprocessed.push(u);							//queue first in first out, stack first in last out.
	
	std::vector<vertex> ordered;
	
	while (!unprocessed.empty()){
		vertex n = unprocessed.front();
		unprocessed.pop();
		if (!visited[find_pos(n)]){
			visited[find_pos(n)] = true;
			ordered.push_back(n);
			for (unsigned i = 0; i < num_vertices(); i++){
				if (adj_matrix[find_pos(n)][i]){
					unprocessed.push(vertices[i]);
				}
			}
		}
	}
		
	
	return ordered;	
}
template <typename vertex> directed_graph<vertex> directed_graph<vertex>::out_tree(const vertex& u) const { 
	directed_graph<vertex> g;						//return is a graph, create a graph first named 'g'
	
	bool visited[num_vertices()];					//a bool vector to check if the vertex has been used to look for it's neighbours. To prevent any repeated searches for neighbours
	for (unsigned i = 0; i < num_vertices(); i++){
		visited[i] = false;
	}
	bool intree[num_vertices()];					//a bool vector to check if the vertex has already connected to the tree. To prevent any reconnections to the vertices
	for (unsigned i = 0; i < num_vertices(); i++){
		intree[i] = false;
	}
	
	std::queue<vertex> unprocessed;					//a waiting queue to process all the vectices
	unprocessed.push(u);							//add the starting/given vertex to the unprocessed vector
	g.add_vertex(u);								//g graph add the first vertex u
	intree[find_pos(u)] = true;						//set intree 'u' vertex to true, u is in the tree now
	while(!unprocessed.empty()){
		vertex n = unprocessed.front();
		unprocessed.pop();
		if(!visited[find_pos(n)]){
			visited[find_pos(n)] = true;			//set visited 'u' vertex to true, u is been used to look for neighbours
			//std::cout << n <<" visited" << std::endl;
			for (unsigned i = 0; i < num_vertices(); i++){ 									//loop through all vertices
				//std::cout << "is " << n << " -> " << vertices[i] << "?"<< std::endl;
				if (adj_matrix[find_pos(n)][i]){											//if there is an edge from the n vertex to the index's vertex(i)
					//std::cout << "yes" << std::endl;
					//unprocessed.push(vertices[i]);
					//std::cout << vertices[i]<<" add to unprocessed" << std::endl;
					if(!intree[i]){															//when a edge is being found check if vertex[i] is already in the tree
						unprocessed.push(vertices[i]);										//when vertex[i] is not in the tree add to the unprocessed queue
						//std::cout << vertices[i]<<" add to unprocessed" << std::endl;
						g.add_vertex(vertices[i]);											//add the vertex[i] to the g graph
						//std::cout << vertices[i] << " added" << std::endl;
						g.add_edge(n,vertices[i]);											//add an edge between n vertex to vertex[i]
						//std::cout << n << " -> " << vertices[i] << std::endl;
						intree[i] = true;													//now vertex[i] is in the tree. set true
						//std::cout << vertices[i] << " is in tree" << std::endl;
					}
				}
			}
		}
		
		
	}
	
	
	return g;
}
template <typename vertex> directed_graph<vertex> directed_graph<vertex>::in_tree(const vertex& u) {
	directed_graph<vertex> g;
	
	bool visited[num_vertices()];
	for (unsigned i = 0; i < num_vertices(); i++){
		visited[i] = false;
	}
	bool intree[num_vertices()];
	for (unsigned i = 0; i < num_vertices(); i++){
		intree[i] = false;
	}
	
	std::queue<vertex> unprocessed;
	unprocessed.push(u);
	g.add_vertex(u);
	intree[find_pos(u)] = true;
	while(!unprocessed.empty()){
		vertex n = unprocessed.front();
		unprocessed.pop();
		if(!visited[find_pos(n)]){
			visited[find_pos(n)] = true;
			//std::cout << n <<" visited" << std::endl;
			for (unsigned i = 0; i < num_vertices(); i++){
				//std::cout << "is " << n << " -> " << vertices[i] << "?"<< std::endl;
				if (adj_matrix[i][find_pos(n)]){										//only difference from out tree to in tree is to reverse the checking 
					//std::cout << "yes" << std::endl;									//out tree (n->vertices[i]); in tree (vertices[i]->n)
					//unprocessed.push(vertices[i]);
					//std::cout << vertices[i]<<" add to unprocessed" << std::endl;
					if(!intree[i]){							
						unprocessed.push(vertices[i]);
						//std::cout << vertices[i]<<" add to unprocessed" << std::endl;
						g.add_vertex(vertices[i]);
						//std::cout << vertices[i] << " added" << std::endl;
						g.add_edge(vertices[i],n);										//the edge is being added reversily as well vertices[i]->n
						//std::cout << n << " -> " << vertices[i] << std::endl;
						intree[i] = true;
						//std::cout << vertices[i] << " is in tree" << std::endl;
					}
				}
			}
		}
		
		
	}
	
	
	return g;
}
template <typename vertex> bool directed_graph<vertex>::reachable(const vertex& u, const vertex& v) const {
	return out_tree(u).contains(v);				//reachable means from u can it reaches v, using out tree create a graph with the starting point u, then use contain to check if v is in the graph. 					
}												//out_tree method need to change to const in order to work

template <typename vertex> vertex_iterator<vertex>::vertex_iterator(const vertex_iterator<vertex>& other) {
	this->vertices = other.vertices;			//saving the copy iterator to the current iterator
	this->position = other.position;
}
template <typename vertex> vertex_iterator<vertex>::vertex_iterator(const directed_graph<vertex>& graph, std::size_t position) {
	auto g = graph;								//save the graph to a local attribute
	this->vertices = g.get_vertices();			//use the graph's get_vertices method to get all vertices and save in to the iterator's vertices vector.
	this->position = position;					//save the given position.
}
template <typename vertex> vertex_iterator<vertex>::~vertex_iterator() {}
template <typename vertex> vertex_iterator<vertex> vertex_iterator<vertex>::operator=(const vertex_iterator<vertex>& other) {
	this->vertices = other.vertices;			//set vertices to other.vertices
	this->position = other.position;			//set position to other.position
	return *this;								//return this iterator
}
template <typename vertex> bool vertex_iterator<vertex>::operator==(const vertex_iterator<vertex>& other) const {
	return this->vertices == other.vertices && this->position == other.position;	//check if this iterator's value is the same as the given iterator
}
template <typename vertex> bool vertex_iterator<vertex>::operator!=(const vertex_iterator<vertex>& other) const {
	return this->vertices != other.vertices || this->position != other.position;	//check if this iterator's value is the same as the given iterator
}
template <typename vertex> vertex_iterator<vertex> vertex_iterator<vertex>::operator++() {
	++position;									//increment the position of the current iterator and then return the iterator
    return *this;
}
template <typename vertex> vertex_iterator<vertex> vertex_iterator<vertex>::operator++(int) {
	auto temp = this;							//this is a increment first like (++i)
    ++position;									//first save the current in to a temp, then increment the current, then return the temp
    return *temp;								//because ++i need to return first then increment but cant write behind return, this is the solution for it
}
template <typename vertex> vertex vertex_iterator<vertex>::operator*() {
	return vertices[position];                  //return the current pointer vertex
}
template <typename vertex> vertex* vertex_iterator<vertex>::operator->() {
	return  &vertices[position]; 				//similate the -> sign like this->vertices this->graph
}

template <typename vertex> neighbour_iterator<vertex>::neighbour_iterator(const neighbour_iterator<vertex>& other) {
	this->neighbours = other.neighbours; 		// almost exactly same as vertices iterator but this one iterator through the neighbour of the given starting vertex
	this->position = other.position;
}
template <typename vertex> neighbour_iterator<vertex>::neighbour_iterator(const directed_graph<vertex>& graph, const vertex& u, std::size_t position) {
	auto g = graph;
	this->neighbours = g.get_neighbours(u); 	//vertex u is the starting location, and get_neighbour will get all the neighours of u and store it in the neighbours vertices.
	this->position = position;
}
template <typename vertex> neighbour_iterator<vertex>::~neighbour_iterator() {}
template <typename vertex> neighbour_iterator<vertex> neighbour_iterator<vertex>::operator=(const neighbour_iterator<vertex>& other) { 
	this->neighbours = other.neighbours;
	this->position = other.position;
	return *this;
}
template <typename vertex> bool neighbour_iterator<vertex>::operator==(const neighbour_iterator<vertex>& other) const {
	return this->neighbours == other.neighbours && this->position == other.position;
}
template <typename vertex> bool neighbour_iterator<vertex>::operator!=(const neighbour_iterator<vertex>& other) const { 
	return this->neighbours != other.neighbours || this->position != other.position;
}
template <typename vertex> neighbour_iterator<vertex> neighbour_iterator<vertex>::operator++() {
	++position;
    return *this;
}
template <typename vertex> neighbour_iterator<vertex> neighbour_iterator<vertex>::operator++(int) {
	auto temp = this;
    ++position;
    return *temp;
}		
template <typename vertex> vertex neighbour_iterator<vertex>::operator*() {
	return neighbours[position];
}
template <typename vertex> vertex* neighbour_iterator<vertex>::operator->() {
	return  &neighbours[position];
}


#endif

