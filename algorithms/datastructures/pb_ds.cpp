#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

typedef pair<int,int> T;  // or any other comparable type

tree < T ,  null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update > pbds_tree;

int ord = pbds_tree.order_of_key(key);  // ord = number of items strictly smaller than key
pbds_tree.find_by_order(ord);  // returns ptr/iter to ord-th element in set.

// plus all normal ordered_set functionality!
// source: https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/
