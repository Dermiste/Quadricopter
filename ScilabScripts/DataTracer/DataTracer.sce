
exec("./Utils.sci",-1);   //

// Mode d'affichage
mode(0);
funcprot(0);
// Affiche un avertissement pour une exception en virgule flottante
ieee(1);

initSerial('/dev/tty.usbmodemfa141');
//initSerial('/dev/tty.Bluetooth-Incoming-Port');
xpause(500000);  //pause 500ms pour attendre reponses 
xpause(1000000);
//disp(readLine());
//flushSerial();
closeSerial();
return;

//selAz();
//goToDebut();

//i = 1;
dataTab = zeros(10,8);
data;
totalData = 10;
iData = 0;

//err = zeros(3,1);
//fixVit(-40);
//start();

//sth=lecSth();       //lecture capteurs course
sendCmd1Byte('t');
while(dataReceived < 10)//test bit 1 : fincourse
    while(getChSerial() == 0xFF);
        
    dataTab(iData,getChSerial());
    dataTab(iData,getChSerial());
    dataTab(iData,getChSerial());
    
    dataTab(iData,getChSerial());
    dataTab(iData,getChSerial());
    dataTab(iData,getChSerial());
    
    dataTab(iData,getChSerial());
    dataTab(iData,getChSerial());
    dataTab(iData,getChSerial());    
    
    getChSerial();
    dataReceived ++;
end;
stop();


[maxP,indexDuMaxP] = max(M(:,2));
posDuMaxP=M(indexDuMaxP,1);
  i = 1;
  taille=size(M);
  while i<=taille(1,1)
          M(i,3) = ((M(i,1)-posDuMaxP)*300)/360;//Chgt d'echelle x pour avoir des deg par rapport à la perpendiculaire
    i = i+1;
  end;
close();                //fermer figure précédente
plot(M(:,3),M(:,2),'-r');    //Tracer puissance(angle)
plot(M(:,3),maxP*cos((M(:,3))*%pi/180),'-b');//tracer cos(angle)
title("Puissance en fonction de la position");
xlabel("Angle d''incidence (degrés)","fontsize",4);
ylabel("Puissance (W)","fontsize",4, "color", "red");

closeserial(s);
