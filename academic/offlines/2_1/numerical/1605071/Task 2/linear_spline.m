function out = linear_spline( x, y, xp )
n = length(x);
t1 =[];
for i = 1:n-1
    m(i) = (y(i+1) - y(i))/(x(i+1)-x(i));
    c(i) = y(i) - (m(i) * x(i));
    tempx = x(i):0.1:x(i+1);
    tempy = tempx.*m(i) + c(i);
    plot(tempx, tempy);
     xlabel('Time (month)');
     ylabel('Shampoo sold');
     title('Linear Spline');
    hold on;
    n1 = length(xp);
    for j=1 : n1
      if(xp(j)>=x(i) && xp(j)<= x(i+1))
       t1 = cat(1,t1,give_y(m(i),c(i),xp(j)));
     endif
   endfor
   
endfor

out = t1;
endfunction

