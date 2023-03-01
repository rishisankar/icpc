#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
// example: cses/range_queries/salary_queries

typedef pair<int,int> T;  // or any other comparable type

typedef tree < T ,  null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update > pbds_tree;

pbds_tree tr;
int ord = tr.order_of_key(key);  // ord = number of items strictly smaller than key
tr.find_by_order(k);  // returns an iterator to the k-th largest element (counting from zero)

// plus all normal ordered_set functionality!
// source: https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/

// if you want to use a multiset... make T a pair and make the second value distinct for each entry
// can then do upper bound/lower bound queries by making the second value in the query large (UB) / small (LB)