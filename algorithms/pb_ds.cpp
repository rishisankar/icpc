#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

typedef pair<int,int> T;  // or any other comparable type

tree < T ,  null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update > pbds_tree;

int ord = pbds_tree.order_of_key({qu.l, -1});  // finds index of key
pbds_tree.find_by_order(ord);  // returns ptr/iter

// plus all normal ordered_set functionality!
