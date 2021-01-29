function m = quadratic_spline(x, y, n)

  N   =   length(x)-1;
  V   =   [0;zeros(2*N,1);zeros(N-1,1)];
  Z   =   zeros(length(V),length(V));
  j=1;
  f=1;
  for i=2:2:2*N    
    Z(i,f:f+2)          =   [x(j)^2 x(j) 1];
    V(i)                =   y(j);
    j                   =   j+1;
    Z(i+1,f:f+2)        =   [x(j)^2 x(j) 1];  
    V(i+1)              =   y(j);
    f                   =   f+3;
  end
  % Filling Matrix from smoothing condition
  j=1;
  l=2;
  for i=2*N+2:3*N
    Z(i,j:j+1)            =   [2*x(l) 1];
    Z(i,j+3:j+4)          =   [-2*x(l) -1];
    j                     =   j+3;
    l                     =   l+1;
  end

  % Adjusting the value of a1 to be zero "Linear Spline"
  Z(1,1)=1;
  % Inverting and obtaining the coeffiecients, Plotting
  Coeff = Z\V;
  j=1;
  hold on;
  for i=1:N
    curve=@(l) Coeff(j)*l.^2+Coeff(j+1)*l+Coeff(j+2);
    ezplot(curve,[x(i),x(i+1)]);
    hndl=get(gca,'Children');
    set(hndl,'LineWidth',2);
    hold on
    j=j+3;
  end
  
 
  xlabel('Time (month)');
  ylabel('Shampoo sold');
  title('Quadratic Spline');
  
%  Coeff
  fprintf('\nfor QuadraticInterpolation: \n');
  for j = 1:length(n)
    for i = 1: length(x)-1
     if x(i) <= n(j) && x(i+1) > n(j) 
       break
      endif
    endfor
    k = 1+(i-1)*3;
    m(j)= Coeff(k)*n(j)^2+Coeff(k+1)*n(j)+Coeff(k+2);
    %fprintf('month = %d Shampoo sold = %f\n', n(j), m(j));
  endfor  
  
  c = linspace(100,300,5);
  scatter(n,m,100,c,'filled');
  hold off;
endfunction