for i=1
for j = 1:length(veldata{:,2*i-1})
xldata{2+j,5*i-4} = veldata{2*i-1}(j);
xldata{2+j,5*i-3} = vposdata{2*i}(j);
xldata{2+j,5*i-2} = hposdata{2*i}(j);
xldata{2+j,5*i-1} = veldata{2*i}(j);
xldata{2+j,5*i} = massdata{2*i}(j);
end
end
