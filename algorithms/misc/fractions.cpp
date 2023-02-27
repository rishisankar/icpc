typedef pair<ll,ll> pll;

void rf(pll& p) {
  if (p.F == 0) p = {0,1};
  else {
    ll g = __gcd(abs(p.F), abs(p.S));
    p = {p.F/g, p.S/g};
    if (p.S < 0) p = {-p.F, -p.S};
  }
}

pll af(pll p1, pll p2) {
  pll res = {p2.S*p1.F+p2.F*p1.S, p1.S*p2.S};
  rf(res);
  return res;
}

pll sf(pll p1, pll p2) {
  pll res = {p2.S*p1.F-p2.F*p1.S, p1.S*p2.S};
  rf(res);
  return res;
}

pll mf(pll p1, pll p2) {
  pll res = {p1.F*p2.F, p1.S*p2.S};
  rf(res); return res;
}

pll df(pll p1, pll p2) {
  pll swp = {p2.S,p2.F};
  return mf(p1,swp);
}

bool lt(pll p1, pll p2) {
  rf(p1); rf(p2);
  return p1.F*p2.S < p1.S*p2.F;
}

bool gt(pll p1, pll p2) {
  rf(p1); rf(p2);
  return p1.F*p2.S > p1.S*p2.F;
}
