function A = multilinear (x, y)
  
  n = length(x(:,1));
  n2 = length(y);
  
  for i = 1 : n+1
    
    if i == 1
    
      a(1,i) = length(x);
    else
      sum = 0;
      for l = 1 : n2
         sum = sum + x(i-1,l);
         
      endfor
      a(1,i) = sum;
      a(i,1) = a(1,i);
     
    end
  endfor
  
  for i=2 : n+1
    for j=2 : i
      sum = 0;
      for l = 1 : n2
        
        sum = sum+ x(i-1,l).* x(j-1,l);
        
      endfor
       a(i,j)= sum;
       a(j,i)= a(i,j);
     
    endfor
 endfor
 
 sum =0;
 n2 = length(y);
 
 for i = 1 : n2
   sum = sum + y(1,i);
 endfor
 
 B(1,1) = sum;
 
 sum = 0;

 for i = 2 : n+1
   sum = 0; 
   for l=1 : n2
     
     sum = sum + y(l).* x(i-1,l);
    
   endfor
   B(i,1) = sum;
    
 endfor

  A = gauss_jordan(a,B);

endfunction
