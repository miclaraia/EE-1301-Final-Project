var getURL = "https://api.particle.io/v1/devices/2d0025000d47343432313031/get_alarm?access_token=3f58b6b8cb492253bc9f083dfbda6bef24d70b8b";
//var tempURL = "http://httpbin.org/get";
var setURL = "https://api.particle.io/v1/devices/2d0025000d47343432313031/set_alarm?access_token=3f58b6b8cb492253bc9f083dfbda6bef24d70b8b";
var actionURL = "https://api.particle.io/v1/devices/2d0025000d47343432313031/action?access_token=3f58b6b8cb492253bc9f083dfbda6bef24d70b8b";


var control = new function() {
    var self = this;

    self.init = function() {
        self.elements = new function() {
            var self = this;
            self.block = $("div#dataBox");
            self.value = $("div#dataBox span#value");
            self.update_button = $("div#dataBox a#updateButton"); 
            self.time_buttons = $("div#set_alarm a.time-set");
            self.action_buttons = $("div#actions a");

            self.custom_alarm = $("div#custom_alarm input");
            self.custom_alarm_button = $("div#custom_alarm_button");
        }

        self.initTimeSetButtons();
        self.initActionButtons();
        self.initUpdateButton();
        self.initCustomAlarm();

        self.getAlarm();
    };

    // button to get new state from server
    self.initUpdateButton = function() {
        var update = self.elements.update_button;
        console.log(update);
        update.click(function(event) {
            event.preventDefault();
            self.getAlarm();
        });
    };

    // buttons in list that set state of photon
    self.initTimeSetButtons = function() {
        var items = self.elements.time_buttons;

        console.log(items);
        items.click(function(event) {
            event.preventDefault();
            console.log(event);

            var minutes = $(event.target).attr("value");
            if (minutes == "time") {
                var text = $(event.target).text().split(":");
                minutes = self.getMinutesFromString(text);
            }
            self.setAlarm(minutes);

        });
    };



    self.initCustomAlarm = function() {
        var field = self.elements.custom_alarm;
        var button = self.elements.custom_alarm_button;

        button.click(function(event) {
            event.preventdefault();
            console.log(event);

            var text = field.text().split(":");
            var minutes = self.getMinutesFromString(text);

            console.log("minutes: ", minutes);
            self.setAlarm(minutes);
        });
    };

    self.initActionButtons = function() {
        var items = self.elements.action_buttons;

        console.log(items);
        items.click(function(event) {
            event.preventDefault();
            console.log(event);

            var command = $(event.target).attr("value");
            self.sendAction(command);

        });
    };

    self.setAlarm = function(minutes) {
        var command = "" + minutes;

        var post = $.post(setURL, {args: command},
            function() {
                console.log("Request sent", this);
            }
        );

        post.done(function(){console.log("request done", post)});
        post.fail(function(){console.log("request failed")});

        self.post = post;
    }

    self.sendAction = function(command) {
        var post = $.post(actionURL, {args: command},
            function() {
                console.log("Request sent", this);
            }
        );

        post.done(function(){console.log("request done", post)});
        post.fail(function(){console.log("request failed")});

        self.post = post;
    }

    self.getAlarm = function() {
        var post = $.post(getURL, {args: ""},
            function(data) {
                console.log("Request sent", this);
                console.log(data);

                self.updateDataBlock(data.return_value);
            }
        );

        post.done(function(){console.log("request done", post)});
        post.fail(function(){console.log("request failed")});

        self.post = post;
    };

    self.updateDataBlock = function(value) {
        console.log(value);
        var hour = Math.floor(value / 60);
        var minute = value % 60;

        if (minute < 10) minute = "0" + minute;
        self.elements.value.text(hour + ":" + minute);
    };

    self.getMinutesFromString = function(time_str) {
        var text = time_str.split(":");
        var hour = parseInt(text[0]);
        var min = parseInt(text[1]);
        var time = hour * 60 + min;

        minutes = "" + time;

        return minutes;
    };

};




$(document).ready(function() {
    control.init();
});