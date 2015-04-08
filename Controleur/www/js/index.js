/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
 /*

/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
/*
var copter = {
  macAddress : "20:13:08:28:12:22",
  init : function(){
    app.log("Copter init");
    var listPorts = function() {
          // list the available BT ports:
          bluetoothSerial.list(
              function(results) {
                  //app.log(JSON.stringify(results));
                  copter.connect();
              },
              function(error) {
                  app.log(JSON.stringify(error));
              }
          );

    }
    var notEnabled = function() {
          app.log("Bluetooth is not enabled.")
     }

    bluetoothSerial.isEnabled(
            listPorts,
            notEnabled
        );  
  },
  connect : function(){
    var onConnect = function () {
        // if not connected, do this:
        // clear the screen and display an attempt to connect
        //app.clear();
        app.log("Attempting to connect. ");
        // attempt to connect:
        bluetoothSerial.connect(
            copter.macAddress,  // device to connect to
            copter.openPort,    // start listening if you succeed
            copter.showError    // show the error if you fail
        );
    };

        // disconnect() will get called only if isConnected() (below)
        // returns success  In other words, if  connected, then disconnect:
    var onDisconnect = function () {
        app.log("Attempting to disconnect");
        // if connected, do this:
        bluetoothSerial.disconnect(
            copter.closePort,     // stop listening to the port
            copter.showError      // show the error if you fail
        );
    };

    // here's the real action of the manageConnection function:
    bluetoothSerial.isConnected(onDisconnect, onConnect);    
  },
  openPort: function() {
      app.log("Connected to: " + copter.macAddress);
      $("#connectionStatus").buttonMarkup({ icon: "check",theme:"b" });
      $("#connectionStatus").attr("disabled","disabled");
      $("#connectionStatus").text("connected");
      bluetoothSerial.subscribeRawData(copter.onRawData, copter.showError);
      //bluetoothSerial.write("1",copter.onWriteSuccess,copter.showError);
  },

  onWriteSuccess : function(){

  },

  closePort: function() {
      app.log("Disconnected from: " + copter.macAddress);
      $("#connectionStatus").buttonMarkup({ icon: "delete",theme:"a" });
      $("#connectionStatus").text("disconnected");
  },  
  showError: function(error) {
      app.log(error);
  },

  onRawData : function(data){
    var bytes = new Uint8Array(data);
    app.log("Just received: "+String.fromCharCode.apply(null, bytes));
  },

  engineOn : function(){
    copter.sendData("b");
    //bluetoothSerial.write("a",copter.onWriteSuccess,copter.showError);
  },
  engineOff: function(){
    copter.sendData("a");
    //bluetoothSerial.write("b",copter.onWriteSuccess,copter.showError);
  },
  sendPitchRoll : function (pitch,roll){
    /*var p = pitch < 0 ? ~Math.abs(pitch) + 1 : pitch;
    if (pitch < 0){
      app.log("Pitch "+pitch+" p "+Math.abs(pitch));
    }
    var r = roll < 0 ? ~Math.abs(roll) + 1 : roll;
    copter.sendData([49,pitch,roll]);
  },
  sendData : function(data){
    app.log("Sending ..."+data[0]);
    app.log("Sending ..."+data[1]);
    app.log("Sending ..."+data[2]);
    bluetoothSerial.write(data,copter.onWriteSuccess,copter.showError);
  }
};*/


var app = {
  s : 0.98,
  angles : [0.0,0.0,0.0],
  gyro : [0.0,0.0,0.0],
  pitch : 0.0,
  roll: 0.0,
  dt : 0.05,
  timestamp: new Date().time,
  timeConstant : 0.5,
  compFilterCoef : 0.0,// app.timeConstant / (app.timeConstant + app.dt),

  initialize: function() {
      this.bindEvents();
  },
  // Bind Event Listeners
  //
  // Bind any events that are required on startup. Common events are:
  // 'load', 'deviceready', 'offline', and 'online'.
  bindEvents: function() {
      document.addEventListener('deviceready', app.onDeviceReady, false);
      window.addEventListener("deviceorientation", app.onDeviceOrientationEvent, true);
  },
  gyroscopeSuccess : function(speed) {
    //app.log("success");
    app.gyro[0] = speed.x;
    app.gyro[1] = speed.y;
    app.gyro[2] = speed.z;
    app.timestamp = speed.timestamp - app.timestamp;
    app.timestamp = speed.timestamp;
    app.computeComplementary();
  },
  onError : function() {
    app.log("error");
  },
  computeComplementary : function(){
    app.pitch += app.gyro[1] * app.dt * (180.0 / Math.PI);
    app.roll += app.gyro[0] * app.dt* (180.0 / Math.PI);

    app.pitch = app.compFilterCoef * app.pitch + (1.0 - app.compFilterCoef) * app.angles[2];
    app.roll = app.compFilterCoef * app.roll + (1.0 - app.compFilterCoef) * app.angles[1];

    $("#accelerometer").html('Pitch:' + app.pitch.toFixed(2) + '<br/>' + 
          'Roll:' + app.roll.toFixed(2) + '<br/>');
  },

  onDeviceOrientationEvent : function (orientationEvent){

    app.angles[0] = orientationEvent.alpha;
    app.angles[1] = orientationEvent.beta;
    app.angles[2] = orientationEvent.gamma;


    var toDisplay2 = "<br/>Roll: "+app.angles[1].toFixed(0);
    toDisplay2 += "<br/>Pitch: "+app.angles[2].toFixed(0);   
    //$("#accelerometer").html(toDisplay2);
  }, 
  onConnectClick : function (event,ui){
    app.log("Connect clicked");
  },

  onDeviceReady: function() {
    app.compFilterCoef = app.timeConstant / (app.timeConstant + app.dt);

    app.log("Device ready "+app.pitch + " " +app.roll);

    $( "#flip-1" ).bind( "change", function(event, ui) {
        if($("#flip-1").val() == "on"){
          //copter.engineOn();
        } else {
          //copter.engineOff();
        }
    });

    var intervalID = setInterval(function(){
      if($("#flip-2").val() == "on"){
        //copter.sendPitchRoll(parseInt(app.angles[1].toFixed(0)),parseInt(app.angles[2].toFixed(0)));
      }
      //
    },100);


    $("#connect").bind("click", app.onConnectClick);
    //copter.init();

      setTimeout(function(){
          $("#accelerometer").show("fast"); 
      }, 1500);

      var watchID = navigator.gyroscope.watchAngularSpeed(app.gyroscopeSuccess,app.onError,{frequency:app.dt * 1000});




  },  

  receivedEvent: function(id) {
      console.log('Received Event: ' + id);
  },
  log : function (toLog){
    $("#logPanel").append("<br/>"+toLog);
  }
};

app.initialize();