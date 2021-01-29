function y = make_eqn (x, a)
  n = length(a);
  xlen = length(x);
  for j = 1 : xlen
    m = a(1);
    for i = 1 : n-1
      m = m + a(i+1) * x(i, j);
    endfor
    y(j) = m;
  endfor
endfunction