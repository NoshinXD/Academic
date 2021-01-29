function out = give_y( m, c, x )
n = numel(x);

for it=1:n
    temp = m*x(it) + c;
    out(it) = temp;
end

