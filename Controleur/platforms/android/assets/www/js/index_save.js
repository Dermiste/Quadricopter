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



var app = {
  s : 0.98,
  angles : [0.0,0.0,0.0],
  initialize: function() {
      this.bindEvents();
  },
  // Bind Event Listeners
  //
  // Bind any events that are required on startup. Common events are:
  // 'load', 'deviceready', 'offline', and 'online'.
  bindEvents: function() {
      //console.log(this);
      document.addEventListener('deviceready', this.onDeviceReady, false);
      window.addEventListener("deviceorientation", this.onDeviceOrientationEvent, true);       

  },
  // deviceready Event Handler
  //
  // The scope of 'this' is the event. In order to call the 'receivedEvent'
  // function, we must explicitly call 'app.receivedEvent(...);'

  onDeviceOrientationEvent : function (orientationEvent){
    app.angles[0] = orientationEvent.alpha + app.s*(app.angles[0] - orientationEvent.alpha);
    app.angles[1] = orientationEvent.beta + app.s*(app.angles[1] - orientationEvent.beta);
    app.angles[2] = orientationEvent.gamma + app.s*(app.angles[2] - orientationEvent.gamma);

    var toDisplay2 = "<br/>Roll: "+app.angles[1].toFixed(0);
    toDisplay2 += "<br/>Pitch: "+app.angles[2].toFixed(0);   
    $("#accelerometer").html(toDisplay2);
  },

  onDeviceReady: function() {
    bmm.init();
    app.receivedEvent('deviceready');

    setTimeout(function(){
        $("#accelerometer").show(); 
    }, 1500);
  },  

  receivedEvent: function(id) {
    return;
      var parentElement = document.getElementById(id);
      var listeningElement = parentElement.querySelector('.listening');
      var receivedElement = parentElement.querySelector('.received');

      listeningElement.setAttribute('style', 'display:none;');
      receivedElement.setAttribute('style', 'display:block;');

      console.log('Received Event: ' + id);
  },
  log : function (toLog){
    $("#bluetoothDebug").append("<br/>"+toLog);
  }
};

// Bluetooth manager
var bmm = {
  macAddress : "20:13:08:28:12:22",
  r : {},

  init : function(){
    bluetoothSerial.list(
    function(results) {
        r = results;
        app.log(results[0].ADDRESS +" to find");
        app.log(results[0]["ADDRESS"] +" to find");
        app.log(r[0]["ADDRESS"] +" to find");
        app.log(JSON.stringify(results));
        var i = 0
        for (i=0;i<1;i++){
          app.log(results[i].ADDRESS +" to find");
        }

        $.each(results, function( index, bluetoothObj ) {
          app.log("Stuff ." + bluetoothObj["ADDRESS"] + " "+bmm.macAddress);
          if (bluetoothObj["ADDRESS"] == bmm.macAddress){
            app.log("Copter found ! ");
            bmm.connectToCopter();
            //return;                    
          }
        });
    }, bmm.onError
    );
  },

  connectToCopter : function(){
    bluetoothSerial.connect(
            bmm.macAddress,  // device to connect to
            bmm.openPort,    // start listening if you succeed
            bmm.onError    // show the error if you fail
        );
  },

  openPort : function(){
    app.log("Connected to :"+app.macAddress);
    bluetoothSerial.subscribeRawData(app.onRawData, app.onError);
    bluetoothSerial.write("1", function(){
      app.log("Caracter sent ...");
    }, function(){
      app.log("Error while sending ...");
    });
  },

  onError : function(error){
    app.log(error);
  },

  onRawData : function(data){
    var bytes = new Uint8Array(data);
    app.log("Just received: "+String.fromCharCode.apply(null, bytes));
  },
};

app.initialize();