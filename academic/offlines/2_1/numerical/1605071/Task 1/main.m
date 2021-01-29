TrainFileName = 'train.csv';
%reading the csv file = TrainFileName, from 2nd row = 1 and 1st column = 0 
TrainData = csvread(TrainFileName,1,0);

%--------- creating plot ----------------
%loading data
figure
plot1_x = TrainData(:,1);
plot1_y = TrainData(:,2);
plot1_population = TrainData(:,5);

plot1_hcolor = TrainData(:,7);

%plotting figure
%figure
plot1 = scatter(plot1_x,plot1_y,plot1_population.*.1,plot1_hcolor,'filled');

colormap jet;

%xlabel('longitude','FontSize',200,'FontWeight','bold','Color','r');
xlabel('longitude');
ylabel('latitude');

plot1_c = colorbar;
hold;

%figure
x1 = TrainData(:,1);
x2 = TrainData(:,2);
x3 = TrainData(:,3);
x4 = TrainData(:,4);
x5 = TrainData(:,5);
x6 = TrainData(:,6);



X=[x1'; x2' ; x3'; x4'; x5'; x6'];
y= TrainData(:,7);
Y = y';

C = multilinear(X,Y);

fprintf("y = %f +(%f) x1 + (%f) x2 + (%f) x3 + (%f) x4+ (%f) x5 + (%f) x6\n\n", C(1), C(2),C(3),C(4),C(5),C(6),C(7));

D = make_eqn(X,C);
RMSE = sqrt((sum((abs(D-Y)).^2))/ 800);
fprintf("RMSE of traindata : %f\n",RMSE);

%fprintf("y = %f +(%f) x1 + (%f) x2 + (%f) x3 + (%f) x4+ (%f) x5 + (%f) x6\n\n", C(1), C(2),C(3),C(4),C(5),C(6),C(7));


%plot(X, Y, 'o', X , D), hold;

figure

Testfilename = 'test.csv';
TestData = csvread(Testfilename,1,0);

plot2_x = TestData(:,1);
plot2_y = TestData(:,2);
plot2_population = TestData(:,5);

plot2_hcolor = TestData(:,7);
%plotting figure

plot2 = scatter(plot2_x,plot2_y,plot2_population.*.1,plot2_hcolor,'filled');

colormap jet;

xlabel('longitude');
ylabel('latitude');

plot2_c = colorbar;
hold;


x21 = TestData(:,1);
x22 = TestData(:,2);
x23 = TestData(:,3);
x24 = TestData(:,4);
x25 = TestData(:,5);
x26 = TestData(:,6);



X2=[x21'; x22' ; x23'; x24'; x25'; x26'];

y2= TestData(:,7);
Y2 = y2';
D2 = make_eqn(X2,C);
RMSE = sqrt((sum((abs(D2-Y2)).^2) )/ 200);
fprintf("RMSE of testdata : %f\n",RMSE);
%RMSE

