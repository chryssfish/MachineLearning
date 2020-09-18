function [beginnings, endings]=endpoints(energy,zerocrossings,ITR,IZCT);


beginnings = [];
endings = []

c=1;
k=1;

wait_frames = 20;

% first stage based on energy

while (c < length(energy))    
    while (c < length(energy) && energy(c)<=ITR)
        c=c+1;
    end
    
    beginnings(k) = c;

    while 1
        while (c < length(energy) && energy(c)>=ITR)
            c=c+1;
        end
        save_ep = c-1;
        % search the next wait_frames to see if energy rises again
        flag = false;
        for c=c:c+wait_frames
            if c > length(energy)
                break
            end
            if energy(c)>=ITR
               flag=true;
            end
        end        
        if ~flag
            ee=save_ep;
            break
        end
    end
    
    endings(k) = ee;
    
    % stage 2
%     z=beginnings(k);
%     
%     for i=beginnings(k):-1:beginnings(k)-5
%         if zerocrossings(i)<IZCT
%             z = i;
%         end
%     end
%     beginnings(k)=z;
% 
%     z=endings(k);
%     
%     for i=endings(k):endings(k)+5
%         if i > length(zerocrossings)
%             break
%         end
%         if zerocrossings(i)<IZCT
%             z = i;
%         end
%     end
%     endings(k)=z;
    
    k = k + 1;
end



end