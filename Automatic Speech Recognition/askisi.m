%% askisi.m
%% Anagnorisi psifiwn
clear


%% Parameters Definition
Fs=8000;                    %% Sampling Frequency after downsample
nfft=1024;                  %% fft length used in spectral calculations
hpforder=30;                %% order of highpass filter  
lowcut=100;                 %% low band reject frequency   (Hz)
highcut=200;                %% high band cut-off frequency (Hz)
                            % transition between lowcut-highcut
% step 4
NS=30;                      %% Frame Duration in ms
L=NS*Fs/1000;               %% Frame Duration in samples
MS=10;                      %% Frame Shift in ms
R=MS*Fs/1000;               %% Frame Shift in samples
overlap=20*Fs/1000;
features = "mfcc"; % wave or mfcc
verbose=false;
%% Step 1
%% load speech file and normalize signal
[speech,FsOrig]=audioread('data/test_1.wav');

speechMin=min(speech);
speechMax=max(speech);
speech=speech/max(speechMax,-speechMin);

%% Step 2
%% resample input signal
x=resample(speech,Fs,FsOrig);

if verbose
    subplot(221)
    stem(speech)
    xlabel('Sample')
    ylabel('Amplitude')
    title(['Original Speech Signal with Fs=' num2str(FsOrig) 'Hz'])
    grid on

    subplot(223)
    stem(x)
    xlabel('Sample')
    ylabel('Amplitude')
    title(['Reasmpled Speech Signal with new Fs=' num2str(Fs) 'Hz'])
    grid on

    subplot(222)
    [Sspeech,f]=freqz(speech,1,1024,FsOrig);
    plot(f,20*log10(abs(Sspeech)))
    xlabel('Frequency (Hz)')
    ylabel('Magnitude (dB)')
    title(['Original Speech Signal Spectrum with Fs=' num2str(FsOrig) 'Hz'])
    grid on

    subplot(224)
    [Sx,f]=freqz(x,1,1024,Fs);
    plot(f,20*log10(abs(Sx)))
    xlabel('Frequency (Hz)')
    ylabel('Magnitude (dB)')
    title(['Resampled Speech Signal Spectrum with new Fs=' num2str(Fs) 'Hz'])
    grid on
    figure, plot(20*log10(abs(fft(speech,1024))))
end

%% Step 3
%% highpass filtering 
%% Band reject 0-100Hz
%% Band transition 100-200Hz
%% Bandpass 100-4000Hz
hpfilter=firpm(hpforder,[0 lowcut highcut Fs/2]/(Fs/2),[0 0 1 1]);
y=filter(hpfilter,1,x);

if verbose
    subplot(311)
    [Sx,f]=freqz(x,1,1024,Fs);
    plot(f,20*log10(abs(Sx)))
    xlabel('Frequency (Hz)')
    ylabel('Magnitude (dB)')
    title(['Resampled Speech Signal and High Pass filter response'])
    grid on
    hold on
    [HP,f]=freqz(hpfilter,1,1024,Fs);
    plot(f,20*log10(abs(HP)),'r')

    subplot(312)
    [Sy,f]=freqz(y,1,1024,Fs);
    plot(f,20*log10(abs(Sy)))
    xlabel('Frequency (Hz)')
    ylabel('Magnitude (dB)')
    title(['High Pass Filtered Resampled Speech Signal Spectrum'])
    grid on

    subplot(313)
    stem(y)
    xlabel('Sample')
    ylabel('Amplitude')
    title(['High Pass Filtered Resampled Speech Signal'])
    grid on
    pause
end


%% Step 5
%% Calculate logarithmic energy and zero crossing rate for every frame

frames = buffer(y,L,overlap,'nodelay'); % buffer signal

h = repmat(hamming(L),[1,size(frames,2)]); 

frames = frames.*h; % hamming windowing

totalSamples=length(y);

energy = 10*log10(sum(frames.^2));
zerocrossings = sum(abs(diff(sign(frames),1,1)));
zerocrossings = zerocrossings *R/(2*L);
totalFrames=length(energy);

if verbose
    clf
    subplot(311)
    stem(y)
    maxAmpl=max(abs(y));
    axis([1 totalFrames*R -abs(maxAmpl) abs(maxAmpl)])
    xlabel('Sample')
    ylabel('Amplitude')
    title(['High Pass Filtered Resampled Speech Signal'])
    grid on
    hold on

    subplot(312)
    stem(energy)
    hold on
    axis([1 totalFrames min(energy) max(energy)])
    xlabel('Frame')
    ylabel('Energy')
    title(['Logarimthmic Energy of Each Frame of speech signal'])
    grid on

    subplot(313)
    stem(zerocrossings)
    hold on
    axis([1 totalFrames 0 50])
    xlabel('Frame')
    ylabel('Zerocrossings')
    title(['Zerocrossings of Each Frame of speech signal'])
    grid on
    pause
end


%% Step 6
%% Calculate average and standard deviation 
%% of energy and zerocrossing for background signal
%% e.g first 10 frame of signal
trainingFrames=10;              %% first 10 frames 
eavg=mean(energy(1:trainingFrames))
esig=std(energy(1:trainingFrames))
zcavg=mean(zerocrossings(1:trainingFrames))
zcsig=std(zerocrossings(1:trainingFrames))

%% Step 7
%% Calculate Detection Parameters
IF=20                       %% Constant Zero Crossing Threshold         
IZCT=max(IF,zcavg+3*zcsig)  %% Variable Zero Crossing Threshold
                            %% Depends on Training
IMX=max(energy)             %% Max Log Energy
ITU=IMX-20                  %% High Log Energy Threshold
ITL=max(eavg+3*esig, ITU-10)%% Low Log Energy Threshold

if verbose
    subplot(312)
%     plot(1:totalFrames,ITU*ones(totalFrames),'g')
    plot(1:totalFrames,ITL*ones(totalFrames),'g')
    title(['Logarimthmic Energy of Each Frame of speech signal and Thresholds'])
    hold on
%     plot(energy)

    subplot(313)
    plot(1:totalFrames,IZCT*ones(totalFrames),'g')
    plot(1:totalFrames,IF*ones(totalFrames),'g')
    title(['Zerocrossings of Each Frame of speech signal and Threshold'])
    hold on
end

%% Step 8
%% Calculate Speech Segments

[beginnings,endings]=endpoints(energy,zerocrossings,ITL,IF)

if verbose
    % plot vertical red lines showing endpoints
    subplot(312)
    % y1=get(gca,'ylim');
    y1 = [-50 50];

    for i=1:length(beginnings)-1
        plot([beginnings(i) beginnings(i)],y1,'r')
        plot([endings(i) endings(i)],y1,'r')
    end
    
    subplot(311)
    % y1=get(gca,'ylim');
    y1 = [-50 50];

    for i=1:length(beginnings)-1
        plot([beginnings(i)*R beginnings(i)*R],y1,'r')
        plot([endings(i)*R endings(i)*R],y1,'r')
    end
    
end
% 
% load template data
k=1;
for i=0:9
    for j=1:3
        file = sprintf('data/%d_%d.wav',i,j);
        [speech,FsOrig]=audioread(file);

        speechMin=min(speech);
        speechMax=max(speech);
        speech=speech/max(speechMax,-speechMin);

        tmp=resample(speech,Fs,FsOrig);

        if features == "mfcc"
            tmp = buffer(tmp,L,overlap,'nodelay'); % buffer signal

            h = repmat(hamming(L),[1,size(tmp,2)]); 

            tmp = tmp.*h; % hamming windowing

            tmp = mfcc(tmp,Fs,size(tmp,1));
            tmp = tmp(:);

            tmp(isinf(tmp)|isnan(tmp)) = 0;

            templates{k} = tmp;
            
        elseif features == "wave"

            templates{k} = tmp;
        end
        labels(k) = i;
        k = k +1;
    end
end



for i=1:length(beginnings)-1
    if endings(i) > size(frames,2)
        break
    end
    
    if features == "mfcc"
        tmp = frames(:,beginnings(i):endings(i));

        a = mfcc(tmp,Fs,size(tmp,1));

        a = a(:);
    elseif features == "wave"
        a = y(beginnings(i)*R:endings(i)*R);
    end
    for j=1:length(templates)
        
        scores(i,j) = dtw(a,templates{j});
    end
end

[min_scores,min_scores_idx] = min(scores,[],2);

recognized_sequence = labels(min_scores_idx);

display('I recognized:');
display(recognized_sequence);


