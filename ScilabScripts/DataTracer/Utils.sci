//function closeAll()
//    slm.close();
//    disp("Serial closed");
//endfunction

function testConnectivity()
    disp("Test connectivity");
    slm.writeln("a");
    sleep(100);
    disp(slm.read(1,1));
endfunction

function recordDataCF()
    disp("Record data");
    
    totalData = double(1);
    //totalMsb = double(totalData/256);
    //totalLsb = double(totalData);
    
    
    dataWidth = 9;
    
    accData = uint8(zeros(totalData,dataWidth));
    accData;
    //s = uint8([ascii("d"),totalMsb,totalLsb]);
    //disp(s);
    
    //slm.writeln(s);
    sleep(100);
    i = 1;
    while i <= totalData
        slm.write('b');
        sleep(20);
        n = dataWidth;
        //while n ~= 0
            t = slm.read(n,1);
            accData(i,1:9) = t;
        //end
        //disp("size",size(t));
        
        //dataTab(i,9) = dataTab(i,1)*256 + dataTab(i,2);
        i = i+1;
        sleep(10);
        
    end;
    clf();
    plot(accData(:,1),'k-');
    plot(accData(:,2),'r-');
    plot(accData(:,3),'g-');
    xlabel("Numéro d échantillon","fontsize",4);
endfunction

function recordDataArdu()
    disp("Record data");
    
    totalData = double(400);
    totalMsb = double(totalData/256);
    totalLsb = double(totalData);
    
    
    dataWidth = 8;
    
    dataTab = uint16(zeros(totalData,dataWidth+1));
    
    s = uint8([ascii("d"),totalMsb,totalLsb]);
    disp(s);
    
    slm.writeln(s);
    sleep(100);
    i = 1;
    while i <= totalData
        t = slm.read(dataWidth,1);
        disp(t);
        dataTab(i,1:8) = t;
        dataTab(i,9) = dataTab(i,1)*256 + dataTab(i,2);
        i = i+1;
        sleep(10);
        
    end;
    clf();
    plot(dataTab(:,5),'k-');
    plot(dataTab(:,6),'r-');
    plot(dataTab(:,7),'g-');
    xlabel("Numéro d échantillon","fontsize",4);
endfunction
