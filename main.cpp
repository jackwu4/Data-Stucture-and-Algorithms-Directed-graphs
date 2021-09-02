#include <iostream>
#include <vector>

#include "directed_graph.hpp"
using std::cout;
using std::endl;
int main() {
	directed_graph<char> g;
	g.add_vertex('a');
	g.add_vertex('b');
	g.add_vertex('c');
	g.add_vertex('d');
	g.add_vertex('e');
	g.add_vertex('f');
	/*g.add_vertex('g');
	g.add_vertex('h');
	g.add_vertex('i');
	g.add_vertex('j');
	g.add_vertex('k');
	g.add_vertex('l');
	g.add_vertex('m');
	g.add_vertex('n');
	g.add_vertex('o');
	*/
	g.add_edge('a','b');
	g.add_edge('b','a');
	g.add_edge('b','c');
	g.add_edge('b','e');
	g.add_edge('c','d');
	g.add_edge('d','b');
	g.add_edge('d','c');
	g.add_edge('e','d');
	/*g.add_edge('e','f');
	g.add_edge('f','g');
	g.add_edge('g','h');
	g.add_edge('h','i');
	g.add_edge('i','j');
	g.add_edge('j','k');
	g.add_edge('k','l');
	g.add_edge('l','m');
	g.add_edge('m','n');
	g.add_edge('n','o');
	g.add_edge('o','m');
	*/
	//g.remove_edge('b','c');
	
	std::cout << "num edges " <<g.num_edges() << std::endl;
	std::cout << "num vertices "<< g.num_vertices() << std::endl;
	//std::cout << g.degree('b') << std::endl;
	directed_graph<char> newg = g.out_tree('a');
	std::cout << "new num edges " << newg.num_edges() << std::endl;
	std::cout << "new num vertices "<<newg.num_vertices() << std::endl;
	std::cout << g.reachable('a','d') << std::endl;
	
	/*cout << std::boolalpha;

    directed_graph<char> g;

    g.add_vertex('A');
    g.add_vertex('B');
    g.add_vertex('C');
    g.add_vertex('D');
    g.add_vertex('E');
    g.add_vertex('F');

    g.add_edge('A', 'B');
    g.add_edge('B', 'C');
    g.add_edge('A', 'C');
    g.add_edge('B', 'E');
    g.add_edge('D', 'B');
    g.add_edge('C', 'D');
    g.add_edge('D', 'C');
    g.add_edge('E', 'D');
    g.add_edge('A', 'B');
    g.add_edge('A', 'E');
    g.add_edge('B', 'C');
    g.add_edge('B', 'D');
    g.add_edge('D', 'E');
    g.add_edge('E', 'F');
    g.add_edge('F', 'A');

    g.out_tree('A');

    g.contains('A');
    g.reachable('A', 'B');

    g.get_neighbours('A');
    std::cout << "Depth First: " << std::endl;
    for(auto alpha: g.depth_first('A')) {
        std::cout << alpha << std::endl;
    }
    std::cout << "Breadth First: " << std::endl;
    for(auto alpha: g.breadth_first('A')) {
        std::cout << alpha << std::endl;
    }

    g.out_tree('A');
    //g.get_reverse_neighbours('A');
    g.in_tree('A');


    // Try Iterator:

    vertex_iterator<char> v = vertex_iterator<char>(g, 0);

    // call to operator++. --> preincrement
    ++v;
    // call to operator++(int) --> postincrement.
    v++;

    vertex_iterator<char> v_copy = v;
    std::cout << "Is v_copy in position 0? " << std::endl;
    std::cout << (v_copy == vertex_iterator<char>(g, 0)) << std::endl;
    std::cout << "Is v_copy in position 2? " << std::endl;
    std::cout <<  (v_copy == vertex_iterator<char>(g, 2)) << std::endl;

    std::cout << "Current position of v_copy" << std::endl;
    std::cout << *v << std::endl;

    std::cout << "Current reference of v_copy" << std::endl; //not so sure.
    char *b = v.operator->(); //access the current position, but contains all the vertices list (REFERENCED!)
    std::cout << b << std::endl;

    std::cout << "Vertex Iterator" << std::endl;
    for (auto vertex_iterator = g.begin(); vertex_iterator != g.end(); vertex_iterator++) {
        std::cout << *(vertex_iterator) << " ";
    }
    std::cout << std::endl;

    std::cout << "Neighbour Iterator" << std::endl;
    for (auto neighbor_iterator = g.nbegin('B'); neighbor_iterator != g.nend('B'); neighbor_iterator++) {

        std::cout << *neighbor_iterator << " ";
    }
	*/
}
