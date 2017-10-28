Clean
load data.mat;
plot(data(1,:),data(2,:));
prettify(gca);
h0 = gca;
xmin = h0.XLim(1) - 100;
xmax = h0.XLim(2) +200;
ymin = h0.YLim(1)-100;
ymax = h0.YLim(2) + 100;
h0.XLim = [xmin xmax];
h0.YLim = [ymin ymax];
xmap = @(val) (val-xmin)/(xmax - xmin);
ymap = @(val) (val-ymin)/(ymax-ymin);

data(1,:) = xmap(data(1,:));
data(2,:) = ymap(data(2,:));

apogee = find(data(2,:)==max(data(2,:)));

rob = imread('Robb.png');
h1 = axes('Position',[data(1,1)-.05, data(2,1)-.05, 0.1 0.1]);
imshow(rob);

chute = imread('Parachute.png');
h2 = axes('Position', [data(1,1)-.05, data(2,1)+.05, 0.1 0.1]);
h2.Visible = 'off';



filename = 'ToInfinity';
v = VideoWriter(filename,'MPEG-4');
open(v);
for n = 1:length(data(1,:))
   h1.Position = [data(1,n)-.05, data(2,n)-.05, 0.1 0.1];
   h2.Position = h1.Position + [0 0.1 0 0];
   if n == apogee
       imshow(chute);
   end
   
   drawnow
   
   frame = getframe(1);
   
   writeVideo(v,frame);
   
%    im = frame2im(frame);
%    [imind,cm]= rgb2ind(im,256);
%    
%   
%    
%    if n == 1;
%        imwrite(imind,cm,[filename '.gif'],'gif', 'Loopcount',inf, 'DelayTime',0.05);
%    else
%        imwrite(imind,cm,[filename '.gif'],'gif','WriteMode','append');
%    end
end
close(v)
 