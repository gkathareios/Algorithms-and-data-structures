#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
using namespace std;

class MinHeap{
public:
	vector<pair<char,int>> v;
	int size;
	unordered_map<char, int> place_in_queue;
	
	MinHeap(vector<pair<char,int>> inp){
		v = inp;
		size = inp.size();
	}

	static inline p(int n) {return ((n-1)/2);}
	static inline l(int n) {return 2*n + 1;}
	static inline r(int n) {return 2*n + 2;}
	int& key(int n) {return v[n].second;}
	int key(char c) {return v[place_in_queue[c]].second;}
	inline bool in_queue(char c) {return place_in_queue[c] < size;}

	void my_swap(int a, int b){
		swap(v[a],v[b]);
		place_in_queue[v[a].first] = a;
		place_in_queue[v[b].first] = b;
	}

	void heapify(int n){
		int m = n;
		if (l(n) < size && key(l(n)) < key(m))
			m = l(n);
		if (r(n) < size && key(r(n)) < key(m))
			m = r(n);
		my_swap(m, n);
		if (m!=n)
			heapify(m);
	}

	void make_heap(){
		for (int i = p(size-1); i >= 0; --i)
			heapify(i);
		for (int i = 0; i< size; ++i)
			place_in_queue[v[i].first] = i;
	}

	pair<char,int> extract_min(){
		pair<char,int> retval = v[0];
		my_swap(0, size-1);
		size--;
		heapify(0);
		return retval;
	}

	void change_value(char c, int new_val){
		int n = place_in_queue[c];
		if (new_val == key(n))
			return;
		if (new_val > key(n)){
			key(n) = new_val;
			heapify(n);
			return;
		}

		//here new_val < v[n]
		key(n) = new_val;
		while(key(p(n)) > key(n)){
			int new_n = p(n);
			my_swap(p(n),n);
			n = new_n;
		}
	}


};

void prim(unordered_map<char, vector<pair<char,int>>> g, char root){
	vector<pair<char,int>> temp_vs(g.size(), pair<char,int>('_',0));
	unordered_map<char,char> parent;

	int ind = 0;
	for(auto it = g.begin(); it != g.end(); ++it){
		parent[it->first] = '_';
		temp_vs[ind].first = it->first;
		if (it->first == root)
			temp_vs[ind].second = 0;
		else
			temp_vs[ind].second = numeric_limits<int>::max();
		ind++;
	}

	MinHeap queue(temp_vs);
	queue.make_heap();

	while(queue.size > 0){
		char u = queue.extract_min().first;
		for(auto v_pair : g[u]){
			char v = v_pair.first;
			int w_uv = v_pair.second;
			if (queue.in_queue(v) && w_uv < queue.key(v)){
				queue.change_value(v, w_uv);
				parent[v] = u;
			}
		}
	}

	for (auto i: parent){
		cout << i.first << " " << i.second << endl;
	}

}


int main(){
	unordered_map<char, vector<pair<char,int>>> g ={
		{ 'a' , {{'b',4},{'h',8}}},
		{ 'b' , {{'a',4},{'c',8},{'h',11}}},
		{ 'c' , {{'b',8},{'d',7},{'f',4},{'i',2}}},
		{ 'd' , {{'c',7},{'f',14},{'e',9}}},
		{ 'e' , {{'d',9},{'f',10}}},
		{ 'f' , {{'c',4},{'d',14},{'e',10},{'g',2}}},
		{ 'g' , {{'i',6},{'h',1},{'f',2}}},
		{ 'h' , {{'a',8},{'b',11},{'i',7},{'g',1}}},
		{ 'i' , {{'c',2},{'g',6},{'h',7}}}
	};

	prim(g,'a');

	return 0;
}





