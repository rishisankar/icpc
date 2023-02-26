// approximation to find max of unimodal function f on some interval
// to switch to min, negate f
// [l,r] = beginning interval
// returns (x, f(x)), where x is the point where f is maximized

// define function f:
ld f(ld x);

pair<ld,ld> ternary_search(ld l, ld r) {
  ld eps = 1e-9; //set the error limit here
  while (r - l > eps) {
    ld m1 = l + (r - l) / 3;
    ld m2 = r - (r - l) / 3;
    ld f1 = f(m1); // evaluates the function at m1
    ld f2 = f(m2); // evaluates the function at m2
    if (f1 < f2) l = m1;
    else r = m2;
  }
  return {l,f(l)}; //return the maximum of f(x) in [l, r]
}
