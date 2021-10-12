% Reading csv file and assigning values
data = readmatrix('pose01.csv');
t = data(:,1);
q1 = data(:,2);
q2 = data(:,3);
q3 = data(:,4);
q4 = data(:,5);
q5 = data(:,6);
x = data(:,7);
y = data(:,8);

figure;
plot(t, q1, 'r', t, q2, 'b', t, q3, 'k',t, q4, 'g',t, q5, 'y');
title('Joint Angles');
legend('Q1','Q2','Q3','Q4','Q5')
xlabel('Time')
ylabel('Angle(rad)')

figure;
subplot(2,1,1)
plot(t, x);
title('End-effector Position');
xlabel('Time')
ylabel('X-coordinates')
ylim([-0.5 3])
subplot(2,1,2)
plot(t, y);
xlabel('Time')
ylabel('Y-coordinates')
ylim([-0.1 0.6])