funcprot(0);
exec("Utils.sci");

arduinoPort = 'tty.usbmodemfa141';
copterPort = 'tty.4xcopter-DevB';

global slm;
slm = serialport( '/dev/'+copterPort, '115200,N,8,1' );  // Larson-davis
slm.line_separator = [13, 10];

totalToFlush = 2;
while totalToFlush
    d = slm.read(1024,1);
    totalToFlush = totalToFlush - 1;
end;
sleep(500);

disp("Serial started");

while 1
    y=input("Enter a command :","s");
    command = part(y,1:1);
    select command,
    case 't' then,
        disp("t entered");
        testConnectivity();        
    case 'r' then,
             disp("r entered: record data");
            
            totalData = double(300);
            
            
            dataWidth = 9;
            
            accData = int8(zeros(totalData,dataWidth));
            accData;
            
            sleep(100);
            i = 1;
            disp("starting loop");
            while i <= totalData
                slm.write('b');
                sleep(10);
                t = int8(slm.read(dataWidth,1));
                n = dataWidth - length(t);
                
                disp(t);
                disp("completing ...");
                while n > 0
                    t = cat(2,t,int8(slm.read(n,1)));
                    disp("One iteration");
                    disp(t);
                    n = dataWidth - length(t);
                end
                disp(t,"One line finished!");
                accData(i,1:9) = t;
                i = i+1;
                sleep(10);
                
            end;
            clf();
            plot(accData(:,1),'k-');
            plot(accData(:,2),'r-');
            plot(accData(:,3),'g-');
            xlabel("Numéro d échantillon","fontsize",4);
    case 'a' then,
        
    case 'q' then,
        disp("q entered, serial connection closed");
        slm.close();
        return;
    else,
        disp("Not know command (r,t or q)");
    end;
end;
