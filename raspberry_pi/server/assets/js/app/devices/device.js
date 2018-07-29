const app = angular.module('dreambedded')

import template from './device.hamlc'

app.directive('device', [
  'Socket',
  (Socket) => {
    return {
      link: (scope, element, attr) => {
        setInterval(() => {
          let payload = ["device", scope.device.pin.toString(), "device_status"]
          Socket.getSocket().emit("action", payload.join("::"))
        }, 1500)

        Socket.getSocket().on('device_status', (message) => {
          let args = message.split("::")

          if (scope.deviceMode && args[1] == "off") {
            console.log(element)
            console.log(angular.element(element).find(".mdl-switch"))
            angular.element(element).find(".mdl-switch").trigger("click")
          }

          scope.deviceMode = args[1] == "on"
        })
      },
      template: template(),
      scope: {
        device: "="
      },
      controller: [
        'Socket',
        (Socket) => {
          let controller = {}

          controller.onModeChange = (device, modeOn) => {
            let msg = modeOn ? "device_on" : "device_off"
            let payload = ["device", "::", device.pin, "::", msg].join("")
            Socket.getSocket().emit("action", payload)
          }

          return controller
        }
      ],
      controllerAs: "devCtrl"
    }
  }
])
