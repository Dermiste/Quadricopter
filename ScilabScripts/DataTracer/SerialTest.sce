funcprot(0);
exec("Utils.sci");

global slm;

dataWidth = 7;
quadSampleRate = 100;

function flushSerial()
    i = 0;
    disp("Flush serial ...");
    dump = int8(slm.read(dataWidth,1));
    while(length(dump) > 0 )
        i = i + 1;
        mprintf( 'Flushing ... %i \n',i);
        dump = int8(slm.read(dataWidth,1));
        sleep(10);
    end;
endfunction

function plotData()
    disp('plot current data');
    clf();
    f1=scf(1);  //creates figure with id==1 and make it the current one
    f1.color_map = jetcolormap(64);
    f1.figure_size = [400, 400];
    f1.figure_position = [0,0];
    plot(accData(:,2),'r-');
    plot(accData(:,4),'g-');  
    plot(accData(:,6),'k-'); 
    
    //plot(accData(:,5),'k-'); 
    xlabel("Numéro d échantillon","fontsize",2);
    xtitle("Accélération et vitesse angulaire");
    //legends(['xAcc';'yAcc';'zAcc';'echelon 1'],[-1,2 3],opt="lr");
    
    //hz = iir(8,'lp','butt',50/quadSampleRate,[]);
    //plot(flts(accData(:,12),hz),'b--');
    //plot(flts(accData(:,13),hz),'k--');
     
    f2=scf(2);  //creates figure with id==2 and make it the current one
    f2.color_map = jetcolormap(64);
    f2.figure_size = [400, 400];
    f2.figure_position = [420,0];
    plot(accData(:,3),'r-');
    plot(accData(:,5),'g-');  
    plot(accData(:,7),'k-');  

    xlabel("Numéro d échantillon","fontsize",2);  
    xtitle("Inclinaison");
    //legends(['x axis speed';'y axis speed';'z axis speed';'echelon 2'],[-1,2 3],opt="lr");
    return
    f3=scf(3);  //creates figure with id==2 and make it the current one
    f3.color_map = jetcolormap(64);
    f3.figure_size = [400, 400];
    f3.figure_position = [840,0];
    plot(accData(:,8),'r-');
    plot(accData(:,9),'g-');
    plot(accData(:,10),'b-');    
    plot(accData(:,11),'m-'); 
    xlabel("Numéro d échantillon","fontsize",2);
    xtitle("Accélération angulaire");     
    //legends(['x axis acc';'y axis acc';'z axis acc';'echelon 3'],[-1,2 3],opt="lr");       
endfunction

function testFFT()
    sample_rate=1000;
    t = 0:1/sample_rate:0.6;
    N=size(t,'*'); //number of samples
    s=sin(2*%pi*50*t)+sin(2*%pi*70*t+%pi/4)+grand(1,N,'nor',0,1);
    
    y=fft(s);
    
    //s is real so the fft response is conjugate symmetric and we retain only the first N/2 points
    f=sample_rate*(0:(N/2))/N; //associated frequency vector
    n=size(f,'*');
    clf();
    plot(f,abs(y(1:n)));
endfunction


function rawFFT()
    t = 0:1/quadSampleRate:0.6;
    N=size(t,'*'); //number of samples
    //s=sin(2*%pi*50*t)+sin(2*%pi*70*t+%pi/4)+grand(1,N,'nor',0,1);
    
    fftVx=fft(double(accData(:,2)));
    
    //s is real so the fft response is conjugate symmetric and we retain only the first N/2 points
    f=quadSampleRate*(0:(N/2))/N; //associated frequency vector
    n=size(f,'*');
    clf();
    plot(f,abs(fftVx(1:n)));
endfunction

function filterFFT()
    t = 0:1/quadSampleRate:0.6;
    N=size(t,'*'); //number of samples
    //s=sin(2*%pi*50*t)+sin(2*%pi*70*t+%pi/4)+grand(1,N,'nor',0,1);
    
    FIR=fft(double(accData(:,12)));
    
    //s is real so the fft response is conjugate symmetric and we retain only the first N/2 points
    f=quadSampleRate*(0:(N/2))/N; //associated frequency vector
    n=size(f,'*');
    clf();
    plot(f,abs(FIR(1:n)));
endfunction

function compareFFT()
    t = 0:1/quadSampleRate:1;
    N=size(t,'*'); //number of samples
    
    fftVx=fft(double(accData(:,2)));

    f=quadSampleRate*(0:(N/2))/N; //associated frequency vector
    n=size(f,'*');
    clf();
    plot(f,abs(fftVx(1:n)),'r-');
    
    FIR=fft(double(accData(:,6)));
    
    plot(f,abs(FIR(1:n)),'b-');    
endfunction




arduinoPort = 'tty.usbmodemfa141';
copterPort = 'tty.4xcopter-DevB';
homeColdfire = 'tty.usbserial-GE2-RS232_2';

slm = serialport( '/dev/'+copterPort, '115200,N,8,1' );  // Larson-davis
slm.flow_control = 0;
slm.timeout = [1500, 1500, 1500, 1500, 1500];
disp(slm);
handle = slm.fd;

//flushSerial();

sleep(500);

disp("Serial started");

stay = 1;


while 1
    y=input("Enter a command :","s");
    command = part(y,1:1);
    select command,
    case 't' then,
        disp("t entered");
        testConnectivity();        
    case 'r' then,
            disp("r entered: record data");
            slm.write('a');
            
            accData = int8(zeros(1,dataWidth)); // initial size
            
            sleep(100);
            i = 1;
            disp("starting loop");
            
            while 1
                sleep(1);
                t = int8(slm.read(dataWidth,%t));
                accData = resize_matrix(accData,i,dataWidth);
                accData(i,1:dataWidth) = t;
                
                if t(1:1) ~= 0 then
                    mprintf( 'Last sample detected  %i\n',i);
                    break;
                end;            
                i = i+1;
            end;

            plotData();
    case 'g' then,
            disp("g entered: record data");

            accData = int8(zeros(totalSample,dataWidth));
            
            sleep(100);
            i = 1;
            disp("starting loop");
            
            while i <= totalSample
                sleep(10);
                slm.write('o');
                t = int8(slm.read(dataWidth,%t));
                accData(i,1:dataWidth) = t;
                
                i = i+1;
            end;
            plotData();     
    case 'q' then,
        //flushSerial();
        serialclose( handle );
        return;                
    else,

        
    end;
end;


