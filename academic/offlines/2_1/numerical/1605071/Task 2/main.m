# Created by Octave 4.2.2, Sun Jul 22 17:06:25 2018 GMT <unknown@unknown>
ShampooFile = 'shampoo.csv';
shampooData = csvread(ShampooFile,1,0);
j=1;
for i=1 : 36
  if (i!=7 && i!=12 && i!=20 && i!=27 && i!=33)
    x(j) = shampooData(i,1);
    y(j) = shampooData(i,2);
    j++;
 endif
endfor

plot(x,y,'o');
xlabel('Time (month)');
ylabel('Shampoo sold');
title('Data plotting');
hold;


figure
xp = 1 : .01 : 36;
d = linear_spline(x,y,xp);
plot(x,y,'o');
hold on;
fprintf("for Linear Spline : \n");
xm = [7;12;20;27;33];
ym = linear_spline(x,y,xm);
ym
c = linspace(100,300,5);
scatter(xm,ym,100,c,'filled');


figure
%xp = 1 : .01 : 36;
b = Newtint(x,y,xp);
plot(x,y,'o',xp,b);
hold on;
fprintf("for Newton: \n");
xm = [7;12;20;27;33];
ym = Newtint(x,y,xm);
ym = ym(:,1)
c = linspace(10,50,5);
scatter(xm,ym,130,c,'filled');
xlabel('Time (month)');
ylabel('Shampoo sold');
title('Newton Interpolation');



figure
e = Lagrange(x,y,31,xp);
plot(x,y,'o',xp,e);
hold on;
fprintf("for Lagrange : \n");
xm = [7;12;20;27;33];
ym = Lagrange(x,y,31,xm);
ym = ym(:,1)
c = linspace(100,300,5);
scatter(xm,ym,100,c,'filled');
xlabel('Time (month)');
ylabel('Shampoo sold');
title('Lagrange Interpolation');


figure
plot(x,y,'o');
hold on;
xm = [7;12;20;27;33];
ym = quadratic_spline(x,y,xm);
ym = ym'


