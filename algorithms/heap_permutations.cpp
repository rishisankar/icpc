// heap's algorithm for generating permutations (recursive or iterative approach)
// benefit: don't get MLE since permutations generated in-place
// run on size of arr and arr (and modify handle to do somethign useful)
// doesn't need to be array of ints! can be anything
// O(n!) time since there are n! permutations, but O(n) memory
// Source: https://en.wikipedia.org/wiki/Heap%27s_algorithm

// idea:
// - try putting each term at the end
// - permute everything else 
// - if size is odd, permutation will leave original array unmodified
// - if size is even, first n-1 elements will be rotated

void handle(vector<int>& arr) {
    for (int i : arr) {
        cout << i << " ";
    }
    cout << '\n';
}

// recursive approach
void generate(int k, vector<int>& arr) {
    if (k == 1) {
        handle(arr); // replace with whatever
    } else {
        // Generate permutations with kth unaltered
        // Initially k == length(A)
        generate(k - 1, arr);

        // Generate permutations for kth swapped with each k-1 initial
        for (int i = 0; i < k-1; ++i) {
            // Swap choice dependent on parity of k (even or odd)
            if (k % 2 == 0) {
                swap(arr[i], arr[k-1]); // zero-indexed, the kth is at k-1
            } else {
                swap(arr[0], arr[k-1]);
            }
            generate(k - 1, arr);
        }
    }
}





//// ITERATIVE APPROACH (confusing but works too if necessary)
// note that handle() is called twice, so if replaced, do that twice too

void generate(int n, vector<int> arr) {
    //c is an encoding of the stack state. c[k] encodes the for-loop counter for when generate(k - 1, A) is called
    vector<int> c(n, 0);

    handle(arr);
    
    //i acts similarly to the stack pointer
    int i = 0;
    while (i < n) {
        if  (c[i] < i) {
            if (i % 2 == 0) {
                swap(arr[0], arr[i]);
            } else {
                swap(arr[c[i]], arr[i]);
            }
            handle(arr);
            //Swap has occurred ending the for-loop. Simulate the increment of the for-loop counter
            ++c[i];
            //Simulate recursive call reaching the base case by bringing the pointer to the base case analog in the array
            i = 0;
        } else {
            //Calling generate(i+1, A) has ended as the for-loop terminated. Reset the state and simulate popping the stack by incrementing the pointer.
            c[i] = 0;
            ++i;
        }
    }
}

    
