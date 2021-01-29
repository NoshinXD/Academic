function yp = Lagrange (x,y,n,xp)
n2 = length(xp);
for i = 1 : n2
  yp(i) = 0;
endfor

for i = 1 : n
  product = y(i);
  for j = 1 :n
    if i~=j
      product = product .* (xp - x(j))./ (x(i) - x(j)) ;
    endif
  endfor
  yp = yp + product;
endfor


endfunction
