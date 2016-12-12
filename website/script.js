var getURL = "https://api.particle.io/v1/devices/2d0025000d47343432313031/get_alarm?access_token=3f58b6b8cb492253bc9f083dfbda6bef24d70b8b";
//var tempURL = "http://httpbin.org/get";
var setURL = "https://api.particle.io/v1/devices/2d0025000d47343432313031/set_alarm?access_token=3f58b6b8cb492253bc9f083dfbda6bef24d70b8b";


var control = new function() {
    var self = this;

    self.init = function() {
        self.elements = new function() {
            var self = this;
            self.block = $("div#dataBox");
            self.value = $("div#dataBox span#value");
            self.updateButton = $("div#dataBox a#updateButton");
        }

        self.controlButtons();
        self.updateButton();
    };

    // button to get new state from server
    self.updateButton = function() {
        var update = self.elements.updateButton;
        console.log(update);
        update.click(function(event) {
            event.preventDefault();
            self.updateValue();
        });
    };

    // buttons in list that set state of photon
    self.controlButtons = function() {
        var items = $("div#input a");

        console.log(items);
        items.click(function(event) {
            event.preventDefault();
            console.log(event);

            var command = $(event.target).attr("value");
            if (command == "time") {
                var text = $(event.target).text().split(":");
                var time = text[0] * 60 + text[1];

                command = "" + time;
                console.log(text, time);
            }
            console.log(command);

            var post = $.post(setURL, {args: command},
                function() {
                    console.log("Request sent", this);
                }
            );

            post.done(function(){console.log("request done", post)});
            post.fail(function(){console.log("request failed")});

            self.post = post;

        });
    };

    self.updateValue = function() {
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
        // var request = $.get(tempURL, function(data) {
        //     console.log(data);

        //     var value = data.result;
        //     console.log("Alarm: " + value);

        //     self.updateDataBlock(value);

        // });
        // console.log(request);
    };

    self.updateDataBlock = function(value) {
        console.log(value);
        var hour = Math.floor(value / 60);
        var minute = value % 60;
        self.elements.value.text(hour + ":" + minute);
    }

};




$(document).ready(function() {
    control.init();
});