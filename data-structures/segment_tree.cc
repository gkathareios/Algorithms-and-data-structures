#include "segment_tree.h"

void SegTree::init_tree(int index, int range_start, int range_end) {
	tree[index].start = range_start;
	tree[index].end = range_end;
	if (range_start == range_end) {
		tree[index].min_ind = range_start;
		point_to_tree[range_start] = index;
		return;
	}

	int m = range_start + (range_end - range_start)/2;
	init_tree(l(index), range_start, m);
	init_tree(r(index), m+1, range_end);
	
	int l_min_val = array[tree[l(index)].min_ind];
	int r_min_val = array[tree[r(index)].min_ind];
	if (l_min_val < r_min_val){
		tree[index].min_ind = tree[l(index)].min_ind;
	} else {
		tree[index].min_ind = tree[r(index)].min_ind;
	}

	return;
}
	
SegTree::SegTree(vector<int>& inp) {
	array = vector<int>(inp.begin(), inp.end());
	point_to_tree = vector<int>(array.size(), 0);
	tree = vector<TreeNode>(2*array.size() - 1);
	init_tree(0, 0, array.size()-1);
}

int SegTree::query(int start, int end) {
	return query_helper(start, end, 0);
}

int SegTree::query_helper(int start, int end, int index) {
	if (start > tree[index].end || end < tree[index].start) {
		return -1;
	}

	if (tree[index].start >= start && tree[index].end <= end) {
		return tree[index].min_ind;
	}

	int l_res = query_helper(start, end, l(index));
	int r_res = query_helper(start, end, r(index));

	if (l_res == -1 && r_res == -1)
		return -1;

	if (l_res == -1)
		return r_res;

	if (r_res == -1)
		return l_res;

	if (array[l_res] < array[r_res])
		return l_res;
	return r_res;
}

bool SegTree::update_node(int index) {
	int l_min = tree[l(index)].min_ind;
	int r_min = tree[r(index)].min_ind;

	int min_ind = (array[l_min] < array[r_min])?(l_min):(r_min);
	
	if (tree[index].min_ind == min_ind)
		return false;

	tree[index].min_ind = min_ind;
	return true;
}

int SegTree::update(int index, int new_val) {
	array[index] = new_val;
	int c = point_to_tree[index];
	while (p(c) != c) {
		if (!update_node(p(c)))
			break;
		c = p(c);
	}
}


