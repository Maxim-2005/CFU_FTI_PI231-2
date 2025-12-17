'use strict';

module.exports = getEmitter;

function getEmitter() {
    var events = {};

    return {

        on: function (event, context, handler) {
            if (!events.hasOwnProperty(event)) {
                events[event] = [];
            }
            events[event].push({
                context: context,
                handler: handler
            });

            return this;
        },

        off: function (event, context) {
            var eventKeys = Object.keys(events);

            eventKeys.forEach(function (key) {
                if (key === event || key.indexOf(event + '.') === 0) {
                    events[key] = events[key].filter(function (subscriber) {
                        return subscriber.context !== context;
                    });
                }
            });

            return this;
        },

        emit: function (event) {
            var currentEvent = event;

            while (currentEvent) {
                if (events.hasOwnProperty(currentEvent)) {
                    events[currentEvent].forEach(function (subscriber) {
                        subscriber.handler.call(subscriber.context);
                    });
                }

                var lastDotIndex = currentEvent.lastIndexOf('.');
                if (lastDotIndex === -1) {
                    break;
                }
                currentEvent = currentEvent.substring(0, lastDotIndex);
            }

            return this;
        }
    };
}