function x = gauss_jordan (A, B)
  [n, m] = size(A);
  if n ~= m
    error('A is not a square matrix');    
  endif
  
  Aug = [A B];
  for i = 1 : n-1
    [big k] = max(abs(Aug(i : n, i)));
    ipr = i + k - 1;
    if ipr ~= i
      Aug([ipr i],:) = Aug([i ipr],:);        
    endif
    for j = i + 1 : n
      factor = Aug(j, i) / Aug(i, i);
      Aug(j , i: n+1) = Aug(j, i:n+1) - factor * Aug(i, i:n+1);
    endfor
  endfor
  
  for i = n : -1 : 1
    for j = i-1 : -1 : 1
      factor = Aug(j, i) / Aug(i, i);
      Aug(j , n+1: -1 : 1) = Aug(j, n+1:-1:1) - factor * Aug(i, n+1:-1:1);      
    endfor
  endfor
  
  for i=1:n
    Aug(i,:) = Aug(i,:) / Aug(i,i);
 
  endfor
  x = zeros(n, 1);
  %x(n) = Aug(n,n+1) / Aug(n,n);
  %for i=n-1:-1:1
  %  x(i) = (Aug(i, n+1) - Aug(i, i+1 :n) * x(i+1:n)) / (Aug(i,i));    
  %endfor
  for i=1:n
    x(i) = Aug(i, n+1);
  endfor
endfunction
